/**
 * @file binson_parser.c
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include <stdio.h>
#include <string.h>

#include "binson_parser.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Type Definitions ==================================================*/

#define BINSON_PTYPE_OBJECT                 (0x01U)
#define BINSON_PTYPE_ARRAY                  (0x02U)

#define BINSON_STATE_UNDEFINED              (0x0000U)
#define BINSON_STATE_IN_OBJ_EXPECTING_FIELD (0x0001U)
#define BINSON_STATE_IN_OBJ_EXPECTING_VALUE (0x0002U)
#define BINSON_STATE_IN_OBJECT              (0x0003U)
#define BINSON_STATE_IN_ARRAY_1             (0x0004U)
#define BINSON_STATE_IN_ARRAY_2             (0x0008U)
#define BINSON_STATE_IN_ARRAY               (0x000CU)

/* Next state after processing one item. */
#define BINSON_STATE_PARSED_STRING          (0x0010U)
#define BINSON_STATE_PARSED_BOOLEAN         (0x0020U)
#define BINSON_STATE_PARSED_DOUBLE          (0x0040U)
#define BINSON_STATE_PARSED_INTEGER         (0x0080U)
#define BINSON_STATE_PARSED_BYTES           (0x0100U)
#define BINSON_STATE_PARSED_OBJECT_BEGIN    (0x0200U)
#define BINSON_STATE_PARSED_OBJECT_END      (0x0400U)
#define BINSON_STATE_PARSED_ARRAY_BEGIN     (0x0800U)
#define BINSON_STATE_PARSED_ARRAY_END       (0x1000U)
#define BINSON_STATE_ERROR                  (0x2000U)
#define BINSON_STATE_PARSED_FIELD_NAME      (0x8000U)

#define BINSON_STATE_VALUE_FLAG             (0x0BF0U)

#define BINSON_ADVANCE_VERIFY               (0x01U)
#define BINSON_ADVANCE_ENTER_OBJECT         (0x02U)
#define BINSON_ADVANCE_LEAVE_OBJECT         (0x04U)
#define BINSON_ADVANCE_ENTER_ARRAY          (0x08U)
#define BINSON_ADVANCE_LEAVE_ARRAY          (0x10U)
#define BINSON_ADVANCE_VALUE                (0x20U)

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define SETBITMASK(x, y)    ((x) |= (y))        /* Set bitmask y in byte x*/
#define CLEARBITMASK(x, y)  ((x) &= (~(y)))     /* Clear bitmask y in byte x*/
#define CHECKBITMASK(x, y)  (((x) & (y)) > 0)   /* Check if any bit in bitmask y is set in byte x*/
#define VERIFYBITMASK(x, y) ((x) == (y))        /* Verify that bits are equal. */

/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

static bool _parse_integer(bbuf *length_data, int64_t *value, bool check_boundaries);
static int _cmp_name(bbuf *a, bbuf *b);
#define _advance(p, s) _advance_parsing(p, s, NULL)
static bool _advance_parsing(binson_parser *parser, uint8_t scan_flags, bbuf *scan_name);
static bool _consume(binson_parser *parser,
                     bbuf *data,
                     size_t size,
                     bool peek);
static bool _check_boundary(size_t a,
                            size_t b,
                            size_t max);

/*======= Global function implementations ===================================*/

bool binson_parser_init_object(binson_parser *parser,
                               const uint8_t *buffer,
                               size_t buffer_size)
{
    if ((NULL == parser) ||
        (NULL == buffer) ||
        (NULL == parser->state) ||
        (0 == parser->max_depth)) {
        return false;
    }

    /*
     * Minimum object size is 2 bytes for an empty
     * object: { }
     */
    if (buffer_size < BINSON_OBJECT_MINIMUM_SIZE) {
        parser->error_flags = BINSON_ERROR_RANGE;
        return false;
    }

    /*
     * The serialized binson object must begin and end correctly:
     * object = { ... }
     */
    if (!((BINSON_DEF_OBJECT_BEGIN == buffer[0]) &&
          (BINSON_DEF_OBJECT_END == buffer[buffer_size-1]))) {
        parser->error_flags = BINSON_ERROR_FORMAT;
        return false;
    }

    memset(parser->state, 0x00U, (sizeof(binson_state)*parser->max_depth));
    parser->buffer_used = 0;
    parser->buffer      = buffer;
    parser->buffer_size = buffer_size;
    parser->error_flags = BINSON_ERROR_NONE;

    parser->type            = BINSON_PTYPE_OBJECT;
    parser->depth           = 0;
    parser->buffer_used     = 0;
    parser->state[0].flags  = BINSON_STATE_UNDEFINED;
    parser->current_state = &parser->state[0];

    return true;
}

