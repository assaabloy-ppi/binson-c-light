#include <stdio.h>
#include "../../../binson_light.h"
#include "assert.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

//#define RAND_BYTE   ((uint8_t)(rand() % 0xff))
//#define RAND_INT16  ((int16_t)(rand() % (0xffff >> 1) - 0xffff >> 1 ))

uint8_t buf[2048];
char    str[2048*4];
int     raw_len;
bbuf    bb;

binson_parser p;



/* try to apply random but valid advance parameters */
void loop_blind_advance(uint8_t scan_flag, int16_t n_steps,
                            const char *scan_name, uint8_t ensure_type)
{
    int cnt = 0;  // watch-dog counter
    while (cnt < 100 && p.io.buf_used < raw_len)
    {
       // clear noncritical error and continue
        if (p.error_flags ==  BINSON_ID_PARSE_WRONG_STATE ||
            p.error_flags ==  BINSON_ID_PARSE_END_OF_BUFFER)
            return;

        p.error_flags = BINSON_ID_OK;

        binson_parser_advance( &p, scan_flag, n_steps, scan_name, ensure_type);
        cnt++; 
    }
}


int main(void)
{
    raw_len = read(0, buf, sizeof(buf));

    // uncomment for debugging
    //const uint8_t b1[]  = "\x40\x43\x34\x00\x7f\x90";
    //memcpy(buf, b1, sizeof(b1));
    //raw_len = sizeof(b1);

    // heuristic advance
    binson_parser_init( &p, buf, raw_len);
    loop_blind_advance(BINSON_PARSER_ADVANCE_N | BINSON_PARSER_ADVANCE_CMP_NAME, -1, "z", BINSON_ID_DOUBLE);

    binson_parser_reset( &p );
    loop_blind_advance(BINSON_PARSER_ADVANCE_N | BINSON_PARSER_ADVANCE_CMP_NAME, -1, "z", BINSON_ID_DOUBLE);

    binson_parser_reset( &p );
    loop_blind_advance(BINSON_PARSER_ADVANCE_N_SAME_DEPTH | BINSON_PARSER_ADVANCE_CMP_NAME, 1, "z", BINSON_ID_DOUBLE);

    binson_parser_reset( &p );
    loop_blind_advance(BINSON_PARSER_ADVANCE_N_SAME_DEPTH, 5, NULL, BINSON_ID_DOUBLE);

    binson_parser_reset( &p );
    loop_blind_advance(BINSON_PARSER_ADVANCE_N_DEPTH | BINSON_PARSER_ADVANCE_ENSURE_TYPE, 1, NULL, BINSON_ID_BLOCK);

    binson_parser_reset( &p );
    loop_blind_advance(BINSON_PARSER_ADVANCE_N_DEPTH, -1, NULL, BINSON_ID_UNKNOWN);

    // string serialization
    binson_parser_reset( &p );
    binson_parser_to_string( &p, (uint8_t*)str, sizeof(str), false );

    // parsing + reconstructing in callback + cmp
    //binson_parser_reset( &p );

    return 0;
}
