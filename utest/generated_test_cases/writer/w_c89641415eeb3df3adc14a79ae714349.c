#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "A": [
    4.83806781712E-312
  ]
}
*/
int main(void)
{
    uint8_t expected[16] = "\x40\x14\x01\x41\x42\x46\x7f\xf0\x00\xff\xe3\x00\x00\x00\x43\x41";
    uint8_t created[16];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x41", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_double(&w, 4.83806781712E-312);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

