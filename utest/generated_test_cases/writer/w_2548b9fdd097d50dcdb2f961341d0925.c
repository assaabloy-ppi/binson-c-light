#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "0": [
    true,
    true,
    true,
    48,
    true,
    false,
    false,
    false,
    false,
    "0x",
    false,
    false,
    true,
    "0x30303030303014010030303030303030",
    true,
    true,
    true,
    true,
    true,
    false,
    true,
    "0x30303030303012303030301230303030",
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    1.398043286095289E-76,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808468528,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432,
    808464432
  ]
}
*/
int main(void)
{
    uint8_t expected[299] = "\x40\x14\x01\x30\x42\x44\x44\x44\x10\x30\x44\x45\x45\x45\x45\x18\x00\x45\x45\x44\x18\x10\x30\x30\x30\x30\x30\x30\x14\x01\x00\x30\x30\x30\x30\x30\x30\x30\x44\x44\x44\x44\x44\x45\x44\x18\x10\x30\x30\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x46\x30\x30\x30\x30\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x40\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30\x43\x41";
    uint8_t created[299];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x30", 1);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 48);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, false);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, false);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, false);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, false);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_bytes(&w, (uint8_t *)"", 0);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, false);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, false);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_bytes(&w, (uint8_t *)"\x30\x30\x30\x30\x30\x30\x14\x01\x00\x30\x30\x30\x30\x30\x30\x30", 16);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, false);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_bytes(&w, (uint8_t *)"\x30\x30\x30\x30\x30\x30\x12\x30\x30\x30\x30\x12\x30\x30\x30\x30", 16);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_double(&w, 1.398043286095289E-76);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808468528);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_integer(&w, 808464432);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_array_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

