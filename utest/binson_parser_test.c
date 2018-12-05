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

TEST(valid_init)
{

    binson_parser parser;
    uint8_t buffer[2] = { BINSON_DEF_OBJECT_BEGIN , BINSON_DEF_OBJECT_END };
    ASSERT_TRUE(binson_parser_init(&parser, buffer, sizeof(buffer)));

}

TEST(invalid_init_null_ptr)
{

    binson_parser parser;
    uint8_t buffer[2] = { BINSON_DEF_OBJECT_BEGIN , BINSON_DEF_OBJECT_END };
    ASSERT_FALSE(binson_parser_init(NULL, buffer, sizeof(buffer)));
    ASSERT_FALSE(binson_parser_init(&parser, NULL, sizeof(buffer)));
    ASSERT_FALSE(binson_parser_init(NULL, NULL, sizeof(buffer)));
}

TEST(invalid_init_buffer_to_small)
{

    binson_parser parser;
    uint8_t buffer[2] = { BINSON_DEF_OBJECT_BEGIN , BINSON_DEF_OBJECT_END };
    ASSERT_FALSE(binson_parser_init(&parser, buffer, BINSON_OBJECT_MINIMUM_SIZE - 1));
    ASSERT_FALSE(binson_parser_init(&parser, buffer, 0));
}

TEST(invalid_init_bad_format)
{

    binson_parser parser;
    uint8_t buffer[2] = {
        (uint8_t) ~BINSON_DEF_OBJECT_BEGIN ,
        (uint8_t) ~BINSON_DEF_OBJECT_END
    };
    ASSERT_FALSE(binson_parser_init(&parser, buffer, sizeof(buffer)));
}

TEST(parse_empty_object)
{

    binson_parser parser;
    /* {} */
    uint8_t buffer[2] = { BINSON_DEF_OBJECT_BEGIN , BINSON_DEF_OBJECT_END };
    ASSERT_TRUE(binson_parser_init(&parser, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_FALSE(binson_parser_next(&parser));
    ASSERT_TRUE(BINSON_ERROR_NONE == parser.error_flags);
}

TEST(parse_verify)
{

    binson_parser parser;
    /* {} */
    uint8_t buffer[2] = { BINSON_DEF_OBJECT_BEGIN , BINSON_DEF_OBJECT_END };
    binson_parser_init(&parser, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&parser));

    uint8_t buffer2[14] = { /* 4014014114014241*/
        0x40,
        0x14, 0x01, 0x41, 0x14, 0x01, 0x42,
        0x14, 0x01, 0x41, 0x14, 0x01, 0x42,
        0x41
    };

    binson_parser_init(&parser, buffer2, sizeof(buffer2));
    ASSERT_FALSE(binson_parser_verify(&parser));

    uint8_t buffer3[4] = {
        0x40, 0x40, 0x41, 0x41
    };

    binson_parser_init(&parser, buffer3, sizeof(buffer3));
    ASSERT_FALSE(binson_parser_verify(&parser));

    uint8_t buffer4[14] = { /* 4014014114014241*/
        0x40,
        0x14, 0x01, 0x42, 0x14, 0x01, 0x42,
        0x14, 0x01, 0x41, 0x14, 0x01, 0x42,
        0x41
    };

    binson_parser_init(&parser, buffer4, sizeof(buffer4));
    ASSERT_FALSE(binson_parser_verify(&parser));

}

TEST(parse_bad_name_length)
{

    binson_parser parser;
    /* 0x14 >= Stringlength <= 127 */
    uint8_t buffer0[8] = {
        0x40,
        0x14, 0xFF, 0x41,
        0x14, 0x01, 0x43,
        0x41
    };

    ASSERT_TRUE(binson_parser_init(&parser, buffer0, sizeof(buffer0)));
    ASSERT_FALSE(binson_parser_verify(&parser));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_FALSE(binson_parser_next(&parser));
    ASSERT_TRUE(BINSON_ERROR_FORMAT == parser.error_flags);

    /* To small buffer to hold field name. */
    uint8_t buffer1[8] = {
        0x40,
        0x14, 0x7F, 0x41,
        0x14, 0x01, 0x43,
        0x41
    };
    ASSERT_TRUE(binson_parser_init(&parser, buffer1, sizeof(buffer1)));
    ASSERT_FALSE(binson_parser_verify(&parser));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_FALSE(binson_parser_next(&parser));
    ASSERT_TRUE(BINSON_ERROR_RANGE == parser.error_flags);
    ASSERT_FALSE(binson_parser_next(&parser));
}

TEST(parse_one_string)
{

    /*
     * Hexstring: 4014014114014241
     * input = {
     *   A := "B"
     * }
     */
    binson_parser parser;
    bbuf *string;
    uint8_t buffer[8] = { /* 4014014114014241*/
        0x40, 0x14, 0x01, 0x41, 0x14, 0x01, 0x42, 0x41
    };

    binson_parser_init(&parser, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&parser));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_TRUE(binson_parser_next(&parser));
    ASSERT_TRUE(binson_parser_get_type(&parser) ==  BINSON_TYPE_STRING);
    string = binson_parser_get_name(&parser);
    ASSERT_TRUE(string != NULL);
    ASSERT_TRUE(string->bptr != NULL);;
    ASSERT_TRUE(string->bsize ==  1);
    ASSERT_TRUE(string->bptr[0] ==  0x41); /* 0x41 = A */
    string = binson_parser_get_string_bbuf(&parser);
    ASSERT_TRUE(string != NULL);
    ASSERT_TRUE(string->bptr != NULL);;
    ASSERT_TRUE(string->bsize ==  1);
    ASSERT_TRUE(string->bptr[0] ==  0x42); /* 0x42 = B */
    ASSERT_FALSE(binson_parser_next(&parser));
    ASSERT_TRUE(BINSON_ERROR_NONE ==  parser.error_flags);

}

