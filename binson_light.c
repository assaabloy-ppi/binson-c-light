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

/*======================== binson_writer methods ===============================*/

static inline void _binson_write_name( binson_writer *pw, const char* pstr );

void binson_write_object_begin( binson_writer *pw );
void binson_write_object_end( binson_writer *pw );
void binson_write_array_begin( binson_writer *pw );
void binson_write_array_end( binson_writer *pw );
void binson_write_boolean( binson_writer *pw, uint8_t bval );
void binson_write_integer( binson_writer *pw, uint64_t ival );
void binson_write_double( binson_writer *pw, double dval );
void binson_write_string( binson_writer *pw, const char* pstr );
void binson_write_name( binson_writer *pw, const char* pstr );
void binson_write_string_with_len( binson_writer *pw, const char* pstr, binson_tok_size len );
void binson_write_bytes( binson_writer *pw, const uint8_t* pbuf, binson_tok_size len );

/*======================== binson_parser methods ===============================*/

void _binson_parser_parse_begin( binson_parser *pp );
void _binson_parser_parse_field_name( binson_parser *pp, uint8_t type_before_name );
void _binson_parser_parse_value( binson_parser *pp, uint8_t type_byte, uint8_t after_value_state );
void _binson_parser_process_lenval( binson_parser *pp, bbuf *pbb, uint8_t len_sizeof ); /* helper to process vatriable length tokens: int+data*/

/*======================== binson_io methods ===================================*/

static inline void	_binson_io_reset( binson_io *io );
static inline void      _binson_io_init( binson_io *io, uint8_t *pbuf, binson_size size );
static inline void	_binson_io_purge( binson_io *io );
static inline uint8_t	_binson_io_write( binson_io *io, const uint8_t *psrc, binson_size sz );
static inline uint8_t	_binson_io_write_byte( binson_io *io, const uint8_t src_byte );
static inline void 	_binson_io_read( binson_io *io, uint8_t *pdst, binson_size sz );
static inline uint8_t	_binson_io_read_byte( binson_io *io );
static inline void	_binson_io_advance( binson_io *io, binson_size offset );
static inline uint8_t*	_binson_io_get_ptr( binson_io *io );

/*======================== utility functions ===================================*/

static uint8_t		_binson_util_pack_integer( int64_t val, uint8_t *pbuf, uint8_t force_64bit );
static int64_t		_binson_util_unpack_integer( uint8_t *pbuf, uint8_t bsize );
static inline uint8_t	_binson_util_sizeof_idx( uint8_t n );

void  	_binson_util_set_bbuf( bbuf *bbuf, uint8_t *bptr, binson_size bsize );
void  	_binson_util_set_bbuf_for_asciiz( bbuf *bbuf, const char* pstr );
void  	_binson_util_cpy_bbuf( bbuf *dst, bbuf *src );
void  	_binson_util_cpy_bbuf2bbuf( bbuf *dst, bbuf *src ); 
int  	_binson_util_cmp_bbuf2bbuf( bbuf *bb1, bbuf *bb2 );
int  	_binson_util_cmp_bbuf2asciiz( bbuf *bb1, const char* pstr );
void	_binson_util_cpy_bbuf2asciiz( char* pstr, bbuf *bb );

/*==============================================================================*/

/* */
void binson_writer_init( binson_writer *pw, uint8_t *pbuf, binson_size buf_size  )
{
  memset( pw, 0, sizeof(binson_writer) );
  _binson_io_init( &(pw->io), pbuf, buf_size );
} 

/* */
void binson_writer_reset( binson_writer *pw )
{
  binson_writer_purge( pw );
  _binson_io_reset( &(pw->io) );
  
  pw->error_flags = 0;
}

