#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "0": "0", 
  "G": 48
}
*/
int main(void)
{
    uint8_t binson_bytes[13] = "\x40\x14\x01\x30\x14\x01\x30\x14\x01\x47\x10\x30\x41";
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
    assert(binson_parser_field_ensure_with_length(&p, "\x30", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 48);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

