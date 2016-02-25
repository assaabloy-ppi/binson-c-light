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

#include "binson_light.h"

/*======================== Forward declarations  ===============================*/
static inline void _binson_write_name( binson_writer *pw, const char* pstr, uint8_t is_pgmspace );

void binson_write_object_begin( binson_writer *pw );
void binson_write_object_end( binson_writer *pw );
void binson_write_array_begin( binson_writer *pw );
void binson_write_array_end( binson_writer *pw );
void binson_write_boolean( binson_writer *pw, uint8_t bval );
void binson_write_integer( binson_writer *pw, uint64_t ival );
#ifdef WITH_FP
void binson_write_double( binson_writer *pw, double dval );
#endif
void binson_write_string( binson_writer *pw, const char* pstr );
void binson_write_name( binson_writer *pw, const char* pstr );
void binson_write_string_with_len( binson_writer *pw, const char* pstr, binson_tok_size len );
void binson_write_bytes( binson_writer *pw, const uint8_t* pbuf, binson_tok_size len );

/* AVR8 only. "_p" functions are interpreting pointer argument as 'program space' pointer (flash) */
#if defined AVR8 && defined WITH_AVR_PGMSPACE								  
void binson_write_string_p( binson_writer *pw, const char* pstr );
void binson_write_name_p( binson_writer *pw, const char* pstr );
void binson_write_string_with_len_p( binson_writer *pw, const char* pstr, binson_tok_size len );
void binson_write_bytes_p( binson_writer *pw, const uint8_t* pbuf, binson_tok_size len );
#endif

static inline void	_binson_io_reset( binson_io *io );
static inline void      _binson_io_init( binson_io *io, uint8_t *pbuf, binson_size size );
static inline void	_binson_io_purge( binson_io *io );
static inline uint8_t	_binson_io_write( binson_io *io, const uint8_t *psrc, binson_size sz, uint8_t is_pgmspace );
static inline uint8_t	_binson_io_write_byte( binson_io *io, const uint8_t src_byte, uint8_t is_pgmspace );
 
static uint8_t		_binson_util_pack_integer( int64_t val, uint8_t *pbuf, uint8_t force_64bit );
static int64_t		_binson_util_unpack_integer( uint8_t *pbuf, uint8_t bsize );
static inline uint8_t	_binson_util_sizeof_idx( uint8_t n );

static inline void  	_binson_util_cpy_bbuf( bbuf *dst, bbuf *src );
static inline int16_t  	_binson_util_cmp_bbuf2bbuf( bbuf *bb1, bbuf *bb2 );

#ifdef WITH_ORDER_CHECKS
static inline void 	_binson_util_writer_track_keyorder( binson_writer *pw, int8_t dir_sign );
#endif

// int8_t binson_util_cmp_str2bbuf   (+ _p version)
// uint8_t binson_util_cpy_bbuf2str

/*======================== binson_writer methods ===============================*/

/* */
void binson_writer_init( binson_writer *pw, uint8_t *pbuf, binson_size buf_size, binson_writer_cb cb )
{
  UNUSED(cb);
  
  memset( pw, 0, sizeof(binson_writer) );
#ifdef WITH_WRITER_CB  
  if (pbuf && buf_size)   /* do not flood callback with BINSON_ID_BUF_FULL events */
    pw->cb = cb;
#endif     
  _binson_io_init( &(pw->io), pbuf, buf_size );
} 

/* */
void binson_writer_reset( binson_writer *pw )
{
  binson_writer_purge( pw );
  _binson_io_reset( &(pw->io) );
  
  CLEARBITMASK( pw->state_flags, BINSON_WRITER_STATE_MASK_ERROR );  /* clear all error flags */
}

/* */
void binson_writer_purge( binson_writer *pw )
{
  _binson_io_purge( &(pw->io) );
  
#ifdef WITH_ORDER_CHECKS
  pw->cur_depth = 0;
  pw->key_stack[0].bptr = 0;
  pw->key_stack[0].bsize = 0;
#endif    
}

/*======================== IO (smart buffer helpers) ===========================*/
/* */
static inline void	_binson_io_reset( binson_io *io )
{
  io->buf_used	= 0;
  io->counter	= 0;
}

/* */
static inline void      _binson_io_init( binson_io *io, uint8_t *pbuf, binson_size size )
{
  io->pbuf = pbuf;
  io->buf_size = size;
  _binson_io_reset( io );
}

/* */
static inline void	_binson_io_purge( binson_io *io )
{
  io->buf_used = 0;
}