/* */
void binson_writer_purge( binson_writer *pw )
{
  _binson_io_purge( &(pw->io) );
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
static inline uint8_t	_binson_io_write( binson_io *io, const uint8_t *psrc, binson_size sz )
{
  io->counter += sz;
  
  if (io->buf_used + sz > io->buf_size)
    return BINSON_ID_BUF_FULL;
  
  if (io->pbuf)
      memcpy( io->pbuf + io->buf_used, psrc, sz );
  
  io->buf_used += sz;
  
  return BINSON_ID_UNKNOWN;
}

/* */
static inline uint8_t	_binson_io_write_byte( binson_io *io, const uint8_t src_byte )
{
  return _binson_io_write( io, &src_byte, 1 );    
}

/* */
static inline void _binson_io_read( binson_io *io, uint8_t *pdst, binson_size sz )
{
  io->counter += sz;
  
  if (io->counter > io->buf_size)
  {
    sz -= io->counter - io->buf_size;
    io->counter = io->buf_size;    
  }
    
  if (pdst && io->pbuf)
      memcpy( pdst, io->pbuf + io->buf_used, sz );
  
  io->buf_used += sz;
}

/* */
static inline uint8_t	_binson_io_read_byte( binson_io *io )
{
  uint8_t b;
  _binson_io_read( io, &b, 1 );
  return b;
}

/* */
static inline void _binson_io_advance( binson_io *io, binson_size offset )
{
  _binson_io_read( io, NULL, offset );
}

/* */
static inline uint8_t*	_binson_io_get_ptr( binson_io *io )
{
  return &(io->pbuf[io->buf_used]);
}

/* */
void  _binson_writer_write_token( binson_writer *pwriter, const uint8_t token_type, binson_value *val )
{
  uint8_t 		res 	= 0;  // write result
  binson_tok_size 	isize 	= 1;  
  UNUSED(res);    
      
  switch (token_type)
  {
    /* optimization: top cases are most probable cases */
    case BINSON_ID_INTEGER:
    case BINSON_ID_STRING_LEN:
    case BINSON_ID_BYTES_LEN:    
    case BINSON_ID_DOUBLE:
    {
      uint8_t pack_buf[ sizeof(int64_t) + 1 ];
      
      isize = _binson_util_pack_integer( val->int_val, &(pack_buf[1]), (token_type == BINSON_ID_DOUBLE)? 1:0 );      
      pack_buf[0] = token_type + ((token_type == BINSON_ID_DOUBLE)? 0 : _binson_util_sizeof_idx( isize )); 
      isize++;      
      res = _binson_io_write( &(pwriter->io), pack_buf, isize );     
     
      break;
    }
    
    case BINSON_ID_STRING:
    case BINSON_ID_BYTES:
    {
      binson_tok_size 	tok_size = val->bbuf_val.bsize;      
      binson_value 	tval;
      
      tval.int_val = tok_size;
      
       // single level of recursuion is not a crime, but still stack size must be monitored
      _binson_writer_write_token( pwriter, token_type+1, &tval ); /* writes sig+len*/
      res = _binson_io_write( &(pwriter->io), val->bbuf_val.bptr, tok_size );  /* writes payload: string (without \0) or bytearray */
      isize += tok_size;
      break;
    }
      
    case BINSON_ID_OBJ_BEGIN:
    case BINSON_ID_ARRAY_BEGIN:              
    case BINSON_ID_OBJ_END:
    case BINSON_ID_ARRAY_END:	
    case BINSON_ID_TRUE:
    case BINSON_ID_FALSE:
      res = _binson_io_write_byte( &(pwriter->io), token_type );
      break;

    case BINSON_ID_BOOLEAN:
      res = _binson_io_write_byte( &(pwriter->io), val->bool_val? BINSON_ID_TRUE : BINSON_ID_FALSE );
      break;    
      
    default:
    return;
  }
     
  if (!res)
    pwriter->error_flags = res;
     
  return;
}

/* */
void binson_write_object_begin( binson_writer *pw )
{
  _binson_writer_write_token( pw, BINSON_ID_OBJ_BEGIN, NULL );
}

/* */
void binson_write_object_end( binson_writer *pw )
{
  _binson_writer_write_token( pw, BINSON_ID_OBJ_END, NULL );  
}

/* */
void binson_write_array_begin( binson_writer *pw )
{
  _binson_writer_write_token( pw, BINSON_ID_ARRAY_BEGIN, NULL );   
}

/* */
void binson_write_array_end( binson_writer *pw )
{
  _binson_writer_write_token( pw, BINSON_ID_ARRAY_END, NULL );  
}

/* */
void binson_write_boolean( binson_writer *pw, uint8_t bval )
{
  pw->tmp_val.bool_val = bval; 
  _binson_writer_write_token( pw, BINSON_ID_BOOLEAN, &(pw->tmp_val) );
}

/* */
void binson_write_integer( binson_writer *pw, uint64_t ival )
{
  pw->tmp_val.int_val = ival; 
  _binson_writer_write_token( pw, BINSON_ID_INTEGER, &(pw->tmp_val) );  
}

/* */
void binson_write_double( binson_writer *pw, double dval )
{
  pw->tmp_val.double_val = dval;
  _binson_writer_write_token( pw, BINSON_ID_DOUBLE, &(pw->tmp_val) );  
}

/* */
void binson_write_string( binson_writer *pw, const char* pstr )
{
  binson_write_string_with_len( pw, pstr, strlen(pstr) );  
}

/* */
void binson_write_name( binson_writer *pw, const char* pstr )
{
  _binson_write_name( pw, pstr );
} 

/* */
static void _binson_write_name( binson_writer *pw, const char* pstr )
{
  pw->tmp_val.bbuf_val.bptr = (uint8_t *)pstr; 
  pw->tmp_val.bbuf_val.bsize = strlen(pstr); 
  _binson_writer_write_token( pw, BINSON_ID_STRING, &pw->tmp_val );  
}

/* */
void binson_write_string_with_len( binson_writer *pw, const char* pstr, binson_tok_size len )
{
  pw->tmp_val.bbuf_val.bptr = (uint8_t *)pstr; 
  pw->tmp_val.bbuf_val.bsize = len; 
 _binson_writer_write_token( pw, BINSON_ID_STRING, &pw->tmp_val );
}

/* */
void binson_write_bytes( binson_writer *pw, const uint8_t* pbuf, binson_tok_size len )
{
  pw->tmp_val.bbuf_val.bptr = (uint8_t *)pbuf; 
  pw->tmp_val.bbuf_val.bsize = len; 
 _binson_writer_write_token( pw, BINSON_ID_BYTES, &pw->tmp_val );  
}

/*======================== PARSER =============================*/

/* */
void binson_parser_init( binson_parser *pp, uint8_t *pbuf, binson_size buf_size )
{
  memset( pp, 0, sizeof(binson_parser) );
  _binson_io_init( &(pp->io), pbuf, buf_size );  
  binson_parser_reset( pp );
}

/* */
void binson_parser_reset( binson_parser *pp )
{
  _binson_io_reset( &(pp->io) );  
  pp->error_flags	= BINSON_ID_OK;
  pp->state		= BINSON_PARSER_STATE_ZERO;
  pp->val_type		= BINSON_ID_UNKNOWN;
  
  _binson_util_set_bbuf( &pp->name, NULL, 0 );
}

/* */
void binson_parser_field( binson_parser *pp, const char *name )
{
  bbuf name_bbuf;
  _binson_util_set_bbuf_for_asciiz( &name_bbuf, name );
    
  while (binson_parser_next_field( pp )) 
  {
    if (!_binson_util_cmp_bbuf2bbuf( &pp->name, &name_bbuf ))  /* if equal */
      return;
  }  
  pp->error_flags = BINSON_ID_PARSE_NO_FIELD_NAME;
}

/* */
bool binson_parser_next_field( binson_parser *pp )
{
    if ( pp->state == BINSON_PARSER_STATE_ZERO )
      _binson_parser_parse_begin( pp );	
    else if ( pp->state == BINSON_PARSER_STATE_END_OF_OBJECT )
    {
        pp->error_flags = BINSON_ID_PARSE_END_OF_OBJECT;
        return false;
    }
    else if ( pp->state == BINSON_PARSER_STATE_BEFORE_OBJECT )
    {
        pp->state = BINSON_PARSER_STATE_BEFORE_FIELD;
        while ( binson_parser_next_field( pp ) ) {}
        pp->state = BINSON_PARSER_STATE_BEFORE_FIELD;
    }
    else if ( pp->state == BINSON_PARSER_STATE_BEFORE_ARRAY )
    {
        pp->state = BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE;
        while ( binson_parser_next_array_value( pp ) ) {}
        pp->state = BINSON_PARSER_STATE_BEFORE_FIELD;
    }

    if ( pp->state != BINSON_PARSER_STATE_BEFORE_FIELD )
    {
        pp->error_flags = BINSON_ID_PARSE_WRONG_STATE;
        return false;
    }
   
    {
      uint8_t type_before_name = _binson_io_read_byte( &pp->io );
      uint8_t type_before_value;
      
      if ( type_before_name == BINSON_ID_OBJ_END )
      {
	pp->state = BINSON_PARSER_STATE_END_OF_OBJECT;
        return false;
      }
      
      _binson_parser_parse_field_name( pp, type_before_name );
       type_before_value = _binson_io_read_byte( &pp->io );
      _binson_parser_parse_value( pp, type_before_value, BINSON_PARSER_STATE_BEFORE_FIELD );
    }

    return true;
}

/* */
bool binson_parser_next_array_value( binson_parser *pp )
{
    if ( pp->state == BINSON_PARSER_STATE_BEFORE_ARRAY )
    {
        pp->state = BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE;
        while ( binson_parser_next_array_value( pp ) ) {}
        pp->state = BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE;
    }

    if ( pp->state == BINSON_PARSER_STATE_BEFORE_OBJECT )
    {
        pp->state = BINSON_PARSER_STATE_BEFORE_FIELD;
        while ( binson_parser_next_field( pp ) ) {}
        pp->state = BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE;
    }

    if ( pp->state != BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE )
    {
        pp->error_flags = BINSON_ID_PARSE_WRONG_STATE;
        return false;
    }

    {
      uint8_t type_byte = _binson_io_read_byte( &pp->io );
      if ( type_byte == BINSON_ID_ARRAY_END )
      {
	  pp->state = BINSON_PARSER_STATE_END_OF_ARRAY;
	  return false;
      }
      _binson_parser_parse_value( pp, type_byte, BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE );
    }
    
    return true;
}

/* */
void binson_parser_go_into_object( binson_parser *pp )
{
    if ( pp->state != BINSON_PARSER_STATE_BEFORE_OBJECT )
      pp->error_flags = BINSON_ID_PARSE_WRONG_STATE;      
    else
      pp->state = BINSON_PARSER_STATE_BEFORE_FIELD;  
}

/* */
void binson_parser_go_into_array( binson_parser *pp )
{
    if ( pp->state != BINSON_PARSER_STATE_BEFORE_ARRAY )
      pp->error_flags = BINSON_ID_PARSE_WRONG_STATE;      
    else      
      pp->state = BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE;
}

/* */
void binson_parser_go_upto_object( binson_parser *pp )
{
    if ( pp->state == BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE )
      while ( binson_parser_next_array_value( pp ) ) {}

    if ( pp->state == BINSON_PARSER_STATE_BEFORE_FIELD )
      while ( binson_parser_next_field( pp ) ) {}

    if ( pp->state != BINSON_PARSER_STATE_END_OF_OBJECT && pp->state != BINSON_PARSER_STATE_END_OF_ARRAY )
      pp->error_flags = BINSON_ID_PARSE_WRONG_STATE; 
    else
      pp->state = BINSON_PARSER_STATE_BEFORE_FIELD;
}

/* */
void binson_parser_go_upto_array( binson_parser *pp )
{
    if ( pp->state == BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE )
      while ( binson_parser_next_array_value( pp ) ) {}

    if ( pp->state == BINSON_PARSER_STATE_BEFORE_FIELD )
      while ( binson_parser_next_field( pp ) ) {}

    if ( pp->state != BINSON_PARSER_STATE_END_OF_OBJECT && pp->state != BINSON_PARSER_STATE_END_OF_ARRAY )
      pp->error_flags = BINSON_ID_PARSE_WRONG_STATE; 
    else  
      pp->state = BINSON_PARSER_STATE_BEFORE_ARRAY_VALUE;
}

/* */
void _binson_parser_parse_begin( binson_parser *pp )
{
    if ( _binson_io_read_byte( &pp->io ) != BINSON_ID_OBJ_BEGIN )
      pp->error_flags = BINSON_ID_PARSE_WRONG_TYPE;
    else
      pp->state = BINSON_PARSER_STATE_BEFORE_FIELD;
}

/* */
void _binson_parser_parse_field_name( binson_parser *pp, uint8_t type_before_name )
{
    switch ( type_before_name ) {
      case BINSON_ID_STRING_8:
      case BINSON_ID_STRING_16:
      case BINSON_ID_STRING_32:
	_binson_parser_process_lenval( pp, &pp->name, 1 << (type_before_name - BINSON_ID_STRING_LEN - 1) );
        break;
	
      default:
        pp->error_flags = BINSON_ID_PARSE_WRONG_TYPE;
    }
}

/* */
void _binson_parser_parse_value( binson_parser *pp, uint8_t type_byte, uint8_t after_value_state )
{
  switch ( type_byte ) {
    case BINSON_ID_OBJ_BEGIN:
        pp->val_type = BINSON_ID_OBJECT;
        pp->state = BINSON_PARSER_STATE_BEFORE_OBJECT;
        break;
    case BINSON_ID_ARRAY_BEGIN:
        pp->val_type = BINSON_ID_ARRAY;
        pp->state = BINSON_PARSER_STATE_BEFORE_ARRAY;
        break;
    case BINSON_ID_FALSE:
    case BINSON_ID_TRUE:
        pp->val_type = BINSON_ID_BOOLEAN;
        pp->val.bool_val = (type_byte == BINSON_ID_TRUE);
        pp->state = after_value_state;
        break;
    case BINSON_ID_DOUBLE:
        pp->val_type = BINSON_ID_DOUBLE;
        pp->val.int_val = _binson_util_unpack_integer ( _binson_io_get_ptr( &pp->io ), 8 );  /* automatic uint64_t -> double translation magic via pp->val union */
        _binson_io_advance ( &pp->io, 8 );
	pp->state = after_value_state;
        break;
    case BINSON_ID_INTEGER_8:
    case BINSON_ID_INTEGER_16:
    case BINSON_ID_INTEGER_32:
    case BINSON_ID_INTEGER_64:
        pp->val_type = BINSON_ID_INTEGER;
        pp->val.int_val = _binson_util_unpack_integer ( _binson_io_get_ptr( &pp->io ), 1 << (type_byte - BINSON_ID_INTEGER - 1) );
	_binson_io_advance ( &pp->io, 1 << (type_byte - BINSON_ID_INTEGER - 1) );
        pp->state = after_value_state;
        break;
    case BINSON_ID_STRING_8:
    case BINSON_ID_STRING_16:
    case BINSON_ID_STRING_32:
      	_binson_parser_process_lenval( pp, &pp->val.bbuf_val, 1 << (type_byte - BINSON_ID_STRING_LEN - 1) );
        pp->val_type = BINSON_ID_STRING;
        pp->state = after_value_state;
        break;
    case BINSON_ID_BYTES_8:
    case BINSON_ID_BYTES_16:
    case BINSON_ID_BYTES_32:
        _binson_parser_process_lenval( pp, &pp->val.bbuf_val, 1 << (type_byte - BINSON_ID_BYTES_LEN - 1) );      
        pp->val_type = BINSON_ID_BYTES;
        pp->state = after_value_state;
        break;
    default:
        pp->error_flags = BINSON_ID_PARSE_WRONG_TYPE;
  }  
}

/* */
void _binson_parser_process_lenval( binson_parser *pp, bbuf *pbb, uint8_t len_sizeof )
{
  binson_size len = ( binson_size ) _binson_util_unpack_integer ( _binson_io_get_ptr ( &pp->io ), len_sizeof );
  _binson_util_set_bbuf ( pbb, _binson_io_get_ptr ( &pp->io ) + len_sizeof, len );
  _binson_io_advance ( &pp->io, len_sizeof + len );
}

/* */
void binson_parser_get_name_copy( binson_parser *pp, char *dst ) 
{
  _binson_util_cpy_bbuf2asciiz( dst, &pp->name );  
}

/* */
int binson_parser_cmp_name( binson_parser *pp, const char *pstr ) 
{ 
  return _binson_util_cmp_bbuf2asciiz( &pp->name, pstr ); 
}

/* */
bool binson_parser_name_equals( binson_parser *pp, const char *pstr ) 
{ 
  return binson_parser_cmp_name( pp, pstr )==0? true:false; 
}


/* */
void binson_parser_get_string_copy( binson_parser *pp, char *dst ) 
{
  _binson_util_cpy_bbuf2asciiz( dst, &pp->val.bbuf_val );  
}

/* */
int binson_parser_cmp_string( binson_parser *pp, const char *pstr ) 
{ 
  return _binson_util_cmp_bbuf2asciiz( &pp->val.bbuf_val, pstr ); 
}

/* */
bool binson_parser_string_equals( binson_parser *pp, const char *pstr ) 
{ 
  return binson_parser_cmp_string( pp, pstr )==0? true:false; 
}

/* */
void binson_parser_get_bytes_copy( binson_parser *pp, bbuf *pbb )
{ 
  _binson_util_cpy_bbuf2bbuf( pbb, &pp->val.bbuf_val ); 
}

/* */
int binson_parser_cmp_bytes( binson_parser *pp, bbuf *pbb ) 
{ 
  return _binson_util_cmp_bbuf2bbuf( &pp->val.bbuf_val, pbb ); 
}

/* */
bool binson_parser_bytes_equals( binson_parser *pp, bbuf *pbb ) 
{ 
  return binson_parser_cmp_bytes( pp, pbb )==0? true:false; 
}


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
  
  if (force_64bit)
  {
    *((uint64_t *)pbuf) = ((uint64_t )val);            
    return sizeof(uint64_t);       
  }
  
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

  if (force_64bit)
  {
    *((uint64_t *)pbuf) = ((uint64_t )val);            
    size = sizeof(uint64_t);          
  } else {
  
  if (val >= -bound8 && val < bound8) 
      size =  sizeof(uint8_t);
  else if (val >= -bound16 && val < bound16)
      size = sizeof(uint16_t);
  else if (val >= -bound32 && val < bound32)
      size = sizeof(uint32_t);    
  else
      size = sizeof(uint64_t);       
  }
  
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
void _binson_util_set_bbuf( bbuf *bbuf, uint8_t *bptr, binson_size bsize )
{
  bbuf->bptr = bptr;
  bbuf->bsize = bsize;
}

/* */
void _binson_util_set_bbuf_for_asciiz( bbuf *bbuf, const char* pstr )
{
  bbuf->bptr = (uint8_t*) pstr;
  bbuf->bsize = strlen( pstr );
}

/* */
void _binson_util_cpy_bbuf( bbuf *dst, bbuf *src )
{
  dst->bptr = src->bptr;
  dst->bsize = src->bsize;
}

/* */
void _binson_util_cpy_bbuf2bbuf( bbuf *dst, bbuf *src )
{
  memcpy( dst->bptr, src->bptr, MIN(dst->bsize, src->bsize) );
}

/* compare two bytearrays in lexicographical sense.  return value same as  strcmp() */
int _binson_util_cmp_bbuf2bbuf( bbuf *bb1, bbuf *bb2 )
{
  int r = memcmp( bb1->bptr, bb2->bptr, MIN(bb1->bsize, bb2->bsize) ); 
  return (r == 0)? (bb1->bsize - bb2->bsize) : r;
}

/* compare zero-terminated string with bytearrays in lexicographical sense.  return value same as  strcmp() */
int _binson_util_cmp_bbuf2asciiz( bbuf *bb1, const char* pstr )
{
  bbuf bb2 = { .bptr = (uint8_t*)pstr, .bsize = (binson_tok_size)strlen(pstr) };
  return _binson_util_cmp_bbuf2bbuf( bb1, &bb2 );
}

/* copy bytearray to zero-terminated string */
void _binson_util_cpy_bbuf2asciiz( char* pstr, bbuf *bb )
{
  memcpy( pstr, bb->bptr, bb->bsize );
  pstr[bb->bsize] = '\0';
}
