#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "": 0.0
}
*/
int main(void)
{
    uint8_t binson_bytes[13] = "\x40\x14\x00\x46\x00\x00\x00\x00\x00\x00\x00\x00\x41";
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
    assert(binson_parser_field_ensure_with_length(&p, "", 0, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 0.0);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

