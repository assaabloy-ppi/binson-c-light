#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "": 12336, 
  "0000000000000000": "00000000000000000000", 
  "00000000000": "00000000000000000000", 
  "0000000000000": "000000000000000(0000", 
  "0000000000000000000": "00000000000000000000", 
  "00000000000000000000": "00000000000000000000"
}
*/
int main(void)
{
    uint8_t binson_bytes[227] = "\x40\x14\x00\x11\x30\x30\x14\x14\x14\x14\x14\x13\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x14\x14\x14\x14\x14\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x28\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x41";
    BINSON_PARSER_DEF(p);
    double dval; (void) dval;
    int64_t intval; (void) intval;
    bool boolval; (void) boolval;
    bbuf *rawval; (void) rawval;
    assert(binson_parser_init(&p, binson_bytes, sizeof(binson_bytes)));
    assert(binson_parser_verify(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "", 0, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 12336);
    assert(binson_parser_field_ensure_with_length(&p, "\x14\x14\x14\x13\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", 20, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x14\x14\x14\x14\x14\x14\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14", 20, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x14\x14\x14\x14\x14\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", 20, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x28\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", 20, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", 20, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

