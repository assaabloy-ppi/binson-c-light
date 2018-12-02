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

static uint8_t buffer[8192];

/*======= Global function implementations ===================================*/

static int __main(int argc, char **argv)
{

    (void) argc;
    (void) argv;

    ssize_t size;
    uint8_t *buffer_cpy;
    bool ret;
    BINSON_PARSER_DEF(parser);

    size = read(0, buffer, sizeof(buffer));

    if (size == 0) {
        return -1;
    }

    buffer_cpy = malloc(size);

    if (buffer_cpy == NULL) {
        return -1;
    }

    memcpy(buffer_cpy, buffer, size);
    ret = binson_parser_init_array(&parser, buffer_cpy, size);
    if (ret) {
        ret = binson_parser_verify(&parser);
        if (ret) {

            assert(binson_parser_go_into_array(&parser));
            assert(binson_parser_leave_array(&parser));

            for (ssize_t i = 0; i < size; i++) {
                printf("%02x", buffer_cpy[i]);
            }
            printf("\r\n");
        }
    }

    free(buffer_cpy);

    return (ret) ? 0 : -1;

}

int main(int argc, char **argv)
{
    #ifdef __AFL_LOOP
    while (__AFL_LOOP(1000)) {
        __main(argc, argv);
    }
    return 0;
    #else
    return __main(argc, argv);
    #endif

}


/*======= Local function implementations ====================================*/
