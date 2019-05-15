#include <stdio.h>
#include "binson.hpp"

int main(void)
{
    printf("=== Binson class example ===\r\n");
    // Serialize to binson format
    uint8_t buf[64];
    binson_writer w;
    BINSON_PARSER_DEF(p);

    Binson b;
    b.put("a", 123);
    b.put("bcd", "Hello world!");

    binson_writer_init(&w, buf, sizeof(buf));
    b.serialize(&w);

    // Deserialize
    binson_parser_init(&p, buf, binson_writer_get_counter(&w));
    Binson b2;
    b2.deserialize(&p);

    printf("a: %d\n", (int)b2.get("a").getInt());
    printf("bcd: %s\n", b2.get("bcd").getString().c_str());

    #ifdef BINSON_PARSER_WITH_PRINT
    std::string str = b.toStr();
    printf("%s\r\n", str.c_str());
    #endif
}
