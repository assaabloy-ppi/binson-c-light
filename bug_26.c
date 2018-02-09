#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include "binson_light.h"

static void test(void) {
    uint8_t buffer[32];
    binson_writer w;
    binson_writer_init(&w, buffer, sizeof(buffer));

    binson_write_object_begin(&w);
    binson_write_name(&w, "a");
    uint8_t byte = 0x00;
    binson_write_bytes(&w, &byte, 1);
    binson_write_name(&w, "fr");
    uint8_t bytes[4] = { 0x02 };
    binson_write_bytes(&w, bytes, sizeof(bytes));
    binson_write_object_end(&w);

    binson_parser p;
    binson_parser_init(&p, buffer, binson_writer_get_counter(&w));
    binson_parser_go_into_object(&p);
    binson_parser_field_ensure(&p, "a", BINSON_ID_BYTES);
}

int main(void) {
    test();
}
