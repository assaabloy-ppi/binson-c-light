
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "binson_light.h"
						
/*======== CRC ========*/			
#define CRC_POLYNOMIAL 0x8005
typedef uint16_t crc;

#define CRC_WIDTH  (8 * sizeof(crc))
#define CRC_TOPBIT (1 << (CRC_WIDTH - 1))

crc crc_16(uint8_t const *msg, unsigned int n)
{
    crc  rm = 0;	

    for (uint8_t byte = 0; byte < n; ++byte)
    {
        rm ^= (crc)(msg[byte] << (CRC_WIDTH - 8));
        for (uint8_t bit = 8; bit > 0; --bit)
	      rm = (crc)((rm & CRC_TOPBIT)? (rm << 1) ^ CRC_POLYNOMIAL : (rm << 1));
    }
    return rm;
}

void intToHex(int intnumber, char *txt)
{    
    unsigned char _s4='0';
    char i=4;
    //intnumber=0xffff;

    do {
        i--;
        _s4 = (unsigned char)  ((intnumber >> i*4 ) & 0x000f);
        if(_s4<10)
            _s4=_s4+48;
        else
            _s4=_s4+55;

        *txt++= _s4;    
    } while(i);     
}

void print_hex_byte(uint8_t src_byte)
{
    unsigned char _s2='0';
    char i=2;

    do {
        i--;
        _s2 = (unsigned char)  ((src_byte >> i*4 ) & 0x0f);
        if(_s2<10)
            _s2=_s2+48;
        else
            _s2=_s2+55;

        putchar(_s2);    
    } while(i);   
}

/*=====================*/
#define UT_TEST(x)	test_no++; \
			if (crc_16(w->io.pbuf, w->io.counter) != x) return test_no; \
			binson_writer_reset( w );
			  
#define UT_RUN(x)	res = (x); \
			if (res == -1) putchar('+'); else { putchar( (unsigned char)(48+res)); failures++; } \
			putchar('\n'); 

#define assert_flags(x) \
      if (x->error_flags != BINSON_ID_OK ) \
         { fputs("error_flags=", stdout); print_hex_byte(x->error_flags); fputs(" state=", stdout); print_hex_byte(x->state); }

/*=====================*/
int8_t  test_writer_boolean( binson_writer *w )
{
  int8_t test_no = -1;
  binson_writer_reset( w );
  
  binson_write_boolean( w, 0 );		UT_TEST(0x819d);
  binson_write_boolean( w, 1 );		UT_TEST(0x0198);
  binson_write_boolean( w, 255 );	UT_TEST(0x0198);  
  
  return -1;
}

/*=====================*/
int8_t  test_writer_integer( binson_writer *w )
{
  int8_t test_no = -1;
  binson_writer_reset( w );
  
  binson_write_integer( w, 0 );  		UT_TEST(0xe003);
  binson_write_integer( w, 55 );  		UT_TEST(0x60b2);
  binson_write_integer( w, -55 );  		UT_TEST(0xe2b5);
  binson_write_integer( w, 128 );  		UT_TEST(0x815d);
  binson_write_integer( w, -128 );  		UT_TEST(0x6300);
  binson_write_integer( w, 212 );  		UT_TEST(0x795b);
  binson_write_integer( w, -212 );  		UT_TEST(0x6b55);
  binson_write_integer( w, 12345 );  		UT_TEST(0x97f4);
  binson_write_integer( w, -12345 );  		UT_TEST(0x91fa);
  binson_write_integer( w, 4294967294L );  	UT_TEST(0xfead);
  binson_write_integer( w, -4294967294L );  	UT_TEST(0x4c86);
  binson_write_integer( w, INT64_MAX );  	UT_TEST(0xed81);
  binson_write_integer( w, INT64_MIN );  	UT_TEST(0x6fa0);
  
  return -1;
}

