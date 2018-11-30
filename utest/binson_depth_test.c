/**
 * @file binson_parser_init.c
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <float.h>
#include <string.h>

#include "binson_defines.h"
#include "binson_writer.h"
#include "utest.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/
/*======= Test cases ========================================================*/

TEST(test_different_depths)
{

    uint8_t buffer[128];

    /* Default depth == 10U */
    BINSON_PARSER_DEF(p10);
    binson_parser_init(&p10, buffer, sizeof(buffer));
    ASSERT_TRUE(p10.max_depth == 10);
    ASSERT_TRUE(sizeof(p10data) == (sizeof(binson_state) * 10));

    BINSON_PARSER_DEF(p2, 2);
    binson_parser_init(&p2, buffer, sizeof(buffer));
    ASSERT_TRUE(p2.max_depth == 2);
    ASSERT_TRUE(sizeof(p2data) == (sizeof(binson_state) * 2));

    BINSON_PARSER_DEF(p100, 100);
    binson_parser_init(&p100, buffer, sizeof(buffer));
    ASSERT_TRUE(p100.max_depth == 100);
    ASSERT_TRUE(sizeof(p100data) == (sizeof(binson_state) * 100));

}

/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(test_different_depths);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

