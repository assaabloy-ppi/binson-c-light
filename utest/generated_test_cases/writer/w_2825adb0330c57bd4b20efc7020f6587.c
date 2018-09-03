#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "0BF@00000000000000000000000": 12336
}
*/
int main(void)
{
    uint8_t expected[42] = "\x40\x14\x23\x30\x42\x46\x40\x30\x30\x30\x30\x30\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x41";
    uint8_t created[42];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x30\x42\x46\x40\x30\x30\x30\x30\x30\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30\x11\x30\x30", 35);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 12336);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