/* */
static inline uint8_t	_binson_io_write( binson_io *io, const uint8_t *psrc, binson_size sz, uint8_t is_pgmspace )
{
  UNUSED(is_pgmspace); /* unused for non-avr8 arch. used to suppress compiler warning */
  uint8_t res = BINSON_ID_UNKNOWN;   /* zero result mean success */
  io->counter += sz;
  
  if (io->buf_used + sz > io->buf_size)
    return BINSON_ID_BUF_FULL;
  
  if (io->buf_used + sz > io->buf_size - BINSON_CFG_BUF_GUARD_LIMIT)
    res = BINSON_ID_BUF_GUARD;

  if (io->pbuf) {
#if defined AVR8 && defined WITH_AVR_PGMSPACE	  
    if (is_pgmspace)
      memcpy_P( io->pbuf + io->buf_used, psrc, sz );  /* interpret psrc as program-space pointer */
    else
#endif    
      memcpy( io->pbuf + io->buf_used, psrc, sz );
  }
  
  io->buf_used += sz;
  
  return res;
}

/* */
static inline uint8_t	_binson_io_write_byte( binson_io *io, const uint8_t src_byte, uint8_t is_pgmspace )
{
  return _binson_io_write( io, &src_byte, 1, is_pgmspace );    
}

/* */
binson_tok_size  _binson_writer_write_token( binson_writer *pwriter, const uint8_t token_type, binson_value *val, const uint8_t is_pgmspace)
{
  uint8_t 		res;  // write result
  binson_tok_size 	isize = 1;  // default is to write single byte
  UNUSED(res);    
      
  switch (token_type)
  {
    /* optimization: top cases are most probable cases */
    case BINSON_ID_INTEGER:
    case BINSON_ID_STRING_LEN:
    case BINSON_ID_BYTES_LEN:    
#ifdef WITH_FP            
    case BINSON_ID_DOUBLE:
#endif                  
    {
      uint8_t pack_buf[ sizeof(int64_t) + 1 ];
      
#ifdef WITH_FP      
      isize = _binson_util_pack_integer( val->int_val, &(pack_buf[1]), (token_type == BINSON_ID_DOUBLE)? 1:0 );      
      pack_buf[0] = token_type + ((token_type == BINSON_ID_DOUBLE)? 0 : _binson_util_sizeof_idx( isize )); 
#else
      isize = _binson_util_pack_integer( val->int_val, &(pack_buf[1]), 0 );      
      pack_buf[0] = token_type + _binson_util_sizeof_idx( isize ); //calculate binson INTEGER signature      
#endif            
      isize++;      
      res = _binson_io_write( &(pwriter->io), pack_buf, isize, 0 );     
     
      break;
    }
    
    case BINSON_ID_STRING:
    case BINSON_ID_BYTES:
    {
      binson_tok_size 	tok_size = val->bbuf_val.bsize;      
      binson_value 	tval;
      
      tval.int_val = tok_size;
      
       // single level of recursuion is not a crime, but still stack size must be monitored
      isize = _binson_writer_write_token( pwriter, token_type+1, &tval, is_pgmspace); /* writes sig+len*/
      res = _binson_io_write( &(pwriter->io), val->bbuf_val.bptr, tok_size, is_pgmspace );  /* writes payload: string (without \0) or bytearray */
      isize += tok_size;
      break;
    }
      
    case BINSON_ID_OBJ_BEGIN:
    case BINSON_ID_ARRAY_BEGIN:              
    case BINSON_ID_OBJ_END:
    case BINSON_ID_ARRAY_END:	
    case BINSON_ID_TRUE:
    case BINSON_ID_FALSE:
      res = _binson_io_write_byte( &(pwriter->io), token_type, 0 );
      break;

    case BINSON_ID_BOOLEAN:
      res = _binson_io_write_byte( &(pwriter->io), val->bool_val? BINSON_ID_TRUE : BINSON_ID_FALSE, 0 );
      break;    
      
    default:
    return 0;
  }
  
  /* single flow for callback invocation */
#ifdef WITH_WRITER_CB
      if (res != BINSON_ID_UNKNOWN && pwriter->cb)
	pwriter->cb( pwriter, res, 0 );
#endif              
     
  return isize;
}

/* */
void binson_write_object_begin( binson_writer *pw )
{
  _binson_writer_write_token( pw, BINSON_ID_OBJ_BEGIN, NULL, 0);
#ifdef WITH_ORDER_CHECKS  
  _binson_util_writer_track_keyorder( pw, +1 );
#endif  
}

/* */
void binson_write_object_end( binson_writer *pw )
{
  _binson_writer_write_token( pw, BINSON_ID_OBJ_END, NULL, 0);  
#ifdef WITH_ORDER_CHECKS  
  _binson_util_writer_track_keyorder( pw, -1 );
#endif    
}

/* */
void binson_write_array_begin( binson_writer *pw )
{
  _binson_writer_write_token( pw, BINSON_ID_ARRAY_BEGIN, NULL, 0);   
#ifdef WITH_ORDER_CHECKS  
  _binson_util_writer_track_keyorder( pw, +1 );
#endif    
}

