#include <stdio.h>
#include <assert.h>

#include "binson_light.h"

void parse_data(uint8_t *buffer, uint32_t size)
{

   bbuf *string;
   binson_parser p;

   binson_parser_init(&p, buffer, size);

   binson_parser_go_into(&p);
   binson_parser_field(&p, "i");
   assert(p.error_flags == BINSON_ID_OK);
   assert(binson_parser_get_type(&p) == BINSON_ID_INTEGER);
   assert(binson_parser_get_integer(&p) == 123);

   binson_parser_field(&p, "x");
   if (p.error_flags == BINSON_ID_OK)
   {
      assert(binson_parser_get_type(&p) == BINSON_ID_STRING);
      string = binson_parser_get_string_bbuf(&p);
      printf("x-field contains: %*.*s\r\n", 0, string->bsize, string->bptr);
   }
   else
   {
      printf("No x-field found\r\n");
   }

   binson_parser_field(&p, "z");
   assert(p.error_flags == BINSON_ID_OK);
   assert(binson_parser_get_type(&p) == BINSON_ID_STRING);
   string = binson_parser_get_string_bbuf(&p);
   printf("z-field contains: %*.*s\r\n", 0, string->bsize, string->bptr);
}

int main(void) {

   binson_writer w;
   uint8_t buffer[256];

   /*
    * Binson object 1, OK, containing x-field
    * {
    *    "i" : 123,
    *    "x" : "x data",   // Optional
    *    "z" : "z data"
    * }
    *
    */
   binson_writer_init(&w, buffer, sizeof(buffer));
   binson_write_object_begin(&w);

   binson_write_name(&w, "i");
   binson_write_integer(&w, 123);

   /* Optional string x */
   binson_write_name(&w, "x");
   binson_write_string(&w, "x data");

   /* Required string z */
   binson_write_name(&w, "z");
   binson_write_string(&w, "z data");
   binson_write_object_end(&w);

   printf("Parsing Binson buffer containing the optional x field\r\n");
   parse_data(buffer, sizeof(buffer));

   /*
    * Binson object 2, OK, no x-field
    * {
    *    "i" : 123,
    *    "z" : "z data"
    * }
    *
    */
   binson_writer_init(&w, buffer, sizeof(buffer));
   binson_write_object_begin(&w);

   binson_write_name(&w, "i");
   binson_write_integer(&w, 123);

   /* No x-field */

   /* Required string z */
   binson_write_name(&w, "z");
   binson_write_string(&w, "z data");
   binson_write_object_end(&w);

   printf("Parsing Binson buffer not containing the optional x field\r\n");
   parse_data(buffer, sizeof(buffer));

   return 0;
}