TEST(parse_integers16)
{

    binson_parser parser;
    int64_t intval;
    uint8_t buffer[26] = {
        0x40,
        0x14, 0x01, 0x41, 0x11, 0x00, 0x80, /* "A": -2^15 - 1 */
        0x14, 0x01, 0x42, 0x11, 0x7F, 0xFF, /* "B": -129 */
        0x14, 0x01, 0x43, 0x11, 0x80, 0x00, /* "C": 128 */
        0x14, 0x01, 0x44, 0x11, 0xFF, 0x7F, /* "D": 2^15 - 1 */
        0x41
    };

    ASSERT_TRUE(binson_parser_init(&parser, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_verify(&parser));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_TRUE(binson_parser_field_ensure(&parser, "A", BINSON_TYPE_INTEGER));
    intval = binson_parser_get_integer(&parser);
    ASSERT_TRUE(parser.error_flags ==  BINSON_ERROR_NONE);
    ASSERT_TRUE(intval ==  INT16_MIN);
    ASSERT_TRUE(binson_parser_field_ensure(&parser, "B", BINSON_TYPE_INTEGER));
    intval = binson_parser_get_integer(&parser);
    ASSERT_TRUE(parser.error_flags ==  BINSON_ERROR_NONE);
    ASSERT_TRUE(intval ==  (INT8_MIN - 1));
    ASSERT_TRUE(binson_parser_field_ensure(&parser, "C", BINSON_TYPE_INTEGER));
    intval = binson_parser_get_integer(&parser);
    ASSERT_TRUE(parser.error_flags ==  BINSON_ERROR_NONE);
    ASSERT_TRUE(intval ==  (INT8_MAX + 1));
    ASSERT_TRUE(binson_parser_field_ensure(&parser, "D", BINSON_TYPE_INTEGER));
    intval = binson_parser_get_integer(&parser);
    ASSERT_TRUE(parser.error_flags ==  BINSON_ERROR_NONE);
    ASSERT_TRUE(intval ==  INT16_MAX);

    /* 2 byte size must have integers larger than 127 or smaller than -128. */
    uint8_t buffer1[8] = {
        0x40,
        0x14, 0x01, 0x41, 0x11, 0x7F, 0x00, /* "A": 127 (0x7F00) */
        0x41
    };

    ASSERT_TRUE(binson_parser_init(&parser, buffer1, sizeof(buffer1)));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_FALSE(binson_parser_field_ensure(&parser, "A", BINSON_TYPE_INTEGER));
    ASSERT_TRUE(parser.error_flags ==  BINSON_ERROR_FORMAT);
    ASSERT_TRUE(binson_parser_reset(&parser));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_FALSE(binson_parser_next(&parser));
    ASSERT_TRUE(parser.error_flags ==  BINSON_ERROR_FORMAT);

    buffer1[5] = 0x80; buffer1[6] = 0xFF; /* "A": -128 */
    ASSERT_TRUE(binson_parser_init(&parser, buffer1, sizeof(buffer1)));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_FALSE(binson_parser_field_ensure(&parser, "A", BINSON_TYPE_INTEGER));
    ASSERT_TRUE(parser.error_flags ==  BINSON_ERROR_FORMAT);
    ASSERT_TRUE(binson_parser_reset(&parser));
    ASSERT_TRUE(binson_parser_go_into_object(&parser));
    ASSERT_FALSE(binson_parser_next(&parser));
    ASSERT_TRUE(parser.error_flags ==  BINSON_ERROR_FORMAT);

}

TEST(one_nested)
{

    binson_parser p;
    /* {"A":{}} */
    uint8_t buffer[13] = {
        0x40,
        0x14, 0x01, 0x41,
            0x40,
                0x14, 0x01, 0x41, 0x18, 0x01, 0x42,
            0x41, /* "A": {"A":"0x42"} */
        0x41
    };
    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&p));

    /* {"A":{{}}} */
    uint8_t buffer3[8] = {
        0x40,
        0x14, 0x01, 0x41, /* "A": */
        0x40, /* { */
            0x40, 0x41, /* {} */
        0x41, /* } */
    };
    binson_parser_init(&p, buffer3, sizeof(buffer3));
    ASSERT_FALSE(binson_parser_verify(&p));

    /*
     * input = {
     *   A := "B",
     *   B := [
     *     "A",
     *     {}
     *   ],
     *   C := {
     *     A := {
     *       A := 2
     *     }
     *   }
     * }
     */
    uint8_t buffer2[33] = { /* 401401411401421401424214014140414314014340140141401401411002414141*/
        0x40, 0x14, 0x01, 0x41, 0x14, 0x01, 0x42, 0x14,
        0x01, 0x42, 0x42, 0x14, 0x01, 0x41, 0x40, 0x41,
        0x43, 0x14, 0x01, 0x43, 0x40, 0x14, 0x01, 0x41,
        0x40, 0x14, 0x01, 0x41, 0x10, 0x02, 0x41, 0x41,
        0x41
    };

    binson_parser_init(&p, buffer2, sizeof(buffer2));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "B", BINSON_TYPE_ARRAY));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "C", BINSON_TYPE_OBJECT));

}

