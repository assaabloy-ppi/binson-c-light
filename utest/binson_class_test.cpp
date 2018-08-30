/**
 * @file binson_class_test.c
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

#include <binson.hpp>
#include "utest.h"
#include <vector>

/*======= Local Macro Definitions ===========================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

using namespace std;

static char convert(char c)
{
    if (c >= ' ' && c < 127)
        return c;
    else
        return '~';
}

static string dump_compare_hex(const uint8_t *data, const uint8_t *data2, size_t size)
{
    string res;

    for (size_t i = 0 ;  i < size ; i++)
    {
        char buf[20];
        sprintf(buf, "%02x(%c) %02x(%c)  %s\n",
                (unsigned)data[i],
                (unsigned)convert(data[i]),
                (unsigned)data2[i],
                (unsigned)convert(data2[i]),
                data[i] == data2[i] ? "=" :  "E" );
        res.append(buf);
    }
    return res;
}

/*======= Test cases ========================================================*/

TEST(binson_class_test1)
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
    uint8_t binson_bytes[105] = "\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x40\x14\x01\x41\x14\x01\x42\x41\x14\x01\x43\x42\x14\x01\x41\x14\x01\x41\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x42\x14\x01\x41\x14\x01\x41\x40\x14\x01\x41\x14\x01\x42\x41\x42\x42\x42\x42\x40\x14\x01\x41\x14\x01\x42\x41\x43\x43\x43\x43\x43\x41\x14\x01\x41\x43\x14\x01\x44\x46\x18\x2d\x44\x54\xfb\x21\x09\x40\x14\x01\x45\x45\x14\x01\x46\x10\x7f\x14\x01\x47\x18\x02\x02\x02\x41";
    size_t binson_expected_size = sizeof(binson_bytes) - 1;
    binson_parser p;
    ASSERT_TRUE(binson_parser_init(&p, binson_bytes, binson_expected_size));
    ASSERT_TRUE(binson_parser_verify(&p));

    Binson b;
    binson_parser_reset(&p);
    ASSERT_TRUE(b.deserialize(&p));

    binson_writer w;
    uint8_t binson_result_buffer[1000];
    ASSERT_TRUE(binson_writer_init(&w, binson_result_buffer, sizeof(binson_result_buffer)));
    b.serialize(&w);
//    string s = b.toStr();
//    printf("%s\n", s.c_str());
    ASSERT_TRUE(binson_writer_get_counter(&w) == binson_expected_size);
    bool result = memcmp(binson_bytes, binson_result_buffer, binson_expected_size) == 0;
    if (!result)
    {
        printf("%s\n", dump_compare_hex(binson_bytes,
                                        binson_result_buffer,
                                        binson_expected_size).c_str());
    }

    ASSERT_TRUE(result);

    ASSERT_TRUE(b.get("A").getString() == string("B"));
    ASSERT_TRUE(b.get("B").getObject().get("A").getString() == string("B"));
    ASSERT_TRUE(b.get("C").getArray()[0].getString() == string("A"));
    ASSERT_TRUE(b.get("C")
                .getArray()[2]
                .getObject()
                .get("B")
                .getArray()[3]
                .getArray()[0]
                .getArray()[0]
                .getArray()[0]
                .getArray()[0]
                .getObject()
                .get("A")
                .getString() == string("B"));
    ASSERT_TRUE(b.get("D").getDouble() == 3.141592653589793);
    ASSERT_TRUE(b.get("E").getBool() == false);
    ASSERT_TRUE(b.get("F").getInt() == 127);
    ASSERT_TRUE(b.get("G").getBin() == vector<uint8_t>({0x02, 0x02}));

    Binson b2;
    b2.put("A", "B");
    b2.put("B", Binson().put("A", "B"));

    b2.put("C", vector<BinsonValue>({
                                        "A",
                                        "A",
                                        Binson().put("A","B")
                                        .put("B", vector<BinsonValue>({
                                            "A",
                                            "A",
                                            Binson().put("A", "B"),
                                            vector<BinsonValue>({
                                                vector<BinsonValue>({
                                                    vector<BinsonValue>({
                                                        vector<BinsonValue>({
                                                            Binson().put("A", "B")
                                                        })
                                                    })
                                                })
                                            })
                                        })),
                                        "A"
                                    })
           );
    b2.put("D", 3.141592653589793);
    b2.put("E", false);
    b2.put("F", 127);
    b2.put("G", vector<uint8_t>({0x02, 0x02}));

    ASSERT_TRUE(binson_writer_init(&w, binson_result_buffer, sizeof(binson_result_buffer)));
    b2.serialize(&w);
//    string s = b.toStr();
//    printf("%s\n", s.c_str());
//    s = b2.toStr();
//    printf("%s\n", s.c_str());
    result = memcmp(binson_bytes, binson_result_buffer, binson_expected_size) == 0;
    if (!result)
    {
        printf("%s\n", dump_compare_hex(binson_bytes,
                                        binson_result_buffer,
                                        binson_expected_size).c_str());
    }
    ASSERT_TRUE(binson_writer_get_counter(&w) == binson_expected_size);

}


/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(binson_class_test1);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

