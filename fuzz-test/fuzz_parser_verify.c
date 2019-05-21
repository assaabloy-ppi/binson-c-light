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

#include "binson_parser.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

/*======= Global function implementations ===================================*/

bool fuzz_one_input(const uint8_t *data, size_t size)
{

    binson_parser parser;
    binson_state *state = malloc(sizeof(binson_state) * 10);

    if (state == NULL) {
        return false;
    }

    parser.state = state;
    parser.max_depth = 10;

    bool ret = binson_parser_init(&parser, data, size);
    if (ret) {
        ret = false;
        while (!ret) {

            ret = binson_parser_verify(&parser);

            if (!ret && parser.error_flags == BINSON_ERROR_MAX_DEPTH_OBJECT)
            {
                if (parser.max_depth < UINT8_MAX) {
                    parser.max_depth++;
                    state = realloc(state, (sizeof(binson_state)*parser.max_depth));
                    if (NULL == state)
                    {
                        break;
                    }
                    parser.state = state;
                }
            }
            else
            {
                break;
            }
        }
    }


    if (ret) {
        for (size_t i = 0; i < size; i++) {
            printf("%02x", data[i]);
        }
        printf("\r\n");
    }

    return ret;

}

/*======= Local function implementations ====================================*/
