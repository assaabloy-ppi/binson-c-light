#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
}
*/
int main(void)
{
    uint8_t expected[2] = "\x40\x41";
    uint8_t created[2];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

