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
#include "binson_writer.h"
#include "utest.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

/*
{
  "A": "B", 
  "B": {
    "A": "B"
  }, 
  "C": [
    "A",
    "A",
    {
      "A": "B", 
      "B": [
        "A",
        "A",
        {
          "A": "B"
        },
        [
          [
            [
              [
                {
                  "A": "B"
                }
              ]
            ]
          ]
        ]
      ]
    },
    "A"
  ], 
  "D": 3.141592653589793, 
  "E": false, 
  "F": 127, 
  "G": "0x0202"
}
*/
static const uint8_t binson_bytes[104] = "\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x40\x14\x01\x41\x14\x01\x42\x41\x14\x01\x43\x42\x14\x01\x41\x14\x01\x41\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x42\x14\x01\x41\x14\x01\x41\x40\x14\x01\x41\x14\x01\x42\x41\x42\x42\x42\x42\x40\x14\x01\x41\x14\x01\x42\x41\x43\x43\x43\x43\x43\x41\x14\x01\x41\x43\x14\x01\x44\x46\x18\x2d\x44\x54\xfb\x21\x09\x40\x14\x01\x45\x45\x14\x01\x46\x10\x7f\x14\x01\x47\x18\x02\x02\x02\x41";


/*======= Test cases ========================================================*/

TEST(verify_should_work)
{
    BINSON_PARSER_DEF(p);
    ASSERT_TRUE(binson_parser_init(&p, binson_bytes, sizeof(binson_bytes)));
    ASSERT_TRUE(binson_parser_verify(&p));
}

TEST(go_into_depth_1)
{
    BINSON_PARSER_DEF(p);
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);
}

TEST(parse_one_field)
{
    BINSON_PARSER_DEF(p);
    bbuf *str;
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));

    /* With parser_next */
    ASSERT_TRUE(binson_parser_reset(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_next(&p));
    str = binson_parser_get_name(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "A", str->bsize) == 0);

    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    str = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "B", str->bsize) == 0);

    /* With parser_next_ensure */
    ASSERT_TRUE(binson_parser_reset(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_next_ensure(&p, BINSON_TYPE_STRING));
    str = binson_parser_get_name(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "A", str->bsize) == 0);

    str = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "B", str->bsize) == 0);

    /* With parser_field */
    ASSERT_TRUE(binson_parser_reset(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field(&p, "A"));

    str = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "B", str->bsize) == 0);

    /* With parser_field_ensure */
    ASSERT_TRUE(binson_parser_reset(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "A", BINSON_TYPE_STRING));
    
    str = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "B", str->bsize) == 0);

    /* Wrong types */
    ASSERT_TRUE(binson_parser_reset(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_FALSE(binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT));
    ASSERT_TRUE(binson_parser_reset(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_FALSE(binson_parser_field_ensure(&p, "A", BINSON_TYPE_BOOLEAN));
}

TEST(go_into_depth_2)
{
    BINSON_PARSER_DEF(p);
    bbuf *str;
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);
    /* Skip "A" field */
    ASSERT_TRUE(binson_parser_field_ensure(&p, "B", BINSON_TYPE_OBJECT));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_get_depth(&p) == 2);

    /* Parse field in object */
    ASSERT_TRUE(binson_parser_next(&p));
    str = binson_parser_get_name(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "A", str->bsize) == 0);

    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    str = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "B", str->bsize) == 0);

    ASSERT_TRUE(binson_parser_leave_object(&p));
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);

    ASSERT_TRUE(binson_parser_reset(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);
    /* Skip "A" field */
    ASSERT_TRUE(binson_parser_field_ensure(&p, "B", BINSON_TYPE_OBJECT));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_get_depth(&p) == 2);
    /* Skip data in object. */
    ASSERT_TRUE(binson_parser_leave_object(&p));
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);
}

TEST(skip_go_into_object)
{
    BINSON_PARSER_DEF(p);
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "C", BINSON_TYPE_ARRAY));
}

TEST(skip_go_into_array)
{
    BINSON_PARSER_DEF(p);
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "D", BINSON_TYPE_DOUBLE));
}

TEST(go_into_array)
{
    BINSON_PARSER_DEF(p);
    bbuf *str;
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "C", BINSON_TYPE_ARRAY));
    ASSERT_TRUE(binson_parser_go_into_array(&p));

    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);

    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);

    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_OBJECT);

    ASSERT_TRUE(binson_parser_go_into_object(&p));

    ASSERT_TRUE(binson_parser_field_ensure(&p, "A", BINSON_TYPE_STRING));
    
    str = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "B", str->bsize) == 0);


}

