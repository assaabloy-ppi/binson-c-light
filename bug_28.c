#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include "binson_light.h"

static void test(void) {

    uint8_t my_buffer[128];
    memset(&my_buffer[32], 0xEE, 128 - 32); /* This is my data */
    binson_writer w;
    binson_writer_init(&w, my_buffer, 128);
    binson_write_object_begin(&w);
    binson_write_name(&w, "my_data");
    binson_write_bytes(&w, &my_buffer[32], 128-32);
    binson_write_name(&w, "p");
    binson_write_string(&w, "q");
    binson_write_object_end(&w);

    /* dumping */
    binson_parser p;
    binson_parser_init(&p, my_buffer, sizeof(my_buffer));

    uint8_t str_buf[1024];
    binson_parser_to_string(&p, str_buf, sizeof(str_buf), false);
    printf("%s", str_buf);    
}

int main(void) {
    test();
}
