#include <assert.h>
#include <string.h>
#include "binson_parser.h"

/*
{
  "c": "login", 
  "i": 10, 
  "o": "s", 
  "z": {
    "A": "v1", 
    "ch": [
      "0x5fc0d0e476aaf6e62a8b89ad53f728aa29aa810cbf356cc19e37aa027c3354949339858b36b76d1b06293e4f9a3b1953a7ee5867af2c045b02ff58df456aed05401401611801001402667218205529ce8ccf68c0b8ac19d437ab0f5b32723782608e93c6264f184ba152c2357b1401704218010b14026c754314027463180c500100000000ffffff7f00001402746e1403426f621402746f182007e28d4ee32bfdc4b07d41c92193c0c25ee6b3094c6296f373413b373d36168b41"
    ]
  }
}
*/
int main(void)
{
    uint8_t binson_bytes[231] = "\x40\x14\x01\x63\x14\x05\x6c\x6f\x67\x69\x6e\x14\x01\x69\x10\x0a\x14\x01\x6f\x14\x01\x73\x14\x01\x7a\x40\x14\x01\x41\x14\x02\x76\x31\x14\x02\x63\x68\x42\x19\xbb\x00\x5f\xc0\xd0\xe4\x76\xaa\xf6\xe6\x2a\x8b\x89\xad\x53\xf7\x28\xaa\x29\xaa\x81\x0c\xbf\x35\x6c\xc1\x9e\x37\xaa\x02\x7c\x33\x54\x94\x93\x39\x85\x8b\x36\xb7\x6d\x1b\x06\x29\x3e\x4f\x9a\x3b\x19\x53\xa7\xee\x58\x67\xaf\x2c\x04\x5b\x02\xff\x58\xdf\x45\x6a\xed\x05\x40\x14\x01\x61\x18\x01\x00\x14\x02\x66\x72\x18\x20\x55\x29\xce\x8c\xcf\x68\xc0\xb8\xac\x19\xd4\x37\xab\x0f\x5b\x32\x72\x37\x82\x60\x8e\x93\xc6\x26\x4f\x18\x4b\xa1\x52\xc2\x35\x7b\x14\x01\x70\x42\x18\x01\x0b\x14\x02\x6c\x75\x43\x14\x02\x74\x63\x18\x0c\x50\x01\x00\x00\x00\x00\xff\xff\xff\x7f\x00\x00\x14\x02\x74\x6e\x14\x03\x42\x6f\x62\x14\x02\x74\x6f\x18\x20\x07\xe2\x8d\x4e\xe3\x2b\xfd\xc4\xb0\x7d\x41\xc9\x21\x93\xc0\xc2\x5e\xe6\xb3\x09\x4c\x62\x96\xf3\x73\x41\x3b\x37\x3d\x36\x16\x8b\x41\x43\x41\x41";
    BINSON_PARSER_DEF(p);
    double dval; (void) dval;
    int64_t intval; (void) intval;
    bool boolval; (void) boolval;
    bbuf *rawval; (void) rawval;
    assert(binson_parser_init(&p, binson_bytes, sizeof(binson_bytes)));
    assert(binson_parser_verify(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x63", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x6c\x6f\x67\x69\x6e", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x69", 1, BINSON_TYPE_INTEGER));
    assert(p.error_flags == BINSON_ID_OK);
    intval = binson_parser_get_integer(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(intval == 10);
    assert(binson_parser_field_ensure_with_length(&p, "\x6f", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x73", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x7a", 1, BINSON_TYPE_OBJECT));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_field_ensure_with_length(&p, "\x41", 1, BINSON_TYPE_STRING));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_string_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x76\x31", rawval->bsize) == 0);
    assert(binson_parser_field_ensure_with_length(&p, "\x63\x68", 2, BINSON_TYPE_ARRAY));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_go_into_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(binson_parser_next_ensure(&p, BINSON_TYPE_BYTES));
    assert(p.error_flags == BINSON_ID_OK);
    rawval = binson_parser_get_bytes_bbuf(&p);
    assert(p.error_flags == BINSON_ID_OK);
    assert(memcmp(rawval->bptr, "\x5f\xc0\xd0\xe4\x76\xaa\xf6\xe6\x2a\x8b\x89\xad\x53\xf7\x28\xaa\x29\xaa\x81\x0c\xbf\x35\x6c\xc1\x9e\x37\xaa\x02\x7c\x33\x54\x94\x93\x39\x85\x8b\x36\xb7\x6d\x1b\x06\x29\x3e\x4f\x9a\x3b\x19\x53\xa7\xee\x58\x67\xaf\x2c\x04\x5b\x02\xff\x58\xdf\x45\x6a\xed\x05\x40\x14\x01\x61\x18\x01\x00\x14\x02\x66\x72\x18\x20\x55\x29\xce\x8c\xcf\x68\xc0\xb8\xac\x19\xd4\x37\xab\x0f\x5b\x32\x72\x37\x82\x60\x8e\x93\xc6\x26\x4f\x18\x4b\xa1\x52\xc2\x35\x7b\x14\x01\x70\x42\x18\x01\x0b\x14\x02\x6c\x75\x43\x14\x02\x74\x63\x18\x0c\x50\x01\x00\x00\x00\x00\xff\xff\xff\x7f\x00\x00\x14\x02\x74\x6e\x14\x03\x42\x6f\x62\x14\x02\x74\x6f\x18\x20\x07\xe2\x8d\x4e\xe3\x2b\xfd\xc4\xb0\x7d\x41\xc9\x21\x93\xc0\xc2\x5e\xe6\xb3\x09\x4c\x62\x96\xf3\x73\x41\x3b\x37\x3d\x36\x16\x8b\x41", rawval->bsize) == 0);
    assert(binson_parser_leave_array(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    assert(!binson_parser_next(&p));
    assert(binson_parser_leave_object(&p));
    assert(p.error_flags == BINSON_ID_OK);
    return 0;
}

