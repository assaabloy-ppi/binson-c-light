#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "A": "0", 
  "B": 48, 
  "C": 1.398043286095289E-76, 
  "D": false, 
  "E": "0x3030", 
  "F": {
  }, 
  "G": [
    "0x3030",
    "0",
    "00000000000000000000",
    "00000000000000000000",
    "00000000000000000000",
    false,
    false,
    false,
    {
      "0": "0"
    },
    "0",
    "B",
    48,
    "0",
    "00000000000000000000",
    "00000000000000000000",
    false,
    false,
    false,
    false,
    false,
    false,
    {
      "0": "0"
    },
    "B",
    "B",
    48,
    false,
    false,
    false,
    false,
    false,
    false,
    {
      "0": "0"
    },
    "B",
    "@",
    48,
    "0",
    1.398043286095289E-76,
    48,
    "0",
    1.398043286095289E-76
  ], 
  "?": [
    
  ]
}
*/
int main(void)
{
    uint8_t binson_bytes[262] = "\x40\x14\x01\x41\x14\x01\x30\x14\x01\x42\x10\x30\x14\x01\x43\x46\x30\x30\x30\x30\x30\x30\x30\x30\x14\x01\x44\x45\x14\x01\x45\x18\x02\x30\x30\x14\x01\x46\x40\x41\x14\x01\x47\x42\x18\x02\x30\x30\x14\x01\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x45\x45\x45\x40\x14\x01\x30\x14\x01\x30\x41\x14\x01\x30\x14\x01\x42\x10\x30\x14\x01\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x14\x14\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x45\x45\x45\x45\x45\x45\x40\x14\x01\x30\x14\x01\x30\x41\x14\x01\x42\x14\x01\x42\x10\x30\x45\x45\x45\x45\x45\x45\x40\x14\x01\x30\x14\x01\x30\x41\x14\x01\x42\x14\x01\x40\x10\x30\x14\x01\x30\x46\x30\x30\x30\x30\x30\x30\x30\x30\x10\x30\x14\x01\x30\x46\x30\x30\x30\x30\x30\x30\x30\x30\x43\x14\x03\xef\xbf\xbd\x42\x43\x41";
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
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 48);
    assert(binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 1.398043286095289E-76);
    assert(binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30", rawval->bsize) == 0);
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
    assert(memcmp(rawval->bptr, "\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x30", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 48);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x30", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 48);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == false);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x30", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x40", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 48);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 1.398043286095289E-76);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 48);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 1.398043286095289E-76);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\xef\xbf\xbd", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

