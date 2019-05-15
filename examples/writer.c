#include "binson_light.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    printf("=== Binson writer example ===\r\n");
    uint8_t        buf[64];
    size_t         cnt;
    binson_writer  w;

    binson_writer_init(&w, buf, sizeof(buf));

    // {"cid":123}
    binson_write_object_begin(&w);
    binson_write_name(&w, "cid");
    binson_write_integer(&w, 123);
    binson_write_object_end(&w);

    cnt = binson_writer_get_counter(&w);

    printf("Hex representation: ");
    for (size_t i = 0; i < cnt; i++) {
        printf( "0x%02x ", buf[i] );
    }
    printf("\r\n");

    printf("JSON Representation: ");
    BINSON_PARSER_DEF(p);
    binson_parser_init(&p, buf, cnt);
    assert(binson_parser_verify(&p));
    #ifdef BINSON_PARSER_WITH_PRINT
    binson_parser_print(&p);
    #endif
    printf("\r\n");

    return 0;
}
