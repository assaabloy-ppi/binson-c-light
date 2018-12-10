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
#include "binson_parser.h"
#include "utest.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/


/*======= Test cases ========================================================*/

TEST(init_of_array_should_work)
{
    uint8_t buffer[2] = { 0x42, 0x43 };
    BINSON_PARSER_DEF(p);
    ASSERT_TRUE(binson_parser_init_array(&p, buffer, sizeof(buffer)));
    ASSERT_FALSE(binson_parser_init_array(&p, buffer, 0));
    ASSERT_FALSE(binson_parser_init_array(&p, buffer, 1));

    buffer[0] = ~buffer[0];
    ASSERT_FALSE(binson_parser_init_array(&p, buffer, sizeof(buffer)));
    buffer[0] = ~buffer[0];
    buffer[1] = ~buffer[1];
    ASSERT_FALSE(binson_parser_init_array(&p, buffer, sizeof(buffer)));
    buffer[0] = ~buffer[0];
    ASSERT_FALSE(binson_parser_init_array(&p, buffer, sizeof(buffer)));

    ASSERT_FALSE(binson_parser_init_array(NULL, buffer, sizeof(buffer)));
    ASSERT_FALSE(binson_parser_init_array(&p, NULL, sizeof(buffer)));
    ASSERT_FALSE(binson_parser_init_array(NULL, NULL, sizeof(buffer)));

}

TEST(verify_should_work)
{
    uint8_t buffer[2] = { 0x42, 0x43 };
    BINSON_PARSER_DEF(p);
    ASSERT_TRUE(binson_parser_init_array(&p, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_verify(&p));
}

TEST(bad_array)
{
    uint8_t buffer[3] = { 0x42, 0x43, 0x43 };
    BINSON_PARSER_DEF(p);
    ASSERT_TRUE(binson_parser_init_array(&p, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_go_into_array(&p));
    ASSERT_FALSE(binson_parser_leave_array(&p));
}


TEST(get_raw_array_should_work)
{
    uint8_t buffer[] = {
        0x40,
        0x14, 0x01, 0x41,
        0x42,
            0x14, 0x01, 0x41,
            0x14, 0x01, 0x42,
        0x43,
        0x41,
    };
    BINSON_PARSER_DEF(p1);
    BINSON_PARSER_DEF(p2);
    bbuf raw;
    binson_parser_init(&p1, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&p1));
    binson_parser_go_into_object(&p1);
    ASSERT_TRUE(binson_parser_field_ensure(&p1, "A", BINSON_TYPE_ARRAY));
    ASSERT_TRUE(binson_parser_get_raw(&p1, &raw));
    ASSERT_TRUE(binson_parser_init_array(&p2, raw.bptr, raw.bsize));
    ASSERT_TRUE(binson_parser_verify(&p2));

    binson_parser_reset(&p1);
    binson_parser_go_into_object(&p1);
    ASSERT_TRUE(binson_parser_field_ensure(&p1, "A", BINSON_TYPE_ARRAY));
    ASSERT_TRUE(binson_parser_go_into_array(&p1));
    ASSERT_FALSE(binson_parser_leave_object(&p1));
    ASSERT_TRUE(binson_parser_leave_array(&p1));
    ASSERT_FALSE(binson_parser_leave_array(&p1));

}


/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(init_of_array_should_work);
    RUN_TEST(bad_array);
    RUN_TEST(verify_should_work);
    RUN_TEST(get_raw_array_should_work);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

