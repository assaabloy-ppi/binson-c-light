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

#include "binson.hpp"

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
    binson_parser parser;

    size = read(0, buffer, sizeof(buffer));

    if (size == 0) {
        return -1;
    }

    buffer_cpy = (uint8_t *) malloc(size);

    if (buffer_cpy == NULL) {
        return -1;
    }

    memcpy(buffer_cpy, buffer, size);

    Binson b;
    try {
        b.deserialize(buffer_cpy, size);
        binson_parser_init(&parser, buffer_cpy, size);

        /*
         * if b.deserialize() didn't throw exception
         * this should be a valid binson object.
         * Is not, trigger crash.
         */
        assert(binson_parser_verify(&parser));

        for (ssize_t i = 0; i < size; i++) {
            printf("%02x", buffer_cpy[i]);
        }
        printf("\r\n");
        ret = true;
    } catch (const std::runtime_error &e) {
        /* Not a valid binson object */
        ret = false;
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