TEST(bad_binson)
{


    uint8_t buffer[259] = { /* 4014015840414214101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101000101010101010107f1010101010101010101010101010103110101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010108c4341*/
        0x40, 0x14, 0x01, 0x58, 0x40, 0x41, 0x42, 0x14,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x7f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x31, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x8c, 0x43, 0x41
    };


    binson_parser p;
    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_FALSE(binson_parser_verify(&p));


}

TEST(parse_doubles)
{

    uint8_t buffer[62] = { /* 4014014146ffffffffffffef7f14014246000000000000100014014346000000000000000014014446ffffffffffffefff14014546000000000000108041*/
        0x40, 0x14, 0x01, 0x41, 0x46, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xef, 0x7f, 0x14, 0x01, 0x42,
        0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
        0x00, 0x14, 0x01, 0x43, 0x46, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x01, 0x44,
        0x46, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef,
        0xff, 0x14, 0x01, 0x45, 0x46, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x10, 0x80, 0x41
    };
    binson_parser p;
    double dval;

    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "A", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == DBL_MAX);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "B", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == DBL_MIN);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "C", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == 0.0f);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "D", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == -DBL_MAX);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "E", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == -DBL_MIN);
}

TEST(parse_bool)
{

    uint8_t buffer[10] = {
        0x40,
        0x14, 0x01, 0x41, 0x44, /* "A": true */
        0x14, 0x01, 0x42, 0x45, /* "B": false */
        0x41
    };
    binson_parser p;
    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "A", BINSON_TYPE_BOOLEAN));
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(binson_parser_get_boolean(&p));
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "B", BINSON_TYPE_BOOLEAN));
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_FALSE(binson_parser_get_boolean(&p));
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
}

