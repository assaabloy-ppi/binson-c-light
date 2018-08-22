# binson-c-light

A light-weight C implementation of the Binson serialization format

> Binson is like JSON, but faster, binary and even simpler. See [binson.org](http://binson.org/)

Features
---------

* Written in c99 standard.
* Portable MCU-friendly code.
* Tested at:
  * x86_64 Linux (gcc, clang)
  * ~~ARM Cortex-M3 (with QEMU)~~
  * ~~ARM Cortex-M4 baremetal (nRF52832 SoC)~~
* Compatible with: 
  * [binson-java](https://github.com/franslundberg/binson-java)
  * [binson-java-light](https://github.com/franslundberg/binson-java-light)
* Has no 3rd party dependencies. (libc only)
* No dynamic memory allocation (in-place parsing)


Limitations
-----------

* Due to no dynamic memory allocation, the maximum levels of nested objects must be defined at compile time by modifying the define BINSON_PARSER_MAX_DEPTH in binson_parser.h
* Maximum array depth limited to 255.

What's new in v3
----------------

* Issues from security audit on v2 fixed.
* Parser callback support (ready to be used as low-level API for "binson-c" project)
* Positioning by index supported for both OBJECT and ARRAY blocks  ( see binson_parser_at() )
* Raw binson encoded block extraction and output supported now (see #8)
* Removed type checks in getters (it's up to user app now)
* Built-in binson-to-string convertion function
* Optimization frendly single-function traversal code.
* Less lines, smaller binary size
* Better unit test coverage.
* Code fixed to be compatible with Clang (std=c99)
* Pass AFL fuzzing tests. (includes custom dict for binson format).

Changes from v2
---------------

* binson_parser_at() removed since it was not used by any projects.
* Verifying of binson object introduced by using binson_parser_verify()
* Parser callback differs from v2.
* 

Looks stable with good unit test coverage, need more eyes for review, API is still a subject of discussion.

API changes in v2:
---------------

* No implicit block level entering: for top-level nor for OBJECT items (e.g. "a":{})
* User level API returns bool (succes/failure), it's up to app to check later "error_flags" if needed.
* All parsing functions are just shortcuts to binson_parser_advance(), controlled with wide range of parameters.
* *_ensure() functions are designed to additionaly check item type (see #8)


TODO in v2:
-----------

* More code review & cleanup
* Add more unit test cases (after code coverage checks)
* Standartized API doc comments in the header/source files (doxygen)
* Try to make quick integration of this project to act as low-level API of binson-c, to proof APIs are valid and flexible enough.


Writer API usage
---------

```c
 uint8_t        buf[64];
 size_t         cnt;
 binson_writer  w;
 
 binson_writer_init( &w, buf, sizeof(buf) );
 
 // {"cid":123}
 binson_write_object_begin(&w); 
 binson_write_name(&w, "cid");
 binson_write_integer(&w, 123);
 binson_write_object_end(&w); 
 
 cnt = binson_writer_get_counter(&w);
 
 for (size_t i = 0; i < cnt; i++)
    printf( "0x%02x ", buf[i] ); 
```
Will print: 

`
0x40 0x14 0x03 0x63 0x69 0x64 0x10 0x7b 0x41
`

Parser API usage
---------


```c
  // { "a":123, "bcd":"Hello world!" }
  const uint8_t src[] = "\x40\x14\x01\x61\x10\x7b\x14\x03\x62\x63\x64\x14\x0c\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x41";
  bbuf          *str;
  uint8_t       buf[64];
  binson_parser p;
 
  binson_parser_init(&p, src, sizeof(src));
 
  binson_parser_go_into(&p);  
  binson_parser_field(&p, "a");
  printf("a: %d\n", (int)binson_parser_get_integer(&p));
    
  binson_parser_field(&p, "bcd");
  str = binson_parser_get_string_bbuf(&p); 
  printf("bcd: %*.*s\n", 0, str->bsize, (char *) str->bptr);
```
Will print:

```
a: 123
bcd: Hello world!
```