/* */
void binson_write_array_end( binson_writer *pw )
{
  _binson_writer_write_token( pw, BINSON_ID_ARRAY_END, NULL, 0);  
#ifdef WITH_ORDER_CHECKS  
  _binson_util_writer_track_keyorder( pw, -1 );
#endif    
}

/* */
void binson_write_boolean( binson_writer *pw, uint8_t bval )
{
  pw->tmp_val.bool_val = bval; 
  _binson_writer_write_token( pw, BINSON_ID_BOOLEAN, &(pw->tmp_val), 0);
}

/* */
void binson_write_integer( binson_writer *pw, uint64_t ival )
{
  pw->tmp_val.int_val = ival; 
  _binson_writer_write_token( pw, BINSON_ID_INTEGER, &(pw->tmp_val), 0);  
}

#ifdef WITH_FP
/* */
void binson_write_double( binson_writer *pw, double dval )
{
  pw->tmp_val.double_val = dval;
  _binson_writer_write_token( pw, BINSON_ID_DOUBLE, &(pw->tmp_val), 0);  
}
#endif

/* */
void binson_write_string( binson_writer *pw, const char* pstr )
{
  binson_write_string_with_len( pw, pstr, strlen(pstr) );  
}

/* */
void binson_write_name( binson_writer *pw, const char* pstr )
{
  _binson_write_name( pw, pstr, 0);
} 

/* */
static void _binson_write_name( binson_writer *pw, const char* pstr, uint8_t is_pgmspace )
{
  pw->tmp_val.bbuf_val.bptr = (uint8_t *)pstr; 
  pw->tmp_val.bbuf_val.bsize = is_pgmspace? strlen_P(pstr) : strlen(pstr); 
#if defined AVR8 && defined WITH_AVR_PGMSPACE								  
  pw->tmp_val.bbuf_val.is_pgm = is_pgmspace;
#endif  
  _binson_writer_write_token( pw, BINSON_ID_STRING, &pw->tmp_val, is_pgmspace );
  
#ifdef WITH_ORDER_CHECKS  
  if ( _binson_util_cmp_bbuf2bbuf( &pw->key_stack[pw->cur_depth], &(pw->tmp_val.bbuf_val) ) >= 0)
  {
      /* set error flag */
      SETBITMASK( pw->state_flags, BINSON_WRITER_STATE_BIT_WRONG_ORDER );
    
#ifdef WITH_WRITER_CB
      if (pw->cb)
	pw->cb( pw, BINSON_ID_WRONG_ORDER, 0 );
#endif    
  }

  /* store last key name for current depth level */
  _binson_util_cpy_bbuf( &pw->key_stack[pw->cur_depth], &pw->tmp_val.bbuf_val );
#endif   
}

/* */
void binson_write_string_with_len( binson_writer *pw, const char* pstr, binson_tok_size len )
{
  pw->tmp_val.bbuf_val.bptr = (uint8_t *)pstr; 
  pw->tmp_val.bbuf_val.bsize = len; 
 _binson_writer_write_token( pw, BINSON_ID_STRING, &pw->tmp_val, 0 );
}

/* */
void binson_write_bytes( binson_writer *pw, const uint8_t* pbuf, binson_tok_size len )
{
  pw->tmp_val.bbuf_val.bptr = (uint8_t *)pbuf; 
  pw->tmp_val.bbuf_val.bsize = len; 
 _binson_writer_write_token( pw, BINSON_ID_BYTES, &pw->tmp_val, 0 );  
}

#if defined AVR8 && defined WITH_AVR_PGMSPACE								  
/* */
void binson_write_string_p( binson_writer *pw, const char* pstr )
{
  binson_write_string_with_len_p( pw, pstr, strlen_P(pstr) );
}

/* */
void binson_write_name_p( binson_writer *pw, const char* pstr )
{
  _binson_write_name( pw, pstr, 1 );  
}

/* */
void binson_write_string_with_len_p( binson_writer *pw, const char* pstr, binson_tok_size len )
{
  pw->tmp_val.bbuf_val.bptr = (uint8_t *)pstr; 
  pw->tmp_val.bbuf_val.bsize = len; 
 _binson_writer_write_token( pw, BINSON_ID_STRING, &pw->tmp_val, 1 );  
}

/* */
void binson_write_bytes_p( binson_writer *pw, const uint8_t* pbuf, binson_tok_size len )
{
  pw->tmp_val.bbuf_val.bptr = (uint8_t *)pbuf; 
  pw->tmp_val.bbuf_val.bsize = len; 
 _binson_writer_write_token( pw, BINSON_ID_BYTES, &pw->tmp_val, 1 );   
}
#endif

/*======================== UTIL ===============================*/

