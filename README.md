[![Build Status](https://travis-ci.org/assaabloy-ppi/binson-c-light.svg?branch=master)](https://travis-ci.org/assaabloy-ppi/binson-c-light) [![codecov](https://codecov.io/gh/assaabloy-ppi/binson-c-light/branch/master/graph/badge.svg)](https://codecov.io/gh/assaabloy-ppi/binson-c-light)


# binson-c-light

A light-weight C implementation of the Binson serialization format

> Binson is like JSON, but faster, binary and even simpler. See [binson.org](http://binson.org/)

Features
---------

* Written in c99 standard.
* Portable MCU-friendly code.
* Tested at:
  * x86_64 Linux (gcc, clang)
  * ARM Cortex-M3
  * ARM Cortex-M4 (nRF52832 and nRF52840 SoC)
* Compatible with:
  * [binson-java](https://github.com/franslundberg/binson-java)
  * [binson-java-light](https://github.com/franslundberg/binson-java-light)
* Has no 3rd party dependencies. (libc only)
* No dynamic memory allocation (in-place parsing)

Limitations
-----------

* Due to no dynamic memory allocation, the maximum levels of nested objects must be defined when defining the parser. See examples below.
* Maximum array depth limited to 255.

What's new in v3
----------------

* Issues from security audit on v2 fixed.
* Parser callback support (ready to be used as low-level API for "binson-c" project)
* Raw binson encoded block extraction and output supported now (see #8)
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

Looks stable with good unit test coverage, need more eyes for review, API is still a subject of discussion.


Writer API usage
---------

```c
 uint8_t        buf[64];
 size_t         cnt;
 binson_writer  w;

 binson_writer_init(&w, buf, sizeof(buf));

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
  /*
   * Defines a parser that can parse up to 10 nested objects.
   * If less or more levels are required use the macro:
   * BINSON_PARSER_DEF_DEPTH(p, depth).
   *
   * It is also possible to do like this:
   * binson_parser p;
   * binson_state states[5];
   * p.state = state;
   * p.max_depth = 5;
   *
   */
  BINSON_PARSER_DEF(p); /* Default maximum depth = 10 */

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

Binson c++ class example
---------

```c
    // Serialize to binson format
    uint8_t buf[64];
    binson_writer w;
    BINSON_PARSER_DEF(p);

    Binson b;
    b.put("a", 123);
    b.put("bcd", "Hello world!");

    binson_writer_init(&w, buf, sizeof(buf));
    b.serialize(&w);

    // Deserialize
    binson_parser_init(&p, buf, binson_writer_get_counter(&w));
    Binson b2;
    b2.deserialize(&p);

    printf("a: %d\n", (int)b2.get("a").getInt());
    printf("bcd: %s\n", b2.get("bcd").getString().c_str());
```
Will print:

```
a: 123
bcd: Hello world!
```
