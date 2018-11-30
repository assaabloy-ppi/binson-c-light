/**
 * @file binson_parser_init.c
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <float.h>
#include <string.h>

#include "utest.h"
#include "binson_defines.h"
#include "binson_parser.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/
/*======= Test cases ========================================================*/

TEST(bad_binson_only_field_name)
{
    uint8_t buffer[5] = { /* 4014010041*/
        0x40, 0x14, 0x01, 0x00, 0x41
    };
    BINSON_PARSER_DEF(p);
    
    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_FALSE(binson_parser_verify(&p));
}


/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(bad_binson_only_field_name);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