static bool test_int16(int16_t intval)
{
    binson_parser p;

    uint8_t buffer1[6 + sizeof(intval)] = {
        /* {"A": 127} represented with two bytes */
        0x40,
        0x14, 0x01, 0x41, BINSON_DEF_INT16, 0x7F, 0x00,
        0x41
    };
    /* Copy intval to buffer */
    memcpy(&buffer1[5], &intval, sizeof(intval));
    VERIFY(binson_parser_init(&p, buffer1, sizeof(buffer1)));
    VERIFY(binson_parser_verify(&p));
    VERIFY(binson_parser_go_into_object(&p));
    VERIFY(binson_parser_field_ensure(&p, "A", BINSON_TYPE_INTEGER));
    VERIFY(p.error_flags == BINSON_ERROR_NONE);
    VERIFY(intval == binson_parser_get_integer(&p));
    return true;
}

static bool test_int32(int32_t intval)
{
    binson_parser p;

    uint8_t buffer1[6 + sizeof(intval)] = {
        /* {"A": 127} represented with two bytes */
        0x40,
        0x14, 0x01, 0x41, BINSON_DEF_INT32, 0x7F, 0x00, 0x7F, 0x00,
        0x41
    };
    /* Copy intval to buffer */
    memcpy(&buffer1[5], &intval, sizeof(intval));
    VERIFY(binson_parser_init(&p, buffer1, sizeof(buffer1)));
    VERIFY(binson_parser_verify(&p));
    VERIFY(binson_parser_go_into_object(&p));
    VERIFY(binson_parser_field_ensure(&p, "A", BINSON_TYPE_INTEGER));
    VERIFY(p.error_flags == BINSON_ERROR_NONE);
    VERIFY(intval == binson_parser_get_integer(&p));
    return true;
}

static bool test_int64(int64_t intval)
{
    binson_parser p;

    uint8_t buffer1[6 + sizeof(intval)] = {
        /* {"A": 127} represented with two bytes */
        0x40,
        0x14, 0x01, 0x41, BINSON_DEF_INT64, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00,
        0x41
    };
    /* Copy intval to buffer */
    memcpy(&buffer1[5], &intval, sizeof(intval));
    VERIFY(binson_parser_init(&p, buffer1, sizeof(buffer1)));
    VERIFY(binson_parser_verify(&p));
    VERIFY(binson_parser_go_into_object(&p));
    VERIFY(binson_parser_field_ensure(&p, "A", BINSON_TYPE_INTEGER));
    VERIFY(p.error_flags == BINSON_ERROR_NONE);
    VERIFY(intval == binson_parser_get_integer(&p));
    return true;
}

TEST(parse_float)
{
    /*
        {
          "A": 1.7976931348623157E308,
          "B": 2.2250738585072014E-308,
          "C": 0.0,
          "D": -1.7976931348623157E308,
          "E": -2.2250738585072014E-308
        }
    */
    binson_parser p;
    double dval;
    uint8_t buffer[62] = { /* 4014014146ffffffffffffef7f14014246000000000000100014014346000000000000000014014446ffffffffffffefff14014546000000000000108041*/
        0x40, 0x14, 0x01, 0x41, 0x46, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xef, 0x7f, 0x14, 0x01, 0x42,
        0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
        0x00, 0x14, 0x01, 0x43, 0x46, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x01, 0x44,
        0x46, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef,
        0xff, 0x14, 0x01, 0x45, 0x46, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x10, 0x80, 0x41
    };

    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "A", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == DBL_MAX);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "B", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == DBL_MIN);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "C", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == 0.0f);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "D", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == -DBL_MAX);
    ASSERT_TRUE(binson_parser_field_ensure(&p, "E", BINSON_TYPE_DOUBLE));
    dval = binson_parser_get_double(&p);
    ASSERT_TRUE(p.error_flags == BINSON_ERROR_NONE);
    ASSERT_TRUE(dval == -DBL_MIN);

}

