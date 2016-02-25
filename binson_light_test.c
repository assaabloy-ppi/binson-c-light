
#include <stdint.h>
#include <math.h>
#include <stdio.h>

#include "binson_light.h"
				
			
/* AVR8 only: data marked as PROGMEM stored in flash memory */	
#if defined AVR8 && defined WITH_AVR_PGMSPACE	
const char abc_p [] PROGMEM = "abc";
const char cab_p [] PROGMEM = "cab";
const uint8_t bytes_p[] PROGMEM = { 0x00, 0x81, 0x00, 0xff, 0x00 };
#endif
				
/*======== CRC ========*/			
#define CRC_POLYNOMIAL 0x8005
typedef uint16_t crc;

#define CRC_WIDTH  (8 * sizeof(crc))
#define CRC_TOPBIT (1 << (CRC_WIDTH - 1))

crc crc_16(uint8_t const *msg, uint8_t n)
{
    crc  rm = 0;	

    for (uint8_t byte = 0; byte < n; ++byte)
    {
        rm ^= (msg[byte] << (CRC_WIDTH - 8));
        for (uint8_t bit = 8; bit > 0; --bit)
	  rm = (rm & CRC_TOPBIT)? (rm << 1) ^ CRC_POLYNOMIAL : (rm << 1);
    }
    return rm;
}

/*=====================*/
#define UT_TEST(x)	test_no++; \
			if (crc_16(w->io.pbuf, w->io.counter) != x) return test_no; \
			binson_writer_reset( w );
			  
#define UT_RUN(x)	res = (x); \
			if (res == -1) putchar('+'); else { putchar(48 + (char)res); failures++; } \
			putchar('\n'); 

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
#ifdef WITH_FP 
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
#endif
/*=====================*/
int8_t  test_writer_string( binson_writer *w )
{
  const char s1[] = "";
  const char s2[] = "abcd";  
  const char s3[] = "größer";  
  
  int8_t test_no = -1;
  binson_writer_reset( w );
    
  binson_write_string( w, s1 );  		UT_TEST(0x7800);  
  binson_write_string( w, s2 );  		UT_TEST(0xb910);  
  binson_write_string( w, s3 );  		UT_TEST(0x63bc);  
  
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
  binson_write_object_end( w );  	UT_TEST(0x0b1a);
    
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
#if defined AVR8 && defined WITH_AVR_PGMSPACE	
uint8_t  test_writer_progmem( binson_writer *w )
{
  int8_t test_no = -1;
  binson_writer_reset( w );

  // {"abc":false}
  binson_write_object_begin( w );    
  binson_write_name_p( w, abc_p );
  binson_write_boolean( w, 0 );
  binson_write_object_end( w );		  	UT_TEST(0xbd8e); 
  
  
  // {"abc":"cab", "ca":"0x008100ff00"}
  binson_write_object_begin( w );    
  binson_write_name_p( w, abc_p );
  binson_write_string_p( w, cab_p );
  binson_write_string_with_len_p( w, cab_p, 2 );
  binson_write_bytes_p( w, bytes_p, sizeof(bytes_p) );
  binson_write_object_end( w );		  	UT_TEST(0xde43); 
    
  return -1;
}
#endif


#if defined AVR8
 #ifndef F_CPU
    #define 16000000UL
#endif // F_CPU

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>


#define set_bit(target, num)    (   target |=   _BV(num))
#define clear_bit(target, num)  (   target &=   ~ _BV(num))
#define toggle_bit(target, num) (   target ^=   _BV(num))

#define DELAY_IN_MS 100 /* 1 sec */

#define BAUD 19200
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int ubrr)
{
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /*Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 1 stop bit */
  UCSR0C = (1<<UCSZ00) | (1 << UCSZ01);
}

/*
void USART_Transmit(unsigned char data )
{
  / Wait for empty transmit buffer /
  while ( !( UCSR0A & (1<<UDRE0)) )
  {
    _delay_ms(1);
  }
  UDR0 = data;
}*/

void uart_putchar(char c, FILE *stream)
{
  if (c == '\n')
     uart_putchar('\r', stream);
  
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
}
#endif

/*=====================*/
int main(void)
{
 int8_t res = -1;
 int8_t failures = 0;
 
 uint8_t buf[128];
 binson_writer w;
 
 binson_writer_init( &w, buf, sizeof(buf), NULL );
 
#ifdef AVR8 
 FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
 USART_Init(MYUBRR);
 stdout = stderr = &uart_str;
 
while(1) 
{
#endif
  
 putchar('\n');
 putchar('1'); UT_RUN( test_writer_boolean( &w ) );
 putchar('2'); UT_RUN( test_writer_integer( &w ) );
#ifdef WITH_FP 
 putchar('3'); UT_RUN( test_writer_double( &w ) );
#endif 
 putchar('4'); UT_RUN( test_writer_string( &w ) );
 putchar('5'); UT_RUN( test_writer_bytes( &w ) );
 putchar('6'); UT_RUN( test_writer_structure( &w ) );

#if defined AVR8 && defined WITH_AVR_PGMSPACE	
 putchar('7'); UT_RUN( test_writer_progmem( &w ) ); 
#endif
  
 putchar('\n'); putchar('\n');
#ifdef AVR8  
 _delay_ms(1000);
}
#endif

  return failures;
}
