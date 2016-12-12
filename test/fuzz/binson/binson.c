#include <stdio.h>
#include "../../../binson_light.h"
#include "assert.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{

    uint8_t buf[2048];
    read(0, buf, sizeof(buf));

    binson_parser p;
    binson_parser_init(
        &p,
        buf,
        sizeof(buf));

    /* We are expecting a byte array in the field "e" */
    binson_parser_field(&p, "e");
    if (p.error_flags != BINSON_ID_OK) {
        return 0;
    }

    if (binson_parser_get_type(&p) != BINSON_ID_BYTES)
    {
        return 0;
    }

    bbuf *binson_bytes = binson_parser_get_bytes_bbuf(&p);
    if (p.error_flags != BINSON_ID_OK) {
        return 0;
    }

    assert(binson_bytes->bptr != NULL);

}