TEST(test_integer_pack)
{

    ASSERT_FALSE(test_int16(0));
    ASSERT_FALSE(test_int16(INT8_MIN));
    ASSERT_FALSE(test_int16(INT8_MAX));
    ASSERT_TRUE(test_int16(INT8_MIN - 1));
    ASSERT_TRUE(test_int16(INT8_MAX + 1));
    ASSERT_TRUE(test_int16(INT16_MIN));
    ASSERT_TRUE(test_int16(INT16_MAX));
    ASSERT_TRUE(test_int16(INT16_MIN+1));
    ASSERT_TRUE(test_int16(INT16_MAX-1));

    ASSERT_FALSE(test_int32(0));
    ASSERT_FALSE(test_int32(INT8_MIN));
    ASSERT_FALSE(test_int32(INT8_MAX));
    ASSERT_FALSE(test_int32(INT8_MIN - 1));
    ASSERT_FALSE(test_int32(INT8_MAX + 1));
    ASSERT_FALSE(test_int32(INT16_MIN));
    ASSERT_FALSE(test_int32(INT16_MAX));
    ASSERT_TRUE(test_int32(INT16_MIN - 1));
    ASSERT_TRUE(test_int32(INT16_MAX + 1));
    ASSERT_TRUE(test_int32(INT32_MIN));
    ASSERT_TRUE(test_int32(INT32_MAX));
    ASSERT_TRUE(test_int32(INT32_MIN+1));
    ASSERT_TRUE(test_int32(INT32_MAX-1));

    ASSERT_FALSE(test_int64(0));
    ASSERT_FALSE(test_int64(INT8_MIN));
    ASSERT_FALSE(test_int64(INT8_MAX));
    ASSERT_FALSE(test_int64(INT8_MIN - 1));
    ASSERT_FALSE(test_int64(INT8_MAX + 1));
    ASSERT_FALSE(test_int64(INT16_MIN));
    ASSERT_FALSE(test_int64(INT16_MAX));
    ASSERT_FALSE(test_int64(INT16_MIN - 1));
    ASSERT_FALSE(test_int64(INT16_MAX + 1));
    ASSERT_FALSE(test_int64(INT32_MIN));
    ASSERT_FALSE(test_int64(INT32_MAX));
    ASSERT_TRUE(test_int64((int64_t) INT32_MIN - 1));
    ASSERT_TRUE(test_int64((int64_t) INT32_MAX + 1));
    ASSERT_TRUE(test_int64(INT64_MIN));
    ASSERT_TRUE(test_int64(INT64_MAX));
    ASSERT_TRUE(test_int64(INT64_MIN+1));
    ASSERT_TRUE(test_int64(INT64_MAX-1));

}

TEST(test_multi_nested)
{

    binson_parser p;
    /* {"A":{"A":{"A":{"A":{"A":{}}}}}, "B":1} */
    uint8_t buffer[] = {
        0x40,
        0x14, 0x01, 0x41,
            0x40,
                0x14, 0x01, 0x41,
                    0x40,
                        0x14, 0x01, 0x41,
                            0x40,
                                0x14, 0x01, 0x41,
                                    0x40,
                                        0x14, 0x01, 0x41,
                                        0x14, 0x01, 0x41,
                                    0x41,
                            0x41,
                    0x41,
            0x41,
        0x14, 0x01, 0x42, 0x10, 0x01,
        0x41
    };
    ASSERT_TRUE(binson_parser_init(&p, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "B", BINSON_TYPE_INTEGER));

    /* {"A":{"A":{"A":{"A":{"A":{"A":{"A":{"A":{"A":{"A":{"A":{}}}}}}}}}}}} */
    uint8_t buffer2[] = {
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x01, 0x41,
        0x14, 0x01, 0x41,
        0x41,
        0x41,
        0x41,
        0x41,
        0x41,
        0x41,
        0x41,
        0x41,
        0x41,
        0x41,
        0x41,
        0x41
    };

    ASSERT_TRUE(binson_parser_init(&p, buffer2, sizeof(buffer2)));
    ASSERT_FALSE(binson_parser_verify(&p));
}

