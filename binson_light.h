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

#ifndef BINSON_LIGHT_H_INCLUDED
#define BINSON_LIGHT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*********** build options ***************/  

#define WITH_WRITER_CB	   /* use callback for writer to notify user when warnings/errors happened */
#define WITH_AVR_PGMSPACE  /* build routines to access strings/data in flash memory for avr8 arch */
#define WITH_FP 	   /* with floating point support */
#define WITH_ORDER_CHECKS  /* build code for key lexicographic order tracking  */

/*****************************************/  
/*********** lib configuration ***************/
#include <stdint.h>  
#include <string.h>

#ifdef AVR8
  #define  __LITTLE_ENDIAN	1234
  #define  __BYTE_ORDER 	__LITTLE_ENDIAN
  #undef WITH_FP  
  #ifdef WITH_AVR_PGMSPACE
    #include <avr/pgmspace.h>
  #endif
#else
  #include <endian.h>
#endif

#if !defined AVR8 || !defined WITH_AVR_PGMSPACE
  #define PROGMEM	 /* empty declaration modifier */
  #define strlen_P	strlen
  #define memcpy_P	memcpy
#endif

/* free bytes threshold to begin generating BINSON_ID_BUF_GUARD events */
#ifndef BINSON_CFG_BUF_GUARD_LIMIT
#define BINSON_CFG_BUF_GUARD_LIMIT  16		
#endif

/* If guard threshold is reached allows to send BINSON_ID_BUF_GUARD event to user callback, */
/* and if callback returns nonzero lbrary clears buffer leaving all counters and state unchanged */
/* If build with WITH_WRITER_CB this also valid for writer */
#ifndef BINSON_CFG_BUF_GUARD_ALLOW_PURGE
#define BINSON_CFG_BUF_GUARD_ALLOW_PURGE  1	
#endif

/* Maximum nesting level of binson OBJECT's/ARRAY's */
#ifndef BINSON_CFG_MAX_DEPTH
#define BINSON_CFG_MAX_DEPTH	5
#endif

typedef uint8_t  binson_tok_size;   /* type to keep token length (key and value are separate tokens). uint8_t limits it to 255 bytes */
typedef uint16_t binson_size;       /* type to keep raw data block sizes and offsets */

/*********** lib constants *******************/  

#define BINSON_RAW_SIG_SIZE               1     /* How many bytes occupies type signature */

/*********** usefull macros ******************/  
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define SETBITMASK(x,y) 	(x |= (y))	/* Set bitmask y in byte x*/
#define CLEARBITMASK(x,y) 	(x &= (~y)) 	/* Clear bitmask y in byte x*/
#define CHECKBITMASK(x,y) 	(x & (y)) 	/* Check bitmask y in byte x*/

#define SETBIT(x,b) 		(x |= (1<<b))
#define CLEARBIT(x,b) 		(x &= ~(1<<b))
#define CHECKBIT(x,b) 		(x & (1<<b))

#define UNUSED(x) (void)(x)   /* for unused variable warning suppression */
/*********************************************/  
#define BINSON_ID_UNKNOWN        0x00  
#define BINSON_ID_OBJ_BEGIN      0x40
#define BINSON_ID_OBJ_END        0x41
#define BINSON_ID_ARRAY_BEGIN    0x42
#define BINSON_ID_ARRAY_END      0x43

#define BINSON_ID_BOOLEAN        0x47  /* Meta ID. Converter to one of 2 next consts during serialization */
#define BINSON_ID_TRUE           0x44
#define BINSON_ID_FALSE          0x45
#define BINSON_ID_DOUBLE         0x46

#define BINSON_ID_INTEGER        0x0f  /* Meta ID. Converter to one of 4 next consts during serialization */
#define BINSON_ID_INTEGER_8      0x10
#define BINSON_ID_INTEGER_16     0x11
#define BINSON_ID_INTEGER_32     0x12
#define BINSON_ID_INTEGER_64     0x13

#define BINSON_ID_STRING         0x12  /* Meta ID. Converter to one of 3 next consts during serialization */
#define BINSON_ID_STRING_LEN	 0x13  /* indicates stringLen part of STRING object */
#define BINSON_ID_STRING_8       0x14
#define BINSON_ID_STRING_16      0x15
#define BINSON_ID_STRING_32      0x16