bool binson_parser_init_array(binson_parser *parser,
                              const uint8_t *buffer,
                              size_t buffer_size)
{
    if ((NULL == parser) ||
        (NULL == buffer) ||
        (NULL == parser->state) ||
        (0 == parser->max_depth)) {
        return false;
    }

    /*
     * Minimum object size is 2 bytes for an empty
     * object: { }
     */
    if (buffer_size < BINSON_OBJECT_MINIMUM_SIZE) {
        parser->error_flags = BINSON_ERROR_RANGE;
        return false;
    }

    /*
     * The serialized binson object must begin and end correctly:
     * array = [ ... ]
     */
    if (!((BINSON_DEF_ARRAY_BEGIN == buffer[0]) &&
          (BINSON_DEF_ARRAY_END == buffer[buffer_size-1]))) {
        parser->error_flags = BINSON_ERROR_FORMAT;
        return false;
    }

    memset(parser->state, 0x00U, (sizeof(binson_state)*parser->max_depth));
    parser->buffer_used = 0;
    parser->buffer      = buffer;
    parser->buffer_size = buffer_size;
    parser->error_flags = BINSON_ERROR_NONE;

    parser->type            = BINSON_PTYPE_ARRAY;
    parser->depth           = 1;
    parser->buffer_used     = 0;
    parser->state[0].flags  = BINSON_STATE_UNDEFINED;
    parser->current_state = &parser->state[0];

    return true;

}

bool binson_parser_reset(binson_parser *parser)
{
    if (NULL == parser) {
        return false;
    }

    bool ret;

    if (parser->type == BINSON_TYPE_OBJECT) {
        ret = binson_parser_init_object(parser, parser->buffer, parser->buffer_size);
    }
    else {
        ret = binson_parser_init_array(parser, parser->buffer, parser->buffer_size);
    }

    return ret;

}

bool binson_parser_verify(binson_parser *parser)
{
    if (NULL == parser) {
        return false;
    }

    if (!binson_parser_reset(parser)) {
        return false;
    }

    bool ret = _advance(parser, BINSON_ADVANCE_VERIFY);
    ret = ((false == ret) && (BINSON_ERROR_NONE == parser->error_flags));

    binson_parser_reset(parser);
    return ret;
}

size_t binson_parser_get_depth(binson_parser *parser)
{
    return (NULL != parser) ? parser->depth : 0;
}

bool binson_parser_next(binson_parser *parser)
{
    if (NULL == parser) {
        return false;
    }

    return _advance(parser, BINSON_ADVANCE_VALUE);
}

bool binson_parser_next_ensure(binson_parser *parser, binson_type field_type)
{
    if (NULL == parser) {
        return false;
    }

    if (!binson_parser_next(parser)) {
        return false;
    }

    if (parser->current_state->current_type != field_type) {
        parser->error_flags = BINSON_ERROR_WRONG_TYPE;
        return false;
    }

    return true;
}

binson_type binson_parser_get_type(binson_parser *parser)
{
    if ((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state)) {
        return parser->current_state->current_type;
    }

    return BINSON_TYPE_NONE;
}

bool binson_parser_field_with_length(binson_parser *parser, const char *field_name, size_t length)
{
    if (NULL == parser) {
        return false;
    }

    if (NULL == field_name) {
        parser->error_flags = BINSON_ERROR_NULL;
        return false;
    }

    bbuf scan_name;
    scan_name.bptr = (const uint8_t *) field_name;
    scan_name.bsize = length;
    int r;

    while (_advance_parsing(parser, BINSON_ADVANCE_VALUE, &scan_name)) {
        r = _cmp_name(&scan_name, &parser->current_state->current_name);
        if (0 == r) {
            return true;
        }
        else if (r < 0) {
            break;
        }
    }

    return false;
}


bool binson_parser_field_ensure_with_length(binson_parser *parser,
                                            const char *field_name,
                                            size_t length,
                                            binson_type field_type)
{

    if ((NULL != parser) &&
        binson_parser_field_with_length(parser, field_name, length)) {
        if (field_type == binson_parser_get_type(parser)) {
            return true;
        }
        parser->error_flags = BINSON_ERROR_WRONG_TYPE;
    }

    return false;
}


bool binson_parser_go_into_object(binson_parser *parser)
{
    if (NULL == parser) {
        return false;
    }

    return _advance(parser, BINSON_ADVANCE_ENTER_OBJECT);
}

bool binson_parser_leave_object(binson_parser *parser)
{
    if (NULL == parser) {
        return false;
    }

    binson_state *state = &parser->state[(parser->depth > 0) ? parser->depth - 1 : 0];
    if (!CHECKBITMASK(state->flags, BINSON_STATE_IN_OBJECT)) {
        return false;
    }

    bool ret = _advance(parser, BINSON_ADVANCE_LEAVE_OBJECT);
    if (!ret) {
        return (parser->error_flags == BINSON_ERROR_NONE);
    }
    return ret;

}

bool binson_parser_go_into_array(binson_parser *parser)
{
    if (NULL == parser) {
        return false;
    }

    return _advance(parser, BINSON_ADVANCE_ENTER_ARRAY);
}