/*=====================*/
int8_t  test_writer_double( binson_writer *w )
{
  int8_t test_no = -1;
  binson_writer_reset( w );

  binson_write_double( w, +0.0 );  		UT_TEST(0x8d46);
  binson_write_double( w, -0.0 );  		UT_TEST(0x0e45);  
  binson_write_double( w, 3.1415e+10 );  	UT_TEST(0x485b);  
  binson_write_double( w, -3.1415e-10 );  	UT_TEST(0xee49);  
  binson_write_double( w, NAN );  		UT_TEST(0x1c4b);
  binson_write_double( w, INFINITY );  		UT_TEST(0xac48);
  binson_write_double( w, -INFINITY );  	UT_TEST(0x2f4b);  
  
  return -1;
}
/*=====================*/
int8_t  test_writer_string( binson_writer *w )
{
  const char s1[] = "";
  const char s2[] = "abcd";  
  const char s3[] = "größer";  
  
  int8_t test_no = -1;
  binson_writer_reset( w );
    
  binson_write_string( w, s1 );  		UT_TEST(0x7800);  
  binson_write_name( w, s1 );  			UT_TEST(0x7800);  
  
  binson_write_string( w, s2 );  		UT_TEST(0xb910);  
  binson_write_name( w, s2 );  			UT_TEST(0xb910);  
  
  binson_write_string( w, s3 );  		UT_TEST(0x63bc);  
  binson_write_name( w, s3 );  			UT_TEST(0x63bc);  
  
  binson_write_string_with_len( w, s2, 3);	UT_TEST(0xf0bb);  
       
  return -1;
}

/*=====================*/
int8_t  test_writer_bytes( binson_writer *w )
{
  const uint8_t b1[] = { 0x00, 0x81, 0x00, 0xff, 0x00 };  
  
  int8_t test_no = -1;
  binson_writer_reset( w );
  
  binson_write_bytes( w, b1, sizeof(b1) );	UT_TEST(0x97b6);  
  
  return -1;  
}

/*=====================*/
int8_t  test_writer_structure( binson_writer *w )
{
  const uint8_t b1[] = { 0x00, 0x81, 0x00, 0xff, 0x00 }; 
  const char s0[] = "";  
  const char b[] = "b";
  const char abc[] = "abc";  
  const char cba[] = "cba";   
  
  int8_t test_no = -1;
  binson_writer_reset( w );
  
  // {}
  binson_write_object_begin( w );
  binson_write_object_end( w );		UT_TEST(0x8180);
      
  // {"爅웡":123}
  binson_write_object_begin( w );
  binson_write_name( w, "爅웡" );  
  binson_write_integer( w, 123 );  
  binson_write_object_end( w );		UT_TEST(0x313d);  
  
  // {"":{"":{"":{}}}}
  binson_write_object_begin( w );
  binson_write_name( w, s0 );
  binson_write_object_begin( w );
  binson_write_name( w, s0 );
  binson_write_object_begin( w );
  binson_write_name( w, s0 );
  binson_write_object_begin( w );
  binson_write_object_end( w );
  binson_write_object_end( w );
  binson_write_object_end( w );
  binson_write_object_end( w );  	
  //for (uint8_t i=0; i<w->io.counter; i++) printf("0x%02x ", *(w->io.pbuf+i));
  UT_TEST(0x0b1a);  
  
  // {"abc":{"cba":{}}, "b":{"abc":{}}}
  binson_write_object_begin( w );
  binson_write_name( w, abc );
  binson_write_object_begin( w );
  binson_write_name( w, cba );
  binson_write_object_begin( w );
  binson_write_object_end( w );
  binson_write_object_end( w );
  binson_write_name( w, b );
  binson_write_object_begin( w );  
  binson_write_name( w, abc );  
  binson_write_object_begin( w );    
  binson_write_object_end( w );
  binson_write_object_end( w );
  binson_write_object_end( w );  	UT_TEST(0x84e3);
  
  // {"b":[[[]]]}
  binson_write_object_begin( w );  
  binson_write_name( w, b );  
  binson_write_array_begin( w );     
  binson_write_array_begin( w );     
  binson_write_array_begin( w );     
  binson_write_array_end( w );     
  binson_write_array_end( w );     
  binson_write_array_end( w );     
  binson_write_object_end( w );  	UT_TEST(0x6c11);  
  
  // {"b":[[],{},[]]}
  binson_write_object_begin( w );  
  binson_write_name( w, b );  
  binson_write_array_begin( w );     
  binson_write_array_begin( w );     
  binson_write_array_end( w );   
  binson_write_object_begin( w );    
  binson_write_object_end( w );
  binson_write_array_begin( w );     
  binson_write_array_end( w );   
  binson_write_array_end( w );     
  binson_write_object_end( w );  	UT_TEST(0xfe2b);
  
  // {"b":[[{}],[{}]]} 
  binson_write_object_begin( w );  
  binson_write_name( w, b );  
  binson_write_array_begin( w );     
  binson_write_array_begin( w );     
  binson_write_object_begin( w );    
  binson_write_object_end( w );
  binson_write_array_end( w );     
  binson_write_array_begin( w );     
  binson_write_object_begin( w );    
  binson_write_object_end( w );
  binson_write_array_end( w );     
  binson_write_array_end( w );     
  binson_write_object_end( w );  	UT_TEST(0x3f53);  
  
  // {"b":[true,13,"cba",{"abc":false, "b":"0x008100ff00", "cba":"abc"},9223372036854775807]}  
  binson_write_object_begin( w );  
  binson_write_name( w, b );  
  binson_write_array_begin( w );  
  binson_write_boolean( w, 1 );
  binson_write_integer( w, 13 );
  binson_write_string( w, cba );  
  binson_write_object_begin( w );  
  binson_write_name( w, abc );  
  binson_write_boolean( w, 0 );  
  binson_write_name( w, b );  
  binson_write_bytes( w, b1, sizeof(b1) );
  binson_write_name( w, cba );  
  binson_write_string( w, abc );    
  binson_write_object_end( w );
  binson_write_integer( w, 9223372036854775807 );    
  binson_write_array_end( w );      
  binson_write_object_end( w );  	UT_TEST(0x9202);  
  
  return -1;
}

