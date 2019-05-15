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
    BINSON_PARSER_DEF(p);
    bool ret = binson_parser_init(&p, data, size);

    if (!ret)
    {
        return false;
    }

    size_t psize = 0;
    ret = binson_parser_to_string(&p, NULL, &psize, true);

    if (ret)
    {
        __builtin_trap();
    }

    char *str_buffer = malloc(size);

    if (NULL == str_buffer)
    {
        return false;
    }

    ret = binson_parser_to_string(&p, str_buffer, &psize, true);

    if (ret)
    {
        printf("%*.*s\r\n", 0, (int) psize, (char*) str_buffer);
    }

    free(str_buffer);

    return ret;

}

/*======= Local function implementations ====================================*/
