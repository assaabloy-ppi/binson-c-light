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

#include "binson_parser.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

static bool parse_binson(const uint8_t *buffer, uint32_t size, uint16_t depth);
static bool handle_type(binson_parser *p, binson_type type, uint16_t depth);

/*======= Global function implementations ===================================*/

bool fuzz_one_input(const uint8_t *data, size_t size)
{
    bool ret = parse_binson(data, size, 0);
    if (ret)
    {
    if (ret) {
            for (size_t i = 0; i < size; i++) {
                printf("%02x", data[i]);
            } printf("\r\n");
        }
    }
    return ret;
}

/*======= Local function implementations ====================================*/

#define VERIFY(x) if(!(x)) return false

static bool parse_binson(const uint8_t *buffer, uint32_t size, uint16_t depth)
{

    BINSON_PARSER_DEF(p);

    bbuf *prev_name = NULL;
    bbuf *current_name = NULL;

    binson_parser_init(&p, buffer, size);
    VERIFY(binson_parser_go_into_object(&p));

    printf("{");

    while (binson_parser_next(&p)) {

        binson_type type = binson_parser_get_type(&p);
        current_name = binson_parser_get_name(&p);

        VERIFY(current_name != NULL);
        VERIFY(current_name->bptr != NULL && current_name->bsize > 0);

        if (prev_name != NULL) {
            printf(",");
            printf("\r\n");
        }

        printf("\"%*.*s\":", 0, (int) current_name->bsize, (const char *) current_name->bptr);
        VERIFY(handle_type(&p, type, depth));

        prev_name = current_name;

    }

    VERIFY(binson_parser_leave_object(&p));
    

    printf("}");

    VERIFY(p.error_flags = BINSON_ERROR_NONE);

    return true;
}

static bool handle_type(binson_parser *p, binson_type type, uint16_t depth)
{
    bbuf    raw_val;
    bbuf    *ptr_val;
    bool    bool_val = 0;
    double  double_val = 0;
    int64_t int_val = 0;

    switch (type) {
        case BINSON_TYPE_OBJECT:
            VERIFY(binson_parser_get_raw(p, &raw_val));
            VERIFY(parse_binson(raw_val.bptr, raw_val.bsize, depth+1));
            break;
        case BINSON_TYPE_ARRAY:
            VERIFY(binson_parser_go_into_array(p));
            printf("[");
            bool_val = false;
            while (binson_parser_next(p)) {
                if (bool_val) {
                    printf(",");
                }
                VERIFY(handle_type(p, binson_parser_get_type(p), depth+1));
                bool_val = true;
            }
            printf("]");
            VERIFY(binson_parser_leave_array(p));
            break;
        case BINSON_TYPE_BOOLEAN:
            bool_val = binson_parser_get_boolean(p);
            printf("%s", (bool_val) ? "true" : "false");
            break;
        case BINSON_TYPE_DOUBLE:
            double_val = binson_parser_get_double(p);
            printf("%f", double_val);
            break;
        case BINSON_TYPE_INTEGER:
            int_val = binson_parser_get_integer(p);
            printf("%d", (int) int_val);
            break;
        case BINSON_TYPE_STRING:
            ptr_val = binson_parser_get_string_bbuf(p);
            VERIFY(ptr_val->bptr != NULL);
            printf("\"%*.*s\"", 0, (int) ptr_val->bsize, (const char *) ptr_val->bptr);
            break;
        case BINSON_TYPE_BYTES:
            ptr_val = binson_parser_get_bytes_bbuf(p);
            VERIFY(ptr_val != NULL);
            VERIFY(ptr_val->bptr != NULL);
            printf("0x");
            for (size_t i = 0; i < ptr_val->bsize; i++) {
                printf("%02x", ptr_val->bptr[i]);
            }
            break;
        case BINSON_TYPE_NONE:
        default:
            return false;

    }

    return true;
}
