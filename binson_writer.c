/**
 * @file binson_writer.c
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include <string.h>
#include "binson_writer.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

static bool _write_token(binson_writer *writer,
                         binson_value *value,
                         binson_type type);

static bool _write(binson_writer *writer, bbuf *data);

/*======= Global function implementations ===================================*/

bool binson_writer_init(binson_writer *writer, uint8_t *buffer, size_t buffer_size)
{
    if (NULL == writer) {
        return false;
    }

    memset(writer, 0x00, sizeof(binson_writer));

    if (NULL == buffer) {
        writer->error_flags = BINSON_ERROR_NULL;
        return false;
    }

    if (buffer_size < 2) {
        writer->error_flags = BINSON_ERROR_RANGE;
        return false;
    }

    writer->buffer_size = buffer_size;
    writer->buffer = buffer;

    return true;
}

bool binson_writer_reset(binson_writer *writer)
{
    if (NULL == writer) {
        return false;
    }

    if (NULL == writer->buffer) {
        writer->error_flags = BINSON_ERROR_NULL;
        return false;
    }

    if (writer->buffer_size < 2) {
        writer->error_flags = BINSON_ERROR_RANGE;
        return false;
    }

    writer->buffer_used = 0;
    writer->error_flags = BINSON_ERROR_NONE;

    return true;
}

size_t binson_writer_get_counter(binson_writer *writer)
{
    return (NULL != writer) ? writer->buffer_used : 0;
}

bool binson_write_name(binson_writer *writer, const char *name)
{
    if (NULL == writer) {
        return false;
    }

    if (NULL == name) {
        writer->error_flags = BINSON_ERROR_NULL;
        return false;
    }

    return binson_write_string_with_len(writer, name, strlen(name));
}

bool binson_write_object_begin(binson_writer *writer)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }

    uint8_t token = BINSON_DEF_OBJECT_BEGIN;
    bval.raw.bptr = &token;
    bval.raw.bsize = 1;
    return _write_token(writer, &bval, BINSON_TYPE_OBJECT);
}

bool binson_write_object_end(binson_writer *writer)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }

    uint8_t token = BINSON_DEF_OBJECT_END;
    bval.raw.bptr = &token;
    bval.raw.bsize = 1;
    return _write_token(writer, &bval, BINSON_TYPE_OBJECT_END);
}

bool binson_write_array_begin(binson_writer *writer)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }

    uint8_t token = BINSON_DEF_ARRAY_BEGIN;
    bval.raw.bptr = &token;
    bval.raw.bsize = 1;
    return _write_token(writer, &bval, BINSON_TYPE_ARRAY);
}

bool binson_write_array_end(binson_writer *writer)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }

    uint8_t token = BINSON_DEF_ARRAY_END;
    bval.raw.bptr = &token;
    bval.raw.bsize = 1;
    return _write_token(writer, &bval, BINSON_TYPE_ARRAY_END);
}

bool binson_write_boolean(binson_writer *writer, bool value)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }

    uint8_t token = (value) ? BINSON_DEF_TRUE : BINSON_DEF_FALSE;
    bval.raw.bptr = &token;
    bval.raw.bsize = 1;
    return _write_token(writer, &bval, BINSON_TYPE_BOOLEAN);
}

bool binson_write_integer(binson_writer *writer, int64_t value)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }

    bval.integer_value = value;
    return _write_token(writer, &bval, BINSON_TYPE_INTEGER);
}

bool binson_write_double(binson_writer *writer, double value)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }

    bval.double_value = value;
    return _write_token(writer, &bval, BINSON_TYPE_DOUBLE);
}

bool binson_write_string_with_len(binson_writer *writer,
                                  const char *value,
                                  size_t length)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }

    bval.string_value.bptr = (const uint8_t *) value;
    bval.string_value.bsize = length;

    if (bval.string_value.bsize > INT32_MAX) {
        writer->error_flags = BINSON_ERROR_FORMAT;
        return false;
    }

    return _write_token(writer, &bval, BINSON_TYPE_STRING);
}

bool binson_write_bytes(binson_writer *writer, const uint8_t *pbuf, size_t length)
{
    binson_value bval;

    if (NULL == writer) {
        return false;
    }


    bval.bytes_value.bptr = pbuf;
    bval.bytes_value.bsize = length;

    if (bval.bytes_value.bsize > INT32_MAX) {
        writer->error_flags = BINSON_ERROR_FORMAT;
        return false;
    }

    return _write_token(writer, &bval, BINSON_TYPE_BYTES);
}

bool binson_parser_to_writer(binson_parser *parser, binson_writer *writer)
{
    if (NULL == writer) {
        return false;
    }

    if (NULL == parser) {
        writer->error_flags = BINSON_ERROR_NULL;
        return false;
    }
    bbuf raw;
    if (!binson_parser_get_raw(parser, &raw)) {
        return false;
    }
    return binson_write_raw(writer, raw.bptr, raw.bsize);
}