bool binson_parser_leave_array(binson_parser *parser)
{
    if (NULL == parser) {
        return false;
    }

    binson_state *state = &parser->state[(parser->depth > 0) ? parser->depth - 1 : 0];
    if (!CHECKBITMASK(state->flags, BINSON_STATE_IN_ARRAY)) {
        return false;
    }

    bool ret = _advance(parser, BINSON_ADVANCE_LEAVE_ARRAY);
    if (!ret) {
        return (parser->error_flags == BINSON_ERROR_NONE);
    }
    return ret;
}

bbuf *binson_parser_get_name(binson_parser *parser)
{
    if ((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state)) {
        return &parser->current_state->current_name;
    }
    return NULL;
}

bbuf *binson_parser_get_string_bbuf(binson_parser *parser)
{
    if ((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state) &&
        (BINSON_TYPE_STRING == parser->current_state->current_type)) {
        return &parser->current_state->current_value.string_value;
    }
    return NULL;
}

bool binson_parser_get_raw(binson_parser *parser, bbuf *raw)
{
    if (!((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state))) {
        return NULL;
    }

    size_t current_pos = parser->buffer_used;
    raw->bptr = &parser->buffer[parser->buffer_used];

    if (parser->current_state->current_type == BINSON_TYPE_OBJECT) {

        if (_advance(parser, BINSON_ADVANCE_ENTER_OBJECT) &&
            _advance(parser, BINSON_ADVANCE_LEAVE_OBJECT)) {
            raw->bsize = parser->buffer_used - current_pos;
            return true;
        }

        return false;

    }

    else if (parser->current_state->current_type == BINSON_TYPE_ARRAY) {
        if (_advance(parser, BINSON_ADVANCE_ENTER_ARRAY) &&
            _advance(parser, BINSON_ADVANCE_LEAVE_ARRAY)) {
            raw->bsize = parser->buffer_used - current_pos;
            return true;
        }

        return false;
    }

    return false;

}

int64_t binson_parser_get_integer(binson_parser *parser)
{
    if ((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state) &&
        (BINSON_TYPE_INTEGER == parser->current_state->current_type)) {
        return parser->current_state->current_value.integer_value;
    }

    return 0;
}

bool binson_parser_get_boolean(binson_parser *parser)
{
    if ((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state) &&
        (BINSON_TYPE_BOOLEAN == parser->current_state->current_type)) {
        return parser->current_state->current_value.bool_value;
    }

    return false;
}

double binson_parser_get_double(binson_parser *parser)
{
    if ((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state) &&
        (BINSON_TYPE_DOUBLE == parser->current_state->current_type)) {
        return parser->current_state->current_value.double_value;
    }


    return 0.0f;
}

bbuf *binson_parser_get_bytes_bbuf(binson_parser *parser)
{
    if ((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state) &&
        (BINSON_TYPE_BYTES == parser->current_state->current_type)) {
        return &parser->current_state->current_value.bytes_value;
    }
    return NULL;
}

bool binson_parser_string_equals(binson_parser *parser, const char *pstr)
{
    bbuf cmp;
    if (!((NULL != parser) &&
        (BINSON_ERROR_NONE == parser->error_flags) &&
        (NULL != parser->current_state) &&
        (BINSON_TYPE_STRING == parser->current_state->current_type))) {
        return false;
    }

    cmp.bptr = (const uint8_t *) pstr;
    cmp.bsize = strlen(pstr);
    return _cmp_name(&parser->current_state->current_value.string_value, &cmp) == 0;
}

static void _binson_print_cb(binson_parser *parser, uint16_t next_state, void *context)
{

    binson_state *state = parser->current_state;
    uint8_t *pstate = (uint8_t *) context;

    if (next_state != BINSON_STATE_PARSED_ARRAY_END && *pstate == 0x05) {
        printf(",");
    }

    if (*pstate == 0x04) {
        *pstate = 0x05;
    }

    switch (next_state)
    {
        case BINSON_STATE_PARSED_OBJECT_BEGIN:
            *pstate = 0x01;
            printf("{");
            break;
        case BINSON_STATE_PARSED_OBJECT_END:
            if (state->array_depth > 0) {
                *pstate = 0x05;
            }
            printf("}");
            break;
        case BINSON_STATE_PARSED_ARRAY_BEGIN:
            *pstate = 0x04;
            printf("[");
            break;
        case BINSON_STATE_PARSED_ARRAY_END:
            if (state->array_depth == 0) {
                *pstate = 0x02;
            }
            printf("]");
            break;
        case BINSON_STATE_PARSED_FIELD_NAME:
            if (*pstate == 0x02) {
                printf(",");
            }
            *pstate = 0x02;
            printf("\"%*.*s\":", 0, (int) state->current_name.bsize, (const char* ) parser->current_state->current_name.bptr);
            break;
        case BINSON_STATE_PARSED_STRING:
            printf("\"%*.*s\"", 0, (int) state->current_value.string_value.bsize, (const char* ) state->current_value.string_value.bptr);
            break;
        case BINSON_STATE_PARSED_BOOLEAN:
            printf("%s", (state->current_value.bool_value) ? "true" : "false");
            break;
        case BINSON_STATE_PARSED_DOUBLE:
            printf("%lf", state->current_value.double_value);
            break;
        case BINSON_STATE_PARSED_INTEGER:
            printf("%" PRId64 "", state->current_value.integer_value);
            break;
        case BINSON_STATE_PARSED_BYTES:
            printf("\"0x");
            size_t i;
            for (i = 0; i < state->current_value.bytes_value.bsize; i++) {
                printf("%02x", state->current_value.bytes_value.bptr[i]);
            }
            printf("\"");
            break;

    }

}

