#include <stdio.h>
#include "binson_light.h"

int main(void)
{
    binson_parser p;

    uint8_t  src[256];

    //Value: #{"B" => #{"A" => #{},"B" => 1}}
    const uint8_t b1[]  ={64,20,1,66,64,20,1,65,64,65,20,1,66,16,1,65,65};

    memcpy( src, b1, sizeof(b1) );
    binson_parser_init( &p, src, sizeof(src) );

    binson_parser_go_into( &p );
    binson_parser_field( &p, "B" );
    printf("Status: %x\n", p.error_flags);

    binson_parser_go_into( &p );
    printf("Status: %x\n", p.error_flags);

    binson_parser_field( &p, "A" );
    printf("Status: %x\n", p.error_flags);

    binson_parser_go_into( &p );
    binson_parser_go_up( &p );

    binson_parser_field( &p, "B" );
    printf("Status: %x\n", p.error_flags);

    printf("int: %d\n", (int)binson_parser_get_integer(&p));
    printf("Status: %x\n", p.error_flags);

    return 0;
}

