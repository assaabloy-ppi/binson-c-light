#ifndef BINSON_LIGHT_H_INCLUDED
#define BINSON_LIGHT_H_INCLUDED

#ifdef WITH_TO_STRING
#include <stdio.h>
#endif

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/* clang-format off */

#ifdef __cplusplus
extern "C" {
#endif


/*********** static config values ************/
#ifndef MAX_DEPTH   /* maximal supported binson object/array nesting level */
#define MAX_DEPTH   16
#endif

#ifdef WITH_TO_STRING
#ifndef INDENT_WIDTH
#define INDENT_WIDTH  3
#endif
#endif

/*********************************************/
#define BINSON_ID_UNKNOWN        0x00
#define BINSON_ID_OBJECT         0x01
#define BINSON_ID_ARRAY          0x02
#define BINSON_ID_BLOCK          0x03  /* Meta ID. BINSON_ID_OBJECT or BINSON_ID_ARRAY */

#define BINSON_ID_OBJ_BEGIN      0x40
#define BINSON_ID_OBJ_END        0x41
#define BINSON_ID_ARRAY_BEGIN    0x42
#define BINSON_ID_ARRAY_END      0x43

#define BINSON_ID_BOOLEAN        0x47  /* Meta ID. Translated to one of 2 next consts during serialization */
#define BINSON_ID_TRUE           0x44
#define BINSON_ID_FALSE          0x45
#define BINSON_ID_DOUBLE         0x46

#define BINSON_ID_INTEGER        0x0f  /* Meta ID. Translated to one of 4 next consts during serialization */
#define BINSON_ID_INTEGER_8      0x10
#define BINSON_ID_INTEGER_16     0x11
#define BINSON_ID_INTEGER_32     0x12
#define BINSON_ID_INTEGER_64     0x13

#define BINSON_ID_STRING         0x12  /* Meta ID. Translated to one of 4 next consts during serialization */
#define BINSON_ID_STRING_LEN     0x13  /* indicates stringLen part of STRING object */
#define BINSON_ID_STRING_8       0x14
#define BINSON_ID_STRING_16      0x15
#define BINSON_ID_STRING_32      0x16

#define BINSON_ID_BYTES          0x16  /* Meta ID. Translated to one of 3 next consts during serialization */
#define BINSON_ID_BYTES_LEN      0x17  /* indicates bytesLen part of BYTES object */
#define BINSON_ID_BYTES_8        0x18
#define BINSON_ID_BYTES_16       0x19
#define BINSON_ID_BYTES_32       0x1a

/* error codes */
#define BINSON_ID_OK                      0x00
#define BINSON_ID_INVALID_ARG             0xe0
#define BINSON_ID_BUF_FULL                0xf0
#define BINSON_ID_PARSE_NO_FIELD_NAME     0xf1
#define BINSON_ID_PARSE_BLOCK_ENDED       0xf2
#define BINSON_ID_PARSE_WRONG_STATE       0xf3
#define BINSON_ID_PARSE_WRONG_TYPE        0xf4
#define BINSON_ID_PARSE_BAD_LEN           0xf5
#define BINSON_ID_PARSE_END_OF_BUFFER     0xf6
#define BINSON_ID_PARSE_MAX_DEPTH_REACHED 0xf7

/* clang-format on */

/* buffer pointer + size aggregation, also used for string references */
typedef struct _bbuf
{
    size_t  bsize;
    uint8_t *bptr;
} bbuf;

/* composite value types located in same memory bytes */
typedef union _binson_value
{
    int64_t int_val;
    double  double_val;
    bool    bool_val;
    bbuf    bbuf_val;
} binson_value;

/* smart buffer structure used for both writer and parser */
typedef struct _binson_io
{
    size_t  buf_size;
    size_t  buf_used;
    uint8_t *pbuf;
} binson_io;

/*======================== WRITER ===============================*/

/* main writer "object" structure */
typedef struct _binson_writer
{
    uint8_t         error_flags;
    binson_io       io;         /* smart buffer */
    binson_value    tmp_val; /* used to simplify passing simple types to/from meta functions */
} binson_writer;

/* writer object initialization / reset */
void binson_writer_init(binson_writer *pw, uint8_t *pbuf, size_t buf_size);
void binson_writer_reset(binson_writer *pw);

/* writer public methods */
void binson_write_name(binson_writer *pw, const char *pstr);
void binson_write_name_bbuf(binson_writer *pw, bbuf *pbbuf);
void binson_write_object_begin(binson_writer *pw);
void binson_write_object_end(binson_writer *pw);
void binson_write_array_begin(binson_writer *pw);
void binson_write_array_end(binson_writer *pw);
void binson_write_boolean(binson_writer *pw, bool bval);
void binson_write_integer(binson_writer *pw, int64_t ival);
void binson_write_double(binson_writer *pw, double dval);
void binson_write_string(binson_writer *pw, const char *pstr);
void binson_write_string_with_len(binson_writer *pw, const char *pstr, size_t len);
void binson_write_bytes(binson_writer *pw, const uint8_t *pbuf, size_t len);

/* write binson-encoded block */
uint8_t binson_write_raw(binson_writer *pw, const uint8_t *psrc, size_t sz);

/* status getters */
static inline size_t binson_writer_get_counter(binson_writer *pw) { return pw->io.buf_used; }

/*======================== PARSER ===============================*/

typedef struct binson_parser binson_parser;

/* parser callback declaration */
typedef bool (*binson_parser_cb)(binson_parser *pp, uint8_t new_state, void *param);

/* block stack item structure */
typedef struct bs_item
{
    uint8_t val_type; /* used to store binson_parser's filed with same name */
    bbuf name;        /* used to store binson_parser's filed with same name */
} bs_item;

/* main parser "object" structure */
struct binson_parser
{
    binson_io       io;
    uint8_t         state;
    uint8_t         error_flags;
    uint8_t         val_type;
    bbuf            name;
    binson_value    val;
    uint8_t         depth;
    bs_item         block_stack[MAX_DEPTH];
    /* Only used for to_string */
    binson_parser_cb    cb;
    void                *cb_param;
};

/* parser object initialization / reset */
void binson_parser_init(binson_parser *pp,
                        uint8_t *pbuf,
                        size_t buf_size);

void binson_parser_reset(binson_parser *pp);

void binson_parser_set_callback(binson_parser *pp,
                                binson_parser_cb cb,
                                void *cb_param);

/* next calls are now just shortcuts to 'binson_parser_advance()' */
bool binson_parser_field_ensure(binson_parser *pp,
                                const char *scan_name,
                                uint8_t ensure_type);

bool binson_parser_next_ensure(binson_parser *pp,
                               uint8_t ensure_type);

bool binson_parser_go_into(binson_parser *pp);
bool binson_parser_go_into_object(binson_parser *pp);
bool binson_parser_go_into_array(binson_parser *pp);
bool binson_parser_go_up(binson_parser *pp);

/* looped "_go_up()" version, moving up till required block type */
bool binson_parser_go_upto_object(binson_parser *pp);
bool binson_parser_go_upto_array(binson_parser *pp);

/* wrappers usefull to ignore value type checks */
#define binson_parser_field(x, y) binson_parser_field_ensure(x, y, BINSON_ID_UNKNOWN)
#define binson_parser_next(x) binson_parser_next_ensure(x, BINSON_ID_UNKNOWN)


/* get location and size of buffer part which reflects whole current block being parsed */
bool binson_parser_get_raw(binson_parser *pp, bbuf *pbb);

/* copy current block to specified writer */
bool binson_parser_to_writer(binson_parser *pp, binson_writer *pw);

static inline uint8_t binson_parser_get_depth(binson_parser *pp) { return pp->depth; }
static inline uint8_t binson_parser_get_type(binson_parser *pp) { return pp->val_type; }

uint8_t binson_parser_get_boolean(binson_parser *pp);
int64_t binson_parser_get_integer(binson_parser *pp);
double binson_parser_get_double(binson_parser *pp);

static inline bbuf *binson_parser_get_name_bbuf(binson_parser *pp) { return &pp->name; }

int binson_parser_cmp_name(binson_parser *pp, const char *pstr);
bbuf *binson_parser_get_string_bbuf(binson_parser *pp);
bool binson_parser_string_equals(binson_parser *pp, const char *pstr);
bbuf *binson_parser_get_bytes_bbuf(binson_parser *pp);

#ifdef WITH_TO_STRING
bool binson_parser_to_string(binson_parser *pp, uint8_t *pbuf, size_t buf_size, bool nice);
#endif


#ifdef __cplusplus
}
#endif

#endif /* BINSON_LIGHT_H_INCLUDED */
