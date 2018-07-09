#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "A": [
    18433,
    1,
    1111683097,
    303234816,
    303174162,
    303186426,
    487723538,
    301990930,
    334511942,
    1302123111085445907,
    303174162,
    303174162,
    303174163,
    303174162,
    1302123111085380114,
    303174162,
    303174162,
    306398207,
    303174162,
    303174162,
    1140789778
  ]
}
*/
int main(void)
{
    uint8_t expected[117] = "\x40\x14\x03\x41\x13\x01\x42\x11\x01\x48\x10\x01\x12\x19\xf0\x42\x42\x12\x00\xff\x12\x12\x12\x12\x12\x12\x12\x12\xfa\x41\x12\x12\x12\x12\x12\x12\x1d\x12\x12\x04\x00\x12\x12\x46\x3f\xf0\x13\x13\x13\x13\x13\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x13\x12\x12\x12\x12\x12\x12\x12\x12\x13\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\xff\x43\x43\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\xff\x43\x43\x41";
    uint8_t created[117];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x41\x13\x01", 3);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 18433);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1111683097);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303234816);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303186426);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 487723538);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 301990930);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 334511942);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1302123111085445907);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174163);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1302123111085380114);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 306398207);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 303174162);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1140789778);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