TEST(skip_object_in_array)
{
    BINSON_PARSER_DEF(p);
    bbuf *str;
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "C", BINSON_TYPE_ARRAY));
    ASSERT_TRUE(binson_parser_go_into_array(&p));
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_OBJECT);
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);

    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    ASSERT_TRUE(binson_parser_get_depth(&p) == 1);
    str = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "A", str->bsize) == 0);

    ASSERT_TRUE(binson_parser_leave_array(&p));
}

TEST(get_raw_object)
{
    BINSON_PARSER_DEF(p);
    bbuf raw;
    bbuf *str;
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "B", BINSON_TYPE_OBJECT));
    ASSERT_TRUE(binson_parser_get_raw(&p, &raw));
    ASSERT_TRUE(raw.bptr != NULL && raw.bsize > 0);
    BINSON_PARSER_DEF(p2);
    ASSERT_TRUE(binson_parser_init(&p2, raw.bptr, raw.bsize));
    ASSERT_TRUE(binson_parser_go_into_object(&p2));
    ASSERT_TRUE(binson_parser_next(&p2));
    str = binson_parser_get_name(&p2);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "A", str->bsize) == 0);

    ASSERT_TRUE(binson_parser_get_type(&p2) == BINSON_TYPE_STRING);
    str = binson_parser_get_string_bbuf(&p2);
    ASSERT_TRUE(str != NULL && str->bptr != NULL && str->bsize == 1);
    ASSERT_TRUE(memcmp(str->bptr, "B", str->bsize) == 0);
}

TEST(parse_all)
{
    BINSON_PARSER_DEF(p);
    double dval; (void) dval;
    int64_t intval; (void) intval;
    bool boolval; (void) boolval;
    bbuf *rawval; (void) rawval;
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_OBJECT);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    binson_parser_leave_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_field_ensure_with_length(&p, "\x43", 1, BINSON_TYPE_ARRAY);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_next_ensure(&p, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    binson_parser_next_ensure(&p, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    binson_parser_field_ensure_with_length(&p, "\x42", 1, BINSON_TYPE_ARRAY);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_next_ensure(&p, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    binson_parser_next_ensure(&p, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    binson_parser_leave_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_next_ensure(&p, BINSON_TYPE_ARRAY);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_next_ensure(&p, BINSON_TYPE_ARRAY);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_next_ensure(&p, BINSON_TYPE_ARRAY);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_next_ensure(&p, BINSON_TYPE_ARRAY);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_next_ensure(&p, BINSON_TYPE_OBJECT);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_go_into_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x42", rawval->bsize) == 0);
    binson_parser_leave_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_leave_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_leave_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_leave_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_leave_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_leave_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_leave_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_next_ensure(&p, BINSON_TYPE_STRING);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x41", rawval->bsize) == 0);
    binson_parser_leave_array(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    binson_parser_field_ensure_with_length(&p, "\x44", 1, BINSON_TYPE_DOUBLE);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(dval == 3.141592653589793);
    binson_parser_field_ensure_with_length(&p, "\x45", 1, BINSON_TYPE_BOOLEAN);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    boolval = binson_parser_get_boolean(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(boolval == false);
    binson_parser_field_ensure_with_length(&p, "\x46", 1, BINSON_TYPE_INTEGER);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(intval == 127);
    binson_parser_field_ensure_with_length(&p, "\x47", 1, BINSON_TYPE_BYTES);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
    ASSERT_TRUE(memcmp(rawval->bptr, "\x02\x02", rawval->bsize) == 0);
    binson_parser_leave_object(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
}

#ifdef BINSON_PARSER_WITH_PRINT
TEST(print_binson)
{
    BINSON_PARSER_DEF(p);
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_print(&p));
}
#endif

/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(verify_should_work);
    RUN_TEST(go_into_depth_1);
    RUN_TEST(parse_one_field);
    RUN_TEST(go_into_depth_2);
    RUN_TEST(skip_go_into_object);
    RUN_TEST(skip_go_into_array);
    RUN_TEST(go_into_array);
    RUN_TEST(skip_object_in_array);
    RUN_TEST(get_raw_object);
    RUN_TEST(parse_all);
    #ifdef BINSON_PARSER_WITH_PRINT
    RUN_TEST(print_binson);
    #endif
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