TEST(skip_object_in_array)
{
    uint8_t buffer[] = {
        0x40,
            0x14, 0x01, 0x41,
            0x42,
                0x14, 0x01, 0x41,
                0x14, 0x01, 0x41,
                0x40,
                    0x14, 0x01, 0x41,
                    0x14, 0x01, 0x41,
                0x41,
                0x14, 0x01, 0x41,
            0x43,
        0x41
    };
    binson_parser p;
    ASSERT_TRUE(binson_parser_init(&p, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field_ensure(&p, "A", BINSON_TYPE_ARRAY));
    ASSERT_TRUE(binson_parser_go_into_array(&p));
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_OBJECT);
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    ASSERT_FALSE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_leave_array(&p));

}

TEST(parse_to_array_end)
{

    binson_parser p;

    uint8_t buffer2[] = {
        0x40,
        0x14, 0x01, 0x41,
        0x42,
        0x14, 0x01, 0x41,
        0x14, 0x01, 0x41,
        0x14, 0x01, 0x41,
        0x43, /* "A": ["A","A","A"] */
        0x41
    };
    binson_parser_init(&p, buffer2, sizeof(buffer2));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_ID_ARRAY);
    ASSERT_TRUE(binson_parser_go_into_array(&p));
    ASSERT_TRUE(binson_parser_leave_array(&p));
    ASSERT_FALSE(binson_parser_next(&p));
    ASSERT_TRUE(p.error_flags == BINSON_ID_OK);
}

TEST(get_raw_object_in_array)
{
    binson_parser p;
    uint8_t buffer[] = {
        0x40,
        0x14, 0x01, 0x41,
        0x42,
            0x14, 0x01, 0x41,
            0x40,
                0x14, 0x01, 0x43,
                0x14, 0x01, 0x41,
                0x14, 0x01, 0x44,
                0x42, 0x43,
            0x41,
        0x43,
        0x41
    };
    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_ID_ARRAY);
    ASSERT_TRUE(binson_parser_go_into_array(&p));
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_ID_STRING);
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_type(&p) == BINSON_ID_OBJECT);
    bbuf raw;
    ASSERT_TRUE(binson_parser_get_raw(&p, &raw));
    ASSERT_TRUE(raw.bptr != NULL);
    binson_parser p2;
    ASSERT_TRUE(binson_parser_init(&p2, raw.bptr, raw.bsize));
    ASSERT_TRUE(binson_parser_verify(&p2));
    ASSERT_TRUE(binson_parser_go_into_object(&p2));
    ASSERT_TRUE(binson_parser_field_ensure(&p2, "C", BINSON_ID_STRING));
}

TEST(parse_to_object_end)
{
    binson_parser p;
    uint8_t buffer[] = {
        0x40,
        0x14, 0x01, 0x41,
        0x14, 0x01, 0x41,
        0x41
    };
    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_FALSE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_leave_object(&p));
}

TEST(object_after_empty_string_in_array)
{
    binson_parser p;
    uint8_t buffer[] = {
        0x40,
        0x14, 0x01, 0x41,
        0x42,
        0x14, 0x00,
        0x40,
        0x41,
        0x43,
        0x41
    };
    binson_parser_init(&p, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&p));
    binson_parser_go_into_object(&p);
    binson_parser_next(&p);
    ASSERT_TRUE(binson_parser_go_into_array(&p));
    ASSERT_TRUE(binson_parser_next_ensure(&p, BINSON_ID_STRING));
    ASSERT_TRUE(binson_parser_next_ensure(&p, BINSON_ID_OBJECT));
    ASSERT_TRUE(binson_parser_go_into_object(&p));

}