/*=====================*/
int8_t test_parser_1( binson_parser *p )
{
  int8_t test_no = -1;  
  UNUSED(test_no);

  char  strbuf[128];   // buffer used to convert bbuf strings to asciiz
  int64_t  t_int;
  
  // { "a":123, "bcd":"Hello world!" }
  const uint8_t b1[] = "\x40\x14\x01\x61\x10\x7b\x14\x03\x62\x63\x64\x14\x0c\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x41";  

  memcpy( p->io.pbuf, b1, sizeof(b1) );  
  binson_parser_reset( p );
  assert_flags(p);

  /* testing begin here */
  assert(binson_parser_field( p, "a" )); assert_flags(p);
  t_int = binson_parser_get_integer( p );  assert_flags(p); assert(t_int == 123);
      
  assert(binson_parser_field( p, "bcd" ));  assert_flags(p);
  binson_parser_get_string_copy( p, strbuf ); 
  assert_flags(p);
  assert( !strcmp(strbuf, "Hello world!") );
  
  return -1;  
}

/*=====================*/
int8_t test_parser_array1(binson_parser *p)
{
  int8_t test_no = -1;  
  UNUSED(test_no);

  // {"a":[{"d":false},{"e":true},9223372036854775807]}
  const uint8_t b1[]  =
    "\x40\x14\x01\x61"
        "\x42"
           "\x40"
                "\x14\x01\x64\x45"
            "\x41"
            "\x40"
                "\x14\x01\x65\x44"
            "\x41"
            "\x13\xff\xff\xff\xff\xff\xff\xff\x7f"
       "\x43"
    "\x41";

  int64_t fff = 0;

  binson_parser_init(p, (uint8_t*)&b1, sizeof(b1));
  //binson_parser_reset( p );
  binson_parser_field( p, "a" );
  //binson_parser_go_into_array( p );

  //assert(binson_parser_next_array_value( p ));

  binson_parser_go_into_object( p );
  binson_parser_field( p, "d" );
  assert(binson_parser_get_boolean(p) == false);
  binson_parser_go_upto_object( p );

  //p->state = 0x02;
  //assert(binson_parser_next_array_value( p ));
  binson_parser_go_into_object( p );

  binson_parser_field( p, "e" );
  assert(binson_parser_get_boolean(p) == true);
  binson_parser_go_upto_object( p );

  //p->state = 0x02;
  assert(binson_parser_next_array_value( p ));

  fff = binson_parser_get_integer( p );
  assert(fff == 9223372036854775807);

  binson_parser_go_upto_array( p );

  return -1;
}

