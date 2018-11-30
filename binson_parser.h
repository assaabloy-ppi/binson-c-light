#ifndef _BINSON_PARSER_H_
#define _BINSON_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file binson_parser.h
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include "binson_defines.h"

/*======= Public macro definitions ==========================================*/

#define BINSON_PARSER_MAX_DEPTH     (10U)
#define _BP_DEF2(p, depth)                          \
    binson_state p##data[depth];                    \
    binson_parser p;                                \
    p.max_depth = depth;                            \
    p.state = p##data
#define _BP_DEF1(p) _BP_DEF2(p, 10U)
#define _BP_GETMACRO(_1, _2, NAME, ...) NAME
#define BINSON_PARSER_DEF(...) _BP_GETMACRO(__VA_ARGS__, _BP_DEF2, _BP_DEF1)(__VA_ARGS__)

/*======= Type Definitions and declarations =================================*/

typedef struct binson_state_s {
    binson_type     current_type;
    binson_value    current_value;
    bbuf            current_name;
    uint16_t        flags;
    uint_fast8_t    array_depth;
} binson_state;

typedef struct binson_parser_s binson_parser;
typedef void (*binson_cb)(binson_parser *parser, uint16_t next_state, void *context);

struct binson_parser_s {
    uint_fast8_t    type;
    uint_fast8_t    depth;
    uint_fast8_t    max_depth;
    size_t          buffer_size;
    size_t          buffer_used;
    const uint8_t   *buffer;
    binson_err      error_flags;
    binson_state    *state;
    binson_state    *current_state;
    binson_cb       cb;
    void            *cb_context;
};

/*======= Public variable declarations ======================================*/
/*======= Public function declarations ======================================*/

/**
 * @brief Initiates a binson parser on a raw buffer.
 *
 * Initiates a binson parser on a raw buffer at zero depth. The parse will fail
 * to initiate if the first and last byte is not the BEGIN and END value. I.e.,
 * if buffer[n] != { 0x40 , ... , 0x41 } this will fail.
 *
 * @param parser        Pointer to binson parser structure.
 * @param buffer        Pointer to buffer that holds byte representation of binson object.
 * @param buffer_size   Size of buffer.
 *
 * @return true     The binson parser was successfully initiated.
 * @return false    The binson parser could not be initiated.
 */
bool binson_parser_init_object(binson_parser *parser,
                               const uint8_t *buffer,
                               size_t buffer_size);

#define binson_parser_init binson_parser_init_object

/**
 * @brief Initiates a binson array parser on a buffer.
 *
 * Initiates a binson parser on a raw buffer at zero array depth. The parse will fail
 * to initiate if the first and last byte is not the ARRAY BEGIN and ARRAY END value. I.e.,
 * if buffer[n] != { 0x42 , ... , 0x43 } this will fail.
 *
 * @param parser        Pointer to binson parser structure.
 * @param buffer        Pointer to buffer that holds byte representation of binson array.
 * @param buffer_size   Size of buffer.
 *
 * @return true     The binson parser was successfully initiated.
 * @return false    The binson parser could not be initiated.
 */
bool binson_parser_init_array(binson_parser *parser,
                              const uint8_t *buffer,
                              size_t buffer_size);

/**
 * @brief Resets the binson parser.
 *
 * @param parser Pointer to binson parser structure.
 *
 * @return true     The binson parser was successfully reseted.
 * @return false    The binson parser could not be reseted.
 */
bool binson_parser_reset(binson_parser *parser);

/**
 * @brief Verifies a binson object.
 *
 * Can be used to verify a binson object prior to parsing specific value. The
 * verifying process walks through the raw byte representation and verifies it
 * according to specficiation.
 *
 * @param parser Pointer to binson parser structure.
 *
 * @return true     The raw byte representation of the binson object was valid.
 * @return false    The raw byte representation of the binson object was NOT valid.
 *                  See parser->error_flags for error code.
 */
bool binson_parser_verify(binson_parser *parser);

/**
 * @brief Gets the current (object) depth of the parser.
 *
 * @param parser Pointer to binson parser structure.
 * @return The current depth. 0 if parser == NULL.
 */
size_t binson_parser_get_depth(binson_parser *parser);

/**
 * @brief Parses the next field and/or value.
 *
 * Depending on the state of the parser, the next field and value, or the next value will
 * be parsed. If in an object, the field and value will be parsed. If in an array, the
 * next value will be parsed.
 *
 *
 * @param parser Pointer to binson parser structure.
 * @return true     The next field was successfully parser.
 * @return false    The next field could not be parsed. Due to format error
 *                  or end of block (object or array).
 */
