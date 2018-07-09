#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "000": [
    "0",
    48,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472312903064891440,
    3472328296228930096,
    3472328296227680304,
    3472328296227680304,
    3472328416486764592,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227674672,
    3472328296227680304,
    3472296410390474800,
    1094427692976058416,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    2607637167772545072,
    3472328296227680304,
    3472328296227680304,
    12304,
    3472328296227680304
  ]
}
*/
int main(void)
{
    uint8_t binson_bytes[260] = "\x40\x14\x03\x30\x30\x30\x42\x14\x01\x30\x10\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x22\x30\x30\x13\x30\x42\x43\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x4c\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x1a\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x13\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x0f\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x24\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x11\x10\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x43\x41";
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
    assert(binson_parser_field_ensure_with_length(&p, "\x30\x30\x30", 3, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x30", rawval->bsize) == 0);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 48);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472312903064891440);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296228930096);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328416486764592);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227674672);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472296410390474800);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 1094427692976058416);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 2607637167772545072);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 12304);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 3472328296227680304);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

