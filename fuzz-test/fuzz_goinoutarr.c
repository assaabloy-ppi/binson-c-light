/**
 * @file binson_fuzz.c.c
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "binson_parser.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

static bool parse_binson(const uint8_t *buffer, uint32_t size);

/*======= Global function implementations ===================================*/

bool fuzz_one_input(const uint8_t *data, size_t size)
{
    bool ret = parse_binson(data, size);
    if (ret)
    {
    if (ret) {
            for (size_t i = 0; i < size; i++) {
                printf("%02x", data[i]);
            } printf("\r\n");
        }
    }
    return ret;
}

/*======= Local function implementations ====================================*/

#define VERIFY(x) if(!(x)) return false

static bool parse_binson(const uint8_t *buffer, uint32_t size)
{

    BINSON_PARSER_DEF(p);

    binson_parser_init(&p, buffer, size);
    VERIFY(binson_parser_go_into_object(&p));
    assert(binson_parser_get_depth(&p) == 1);

    while (binson_parser_next(&p)) {
        if (binson_parser_get_type(&p) == BINSON_TYPE_ARRAY) {
            assert(p.current_state->array_depth == 0);
            VERIFY(binson_parser_go_into_array(&p));
            assert(p.current_state->array_depth == 1);
            VERIFY(binson_parser_leave_array(&p));
            assert(p.current_state->array_depth == 0);
        }
    }

    VERIFY(binson_parser_leave_object(&p));
    assert(binson_parser_get_depth(&p) == 0);
    VERIFY(binson_parser_verify(&p));

    printf("}");

    return true;
}