/* */
static int64_t	_binson_util_unpack_integer( uint8_t *pbuf, uint8_t bsize )
{
  int64_t i64 = pbuf[bsize-1] & 0x80 ? -1LL:0;  /* prefill with ones or zeroes depending of sign presence */

  for (int8_t i=bsize-1; i>=0; i--)
  {
    i64 <<= 8;
    i64 |= pbuf[i];
  }
  return i64;
}

/* */
static uint8_t	_binson_util_pack_integer( int64_t val, uint8_t *pbuf, uint8_t force_64bit )
{
  (void)(force_64bit); /* suppress unused warnings when WITH_FP is undefined */
  const int16_t bound8 = ((int16_t)1U) << 7;
  const int32_t bound16 = ((int32_t)1U) << 15;
  const int64_t bound32 = ((int64_t)1ULL) << 31;

#if __BYTE_ORDER == __LITTLE_ENDIAN
  
#ifdef WITH_FP
  if (force_64bit)
  {
    *((uint64_t *)pbuf) = ((uint64_t )val);            
    return sizeof(uint64_t);       
  }
#endif  
  
  if (val >= -bound8 && val < bound8) {
      *((uint8_t *)pbuf) = ((uint8_t )val);
      return sizeof(uint8_t);
  } else if (val >= -bound16 && val < bound16) {
      *((uint16_t *)pbuf) = ((uint16_t )val);    
      return sizeof(uint16_t);
  } else if (val >= -bound32 && val < bound32) {
      *((uint32_t *)pbuf) = ((uint32_t )val);        
      return sizeof(uint32_t);    
  } else {
      *((uint64_t *)pbuf) = ((uint64_t )val);            
      return sizeof(uint64_t);       
  }  
#else
  uint8_t size;

#ifdef WITH_FP
  if (force_64bit)
  {
    *((uint64_t *)pbuf) = ((uint64_t )val);            
    size = sizeof(uint64_t);          
  } else {
#endif  
  
  if (val >= -bound8 && val < bound8) 
      size =  sizeof(uint8_t);
  else if (val >= -bound16 && val < bound16)
      size = sizeof(uint16_t);
  else if (val >= -bound32 && val < bound32)
      size = sizeof(uint32_t);    
  else
      size = sizeof(uint64_t);       

#ifdef WITH_FP
  }
#endif  
  
  for (uint8_t i=0; i<size; i++)
  {
     pbuf[i] = val & 0xff;
     val >>= 8;
  } 
 
  return size;  
#endif
}

/* convert sizeof argument to index in constant list */
static inline uint8_t	_binson_util_sizeof_idx( uint8_t n )
{
 if (n < 4)
   return n;
 else if (n == 4)
   return 3;
 else
   return 4;
}

/* */
static inline void _binson_util_cpy_bbuf( bbuf *dst, bbuf *src )
{
  dst->bptr = src->bptr;
  dst->bsize = src->bsize;
#if defined AVR8 && defined WITH_AVR_PGMSPACE								  
  dst->is_pgm = src->is_pgm;
#endif    
}

/* compare two bytearrays in lexicographical sense.  return value same as  strcmp() */
static inline int16_t  	_binson_util_cmp_bbuf2bbuf( bbuf *bb1, bbuf *bb2 )
{
 const uint8_t *s1 = (const uint8_t *) bb1->bptr;
 const uint8_t *s2 = (const uint8_t *) bb2->bptr;
 binson_tok_size n = MIN(bb1->bsize, bb2->bsize); 
 uint8_t c1 = 0;
 uint8_t c2 = 0;

  do {     
    if (n-- == 0)
      break;      

#if defined AVR8 && defined WITH_AVR_PGMSPACE
      c1 = bb1->is_pgm? pgm_read_byte(s1++) : (uint8_t) *s1++;            
      c2 = bb2->is_pgm? pgm_read_byte(s2++) : (uint8_t) *s2++;      
#else
      c1 = (uint8_t) *s1++;      
      c2 = (uint8_t) *s2++;            
#endif
  }
  while (c1 == c2);
  
  return (c1 == c2)? (bb1->bsize - bb2->bsize) : (c1 - c2);  
}

#ifdef WITH_ORDER_CHECKS
/* */
static inline void 	_binson_util_writer_track_keyorder( binson_writer *pw, int8_t dir_sign )
{
  bbuf   *pb;
  int8_t  tmp_depth = pw->cur_depth + dir_sign;
  
  if (tmp_depth < 0 || tmp_depth >= BINSON_CFG_MAX_DEPTH)
    return;
  else
    pw->cur_depth = (uint8_t)tmp_depth;
  
  pb = &pw->key_stack[(uint8_t)tmp_depth];
  pb->bptr = NULL;
  pb->bsize = 0;
}
#endif