TEST(null_args)
{
    uint8_t buffer;
    binson_parser p;
    bbuf raw;
    ASSERT_FALSE(binson_parser_init_object(NULL, NULL, 0));
    ASSERT_FALSE(binson_parser_init_object(&p, NULL, 0));
    ASSERT_FALSE(binson_parser_init_object(NULL, &buffer, 0));

    ASSERT_FALSE(binson_parser_reset(NULL));
    ASSERT_FALSE(binson_parser_verify(NULL));
    ASSERT(binson_parser_get_depth(NULL) == 0);
    ASSERT_FALSE(binson_parser_next(NULL));
    ASSERT_FALSE(binson_parser_next_ensure(NULL, BINSON_ID_STRING));
    ASSERT_TRUE(BINSON_TYPE_NONE == binson_parser_get_type(NULL));

    ASSERT_FALSE(binson_parser_field_with_length(NULL, "A", 1));
    ASSERT_FALSE(binson_parser_field_with_length(&p, NULL, 1));
    ASSERT_FALSE(binson_parser_field_with_length(NULL, NULL, 1));

    ASSERT_FALSE(binson_parser_field_ensure(NULL, "A", BINSON_ID_STRING));
    ASSERT_FALSE(binson_parser_field_ensure(&p, NULL, BINSON_ID_STRING));
    ASSERT_FALSE(binson_parser_field_ensure(NULL, NULL, BINSON_ID_STRING));

    ASSERT_FALSE(binson_parser_go_into_object(NULL));
    ASSERT_FALSE(binson_parser_leave_object(NULL));
    ASSERT_FALSE(binson_parser_go_into_array(NULL));
    ASSERT_FALSE(binson_parser_leave_array(NULL));
    ASSERT_TRUE(binson_parser_get_name(NULL) == NULL);
    ASSERT_TRUE(binson_parser_get_string_bbuf(NULL) == NULL);
    ASSERT_FALSE(binson_parser_get_raw(NULL, &raw));
    ASSERT_FALSE(binson_parser_get_raw(&p, NULL));
    ASSERT_FALSE(binson_parser_get_raw(NULL, NULL));
    ASSERT_TRUE(binson_parser_get_integer(NULL) == 0);
    ASSERT_FALSE(binson_parser_get_boolean(NULL));
    ASSERT_TRUE(binson_parser_get_double(NULL) == 0.0f);
    ASSERT_TRUE(binson_parser_get_bytes_bbuf(NULL) == NULL);

}

TEST(get_raw_should_not_work_on_integer)
{
    uint8_t buffer[] = {
        0x40,
        0x14, 0x01, 0x41, 0x10, 0x00,
        0x41,
    };
    binson_parser p1;
    bbuf raw;
    binson_parser_init(&p1, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&p1));
    binson_parser_go_into_object(&p1);
    ASSERT_TRUE(binson_parser_field_ensure(&p1, "A", BINSON_TYPE_INTEGER));
    ASSERT_FALSE(binson_parser_get_raw(&p1, &raw));
    binson_parser_leave_object(&p1);

    ASSERT_FALSE(binson_parser_field_ensure(&p1, "B", BINSON_TYPE_INTEGER));
    ASSERT_FALSE(binson_parser_next_ensure(&p1, BINSON_TYPE_ARRAY));


}