bool binson_parser_print(binson_parser *parser)
{
    if (NULL == parser) {
        return false;
    }
    uint8_t pstate = 0x00;
    parser->cb_context = &pstate;
    parser->cb = _binson_print_cb;
    bool ret = binson_parser_verify(parser);
    parser->cb = NULL;
    parser->cb_context = NULL;
    return ret;
}

struct _to_string_ctx {
    char *buffer;
    size_t buffer_size;
    size_t buffer_used;
    uint8_t pstate;
    bool nice;
    bool buffer_full;
};

static void _binson_to_string_cb(binson_parser *parser, uint16_t next_state, void *context)
{

    binson_state *state = parser->current_state;
    struct _to_string_ctx *ctx = (struct _to_string_ctx *) context;
    uint8_t *pstate = &ctx->pstate;
    char *pbuf = &ctx->buffer[ctx->buffer_used];

    if (ctx->buffer_full || ctx->buffer_used >= ctx->buffer_size) {
        return;
    }

    size_t available = ctx->buffer_size - ctx->buffer_used;
    size_t ret = 0;

    if (next_state != BINSON_STATE_PARSED_ARRAY_END && *pstate == 0x05) {
        ret = snprintf(pbuf, available, ",");
        if (!_check_boundary(ctx->buffer_used, ret, ctx->buffer_size)) {
            ctx->buffer_full = true;
            return;
        }
        ctx->buffer_used += ret;
        pbuf = &ctx->buffer[ctx->buffer_used];
    }

    if (*pstate == 0x04) {
        *pstate = 0x05;
    }

    switch (next_state)
    {
        case BINSON_STATE_PARSED_OBJECT_BEGIN:
            *pstate = 0x01;
            ret = snprintf(pbuf, available, "{");
            break;
        case BINSON_STATE_PARSED_OBJECT_END:
            if (state->array_depth > 0) {
                *pstate = 0x05;
            }
            ret = snprintf(pbuf, available, "}");
            break;
        case BINSON_STATE_PARSED_ARRAY_BEGIN:
            *pstate = 0x04;
            ret = snprintf(pbuf, available, "[");
            break;
        case BINSON_STATE_PARSED_ARRAY_END:
            if (state->array_depth == 0) {
                *pstate = 0x02;
            }
            ret = snprintf(pbuf, available, "]");
            break;
        case BINSON_STATE_PARSED_FIELD_NAME:
            if (*pstate == 0x02) {
                ret = snprintf(pbuf, available, ",");
                if (!_check_boundary(ctx->buffer_used, ret, ctx->buffer_size)) {
                    ctx->buffer_full = true;
                    return;
                }
                ctx->buffer_used += ret;
                pbuf = &ctx->buffer[ctx->buffer_used];
            }
            *pstate = 0x02;
            ret = snprintf(pbuf, available, "\"%*.*s\":", 0, (int) state->current_name.bsize, (const char* ) parser->current_state->current_name.bptr);
            break;
        case BINSON_STATE_PARSED_STRING:
            ret = snprintf(pbuf, available, "\"%*.*s\"", 0, (int) state->current_value.string_value.bsize, (const char* ) state->current_value.string_value.bptr);
            break;
        case BINSON_STATE_PARSED_BOOLEAN:
            ret = snprintf(pbuf, available, "%s", (state->current_value.bool_value) ? "true" : "false");
            break;
        case BINSON_STATE_PARSED_DOUBLE:
            ret = snprintf(pbuf, available, "%lf", state->current_value.double_value);
            break;
        case BINSON_STATE_PARSED_INTEGER:
            ret = snprintf(pbuf, available, "%" PRId64 "", state->current_value.integer_value);
            break;
        case BINSON_STATE_PARSED_BYTES:
            ret = snprintf(pbuf, available, "\"0x");
            if (!_check_boundary(ctx->buffer_used, ret, ctx->buffer_size)) {
                ctx->buffer_full = true;
                return;
            }
            ctx->buffer_used += ret;
            pbuf = &ctx->buffer[ctx->buffer_used];
            if ((state->current_value.bytes_value.bsize > (SIZE_MAX/2)) &&
                !_check_boundary(ctx->buffer_used, (state->current_value.bytes_value.bsize*2) + 1, ctx->buffer_size)) {
                ctx->buffer_full = true;
                return;
            }
            ret = 0;
            size_t i;
            for (i = 0; i < state->current_value.bytes_value.bsize; i++) {
                ret += snprintf(&pbuf[ret], available, "%02x", state->current_value.bytes_value.bptr[i]);
            }
            ret += snprintf(&pbuf[ret], available, "\"");
            break;

    }


    if (!_check_boundary(ctx->buffer_used, ret, ctx->buffer_size)) {
        ctx->buffer_full = true;
        return;
    }

    ctx->buffer_used += ret;

}

