#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "": [
    [
      
    ],
    49,
    303174162,
    303436306,
    286331153,
    4369,
    4369,
    4369,
    4370,
    16913,
    {
    }
  ]
}
*/
int main(void)
{
    uint8_t expected[42] = "\x40\x14\x00\x42\x42\x43\x10\x31\x12\x12\x12\x12\x12\x12\x12\x12\x16\x12\x12\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x12\x11\x11\x11\x42\x40\x41\x43\x41";
    uint8_t created[42];
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
    binson_write_integer(&w, 49);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303436306);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 286331153);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 4369);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 4369);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 4369);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 4370);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 16913);
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

