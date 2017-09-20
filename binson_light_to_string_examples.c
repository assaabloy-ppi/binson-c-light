//#include "binson_light_to_string.h"
#include "binson_light.h"

#include <stdint.h>
#include <stdio.h>

static void example1(void)
{
  binson_parser  p;
  // {"a":[true,13,-2.34,"zxc",{"d":false, "e":"0x030405", "q":"qwe"},9223372036854775807]}
  const uint8_t b1[]  = "\x40\x14\x01\x61\x42\x44\x10\x0d\x46\xb8\x1e\x85\xeb\x51\xb8\x02\xc0\x14\x03\x7a\x78\x63\x40\x14\x01\x64\x45\x14\x01\x65\x18\x03\x03\x04\x05\x14\x01\x71\x14\x03\x71\x77\x65\x41\x13\xff\xff\xff\xff\xff\xff\xff\x7f\x43\x41";

  uint8_t src[500];
  memcpy(src, b1, sizeof(b1));
  binson_parser_init(&p, src, sizeof(src));

  printf("%s: \n", __FUNCTION__);
  char buf[1000];
  //binson_to_string(&p, buf, sizeof(buf));
  binson_parser_to_string( &p, (uint8_t*)buf, sizeof(buf), false );

  printf("%s", buf);
}

static void example2(void)
{
  binson_parser  p;
  // {"a":[true,13,-2.34,"zxc",{"d":false, "e":"0x030405", "q":"qwe"},9223372036854775807]}
  const uint8_t b1[]  = "\x40\x14\x01\x61\x42\x44\x10\x0d\x46\xb8\x1e\x85\xeb\x51\xb8\x02\xc0\x14\x03\x7a\x78\x63\x40\x14\x01\x64\x45\x14\x01\x65\x18\x03\x03\x04\x05\x14\x01\x71\x14\x03\x71\x77\x65\x41\x13\xff\xff\xff\xff\xff\xff\xff\x7f\x43\x41";

  uint8_t src[500];
  memcpy(src, b1, sizeof(b1));
  binson_parser_init(&p, src, sizeof(src));

  printf("%s: \n", __FUNCTION__);
  char buf[1000]; // Use a buffer that is too small, output will be truncated
  //binson_to_string(&p, buf, sizeof(buf));
  binson_parser_to_string( &p, (uint8_t*)buf, sizeof(buf), true );

  printf("%s\n", buf);
}

int main(int argc, char **argv)
{
  example1();
  printf("\n\n");   
  example2();

  return 0;
}
