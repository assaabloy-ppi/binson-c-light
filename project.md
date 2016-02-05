Date: 2016-02-05
Author: Frans Lundberg, ASSA ABLOY AB


Project specification
=====================

This document describes a development project to create software
to convert an array of bytes to a Binson representation and a Binson
representation to an array of bytes. The implementation does not build
an in-memory representation of Binson object. It is more of a streaming library
similar to SAX for XML (instead of DOM).

Project information, scope, requirements:

* Project name: binson-c-light
* Conversion byte array -> stream of Binson fields must be supported.
* Conversion Binson fields -> byte array must be supported.
* Similar in scope to binson-java-light (see Github).
* No dynamic memory allocation while serializing / deserializing
  is allowed.
* Goal is to keep binson-light.c within 1500 lines of code.
  (binson-java-light is around 600 lines).
* UTF-8 does not need to be handled "explicitely". Assuming US-ASCII for
  string literals is OK. It must however be possible to match field
  names using raw UTF-8 bytes too.
* Deliverables, 4 files:
     - binson-light.c        // source code
     - binson-light.h        // header file
     - README.md             // information
     - binson-light-test.c   // main method with some tests
     - binson-examples.c     // example code
* No dependencies on libraries beyond C lib.
* The library binson-c-light is used by including
  the C-source directly in application project.
* The C code is designed for small devices. It should work on Arduino Nano.
* There are natural limitations on the Arduino Nano, for example int64_t is
  not supported, so on Arduino, support for 64-bit integer (and float, I guess)
  is not required.
* The source should build with simple GCC commands described in README.md.
* The software should run on Arduino Nano.
* The software should build and run on Linux Ubuntu + GCC.
* High code quality is important.
* The code should follow the field ordering notes below in this document.

The project is divided into three phases.

* Phase 1: first implementation. A complete implementation.
* Phase 2: refactoring of Phase 1 code after discussions with Frans Lundberg. Testing.
* Phase 3: one month of support (fixing bugs, answering questions) after Phase 2 
  has been completed.
  
Field ordering
--------------

The ordering of Binson fields is the responsibility of the application developer.

Serializer: The serializer should raise an error condition if the application 
developer tries to use a bad ordering of the fields.

Parser: The parser can assume the fields are ordered correctly. The parser should
raise an error condition if that is not the case (byte array is not valid Binson bytes).


Byte array length
-----------------

Error handling
--------------