bool binson_parser_to_string(binson_parser *parser,
                             char *pbuf,
                             size_t *buf_size,
                             bool nice)
{
    if (NULL == parser || NULL == pbuf || NULL == buf_size) {
        return false;
    }

    struct _to_string_ctx ctx;
    ctx.buffer = pbuf;
    ctx.buffer_size = *buf_size;
    ctx.buffer_used = 0;
    ctx.pstate = 0;
    ctx.nice = nice;
    ctx.buffer_full = false;

    parser->cb_context = &ctx;
    parser->cb = _binson_to_string_cb;
    bool ret = binson_parser_verify(parser);
    parser->cb = NULL;
    parser->cb_context = NULL;
    if (ret && !ctx.buffer_full) {
        *buf_size = ctx.buffer_used;
        return true;
    }
    return false;
}

/*======= Local function implementations ====================================*/



static bool _parse_integer(bbuf *length_data, int64_t *value, bool check_boundaries)
{
    /* prefill with ones or zeroes depending of sign presence */
    uint64_t ui64 = (length_data->bptr[length_data->bsize - 1] & 0x80) ? ~0ULL : 0;
    size_t i;

    for (i = length_data->bsize; i > 0; i--) {
        ui64 <<= 8;
        ui64 |= length_data->bptr[i-1];
    }

    *value = (int64_t) ui64;

    if (!check_boundaries) {
        if (length_data->bsize != 8) {
            return false;
        }
        return true;
    }

    if ((*value >= INT8_MIN && *value <= INT8_MAX) && length_data->bsize == 1) {
        return true;
    }

    else if (length_data->bsize == 2 && (*value < INT8_MIN || *value > INT8_MAX)) {
        return true;
    }

    else if (length_data->bsize == 4 && (*value < INT16_MIN || *value > INT16_MAX)) {
        return true;
    }

    else if (length_data->bsize == 8 && (*value < INT32_MIN || *value > INT32_MAX)) {
        return true;
    }

    return false;
}

static int _cmp_name(bbuf *a, bbuf *b)
{
    int r = memcmp(a->bptr,
                   b->bptr,
                   MIN(a->bsize, b->bsize));

    return (r == 0) ? (int) (a->bsize - b->bsize) : r;
}

static uint16_t _process_one(binson_parser *parser, bbuf *consumed, size_t *bytes_consumed)
{
    size_t to_consume = 1;
    int64_t length_value;
    uint16_t next_state = BINSON_STATE_ERROR;
    uint8_t type;

    /* Prior usage of _consume in _advance holds next data byte */
    parser->buffer_used += 1;
    *bytes_consumed = 1;
    switch (consumed->bptr[0]) {
        /*
         * Handeled by the peek in _advance
         *
         * case BINSON_DEF_OBJECT_BEGIN:
         * case BINSON_DEF_OBJECT_END:
         * case BINSON_DEF_ARRAY_BEGIN:
         * case BINSON_DEF_ARRAY_END:
         */
        case BINSON_DEF_TRUE:
        case BINSON_DEF_FALSE:
            next_state = BINSON_STATE_PARSED_BOOLEAN;
            break;
        case BINSON_DEF_DOUBLE:
            to_consume = 8;
            if (!_consume(parser, consumed, to_consume, false)) {
                /* Return code set by _consume. */
                break;
            }
            *bytes_consumed += 8;
            next_state = BINSON_STATE_PARSED_DOUBLE;
            break;
        case BINSON_DEF_INT8:
        case BINSON_DEF_INT16:
        case BINSON_DEF_INT32:
        case BINSON_DEF_INT64:

            /* Flag 0x03 will tell if the size is 1, 2, 4 or 8 bytes. */
            to_consume = 1U << (consumed->bptr[0] & 0x03U);
            if (!_consume(parser, consumed, to_consume, false)) {
                /* Return code set by _consume. */
                break;
            }
            *bytes_consumed += to_consume;
            next_state = BINSON_STATE_PARSED_INTEGER;
            break;
        case BINSON_DEF_STRINGLEN_INT8:
        case BINSON_DEF_STRINGLEN_INT16:
        case BINSON_DEF_STRINGLEN_INT32:
        case BINSON_DEF_BYTESLEN_INT8:
        case BINSON_DEF_BYTESLEN_INT16:
        case BINSON_DEF_BYTESLEN_INT32:

            type = consumed->bptr[0];

            /* Flag 0x03 will tell if the size is 1, 2, 4 or 8 bytes. */
            to_consume = 1U << (consumed->bptr[0] & 0x03U);
            if (!_consume(parser, consumed, to_consume, false)) {
                /* Return code set by _consume. */
                break;
            }

            *bytes_consumed += to_consume;

            if (!(_parse_integer(consumed, &length_value, true))) {
                parser->error_flags = BINSON_ERROR_FORMAT;
                break;
            }

            /*
             * A string or byte array is expected. The length must be
             * in the range 0 <= length <= INT32_MAX
             */
            if (!((0 <= length_value) && (length_value <= INT32_MAX))) {
                parser->error_flags = BINSON_ERROR_FORMAT;
                break;
            }



            if (!_consume(parser, consumed, (size_t) length_value, false)) {
                /* Return code set by _consume. */
                break;
            }

            *bytes_consumed += length_value;

            if (type < BINSON_DEF_BYTESLEN_INT8) {
                /* A string is expected. */
                next_state = BINSON_STATE_PARSED_STRING;
            }

            else {
                /* A byte array is expected. */
                next_state = BINSON_STATE_PARSED_BYTES;
            }

            break;
        default:
            parser->error_flags = BINSON_ERROR_FORMAT;
            break;
    }

    return next_state;

}

