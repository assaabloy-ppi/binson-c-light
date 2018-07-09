#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "BDcDDDDcDDDDDDDD^DDDDDDDDDeD=DD": true
}
*/
int main(void)
{
    uint8_t binson_bytes[36] = "\x40\x14\x1f\x42\x44\x63\x44\x44\x44\x44\x63\x44\x44\x44\x44\x44\x44\x44\x44\x5e\x44\x44\x44\x44\x44\x44\x44\x44\x44\x65\x44\x3d\x44\x44\x44\x41";
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
    assert(binson_parser_field_ensure_with_length(&p, "\x42\x44\x63\x44\x44\x44\x44\x63\x44\x44\x44\x44\x44\x44\x44\x44\x5e\x44\x44\x44\x44\x44\x44\x44\x44\x44\x65\x44\x3d\x44\x44", 31, BINSON_TYPE_BOOLEAN));
    assert(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(boolval == true);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

