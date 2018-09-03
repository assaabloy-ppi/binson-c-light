#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "": "", 
  "A": 67
}
*/
int main(void)
{
    uint8_t expected[11] = "\x40\x14\x00\x14\x00\x14\x01\x41\x10\x43\x41";
    uint8_t created[11];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "", 0);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_string_with_len(&w, "", 0);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x41", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 67);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

