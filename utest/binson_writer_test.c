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
#include <stdlib.h>

#include "binson_defines.h"
#include "binson_writer.h"
#include "utest.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/
/*======= Test cases ========================================================*/

TEST(valid_init)
{

    binson_writer writer;
    uint8_t buffer[2] = { BINSON_DEF_OBJECT_BEGIN , BINSON_DEF_OBJECT_END };
    ASSERT_TRUE(binson_writer_init(&writer, buffer, sizeof(buffer)));

}

TEST(invalid_init_null_ptr)
{

    binson_writer writer;
    uint8_t buffer[2] = { BINSON_DEF_OBJECT_BEGIN , BINSON_DEF_OBJECT_END };
    ASSERT_FALSE(binson_writer_init(NULL, buffer, sizeof(buffer)));
    ASSERT_FALSE(binson_writer_init(&writer, NULL, sizeof(buffer)));
    ASSERT_FALSE(binson_writer_init(NULL, NULL, sizeof(buffer)));
}


TEST(test_0)
{
    uint8_t expected[34] = "\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x42\x14\x0b\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x40\x14\x01\x41\x14\x01\x42\x41\x43\x41";
    uint8_t created[34];
    binson_writer w;
    ASSERT_TRUE(binson_writer_init(&w, created, sizeof(created)));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_object_begin(&w));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_name(&w, "A"));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_string(&w, "B"));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_name(&w, "B"));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_array_begin(&w));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_string(&w, "Hello world"));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_object_begin(&w));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_name(&w, "A"));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_string(&w, "B"));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_object_end(&w));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_array_end(&w));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_write_object_end(&w));
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(binson_writer_verify(&w));
    ASSERT_TRUE(memcmp(expected, created, sizeof(expected)) == 0);
    BINSON_PARSER_DEF(p);
    ASSERT_TRUE(binson_parser_init(&p, created, sizeof(created)));
    ASSERT_TRUE(binson_parser_verify(&p));
}

TEST(error_should_be_reported)
{
    binson_writer w;
    uint8_t buffer[4];
    binson_writer_init(&w, buffer, sizeof(buffer));
    binson_write_object_begin(&w);
    binson_write_name(&w, "A");
    binson_write_string(&w, "Hello world");
    binson_write_object_end(&w);
    ASSERT_FALSE(w.error_flags == BINSON_ID_OK);
}

TEST(writer_should_give_required_size)
{
    binson_writer w;
    uint8_t *buffer = malloc(4);
    if (NULL == buffer) {
        return;
    }
    ASSERT_TRUE(buffer != NULL);
    binson_writer_init(&w, buffer, 4);
    binson_write_object_begin(&w);
    binson_write_name(&w, "A");
    ASSERT_FALSE(binson_write_string(&w, "Hello world"));
    ASSERT_FALSE(binson_write_object_end(&w));
    ASSERT_FALSE(w.error_flags == BINSON_ID_OK);
    size_t required = binson_writer_get_counter(&w);
    uint8_t *new_buffer;
    new_buffer = realloc(buffer, required);
    if (NULL == new_buffer) {
        free(buffer);
        return;
    }
    buffer = new_buffer;
    binson_writer_init(&w, buffer, required);
    binson_write_object_begin(&w);
    binson_write_name(&w, "A");
    binson_write_string(&w, "Hello world");
    binson_write_object_end(&w);
    ASSERT_TRUE(w.error_flags == BINSON_ID_OK);
    free(buffer);
}

TEST(write_string)
{
    uint8_t buffer[100];
    const char *str = "Hello world";

    binson_writer w;

    ASSERT_TRUE(binson_writer_init(&w, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_write_object_begin(&w));
    ASSERT_TRUE(binson_write_name(&w, "A"));
    ASSERT_TRUE(binson_write_string(&w, str));
    ASSERT_TRUE(binson_write_object_end(&w));

    BINSON_PARSER_DEF(p);
    bbuf *b;
    ASSERT_TRUE(binson_parser_init(&p, buffer, binson_writer_get_counter(&w)));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_next(&p));
    b = binson_parser_get_string_bbuf(&p);
    ASSERT(b != NULL);
    ASSERT_TRUE(b->bsize == strlen(str));
    ASSERT_TRUE(memcmp(str, b->bptr, strlen(str)) == 0);
    ASSERT_TRUE(binson_parser_leave_object(&p));
}

/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(valid_init);
    RUN_TEST(invalid_init_null_ptr);
    RUN_TEST(test_0);
    RUN_TEST(error_should_be_reported);
    RUN_TEST(writer_should_give_required_size);
    RUN_TEST(write_string);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

