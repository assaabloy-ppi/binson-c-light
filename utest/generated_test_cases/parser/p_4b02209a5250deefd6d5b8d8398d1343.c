#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "BBCF??      BBBBBBFF?FFFFFFFFF": 1.0347915464784313E10
}
*/
int main(void)
{
    uint8_t binson_bytes[49] = "\x40\x14\x24\x42\x42\x43\x46\xef\xbf\xbd\xef\xbf\xbd\x00\x00\x00\x00\x00\x00\x42\x42\x42\x42\x42\x42\x46\x46\xef\xbf\xbd\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x45\x46\x03\x42\x41";
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
    assert(binson_parser_field_ensure_with_length(&p, "\x42\x42\x43\x46\xef\xbf\xbd\xef\xbf\xbd\x00\x00\x00\x00\x00\x00\x42\x42\x42\x42\x42\x42\x46\x46\xef\xbf\xbd\x46\x46\x46\x46\x46\x46\x46\x46\x46", 36, BINSON_TYPE_DOUBLE));
    assert(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(dval == 1.0347915464784313E10);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