#define BINSON_ID_BYTES          0x16  /* Meta ID. Converter to one of 3 next consts during serialization */
#define BINSON_ID_BYTES_LEN      0x17  /* indicates bytesLen part of BYTES object */
#define BINSON_ID_BYTES_8        0x18
#define BINSON_ID_BYTES_16       0x19
#define BINSON_ID_BYTES_32       0x1a  
  
#define BINSON_ID_BEGIN		 0xe0  /* used in notification callback */
#define BINSON_ID_END		 0xe1  /* used in notification callback */

#define BINSON_ID_WRONG_ORDER	 0xfc  /* some fields are out of lexicographic order */
#define BINSON_ID_BUF_GUARD	 0xfd
#define BINSON_ID_BUF_FULL	 0xfe
#define BINSON_ID_PARSING_ERROR  0xff

typedef struct bbuf    /* buffer pointer + size aggregation */ 
{    
  uint8_t              *bptr;
  binson_tok_size	bsize;

#if defined AVR8 && defined WITH_AVR_PGMSPACE	
  uint8_t               is_pgm;
#endif  
  
} bbuf;

typedef union binson_value {

    uint8_t   bool_val;
    int64_t   int_val;
    
#ifdef WITH_FP
    double    double_val;
#endif
    
    bbuf bbuf_val;
    
} binson_value;  

/* smart buffer structure used for both writer and parser */
typedef struct binson_io {
  
  uint8_t      *pbuf;
  binson_size  	buf_size;
  binson_size   buf_used;  
  binson_size   counter;
  
} binson_io;  

/*======================== WRITER ===============================*/

typedef struct _binson_writer binson_writer; /* forward decl */
typedef uint8_t (*binson_writer_cb)(binson_writer *obj, uint8_t event_id, void* param );

#define BINSON_WRITER_MODE_BIT_IGNORE_ERR	0x01  /* Bit 0. Continue processing, ignoring error flags in state_flag */

#define BINSON_WRITER_STATE_BIT_WRONG_ORDER	0x01  /* bit 0 */
#define BINSON_WRITER_STATE_BIT_BUF_FULL	0x02  /* bit 1 */
#define BINSON_WRITER_STATE_MASK_ERROR		0x07  /* bits 0-2 */

typedef struct _binson_writer {

  //uint8_t   	mode_flags;  
  uint8_t   	state_flags;  /* state bitflags: errors, etc */
  
  binson_io     io;  /* smart buffer */
  
  binson_value  tmp_val;		/* used to simplify passing simple types to/from meta functions */
  
#ifdef WITH_WRITER_CB
  binson_writer_cb  cb;   
#endif  

#ifdef WITH_ORDER_CHECKS
  uint8_t cur_depth;
  bbuf    key_stack[ BINSON_CFG_MAX_DEPTH ];  /* used to store prevoius key written to verify lexicographic ordering in realtime */
#endif     
} _binson_writer;
  
void binson_writer_init( binson_writer *pw, uint8_t *pbuf, binson_size buf_size, binson_writer_cb cb );
void binson_writer_reset( binson_writer *pw );
void binson_writer_purge( binson_writer *pw );

inline binson_size binson_writer_get_counter( binson_writer *pw ) { return pw->io.counter; }
inline uint8_t binson_writer_state( binson_writer *pw, uint8_t bitmask ) { return CHECKBITMASK(pw->state_flags, bitmask ); }

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
#else
#define binson_write_string_p		binson_write_string
#define binson_write_name_p		binson_write_name
#define binson_write_string_with_len_p	binson_write_string_with_len
#define binson_write_bytes_p		binson_write_bytes
#endif

/*======================== PARSER ===============================*/

/*  event structure is used to pass  found token details to user's callback function */
typedef struct binson_event {

  uint8_t   id;
  
  uint8_t  *pkey;
  uint8_t   key_len;
  
  uint8_t  *pval;
  uint8_t   val_len;  
  
} binson_event;

typedef struct binson_parser binson_parser; /* forward decl */
typedef uint8_t (*binson_parser_cb)(binson_parser *obj, void* param );

struct binson_parser {

  //uint8_t   	mode_flags;  
  uint8_t   	state_flags;
  
  binson_io    	io;  /* smart buffer */
  
  binson_event      event;
  binson_parser_cb  cb;    /* single callback used to pass all found type of tokens to lib's user */
};

uint8_t      binson_parser_init( binson_parser *pparser );
//#define      binson_parser_purge_buf( pparser )  (pparser->buf_used = 0);

/*======================== UTIL ===============================*/

#ifdef __cplusplus
}
#endif

#endif /* BINSON_LIGHT_H_INCLUDED */