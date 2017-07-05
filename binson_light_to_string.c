/*
 *  Copyright (c) 2017 APTUS AB
 *
 *  This file is part of binson-c-light, BINSON serialization format library in C.
 *
 *  License: MIT, Please see the file LICENSE for mor information
 */
#include "binson_light_to_string.h"

#include <stdint.h>
#include <stdio.h>

//#define USE_SPACES_FOR_INDENT

#define MAX(x,y) (x) > (y) ? (x) : (y)
#define MIN(x,y) (x) < (y) ? (x) : (y)

static char tmp_str[50];

static char *append_str(char *dest, char *src, int *max_dest_size);
static char *indent(int level, char *str, int *max_dest_size);
static char *append_bbuf_str(char *dest, bbuf *buf, int *max_dest_size);

static char *append_str(char *dest, char *src, int *max_dest_size)
{
  if (*max_dest_size <= 1)
    return dest;
  int size = MIN((int)(strlen(src)), *max_dest_size - 1);
  memcpy(dest, src, size);
  dest[size] = 0;
  *max_dest_size -= size;
  return &dest[size];
}

static char * indent(int level, char *str, int *max_dest_size)
{
#ifdef USE_SPACES_FOR_INDENT
  const int indentSpaces = 4;
  for(int i = 0 ; i < level*indentSpaces ; ++i)
    str = appendStr(str, " ", maxDestSize);
#else
  for(int i = 0 ; i < level; ++i)
    str = append_str(str, "\t", max_dest_size);
#endif
  return str;
}

static char *append_bbuf_str(char *dest, bbuf *buf, int *max_dest_dize)
{
  if (*max_dest_dize <= 1 || buf == NULL)
    return dest;

  int size_to_copy = MIN(*max_dest_dize - 1, buf->bsize);
  if (size_to_copy <= 0)
    return dest;
  memcpy(dest, buf->bptr, size_to_copy);

  dest[size_to_copy] = 0;
  *max_dest_dize -= size_to_copy;

  return &dest[size_to_copy];
}

static char * binson_to_string_(char *str, int *max_str_size,
                                int level, binson_parser *parser,
                                bool (*next)(binson_parser *pp), bool is_array)
{
  if (*max_str_size <= 1)
    return str;

  bool firstLap = true;
  while (next(parser))
  {
    int64_t val;
    int type = binson_parser_get_type(parser);
    bbuf *buf = binson_parser_get_name_bbuf(parser);

    if (!firstLap)
      str = append_str(str, ",", max_str_size);
    str = append_str(str, "\n", max_str_size);
    str = indent(level, str, max_str_size);

    if (!is_array)
    {
      str = append_str(str, "\"", max_str_size);
      str = append_bbuf_str(str, buf, max_str_size);
      str = append_str(str, "\":", max_str_size);
    }
    switch(type)
    {
    case BINSON_ID_INTEGER:
      val = binson_parser_get_integer(parser);
      sprintf(tmp_str, "%ld", val);
      str = append_str(str, tmp_str, max_str_size);
      break;
    case BINSON_ID_STRING:
      buf = binson_parser_get_string_bbuf(parser);
      str = append_str(str, "\"", max_str_size);
      str = append_bbuf_str(str, buf, max_str_size);
      str = append_str(str, "\"", max_str_size);
      break;
    case BINSON_ID_BOOLEAN:
    {
      uint8_t val = binson_parser_get_boolean(parser);
      if (val == 0)
        str = append_str(str, "false", max_str_size);
      else
        str = append_str(str, "true", max_str_size);
    }
    break;
    case BINSON_ID_DOUBLE:
    {
      double val = binson_parser_get_double(parser);
      sprintf(tmp_str, "%f", val);
      str = append_str(str, tmp_str, max_str_size);
    }
    break;
    case BINSON_ID_BYTES:
      buf = binson_parser_get_bytes_bbuf(parser);
      if (buf)
        sprintf(tmp_str, " <data> bytes len: %d", buf->bsize);
      else
        sprintf(tmp_str, " buf: %p", (void *)buf);
      str = append_str(str, tmp_str, max_str_size);
      break;
    case BINSON_ID_OBJECT:
      binson_parser_go_into_object(parser);
      if (!is_array)
      {
        str = append_str(str, "\n", max_str_size);
        str = indent(level, str, max_str_size);
      }
      str = append_str(str, "{", max_str_size);
      str = binson_to_string_(str, max_str_size, level + 1, parser, binson_parser_next_field, false);
      str = append_str(str, "\n", max_str_size);
      str = indent(level, str, max_str_size);
      str = append_str(str, "}", max_str_size);
      binson_parser_go_upto_object(parser);
      break;
    case BINSON_ID_ARRAY:
      binson_parser_go_into_array(parser);
      str = append_str(str, "\n", max_str_size);
      str = indent(level, str, max_str_size);
      str = append_str(str, "[", max_str_size);
      str = binson_to_string_(str, max_str_size, level + 1, parser, binson_parser_next_array_value, true);
      str = append_str(str, "\n", max_str_size);
      str = indent(level, str, max_str_size);
      str = append_str(str, "]", max_str_size);
      binson_parser_go_upto_array(parser);
      break;
    default:
      str = append_str(str, "PARSE ERROR!!!\n", max_str_size);
      break;
    }
    if (firstLap)
      firstLap = false;
  }
  return str;
}

void binson_to_string(binson_parser *parser, char *str, int max_str_size)
{
  int size = max_str_size;
  str = append_str(str, "{", &size);
  str = binson_to_string_(str, &size, 1, parser, binson_parser_next_field, false);
  str = append_str(str, "\n}\n", &size);
}
