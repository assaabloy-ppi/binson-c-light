#include "binson_light.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    printf("=== Binson parser example ===\r\n");

    const uint8_t src[26] = "\x40\x14\x01\x61\x10\x7b\x14\x03\x62\x63\x64\x14\x0c\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x41";
    bbuf          *str;
    /*
    * Defines a parser that can parse up to 10 nested objects.
    * If less or more levels are required use the macro:
    * BINSON_PARSER_DEF_DEPTH(p, depth).
    *
    * It is also possible to do like this:
    * binson_parser p;
    * binson_state states[5];
    * p.state = state;
    * p.max_depth = 5;
    *
    */
    BINSON_PARSER_DEF(p); /* Default maximum depth = 10 */

    binson_parser_init(&p, src, sizeof(src));
    assert(binson_parser_verify(&p));

    binson_parser_go_into_object(&p);
    binson_parser_field(&p, "a");
    printf("a: %d\n", (int)binson_parser_get_integer(&p));

    binson_parser_field(&p, "bcd");
    str = binson_parser_get_string_bbuf(&p);
    printf("bcd: %*.*s\n", 0, (int) str->bsize, (const char *) str->bptr);
    return 0;
}
