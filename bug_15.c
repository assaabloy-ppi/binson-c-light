#include <stdio.h>
#include <assert.h>

#include "binson_light.h"


int main(void)
{

    printf("=== Binson test program started ===\r\n");


    uint8_t buffer[256];
    binson_writer writer;
    binson_writer_init(&writer, buffer, sizeof(buffer));

    /* Create a binson object like this:

     * {
     *  "c": "l",       - String
     *  "i": 1,         - Integer
     *  "t": 0x0202,    - Byte array
     *  "z": { }        - Empty object
     * }
     * 
     */

    binson_write_object_begin(&writer);
    binson_write_name(&writer, "c");
    binson_write_string_with_len(&writer, "l", 1);

    binson_write_name(&writer, "i");
    binson_write_integer(&writer, 1);

    binson_write_name(&writer, "t");
    binson_write_bytes(&writer, (uint8_t *)"\x02\x02", 2);

    binson_write_name(&writer, "z");
    binson_write_object_begin(&writer);
    binson_write_object_end(&writer);

    binson_write_object_end(&writer);

    binson_parser parser;

    /* Should work */
    binson_parser_init(&parser, buffer, binson_writer_get_counter(&writer));
    assert(binson_parser_go_into(&parser) == true);
    assert(IS_CLEAN(&parser));
    assert(binson_parser_field_ensure(&parser, "c", BINSON_ID_STRING) == true);
    assert(binson_parser_get_type(&parser) == BINSON_ID_STRING);
    assert(IS_CLEAN(&parser));
    assert(binson_parser_field_ensure(&parser, "i", BINSON_ID_INTEGER) == true);
    assert(binson_parser_get_type(&parser) == BINSON_ID_INTEGER);
    assert(IS_CLEAN(&parser));
    assert(binson_parser_field_ensure(&parser, "t", BINSON_ID_BYTES) == true);
    assert(binson_parser_get_type(&parser) == BINSON_ID_BYTES);
    assert(IS_CLEAN(&parser));
    assert(binson_parser_field_ensure(&parser, "z", BINSON_ID_OBJECT) == true);
    assert(binson_parser_get_type(&parser) == BINSON_ID_OBJECT);
    assert(IS_CLEAN(&parser));

    /* Should NOT work */
    binson_parser_init(&parser, buffer, binson_writer_get_counter(&writer));
    binson_parser_go_into(&parser);
    assert(binson_parser_field_ensure(&parser, "c", BINSON_ID_INTEGER) == false);
    assert(parser.error_flags == BINSON_ID_PARSE_WRONG_TYPE);
    assert(binson_parser_field_ensure(&parser, "i", BINSON_ID_STRING) == false);
    assert(parser.error_flags == BINSON_ID_PARSE_WRONG_TYPE);    
    assert(binson_parser_field_ensure(&parser, "t", BINSON_ID_DOUBLE) == false);
    assert(parser.error_flags == BINSON_ID_PARSE_WRONG_TYPE);    
    assert(binson_parser_field_ensure(&parser, "z", BINSON_ID_BOOLEAN) == false);
    assert(parser.error_flags == BINSON_ID_PARSE_WRONG_TYPE);

    parser.error_flags = BINSON_ID_OK;
    assert(binson_parser_field_ensure(&parser, "z", BINSON_ID_OBJECT) == true);
    assert(binson_parser_get_type(&parser) == BINSON_ID_OBJECT);
    assert(IS_CLEAN(&parser));

    return 0;
}

