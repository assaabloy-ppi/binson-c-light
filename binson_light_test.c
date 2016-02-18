
#include <stdint.h>
#include "binson_light.h"

//const uint8_t string_1[] PROGMEM = "Stadfgsssssss";


int main(void)
{
  /*int r;
  int64_t val = 777;
  uint8_t buf[10];*/
   uint8_t  ttt = 2;
   binson_writer w;
   //unsigned int displayInt = pgm_read_byte_near(&string_1);

   //r = dbg();

   ttt = 3;
   //ttt = _binson_util_next_pow2( ttt );
   //ttt = _binson_io_write_byte( &(w.io), ttt*ttt);
   ttt = _binson_writer_write_token( &(w), BINSON_ID_INTEGER, 0, 0);
   ttt = _binson_writer_write_token( &(w), BINSON_ID_DOUBLE, 0, 0);   
   
   return  ttt;//
}
