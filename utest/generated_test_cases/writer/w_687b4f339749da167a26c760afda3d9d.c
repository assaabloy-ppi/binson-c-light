#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "": [
    [
      
    ],
    16,
    303174162,
    303175442,
    303174162,
    303174162,
    303176210,
    303174162,
    303174162,
    303174162,
    303174194,
    303174162,
    303174162,
    305140242,
    303174162,
    303174162,
    303174162,
    303174194,
    303174162,
    303174162,
    303174162,
    303567378,
    301994514,
    303174162,
    303501842,
    303174162,
    303174162,
    303174162,
    303170578,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303175698,
    303169554,
    303174162,
    303175442,
    303174162,
    303174162,
    303174162,
    303174148,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303171090,
    303174162,
    303174150,
    303567378,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    554832402,
    1094730258
  ]
}
*/
int main(void)
{
    uint8_t expected[325] = "\x40\x14\x00\x42\x42\x43\x10\x10\x12\x12\x12\x12\x12\x12\x12\x17\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x1a\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x32\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x30\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x32\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x18\x12\x12\x12\x12\x00\x12\x12\x12\x12\x12\x12\x12\x12\x12\x17\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x04\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x18\x12\x12\x12\x12\x00\x12\x12\x12\x12\x12\x12\x12\x12\x12\x17\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x04\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x06\x12\x12\x12\x12\x12\x12\x12\x12\x06\x12\x12\x12\x12\x12\x12\x18\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x21\x12\x12\x42\x40\x41\x43\x41";
    uint8_t created[325];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "", 0);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 16);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303175442);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303176210);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174194);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 305140242);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174194);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303567378);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 301994514);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303501842);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303170578);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303175698);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303169554);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303175442);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174148);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303171090);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174150);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303567378);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 554832402);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1094730258);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

