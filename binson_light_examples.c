
#include <stdint.h>
#include <math.h>
#include <stdio.h>

#ifdef AVR8   
#include <avr/io.h> 
#include <util/delay.h> 
#endif

#include "binson_light.h"

#define BUF_SIZE	128
#define GUARD_SPACE_LEN	16

#ifndef UNUSED
#define UNUSED(x) (void)(x)   /* for unused variable warning suppression */
#endif

// PROGMEM modifier is required to place static data in program space (flash memory) on AVR8
const char  name_cid[] PROGMEM = "cid";
const char  name_cmd[] PROGMEM = "cmd";
const char  name_data[] PROGMEM = "data";
const char  cmd_reqest[] PROGMEM = "req";
const char  cmd_ack[] PROGMEM = "ack";
const uint8_t data_bin1[] PROGMEM = { 0x01, 0x02, 0x03 };

/* writer callback */
uint8_t gen_cb( binson_writer *pw, uint8_t event_id, void* param )
{
  UNUSED(pw); UNUSED(param);
  
  switch (event_id)
  {
    case BINSON_ID_WRONG_ORDER:
      printf("\n*WRONG_ORDER*\n");
      break;

    case BINSON_ID_BUF_GUARD:
      printf("\n*BUF_GUARD*\n");
      break;

    case BINSON_ID_BUF_FULL:
      printf("\n*BUF_FULL*\n");      
    break;    
    
    default:
    break;
  }
  return 0;
}

/* */
binson_size gen_msg( binson_writer *pw, uint16_t cid )
{  
  binson_writer_reset( pw );

  // {"cid":123, "cmd":"req", "data":"0x008100ff00"}
  binson_write_object_begin( pw );    

  binson_write_name_p( pw, name_cid );
  binson_write_integer( pw, cid );  
  binson_write_name_p( pw, name_cmd );  
  binson_write_string_p( pw, cmd_reqest );
  binson_write_name_p( pw, name_data );    
  binson_write_bytes_p( pw, data_bin1, sizeof(data_bin1) );
  binson_write_object_end( pw );	  
  
  return binson_writer_get_counter( pw );
}

#ifdef AVR8  
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

void uart_putchar(char c, FILE *stream)
{
  if (c == '\n')
     uart_putchar('\r', stream);
  
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
}

#endif

/* */
int main()
{ 
  binson_writer  w;
  binson_size    sz;
  
  binson_writer_init( &w, NULL, 0, NULL );  
  sz = gen_msg( &w, INT16_MAX );
  
#ifdef AVR8   
  FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);  
  USART_Init(MYUBRR);  
  stdout = stderr = &uart_str;  
  
  while(1)
#endif    
  // use local block here to allocate dynamic sized buffer in stack instead of malloc
  {  
    uint8_t        buf[sz + GUARD_SPACE_LEN];
    binson_size    cnt;
    
    binson_writer_init( &w, buf, sz + GUARD_SPACE_LEN, gen_cb );  
    cnt = gen_msg( &w, 123 );
     
    printf("sz: %d, cnt: %d\n", sz, cnt);
    for (uint8_t i=0; i<cnt; i++) printf("0x%02x ", buf[i]);
    putchar('\n');
    
#ifdef AVR8  
 _delay_ms(1000);
#endif
  }    
  // be carefull because 'buf' doesnt exist now 
  
  return 0;
}