TEST(object_first_element_in_array)
{
    /* [{"A":["A"]}] */
    uint8_t buffer[] = {
        0x42,
            0x40,
                0x14, 0x01, 0x41,
                0x42,
                0x14, 0x01, 0x41,
                0x43,
            0x41,
        0x43,
    };

    binson_parser p;
    bool found = false;

    ASSERT_TRUE(binson_parser_init_array(&p, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_verify(&p));


    ASSERT_TRUE(binson_parser_go_into_array(&p));

    while (binson_parser_next(&p)) {
        ASSERT_TRUE(binson_parser_go_into_object(&p));
        ASSERT_TRUE(binson_parser_field_ensure(&p, "A", BINSON_ID_ARRAY));
        ASSERT_TRUE(binson_parser_go_into_array(&p));
        while (binson_parser_next(&p)) {
            if (binson_parser_string_equals(&p, "A")) {
                found = true;
            }
        }
        ASSERT_TRUE(binson_parser_leave_array(&p));
        ASSERT_TRUE(binson_parser_leave_object(&p));

    }

    ASSERT_TRUE(binson_parser_leave_array(&p));
    ASSERT_TRUE(found);

}

TEST(optional_field)
{

    /*
        {
          "A": {
          },
          "classic": true,
          "evolved": false
        }
    */
    uint8_t with_optional[27] = { /* 4014014140411407636c617373696344140765766f6c7665644541*/
        0x40, 0x14, 0x01, 0x41, 0x40, 0x41, 0x14, 0x07,
        0x63, 0x6c, 0x61, 0x73, 0x73, 0x69, 0x63, 0x44,
        0x14, 0x07, 0x65, 0x76, 0x6f, 0x6c, 0x76, 0x65,
        0x64, 0x45, 0x41
    };

    /*
        {
          "A": {
            "classic": true
          },
          "evolved": false
        }
    */
    uint8_t without_optional[27] = { /* 401401414041140765766f6c7665644541*/
        0x40,
        0x14, 0x01, 0x41,
        0x40,
        0x14, 0x07, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x69, 0x63, 0x44,
        0x41,
        0x14, 0x07,
        0x65, 0x76, 0x6f, 0x6c, 0x76, 0x65, 0x64, 0x45,
        0x41
    };

    binson_parser p;
    binson_parser_init(&p, with_optional, sizeof(with_optional));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field(&p, "classic"));
    ASSERT_TRUE(binson_parser_get_boolean(&p));
    ASSERT_TRUE(binson_parser_field(&p, "evolved"));
    ASSERT_FALSE(binson_parser_get_boolean(&p));
    ASSERT_TRUE(binson_parser_leave_object(&p));

    binson_parser_init(&p, without_optional, sizeof(without_optional));
    ASSERT_TRUE(binson_parser_verify(&p));
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_FALSE(binson_parser_field(&p, "classic"));
    ASSERT_TRUE(binson_parser_field(&p, "evolved"));
    ASSERT_FALSE(binson_parser_get_boolean(&p));
    ASSERT_TRUE(binson_parser_leave_object(&p));

}

TEST(get_raw)
{
    /* {"A":[{"A":"A"}]} */
    uint8_t buffer[] = {
        0x40,
        0x14, 0x01, 0x41,
        0x42,
            0x40,
                0x14, 0x01, 0x41,
                0x42,
                0x14, 0x01, 0x41,
                0x43,
            0x41,
        0x43,
        0x41
    };

    binson_parser p;
    bbuf raw;

    ASSERT_TRUE(binson_parser_init(&p, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_verify(&p));

    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field(&p, "A"));
    ASSERT_TRUE(binson_parser_get_raw(&p, &raw));
    ASSERT_TRUE(raw.bsize == 12);
    ASSERT_TRUE(memcmp(raw.bptr, &buffer[4], 12) == 0);

    binson_parser_reset(&p);
    ASSERT_TRUE(binson_parser_go_into_object(&p));
    ASSERT_TRUE(binson_parser_field(&p, "A"));
    ASSERT_TRUE(binson_parser_go_into_array(&p));
    ASSERT_TRUE(binson_parser_next(&p));
    ASSERT_TRUE(binson_parser_get_raw(&p, &raw));
    ASSERT_TRUE(raw.bsize == 10);
    ASSERT_TRUE(memcmp(raw.bptr, &buffer[5], 10) == 0);
}

/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(valid_init);
    RUN_TEST(invalid_init_null_ptr);
    RUN_TEST(invalid_init_buffer_to_small);
    RUN_TEST(invalid_init_bad_format);
    RUN_TEST(parse_verify);
    RUN_TEST(parse_empty_object);
    RUN_TEST(parse_one_string);
    RUN_TEST(parse_bad_name_length);
    RUN_TEST(parse_integers16);
    RUN_TEST(parse_float);
    RUN_TEST(one_nested);
    RUN_TEST(bad_binson);
    RUN_TEST(parse_doubles);
    RUN_TEST(parse_bool);
    RUN_TEST(test_integer_pack);
    RUN_TEST(test_multi_nested);
    RUN_TEST(skip_object_in_array);
    RUN_TEST(parse_to_array_end);
    RUN_TEST(get_raw_object_in_array);
    RUN_TEST(parse_to_object_end);
    RUN_TEST(object_after_empty_string_in_array);
    RUN_TEST(null_args);
    RUN_TEST(get_raw_should_not_work_on_integer);
    RUN_TEST(object_first_element_in_array);
    RUN_TEST(optional_field);
    RUN_TEST(get_raw);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

