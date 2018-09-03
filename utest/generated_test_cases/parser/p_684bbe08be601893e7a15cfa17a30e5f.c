#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "A": "B", 
  "B": 1, 
  "C": 3.0, 
  "D": false, 
  "E": "0x0102", 
  "F": {
  }, 
  "G": [
    "0x"
  ]
}
*/
int main(void)
{
    uint8_t binson_bytes[48] = "\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x01\x43\x46\x00\x00\x00\x00\x00\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x02\x14\x01\x46\x40\x41\x14\x01\x47\x42\x18\x00\x43\x41";
    binson_parser p;
    double dval; (void) dval;
    int64_t intval; (void) intval;
    bool boolval; (void) boolval;
    bbuf *rawval; (void) rawval;
    assert(binson_parser_init(&p, binson_bytes, sizeof(binson_bytes)));
    assert(binson_parser_verify(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 3.0);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x01\x02", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "", rawval->bsize) == 0);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

