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
#include <unistd.h>
#include <stdio.h>
#include "binson_light_test_stream.h"

char str_buf[2048];

/* binson-to-binson parser callback, used for testing */
bool _to_binson_cb( binson_parser *pp, uint8_t new_state, void *param )
{
  binson_writer *w = (binson_writer*) param;

  switch (new_state)
  {
    case 0x01: /*BINSON_PARSER_STATE_BLOCK:*/
      binson_write( w, pp->val_type == BINSON_ID_OBJECT? BINSON_ID_OBJ_BEGIN : BINSON_ID_ARRAY_BEGIN );
      return true;

    case 0x08: /* BINSON_PARSER_STATE_BLOCK_END:*/
      binson_write( w, pp->val_type == BINSON_ID_OBJECT? BINSON_ID_OBJ_END : BINSON_ID_ARRAY_END );
      return true;

    case 0x10: /* BINSON_PARSER_STATE_NAME: */
        binson_write_name_bbuf( w, &pp->name );
        return true;

    case 0x20: /* BINSON_PARSER_STATE_VAL: */
      switch (pp->val_type)
      {
        case BINSON_ID_BOOLEAN:
          binson_write_boolean( w, pp->val.bool_val );
          break;
        case BINSON_ID_DOUBLE:
          binson_write_double( w, pp->val.double_val );        
          break;
        case BINSON_ID_INTEGER:
          binson_write_integer( w, pp->val.int_val );        
          break;
        case BINSON_ID_STRING:
          binson_write_string_bbuf( w, &pp->val.bbuf_val );
          break;
        case BINSON_ID_BYTES:
          binson_write_bytes_bbuf( w, &pp->val.bbuf_val );
          break;

        default:  /* we should not get here */
          return true;
      }
      break;

    default:
      return true;  /* do nothing */
  }

  return true;
}

/*
Parses 'raw_chunk_size' bytes and serialize back to 'binson_writer'.
Return true, if input is equal to output
*/
bool binson_stream_test_start(binson_parser *p, binson_writer *w, int raw_chunk_size)
{
  binson_parser_cb    stored_cb = p->cb;  /* store current callback & param */
  void*               stored_cb_param = p->cb_param;

  binson_parser_set_callback(p, _to_binson_cb, w);
  binson_parser_advance(p, BINSON_PARSER_ADVANCE_N_SAME_DEPTH, -1, NULL, BINSON_ID_UNKNOWN);

  /* restore saved callback & param */
  p->cb = stored_cb;
  p->cb_param = stored_cb_param;

  /* compare input vs output */
  return memcmp(p->io.pbuf, w->io.pbuf, raw_chunk_size) == 0? true:false;
}

#ifdef TEST_STREAM_MAIN
int main(void)
{
    binson_parser p;
    binson_writer w;
    bool res;

    uint8_t src_buf[65535], dst_buf[65535];
    int raw_len;

    puts("Reading from stdin...");
    raw_len = read(0, src_buf, sizeof(src_buf));

    binson_parser_init(&p, src_buf, raw_len);
    binson_writer_init(&w, dst_buf, sizeof(dst_buf));

    res = binson_stream_test_start(&p, &w, raw_len);
    
    if (res)
      puts("input == output");
    else
      puts("input != output");

    return 0;
}
#endif /* TEST_STREAM_MAIN */