/*=====================*/
int8_t test_parser_basic( binson_parser *p )
{
  int8_t test_no = -1;  
  UNUSED(test_no);

  char  strbuf[128];   // buffer used to convert bbuf strings to asciiz
  
  // { "a":123, "bcd":"Hello world!" }
  const uint8_t b1[] = "\x40\x14\x01\x61\x10\x7b\x14\x03\x62\x63\x64\x14\x0c\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x41";  
  
  binson_parser_reset( p );
  
  // { "a":123, "bcd":"Hello world!" }
  memcpy( p->io.pbuf, b1, sizeof(b1) );
  
  binson_parser_field( p, "a" );  assert( p->error_flags == BINSON_ID_OK );  
  assert( p->error_flags == BINSON_ID_OK );
  assert( binson_parser_get_integer( p ) == 123 );
    
  binson_parser_field( p, "bcd" );  assert( p->error_flags == BINSON_ID_OK );
  binson_parser_get_string_copy( p, strbuf ); 
  assert( p->error_flags == BINSON_ID_OK );
  assert( !strcmp(strbuf, "Hello world!") );
  
  return -1;  
}

/*=====================*/
int8_t test_parser_lenfuzz( binson_parser *p )
{
  int8_t test_no = -1;
  UNUSED(test_no);

  char  strbuf[128];   // buffer used to convert bbuf strings to asciiz

  // { "a":123, "bcd":"Hello world!" }
  const uint8_t b1[] = "\x40\x14\x01\x61\x10\x7b\x14\x03\x62\x63\x64\x14\x0c\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x41";
  uint8_t i;

  for (i=0; i<=254; i++)
  {
     binson_parser_reset( p );
     // { "a":123, "bcd":"Hello world!" }
     memcpy( p->io.pbuf, b1, sizeof(b1) );
     p->io.pbuf[12] = i;   // simulate broken length

     binson_parser_field( p, "bcd" );
     if (p->error_flags != BINSON_ID_OK)
         continue;

     binson_parser_get_string_copy( p, strbuf );
  }

  return -1;
}


/*=====================*/
int main(void)
{
 int res = -1;
 int failures = 0;
 
 uint8_t buf[128];
 binson_writer w;
 binson_parser p;
 
 binson_writer_init( &w, buf, sizeof(buf) );
 binson_parser_init( &p, buf, sizeof(buf) );
   
 fputs("\n", stdout);
 fputs("w1", stdout); UT_RUN( test_writer_boolean( &w ) );
 fputs("w2", stdout); UT_RUN( test_writer_integer( &w ) );
 fputs("w3", stdout); UT_RUN( test_writer_double( &w ) );
 fputs("w4", stdout); UT_RUN( test_writer_string( &w ) );
 fputs("w5", stdout); UT_RUN( test_writer_bytes( &w ) );
 fputs("w6", stdout); UT_RUN( test_writer_structure( &w ) );
 fputs("\n", stdout);

 fputs("p1", stdout); UT_RUN( test_parser_1( &p ) ); 
 fputs("p2", stdout); UT_RUN( test_parser_array1( &p ) ); 


 fputs("p11", stdout); UT_RUN( test_parser_basic( &p ) );
 fputs("p12", stdout); UT_RUN( test_parser_lenfuzz( &p ) );  
 fputs("\n\n", stdout);
 fflush(stdout);

 return failures;
}
