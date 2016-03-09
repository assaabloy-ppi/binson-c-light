# binson-c-light

A light-weight C implementation of the Binson serialization format

> Binson is like JSON, but faster, binary and even simpler. See [binson.org](http://binson.org/)


Features
---------

* Written in ANSI C (C99 standard)
* Portable code. Tested at:
  * x86_64 Linux
  * ARM Cortex-M3 (with QEMU)
* Compatible with: 
  * [binson-java](https://github.com/franslundberg/binson-java)
  * [binson-java-light](https://github.com/franslundberg/binson-java-light)
* Has no 3rd party dependencies. (libc only)
* Partial destination buffer allow to stream objects even larger than RAM available

Writer API usage
---------

```
 uint8_t        buf[64];
 int            cnt;
 binson_writer  w;
 
 binson_writer_init( &w, buf, sizeof(buf) );
 
 // {"cid":123}
 binson_write_object_begin( &w ); 
 binson_write_name( &w, "cid" );
 binson_write_integer( &w, 123 );
 binson_write_object_end( &w ); 
 
 cnt = binson_writer_get_counter( &w );
 
 for (int i=0; i<cnt; i++)
   printf( "0x%02x ", buf[i] ); 
```
Will print: 

`
0x40 0x14 0x03 0x63 0x69 0x64 0x10 0x7b 0x41
`

Parser API usage
---------


```
  // { "a":123, "bcd":"Hello world!" }
  const uint8_t src[] = "\x40\x14\x01\x61\x10\x7b\x14\x03\x62\x63\x64\x14\x0c\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x41";
  uint8_t       buf[64];
  binson_parser p;
 
  binson_parser_init( &p, src, sizeof(src) );
 
  binson_parser_field( &p, "a" );
  printf("a: %d\n", (int)binson_parser_get_integer( &p ));
    
  binson_parser_field( &p, "bcd" );
  binson_parser_get_string_copy( &p, buf ); 
  printf("bcd: %s\n", buf);
```
Will print:

```
a: 123
bcd: Hello world!
```


Build
---------

`
$ ./build.sh
`

Resulting binary files will be placed under ./build



