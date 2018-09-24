#ifndef _BINSON_WRITER_H_
#define _BINSON_WRITER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file binson_writer.h
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include <stdlib.h>
#include <stdint.h>

#include "binson_parser.h"

/*======= Public macro definitions ==========================================*/
/*======= Type Definitions and declarations =================================*/

typedef struct binson_writer_s {
    size_t      buffer_size;
    size_t      buffer_used;
    uint8_t     *buffer;
    binson_err  error_flags;
} binson_writer;

/*======= Public variable declarations ======================================*/
/*======= Public function declarations ======================================*/

bool binson_writer_init(binson_writer *writer, uint8_t *buffer, size_t buffer_size);
bool binson_writer_reset(binson_writer *writer);
size_t binson_writer_get_counter(binson_writer *writer);

bool binson_write_name(binson_writer *writer, const char *name);
#define binson_write_name_with_len binson_write_string_with_len
bool binson_write_object_begin(binson_writer *writer);
bool binson_write_object_end(binson_writer *writer);
bool binson_write_array_begin(binson_writer *writer);
bool binson_write_array_end(binson_writer *writer);
bool binson_write_boolean(binson_writer *writer, bool value);
bool binson_write_integer(binson_writer *writer, int64_t value);
bool binson_write_double(binson_writer *writer, double value);
bool binson_write_string(binson_writer *writer, const char *value);
#define binson_write_string(w,s) binson_write_string_with_len(w, s, strlen(s))
bool binson_write_string_with_len(binson_writer *writer,
                                  const char *value,
                                  size_t length);
bool binson_write_bytes(binson_writer *writer, const uint8_t *pbuf, size_t length);
bool binson_parser_to_writer(binson_parser *parser, binson_writer *writer);
bool binson_write_raw(binson_writer *writer, const uint8_t *psrc, size_t length);
bool binson_writer_verify(binson_writer *writer);

#ifdef __cplusplus
}
#endif

#endif /* _BINSON_WRITER_H_ */
