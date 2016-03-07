* 2016-03-07: edit: Arduino Nano support removed etc.
* 2016-02-08: first version

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
* Writer: Conversion Binson fields -> byte array must be supported.
* Parser: Conversion byte array -> stream of Binson fields must be supported.
* The writer does not have be "validating". It should be easy to 
  generate valid Binson bytes with the writer, but it may be possible
  to generate invalid Binson bytes too.
* Similarly, the parser does not necessarily have to be able to detect whether 
  the input is valid or not for every possible input.
* The project is similar in scope to the [binson-java-light project](https://github.com/franslundberg/binson-java-light) 
  on Github.
* No dynamic memory allocation while serializing / deserializing is allowed.
* A goal is to keep binson-light.c within 1500 lines of code. binson-java-light is around 600 lines.
  Clean code and a small code size is important.
* UTF-8 does not need to be handled "explicitely". Assuming US-ASCII for
  string literals is OK. It must however be possible to match field names using raw UTF-8 bytes
  and use raw UTF-8 bytes when serializing.
* Deliverables, the following files (filenames may be changed if appropriate):
     - binson_light.c           // source code
     - binson_light.h           // header file(s), possibly two versions, one for Linux and one for Arduino Nan
     - README.md                // information
     - binson_light_test.c      // main method with some tests
     - binson_light_examples.c  // example code
* No dependencies on libraries beyond C lib.
* The library binson-c-light is used by including
  the C-source (binson_light.c, binson_light.h) directly in the application project.
* The C code should be designed with small devices in mind, for example a Cortex M0 MCU.
  8-bit and 16-bit processors do not have to be considered.
* The source should build with simple GCC commands described in README.md. No build framework or
  test framework should be used.
* The software should build and run on Linux Ubuntu + GCC.
* High code quality is important.
* The writer code does not need to enforce correct field ordering. It can be the responsibility of the application code.
* See the "Output buffer size" section.
* See the "Error handling" section.

Feel free to discuss the requirements; they will likely evolve during the project.

The project is divided into three phases.

* Phase 1: first implementation. A complete implementation.
* Phase 2: refactoring of Phase 1 code after discussions with Frans Lundberg. More testing.
* Phase 3: one month of support (fixing bugs, answering questions) after Phase 2 
  has been completed.

Output buffer size
------------------

When a Binson object is serialized to an output byte array, there is the issue 
of array size. The resulting length in bytes is typically not known in advance.
The binson-c-light serializer should check that is it not writing beond the
boundary of the array.

The application code should be able to do the following (just to demonstrate
the feature; code does not suggest any specific naming approach etc):

    binson_writer* w;
    binson_writer_init(w, buffer, buffer_size);
    
    binson_write_begin(w);
    binson_write_integer_field(w, "myInteger", 12345);
    ...
    binson_write_end(w);
    
    /* 
    Here, the application can check w for errors. Furthermore 
    "w->size" or similar should contain the result size
    even in cases when the buffer_size was exceeded! Writer should be 
    able to continue somehow not actually writing to buffer, but counting 
    the result size. This allows the application to increase
    buffer size and run the code again. This time the size is known in advance.
    */
    
If buffer_size == 0, the code is used to calculate the result size. No actual
data will be written to buffer in this case.

Error handling
--------------

The application code uses the library to serialize or deserialize using 
potentially many function calls. For example:

    binson_writer* w;
    binson_writer_init(w, buffer, buffer_size);
    
    binson_write_begin(w);
    binson_write_integer_field(w, "myInteger", 12345);
    ...
    binson_write_end(w);
    
It should be possible for the application code to check for errors *once*
after a serialization (or deserialization). Checking for errors after every line
of code is cumbersome and makes the code harder to read. This is likely implemented
by checking "w.error" or similar for every binson_writer_x function (for the serialization
case):

    void binson_write_integer_field(binson_writer* w, ...) 
    {
        if (w.error) return;
        // actual function implementation...
    }

The example code is used just to demonstrate the idea.

