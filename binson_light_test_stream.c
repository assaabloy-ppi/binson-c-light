/*
 *  Copyright (c) 2015 ASSA ABLOY AB
 *
 *  This file is part of binson-c-light, BINSON serialization format library in C.
 *
 *  binson-c-light is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU Lesser General Public License (LGPL) as published
 *  by the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  As a special exception, the Contributors give you permission to link
 *  this library with independent modules to produce an executable,
 *  regardless of the license terms of these independent modules, and to
 *  copy and distribute the resulting executable under terms of your choice,
 *  provided that you also meet, for each linked independent module, the
 *  terms and conditions of the license of that module. An independent
 *  module is a module which is not derived from or based on this library.
 *  If you modify this library, you must extend this exception to your
 *  version of the library.
 *
 *  binson-c-light is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "binson_light_to_string.h"

#include <stdint.h>
#include <stdio.h>


bool to_string_cb( binson_parser *pp, void *param )
{
  bbuf *dst = (bbuf*)param;

}

void binson_to_string(binson_parser *parser, char *str, int max_str_size)
{
  /* store current callback & param */
  binson_parser_cb   stored_cb = pp->cb;
  void*              stored_cb_param = pp->cb_param;
  bbuf               dst;

  /* set own callback */
  binson_util_set_bbuf( &dst, (uint8_t *)str, (binson_size)max_str_size );
  binson_parser_set_callback(pp, to_string_cb, &dst);


}

/*
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

bool next_wrapper( binson_parser *pp )
{
  return binson_parser_advance( pp, BINSON_PARSER_ADVANCE_N_SAME_DEPTH, 1, NULL );
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
      sprintf(tmp_str, "%lld", (long long int)val);
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
      str = binson_to_string_(str, max_str_size, level + 1, parser, next_wrapper, false);
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
      str = binson_to_string_(str, max_str_size, level + 1, parser, next_wrapper, true);
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
  str = binson_to_string_(str, &size, 1, parser, next_wrapper, false);
  str = append_str(str, "\n}\n", &size);
}
*/