bool binson_parser_next(binson_parser *parser);

/**
 * @brief Parses the next field and/or value and verifies the type.
 *
 * See @\ref binson_parser_next
 *
 * @param parser Pointer to binson parser structure.
 * @return false    The next field could not be parsed. Due to format error
 *                  or end of block (object or array).
 */
bool binson_parser_next_ensure(binson_parser *parser, binson_type field_type);

/**
 * @brief Returns the type of the currently parsed value.
 *
 * @param parser Pointer to binson parser structure.
 * @return Type of current value. See @\ref binson_type.
 */
binson_type binson_parser_get_type(binson_parser *parser);

/**
 * @brief Parses until a field is found (or not found) in an object.
 *        This is a macro for binson_parser_field_with_length so be
 *        careful to not input a pointer as the argument field_name.
 *        The length of the field name is determined using sizeof("string")-1
 *        and not strlen().
 *        I.e., if the field name is a pointer, the length will be the size of a pointer.
 *        If the data field name points to is shorter than a pointer, a memory read out
 *        of the limit will be caused.
 *
 * Example usage:
 *
 *  // Ok
 *  binson_parser p;
 *  if (binson_parser_field(&p, "foo")) {
 *    // Field "foo" exists"
 *  }
 *
 *  // Not ok
 *  binson_parser p;
 *  char *field_name_from_external_string;
 *  if (binson_parser_field(&p, field_name_from_external_string)) {
 *    // Might cause crash
 *  }
 *
 * @param parser      Pointer to binson parser structure.
 * @param field_name  String (not a pointer) with field name.
 *
 * @return true   The field name was present in the object.
 * @return false  The field name could be found (or was already found previous).
 */

#define binson_parser_field(p, f) binson_parser_field_with_length(p, f, sizeof(f)-1)

/**
 * @brief Parses until a field is found (or not found) in an object.
 *        See \ref @binson_parser_field. This function differs from
 *        that and a field name length argument must be provided.
 *
 * @param parser      Pointer to binson parser structure.
 * @param field_name  String (not a pointer) with field name.
 * @param length      Length of field name.
 *
 * @return true   The field name was present in the object.
 * @return false  The field name could be found (or was already found previous).
 */
bool binson_parser_field_with_length(binson_parser *parser,
                                     const char *field_name,
                                     size_t length);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param field_name [description]
 * @param field_type [description]
 * @return [description]
 */
bool binson_parser_field_ensure(binson_parser *parser,
                               const char *field_name,
                               binson_type field_type);
#define binson_parser_field_ensure(p, f, t) binson_parser_field_ensure_with_length(p, f, sizeof(f)-1, t)

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param field_name [description]
 * @param field_type [description]
 * @return [description]
 */
bool binson_parser_field_ensure_with_length(binson_parser *parser,
                                            const char *field_name,
                                            size_t length,
                                            binson_type field_type);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param p [description]
 * @return [description]
 */
bool binson_parser_go_into_object(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param p [description]
 * @return [description]
 */
bool binson_parser_leave_object(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param p [description]
 * @return [description]
 */
bool binson_parser_go_into_array(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param p [description]
 * @return [description]
 */
bool binson_parser_leave_array(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param string [description]
 *
 * @return [description]
 */
bbuf *binson_parser_get_name(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param string [description]
 *
 * @return [description]
 */
bbuf *binson_parser_get_string_bbuf(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param string [description]
 *
 * @return [description]
 */
bool binson_parser_get_raw(binson_parser *parser, bbuf *raw);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param string [description]
 *
 * @return [description]
 */
int64_t binson_parser_get_integer(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param string [description]
 *
 * @return [description]
 */
bool binson_parser_get_boolean(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param string [description]
 *
 * @return [description]
 */
double binson_parser_get_double(binson_parser *parser);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param parser Pointer to binson parser structure.
 * @param string [description]
 *
 * @return [description]
 */
bbuf *binson_parser_get_bytes_bbuf(binson_parser *parser);

bool binson_parser_string_equals(binson_parser *pp, const char *pstr);
bool binson_parser_print(binson_parser *parser);
bool binson_parser_to_string(binson_parser *parser,
                             char *pbuf,
                             size_t *buf_size,
                             bool nice);

#ifdef __cplusplus
}
#endif

#endif /* _BINSON_PARSER_H_ */