static bool _advance_parsing(binson_parser *parser, uint8_t scan_flags, bbuf *scan_name)
{

    if (BINSON_ERROR_NONE != parser->error_flags) {
        return false;
    }

    bbuf consumed;
    uint16_t next_state;
    size_t bytes_consumed = 0;
    bool proceed = true;
    binson_state *state = parser->current_state;
    uint_fast8_t orig_array_depth = state->array_depth;
    uint_fast8_t orig_object_depth = parser->depth;
    while (proceed) {

        proceed = false;
        state = &parser->state[(parser->depth > 0) ? parser->depth - 1 : 0];

        if (!_consume(parser, &consumed, 1, true)) {
            return false;
        }

        switch (consumed.bptr[0]) {
            case BINSON_DEF_OBJECT_BEGIN:
                next_state = BINSON_STATE_PARSED_OBJECT_BEGIN;
                state->current_type = BINSON_TYPE_OBJECT;
                break;
            case BINSON_DEF_OBJECT_END:
                next_state = BINSON_STATE_PARSED_OBJECT_END;
                break;
            case BINSON_DEF_ARRAY_BEGIN:
                next_state = BINSON_STATE_PARSED_ARRAY_BEGIN;
                state->current_type = BINSON_TYPE_ARRAY;
                break;
            case BINSON_DEF_ARRAY_END:
                next_state = BINSON_STATE_PARSED_ARRAY_END;
                break;
            default:
                next_state = _process_one(parser, &consumed, &bytes_consumed);
                break;
        }

        if (BINSON_STATE_ERROR == next_state) {
            /* Error code set from _process_one. */
            return false;
        }

        if (CHECKBITMASK(state->flags, BINSON_STATE_IN_OBJECT)) {

            if (CHECKBITMASK(state->flags, BINSON_STATE_IN_OBJ_EXPECTING_FIELD) &&
               (BINSON_STATE_PARSED_STRING == next_state)) {
                next_state = BINSON_STATE_PARSED_FIELD_NAME;
            }

            if (CHECKBITMASK(next_state, BINSON_STATE_VALUE_FLAG)) {
                if (CHECKBITMASK(state->flags, BINSON_STATE_IN_OBJ_EXPECTING_VALUE)) {
                    state->flags = BINSON_STATE_IN_OBJ_EXPECTING_FIELD;
                }
                else {
                    parser->error_flags = BINSON_ERROR_FORMAT;
                    return false;
                }
            }
        }

        if (CHECKBITMASK(state->flags, BINSON_STATE_IN_ARRAY)) {
            if ((orig_array_depth == state->array_depth) &&
                (orig_object_depth == parser->depth)) {

                /*
                 * When parsing BINSON_STATE_PARSED_OBJECT_BEGIN or BINSON_STATE_PARSED_ARRAY_BEGIN
                 * we toggle between state ARRAY_1 and ARRAY_2. This is to make sure the parser stops.
                 * At next advance we will enter the array/object.
                 */

                if ((next_state == BINSON_STATE_PARSED_OBJECT_BEGIN) ||
                    (next_state == BINSON_STATE_PARSED_ARRAY_BEGIN)) {
                    if (CHECKBITMASK(state->flags, BINSON_STATE_IN_ARRAY_1)) {
                        state->flags = BINSON_STATE_IN_ARRAY_2;
                        CLEARBITMASK(scan_flags, BINSON_ADVANCE_VALUE);
                    }
                    else {
                        state->flags = BINSON_STATE_IN_ARRAY_1;
                    }
                }
                else {
                    CLEARBITMASK(scan_flags, BINSON_ADVANCE_VALUE);
                }
            }
        }

        switch (next_state) {
            case BINSON_STATE_PARSED_OBJECT_BEGIN:

                /* Check if we should continue. */
                if (CHECKBITMASK(scan_flags, BINSON_ADVANCE_VERIFY |
                                             BINSON_ADVANCE_ENTER_OBJECT |
                                             BINSON_ADVANCE_VALUE |
                                             BINSON_ADVANCE_LEAVE_ARRAY |
                                             BINSON_ADVANCE_LEAVE_OBJECT)) {
                    CLEARBITMASK(scan_flags, BINSON_ADVANCE_ENTER_OBJECT);
                    parser->buffer_used += 1;
                    if (parser->depth < BINSON_PARSER_MAX_DEPTH) {
                        parser->depth++;
                        parser->current_state = &parser->state[parser->depth - 1];
                        state = parser->current_state;
                        state->flags = BINSON_STATE_IN_OBJ_EXPECTING_FIELD;
                    }
                    else {
                        parser->error_flags = BINSON_ERROR_MAX_DEPTH;
                        break;
                    }

                }
                else if (state->flags == BINSON_STATE_IN_OBJ_EXPECTING_FIELD) {
                    state->flags = BINSON_STATE_IN_OBJ_EXPECTING_VALUE;
                }
                break;
            case BINSON_STATE_PARSED_OBJECT_END:
                /*
                 * Object in MUST only occur if a field name is expected and
                 * if we are in an object.
                 */
                if (!CHECKBITMASK(state->flags, BINSON_STATE_IN_OBJ_EXPECTING_FIELD)) {
                    parser->error_flags = BINSON_ERROR_FORMAT;
                    break;
                }

                if (CHECKBITMASK(scan_flags, BINSON_ADVANCE_VERIFY |
                                             BINSON_ADVANCE_LEAVE_OBJECT |
                                             BINSON_ADVANCE_VALUE |
                                             BINSON_ADVANCE_LEAVE_ARRAY)) {
                    if (orig_object_depth == parser->depth) {
                        CLEARBITMASK(scan_flags, BINSON_ADVANCE_LEAVE_OBJECT);
                        if (CHECKBITMASK(scan_flags, BINSON_ADVANCE_VALUE)) {
                            return false;
                        }
                    }

                    parser->buffer_used += 1;
                    memset(parser->current_state, 0x00, sizeof(binson_state));
                    if (parser->depth > 1) {
                        parser->depth--;
                        parser->current_state = &parser->state[parser->depth - 1];
                    }
                    else if (parser->depth == 1) {
                        parser->depth--;
                        parser->current_state = &parser->state[0];
                        if (parser->buffer_used != parser->buffer_size) {
                            parser->error_flags = BINSON_ERROR_FORMAT;
                        }
                        if (NULL != parser->cb) {
                            parser->cb(parser, next_state, parser->cb_context);
                        }
                        return false;
                    }
                    else {
                        /* Shuld never happend. */
                        parser->error_flags = BINSON_ERROR_FORMAT;
                        return false;
                    }

                }
                else {
                    /* End of block */
                    return false;
                }
                break;
            case BINSON_STATE_PARSED_FIELD_NAME:
                if (state->current_name.bptr != NULL) {
                    int r = _cmp_name(&state->current_name, &consumed);

                    if (r >= 0) {
                        parser->error_flags = BINSON_ERROR_FORMAT;
                        break;
                    }

                }

                if ((orig_array_depth == state->array_depth) &&
                    (orig_object_depth == parser->depth)) {

                    if ((NULL != scan_name)) {
                        int r = _cmp_name(&consumed, scan_name);
                        if (r > 0) {
                            /* Reverse */
                            parser->buffer_used -= bytes_consumed;
                            state->flags = BINSON_STATE_IN_OBJ_EXPECTING_FIELD;
                            return false;
                        }
                    }

                    CLEARBITMASK(scan_flags, BINSON_ADVANCE_VALUE);
                }

                state->current_name.bptr = consumed.bptr;
                state->current_name.bsize = consumed.bsize;
                state->flags = BINSON_STATE_IN_OBJ_EXPECTING_VALUE;

                proceed = true;

                break;
            case BINSON_STATE_PARSED_ARRAY_BEGIN:

                if (state->array_depth >= UINT8_MAX) {
                    parser->error_flags = BINSON_ERROR_MAX_DEPTH;
                    break;
                }

                if (CHECKBITMASK(scan_flags, BINSON_ADVANCE_VERIFY |
                                             BINSON_ADVANCE_VALUE |
                                             BINSON_ADVANCE_ENTER_ARRAY |
                                             BINSON_ADVANCE_LEAVE_ARRAY |
                                             BINSON_ADVANCE_LEAVE_OBJECT)) {
                    CLEARBITMASK(scan_flags, BINSON_ADVANCE_ENTER_ARRAY);
                    parser->buffer_used += 1;
                    state->flags = BINSON_STATE_IN_ARRAY_1;
                    state->array_depth++;
                }
                else {
                    state->flags = BINSON_STATE_IN_OBJ_EXPECTING_VALUE;
                }
                break;
            case BINSON_STATE_PARSED_ARRAY_END:

                /* ARRAY_END is only allowed when in an array. */
                if (!CHECKBITMASK(state->flags, BINSON_STATE_IN_ARRAY)) {
                    parser->error_flags = BINSON_ERROR_FORMAT;
                    break;
                }

                if (CHECKBITMASK(scan_flags, BINSON_ADVANCE_VERIFY |
                                             BINSON_ADVANCE_VALUE |
                                             BINSON_ADVANCE_LEAVE_ARRAY |
                                             BINSON_ADVANCE_LEAVE_OBJECT)) {
                    if ((orig_object_depth == parser->depth) &&
                        (orig_array_depth == state->array_depth)) {
                        CLEARBITMASK(scan_flags, BINSON_ADVANCE_LEAVE_ARRAY);
                    }

                    if (state->array_depth == 0) {
                        /* Should never happend. */
                        parser->error_flags = BINSON_ERROR_FORMAT;
                        break;
                    }

                    state->array_depth--;
                    parser->buffer_used += 1;

                    if (state->array_depth == 0) {
                        state->flags = BINSON_STATE_IN_OBJ_EXPECTING_FIELD;
                        if (parser->type == BINSON_PTYPE_ARRAY && parser->depth == 1) {
                            if (parser->buffer_used != parser->buffer_size) {
                                parser->error_flags = BINSON_ERROR_FORMAT;
                            }
                            if (NULL != parser->cb) {
                                parser->cb(parser, next_state, parser->cb_context);
                            }
                            return false;
                        }
                    }

                }
                else {
                    /* End of block */
                    return false;
                }
                break;
            case BINSON_STATE_PARSED_STRING:
                state->current_type = BINSON_TYPE_STRING;
                state->current_value.string_value.bptr = consumed.bptr;
                state->current_value.string_value.bsize = consumed.bsize;
                break;
            case BINSON_STATE_PARSED_BYTES:
                state->current_type = BINSON_TYPE_BYTES;
                state->current_value.string_value.bptr = consumed.bptr;
                state->current_value.string_value.bsize = consumed.bsize;
                break;
            case BINSON_STATE_PARSED_INTEGER:
                if (!_parse_integer(&consumed, &state->current_value.integer_value, true)) {
                    parser->error_flags = BINSON_ERROR_FORMAT;
                    break;
                }
                state->current_type = BINSON_TYPE_INTEGER;
                break;
            case BINSON_STATE_PARSED_DOUBLE:
                if (!_parse_integer(&consumed, (int64_t *) &state->current_value.double_value, false)) {
                    parser->error_flags = BINSON_ERROR_FORMAT;
                    break;
                }
                state->current_type = BINSON_TYPE_DOUBLE;
                break;
            case BINSON_STATE_PARSED_BOOLEAN:
                state->current_value.bool_value = (consumed.bptr[0] == BINSON_DEF_TRUE);
                state->current_type = BINSON_TYPE_BOOLEAN;
                break;
            default:
                parser->error_flags = BINSON_ERROR_FORMAT;
                return false;
        }

        if (BINSON_ERROR_NONE != parser->error_flags) {
            return false;
        }

        if (NULL != parser->cb) {
            parser->cb(parser, next_state, parser->cb_context);
        }

        if (CHECKBITMASK(scan_flags, BINSON_ADVANCE_VERIFY |
                                     BINSON_ADVANCE_LEAVE_OBJECT |
                                     BINSON_ADVANCE_VALUE |
                                     BINSON_ADVANCE_LEAVE_ARRAY)) {
            proceed = true;
        }


    }

    return (BINSON_ERROR_NONE == parser->error_flags);
}

static bool _consume(binson_parser *parser,
                     bbuf *data,
                     size_t size,
                     bool peek)
{

    if (!_check_boundary(parser->buffer_used, size, parser->buffer_size)) {
        parser->error_flags = BINSON_ERROR_RANGE;
        return false;
    }

    data->bptr = &parser->buffer[parser->buffer_used];
    data->bsize = size;

    if (!peek) {
        parser->buffer_used += size;
    }

    return true;

}

static bool _check_boundary(size_t a,
                            size_t b,
                            size_t max)
{
    size_t c = a + b;

    if (c > max) {
        /* Boundary violated */
        return false;
    }

    else if (c < a) {
        /* Unsigned overflow */
        return false;
    }

    return true;
}
