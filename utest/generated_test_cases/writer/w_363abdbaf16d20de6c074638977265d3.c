#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "BDcDDDDcDDDDDDDD^DDDDDDDDDeD=DD": true
}
*/
int main(void)
{
    uint8_t expected[36] = "\x40\x14\x1f\x42\x44\x63\x44\x44\x44\x44\x63\x44\x44\x44\x44\x44\x44\x44\x44\x5e\x44\x44\x44\x44\x44\x44\x44\x44\x44\x65\x44\x3d\x44\x44\x44\x41";
    uint8_t created[36];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x42\x44\x63\x44\x44\x44\x44\x63\x44\x44\x44\x44\x44\x44\x44\x44\x5e\x44\x44\x44\x44\x44\x44\x44\x44\x44\x65\x44\x3d\x44\x44", 31);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_boolean(&w, true);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

