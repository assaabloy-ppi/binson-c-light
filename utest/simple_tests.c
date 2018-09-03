#include <stdio.h>
#include <assert.h>

#include "binson_defines.h"
#include "binson_parser.h"

static void verify_empty_object(void)
{
    binson_parser parser;
    /* {} */
    uint8_t buffer[2] = { BINSON_DEF_OBJECT_BEGIN , BINSON_DEF_OBJECT_END };
    assert(binson_parser_init(&parser, buffer, sizeof(buffer)));
    assert(binson_parser_verify(&parser));
}

static void verify_one_string(void)
{
    binson_parser parser;
    /* {"A":"B"} */
    uint8_t buffer[8] = {
        0x40,
        0x14, 0x01, 0x41, 0x14, 0x01, 0x42,
        0x41
    };
    assert(binson_parser_init(&parser, buffer, sizeof(buffer)));
    assert(binson_parser_verify(&parser));
}


int main(void)
{

    verify_empty_object();
    verify_one_string();


    return 0;
}
