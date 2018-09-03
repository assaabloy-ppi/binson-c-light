#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "000": [
    "0",
    48,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472312903064891440,
    3472328296228930096,
    3472328296227680304,
    3472328296227680304,
    3472328416486764592,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227674672,
    3472328296227680304,
    3472296410390474800,
    1094427692976058416,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    3472328296227680304,
    2607637167772545072,
    3472328296227680304,
    3472328296227680304,
    12304,
    3472328296227680304
  ]
}
*/
int main(void)
{
    uint8_t expected[260] = "\x40\x14\x03\x30\x30\x30\x42\x14\x01\x30\x10\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x22\x30\x30\x13\x30\x42\x43\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x4c\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x1a\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x13\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x0f\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x24\x13\x30\x30\x30\x30\x30\x30\x30\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x11\x10\x30\x13\x30\x30\x30\x30\x30\x30\x30\x30\x43\x41";
    uint8_t created[260];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x30\x30\x30", 3);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_string_with_len(&w, "\x30", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 48);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472312903064891440);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296228930096);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328416486764592);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227674672);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472296410390474800);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 1094427692976058416);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 2607637167772545072);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 12304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 3472328296227680304);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

