#include <stdio.h>
#include <assert.h>
#include "binson_light.h"

int main(void)
{
    binson_parser p;
    //bool res;

    uint8_t  src[256];
    //uint8_t  buf[256];

    //#{"A" => #{"A" => 1}}
    //const uint8_t b1[]  ={64,20,1,65,64,20,1,65,16,1,65,65};
    const uint8_t b1[]  = "\x40\x14\x01\x41\x40\x14\x01\x41\x10\x01\x41\x41";

    memcpy( src, b1, sizeof(b1) );
    binson_parser_init( &p, src, sizeof(src) );
    assert(binson_parser_get_depth(&p) == 0);

    binson_parser_go_into( &p );
    assert(binson_parser_get_depth(&p) == 1);
    assert(binson_parser_get_type(&p) == BINSON_ID_OBJECT);

    assert(binson_parser_field( &p, "A" ));
    printf("Status: %x\n", p.error_flags);

    binson_parser_go_into( &p );
    assert(binson_parser_get_depth(&p) == 2);
    assert(binson_parser_get_type(&p) == BINSON_ID_OBJECT);

    assert(binson_parser_field( &p, "A" ));
    printf("Status: %x\n", p.error_flags);

    printf("int: %d\n", (int)binson_parser_get_integer(&p));
    printf("Status: %x\n", p.error_flags);
    return 0;
}

