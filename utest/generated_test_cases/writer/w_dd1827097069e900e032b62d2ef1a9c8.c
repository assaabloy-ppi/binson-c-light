#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "A": "B", 
  "B": 1, 
  "CF      \b@DEE": "0x0102", 
  "F": {
  }, 
  "G": [
    
  ]
}
*/
int main(void)
{
    uint8_t expected[46] = "\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x10\x01\x14\x11\x43\x46\x00\x00\x00\x00\x00\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45\x18\x02\x01\x02\x14\x01\x46\x40\x41\x14\x01\x47\x42\x43\x41";
    uint8_t created[46];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x41", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_string_with_len(&w, "\x42", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x42", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x43\x46\x00\x00\x00\x00\x00\x00\x08\x40\x14\x01\x44\x45\x14\x01\x45", 17);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_bytes(&w, (uint8_t *)"\x01\x02", 2);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x46", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x47", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

