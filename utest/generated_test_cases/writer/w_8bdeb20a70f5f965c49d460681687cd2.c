#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "": [
    [
      
    ],
    16,
    "0x121212121217121212121212121212121212",
    303174162,
    303174162,
    303174162,
    303174162,
    303174194,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174162,
    303174194,
    303174162,
    303174162,
    303174162,
    303567378,
    303174162,
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
    302387730,
    303174162,
    "0x121212121212121212121212121212121212",
    303174162,
    303174162,
    303174162,
    303174162,
    1108480545,
    {
    }
  ]
}
*/
int main(void)
{
    uint8_t expected[232] = "\x40\x14\x00\x42\x42\x43\x10\x10\x18\x12\x12\x12\x12\x12\x12\x17\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x32\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x32\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x18\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x17\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x04\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x06\x12\x12\x12\x12\x12\x12\x18\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x21\x12\x12\x42\x40\x41\x43\x41";
    uint8_t created[232];
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
    binson_write_bytes(&w, (uint8_t *)"\x12\x12\x12\x12\x12\x17\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12", 18);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
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
    binson_write_integer(&w, 303174162);
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
    binson_write_integer(&w, 302387730);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_bytes(&w, (uint8_t *)"\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12", 18);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1108480545);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

