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

TEST(verify_empty_object)
{
    uint8_t buffer[2] = { 0x40, 0x41 };
    BINSON_PARSER_DEF(p);
    ASSERT_TRUE(binson_parser_init(&p, buffer, sizeof(buffer)));
    ASSERT_TRUE(binson_parser_verify(&p));
}

TEST(verify_object_with_string)
{
    BINSON_PARSER_DEF(parser);
    uint8_t buffer[8] = { /* 4014014114014241*/
        0x40, 0x14, 0x01, 0x41, 0x14, 0x01, 0x42, 0x41
    };

    binson_parser_init(&parser, buffer, sizeof(buffer));
    ASSERT_TRUE(binson_parser_verify(&parser));
}

TEST(verify_with_only_field_name)
{
    BINSON_PARSER_DEF(parser);
    uint8_t buffer[4] = { 0x40, 0x14, 0x00, 0x41 };
    binson_parser_init(&parser, buffer, sizeof(buffer));
    ASSERT_FALSE(binson_parser_verify(&parser));
}

TEST(verify_complex_object)
{
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
    uint8_t binson_bytes[104] = "\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x40\x14\x01\x41\x14\x01\x42\x41\x14\x01\x43\x42\x14\x01\x41\x14\x01\x41\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x42\x14\x01\x41\x14\x01\x41\x40\x14\x01\x41\x14\x01\x42\x41\x42\x42\x42\x42\x40\x14\x01\x41\x14\x01\x42\x41\x43\x43\x43\x43\x43\x41\x14\x01\x41\x43\x14\x01\x44\x46\x18\x2d\x44\x54\xfb\x21\x09\x40\x14\x01\x45\x45\x14\x01\x46\x10\x7f\x14\x01\x47\x18\x02\x02\x02\x41";
    BINSON_PARSER_DEF(p);
    ASSERT_TRUE(binson_parser_init(&p, binson_bytes, sizeof(binson_bytes)));
    ASSERT_TRUE(binson_parser_verify(&p));
}


/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(verify_empty_object);
    RUN_TEST(verify_object_with_string);
    RUN_TEST(verify_with_only_field_name);
    RUN_TEST(verify_complex_object);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