bool binson_write_raw(binson_writer *writer, const uint8_t *data, size_t length)
{
    if (NULL == writer) {
        return false;
    }

    if (NULL == data) {
        writer->error_flags = BINSON_ERROR_NULL;
        return false;
    }

    bbuf to_write;
    to_write.bptr = data;
    to_write.bsize = length;
    return _write(writer, &to_write);
}

bool binson_writer_verify(binson_writer *writer)
{
    if (NULL == writer) {
        return false;
    }
    binson_parser p;
    if (!binson_parser_init(&p, writer->buffer, writer->buffer_used)) {
        return false;
    }
    return binson_parser_verify(&p);
}

/*======= Local function implementations ====================================*/

static uint8_t _int_pack_size(int64_t length, uint8_t *buffer, bool is_double)
{
    uint8_t size = 0;

    if (is_double) {
        size = 8;
    }
    else {
        if ((length >= INT8_MIN) && (length <= INT8_MAX)) {
            size = sizeof(int8_t);
        }
        else if ((length >= INT16_MIN) && (length <= INT16_MAX)) {
            buffer[0] += 1;
            size = sizeof(int16_t);
        }
        else if ((length >= INT32_MIN) && (length <= INT32_MAX)) {
            buffer[0] += 2;
            size = sizeof(int32_t);
        }
        else {
            size = sizeof(int64_t);
            buffer[0] += 3;
        }
    }

    uint64_t uval = (uint64_t) length;

    uint8_t i;
    for (i = 0; i < size; i++) {
        buffer[1 + i] = (uint8_t) (uval & 0xFFU);
        uval >>= 8U;
    }

    return 1 + size;

}

static bool _write_token(binson_writer *writer,
                         binson_value *value,
                         binson_type type)
{

    uint8_t pack_buffer[sizeof(int64_t) + 1];
    bbuf value_descriptor;
    value_descriptor.bsize = 0;
    value_descriptor.bptr = pack_buffer;

    bbuf value_data;
    value_data.bsize = 0;
    value_data.bptr = pack_buffer;


    switch (type) {
        case BINSON_TYPE_OBJECT:
        case BINSON_TYPE_OBJECT_END:
        case BINSON_TYPE_ARRAY:
        case BINSON_TYPE_ARRAY_END:
        case BINSON_TYPE_BOOLEAN:
            value_descriptor.bsize = 1;
            value_descriptor.bptr = value->raw.bptr;
            return _write(writer, &value_descriptor);
        case BINSON_TYPE_INTEGER:
            pack_buffer[0] = BINSON_DEF_INT8;
            value_descriptor.bptr = pack_buffer;
            value_descriptor.bsize = _int_pack_size(value->integer_value,
                                                    pack_buffer,
                                                    false);
            return _write(writer, &value_descriptor);
        case BINSON_TYPE_DOUBLE:
            pack_buffer[0] = BINSON_DEF_DOUBLE;
            value_descriptor.bptr = pack_buffer;
            value_descriptor.bsize = _int_pack_size(value->integer_value,
                                                    pack_buffer,
                                                    true);
            return _write(writer, &value_descriptor);
        case BINSON_TYPE_STRING:
            pack_buffer[0] = BINSON_DEF_STRINGLEN_INT8;
            value_data.bptr = value->string_value.bptr;
            value_data.bsize = value->string_value.bsize;
            break;
        case BINSON_TYPE_BYTES:
            pack_buffer[0] = BINSON_DEF_BYTESLEN_INT8;
            value_data.bptr = value->bytes_value.bptr;
            value_data.bsize = value->bytes_value.bsize;
            break;
        default:
            writer->error_flags = BINSON_ERROR_STATE;
            return false;
    }

    value_descriptor.bsize = _int_pack_size((int64_t) value->raw.bsize,
                                            pack_buffer,
                                            false);
    value_descriptor.bptr = pack_buffer;

    bool ret = _write(writer, &value_descriptor);

    if (value_data.bsize > 0) {
        ret = _write(writer, &value_data);
    }

    return ret;

}

static bool _write(binson_writer *writer, bbuf *data)
{
    size_t c = writer->buffer_used + data->bsize;

    if (c > writer->buffer_size) {
        writer->error_flags = BINSON_ERROR_RANGE;
    }
    else if (c < writer->buffer_used) {
        writer->error_flags = BINSON_ERROR_RANGE;
    }

    if (NULL == writer->buffer) {
        writer->error_flags = BINSON_ERROR_NULL;
    }

    if (writer->error_flags == BINSON_ERROR_NONE) {
        memmove(&writer->buffer[writer->buffer_used], data->bptr, data->bsize);
    }
    
    writer->buffer_used += data->bsize;
    return (writer->error_flags == BINSON_ERROR_NONE);
}
