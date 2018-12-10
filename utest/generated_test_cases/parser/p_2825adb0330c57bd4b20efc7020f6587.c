#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "0BF@00000000000000000000000": 12336
}
*/
int main(void)
{
    uint8_t binson_bytes[42] = "\x40\x14\x23\x30\x42\x46\x40\x30\x30\x30\x30\x30\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x41";
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
    assert(binson_parser_field_ensure_with_length(&p, "\x30\x42\x46\x40\x30\x30\x30\x30\x30\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30", 35, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 12336);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

