
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#include "binson_light.h"

#define BUF_SIZE	128
#define GUARD_SPACE_LEN	16

#ifndef UNUSED
#define UNUSED(x) (void)(x)   /* for unused variable warning suppression */
#endif

const char  name_cid[]  = "cid";
const char  name_cmd[]  = "cmd";
const char  name_data[]  = "data";
const char  cmd_reqest[]  = "req";
const char  cmd_ack[]  = "ack";
const uint8_t data_bin1[]  = { 0x01, 0x02, 0x03 };

/* */
binson_size gen_msg( binson_writer *pw, uint16_t cid )
{  
  
  binson_writer_reset( pw );

  // {"cid":123, "cmd":"req", "data":"0x008100ff00"}
  binson_write_object_begin( pw );    

  binson_write_name( pw, name_cid );
  binson_write_integer( pw, cid );  
  binson_write_name( pw, name_cmd );  
  binson_write_string( pw, cmd_reqest );
  binson_write_name( pw, name_data );    
  binson_write_bytes( pw, data_bin1, sizeof(data_bin1) );
  binson_write_object_end( pw );	  
  
  return binson_writer_get_counter( pw );
}

/* */
void parser_demo1( binson_parser *p )
{
  uint8_t  src[256];
  int64_t fff = 0;;
  char     strbuf[32];   // buffer used to convert bbuf strings to asciiz  
  
  // {"a":[true,13,-2.34,"zxc",{"d":false, "e":"0x030405", "q":"qwe"},9223372036854775807]}
  const uint8_t b1[]  = "\x40\x14\x01\x61\x42\x44\x10\x0d\x46\xb8\x1e\x85\xeb\x51\xb8\x02\xc0\x14\x03\x7a\x78\x63\x40\x14\x01\x64\x45\x14\x01\x65\x18\x03\x03\x04\x05\x14\x01\x71\x14\x03\x71\x77\x65\x41\x13\xff\xff\xff\xff\xff\xff\xff\x7f\x43\x41";
  
  binson_parser_init( p, src, sizeof(src) );
  memcpy( src, b1, sizeof(b1) );  
  
  binson_parser_go_into( p );
  binson_parser_field( p, "a" );
  binson_parser_go_into_array( p );
  binson_parser_next_array_value( p );
  printf( "%d\n", binson_parser_get_boolean( p ) );
  
  binson_parser_next_array_value( p );
  printf( "%"PRId64"\n", binson_parser_get_integer( p ) );
  
  binson_parser_next_array_value( p );
  printf( "%lf\n", binson_parser_get_double( p ) );
  
  binson_parser_next_array_value( p );
  binson_parser_get_string_copy( p, strbuf ); 
  printf( "`%s`\n", strbuf );    
  
  binson_parser_next_array_value( p );
  binson_parser_go_into_object( p );
  binson_parser_field( p, "d" );
  printf( "d: %d\n", binson_parser_get_boolean( p ) );
  
  binson_parser_field( p, "e" );
  if ( binson_parser_get_type( p ) == BINSON_ID_BYTES )
    for (int i=0; i<(int)p->val.bbuf_val.bsize; i++)
      printf( "0x%02x ", p->val.bbuf_val.bptr[i] );
  
  binson_parser_field( p, "q" );
  binson_parser_get_string_copy( p, strbuf ); 
  printf( "\n`%s`\n", strbuf );        
    
  binson_parser_go_up( p );
  binson_parser_next_array_value( p );
  //printf( "%"PRId64"\n", binson_parser_get_integer( p )  );   
  fff = binson_parser_get_integer( p );
  printf( "%"PRId64"\n", fff  );   
}

/* */
int main()
{   
  binson_writer  w;
  binson_parser  p;
  binson_size    sz;
  
  binson_writer_init( &w, NULL, 0 );
  
  sz = gen_msg( &w, INT16_MAX );
  
  // use local block here to allocate dynamic sized buffer in stack instead of malloc
  {  
    uint8_t        buf[sz + GUARD_SPACE_LEN];
    binson_size    cnt;
    
    binson_writer_init( &w, buf, sz + GUARD_SPACE_LEN );  
    cnt = gen_msg( &w, 123 );
     
    printf("sz: %u, cnt: %u\n", sz, cnt);  // for ARM32 replace %u to %lu
    for (uint8_t i=0; i<cnt; i++) printf("0x%02x ", buf[i]);
    putchar('\n');
  }    
  // be carefull because 'buf' doesnt exist now 
  
  parser_demo1( &p ); 
  
  return 0;
}
