#ifndef _BINSON_DEFINES_H_
#define _BINSON_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file binson_defines.h
 *
 * object     = begin *field end
 * field      = string value
 * value      = boolean / integer / double / string / bytes / array / object
 * array      = beginArray *value endArray
 * string     = stringLen utf
 * bytes      = bytesLen raw
 * boolean    = true / false
 *
 * begin      = %x40
 * end        = %x41
 * beginArray = %x42
 * endArray   = %x43
 * true       = %x44
 * false      = %x45
 * double     = %x46 float64
 * integer    = %x10 int8 / %x11 int16 / %x12 int32 / %x13 int64
 * stringLen  = %x14 int8 / %x15 int16 / %x16 int32
 * bytesLen   = %x18 int8 / %x19 int16 / %x1a int32
 *
 * float64    = 8OCTET ; double precision floation point number [IEEE-754]
 * int8       = 1OCTET ;  8-bit signed two's complement integer
 * int16      = 2OCTET ; 16-bit signed two's complement integer
 * int32      = 4OCTET ; 32-bit signed two's complement integer
 * int64      = 8OCTET ; 64-bit signed two's complement integer
 * utf        = *OCTET ; stringLen number of [UTF-8] bytes
 * raw        = *OCTET ; any sequence of bytesLen bytes
 *
 */

/*======= Includes ==========================================================*/

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

/*======= Public macro definitions ==========================================*/

#define BINSON_OBJECT_MINIMUM_SIZE  (2U)

#define BINSON_DEF_OBJECT_BEGIN     (0x40U)
#define BINSON_DEF_OBJECT_END       (0x41U)
#define BINSON_DEF_ARRAY_BEGIN      (0x42U)
#define BINSON_DEF_ARRAY_END        (0x43U)
#define BINSON_DEF_TRUE             (0x44U)
#define BINSON_DEF_FALSE            (0x45U)
#define BINSON_DEF_DOUBLE           (0x46U)
#define BINSON_DEF_INT8             (0x10U)
#define BINSON_DEF_INT16            (0x11U)
#define BINSON_DEF_INT32            (0x12U)
#define BINSON_DEF_INT64            (0x13U)
#define BINSON_DEF_STRINGLEN_INT8   (0x14U)
#define BINSON_DEF_STRINGLEN_INT16  (0x15U)
#define BINSON_DEF_STRINGLEN_INT32  (0x16U)
#define BINSON_DEF_BYTESLEN_INT8    (0x18U)
#define BINSON_DEF_BYTESLEN_INT16   (0x19U)
#define BINSON_DEF_BYTESLEN_INT32   (0x1AU)

/*======= Type Definitions and declarations =================================*/

/* For backwards compatibility */
typedef size_t binson_size;

typedef enum binson_type_e {
    BINSON_TYPE_NONE,
    BINSON_TYPE_OBJECT,
    BINSON_TYPE_OBJECT_END,     /* Only used internally */
    BINSON_TYPE_ARRAY,
    BINSON_TYPE_ARRAY_END,      /* Only used internally */
    BINSON_TYPE_BOOLEAN,
    BINSON_TYPE_INTEGER,
    BINSON_TYPE_DOUBLE,
    BINSON_TYPE_STRING,
    BINSON_TYPE_BYTES
} binson_type;

typedef enum binson_err_e {
    BINSON_ERROR_NONE,
    BINSON_ERROR_RANGE,
    BINSON_ERROR_FORMAT,
    BINSON_ERROR_EOF,
    BINSON_ERROR_END_OF_BLOCK,
    BINSON_ERROR_NULL,
    BINSON_ERROR_STATE,
    BINSON_ERROR_WRONG_TYPE,
    BINSON_ERROR_MAX_DEPTH_OBJECT,
    BINSON_ERROR_MAX_DEPTH_ARRAY
} binson_err;

/* For backwards compatibility */
#define BINSON_ID_OK            BINSON_ERROR_NONE
#define BINSON_ID_NONE          BINSON_TYPE_NONE
#define BINSON_ID_OBJECT        BINSON_TYPE_OBJECT
#define BINSON_ID_ARRAY         BINSON_TYPE_ARRAY
#define BINSON_ID_BOOLEAN       BINSON_TYPE_BOOLEAN
#define BINSON_ID_INTEGER       BINSON_TYPE_INTEGER
#define BINSON_ID_DOUBLE        BINSON_TYPE_DOUBLE
#define BINSON_ID_STRING        BINSON_TYPE_STRING
#define BINSON_ID_BYTES         BINSON_TYPE_BYTES
#define BINSON_ID_PARSE_WRONG_TYPE BINSON_ERROR_WRONG_TYPE
#define BINSON_ID_INTEGER_64 BINSON_DEF_INT64
#define BINSON_ID_INTEGER_32 BINSON_DEF_INT32
#define BINSON_ID_INTEGER_16 BINSON_DEF_INT16
#define BINSON_ID_INTEGER_8 BINSON_DEF_INT8

typedef struct bbuf_e {
    size_t          bsize;
    const uint8_t   *bptr;
} bbuf;

typedef union binson_value_e {
    int64_t integer_value;
    bool    bool_value;
    bbuf    string_value;
    bbuf    bytes_value;
    bbuf    object_value;
    bbuf    array_value;
    bbuf    raw;
    double  double_value;
} binson_value;


/*======= Public variable declarations ======================================*/
/*======= Public function declarations ======================================*/

#ifdef __cplusplus
}
#endif

#endif /* _BINSON_DEFINES_H_ */
