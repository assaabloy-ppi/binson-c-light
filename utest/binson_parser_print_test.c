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

TEST(print_binson)
{
    BINSON_PARSER_DEF(p);
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_print(&p));
    /* Expected:
     * {"A":"B","B":{"A":"B"},"C":["A","A",{"A":"B","B":["A","A",{"A":"B"},[[[[{"A":"B"}]]]]]},"A"],"D":3.141593,"E":false,"F":127,"G":"0x0202"}
     * Actual:
     * {"A":"B","B":{"A":"B"},"C":["A","A",{"A":"B","B":["A","A",{"A":"B"},[[[[{"A":"B"}]]]]]},"A"],"D":3.141593,"E":false,"F":127,"G":"0x0202"}
     */
    char buffer[512];
    size_t size = sizeof(buffer);
    ASSERT_TRUE(binson_parser_to_string(&p, buffer, &size, false));
    printf("%*.*s", 0, (int) size, buffer);

    ASSERT_FALSE(binson_parser_print(NULL));
    ASSERT_FALSE(binson_parser_to_string(NULL, buffer, &size, false));
    ASSERT_FALSE(binson_parser_to_string(NULL, NULL, &size, false));
    ASSERT_FALSE(binson_parser_to_string(NULL, buffer, NULL, false));

    size_t to_small_size = 4;
    ASSERT_FALSE(binson_parser_to_string(&p, buffer, &to_small_size, false));

}

/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(print_binson);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

