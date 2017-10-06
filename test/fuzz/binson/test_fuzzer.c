#include <stdint.h>
#include <stddef.h>
#include "../../../binson_light.h"

/* try to apply random but valid advance parameters */
void loop_blind_advance(binson_parser *p, size_t size, 
									uint8_t scan_flag, int16_t n_steps,
                            const char *scan_name, uint8_t ensure_type)
{
    int cnt = 0;  // watch-dog counter
    while (cnt < 100 && p->io.buf_used < size)
    {
       // clear noncritical error and continue
        if (p->error_flags ==  BINSON_ID_PARSE_WRONG_STATE ||
            p->error_flags ==  BINSON_ID_PARSE_END_OF_BUFFER)
            return;

        p->error_flags = BINSON_ID_OK;

        binson_parser_advance( p, scan_flag, n_steps, scan_name, ensure_type);
        cnt++; 
    }
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

    binson_parser p;
	char          str[10*1024];


    binson_parser_init( &p, (uint8_t *)data, size);

    /*loop_blind_advance( &p, size, BINSON_PARSER_ADVANCE_N | BINSON_PARSER_ADVANCE_CMP_NAME, -1, "z", BINSON_ID_DOUBLE);

    binson_parser_reset( &p );
    loop_blind_advance( &p, size, BINSON_PARSER_ADVANCE_N | BINSON_PARSER_ADVANCE_CMP_NAME, -1, "z", BINSON_ID_DOUBLE);

    binson_parser_reset( &p );
    loop_blind_advance( &p, size, BINSON_PARSER_ADVANCE_N_SAME_DEPTH | BINSON_PARSER_ADVANCE_CMP_NAME, 1, "z", BINSON_ID_DOUBLE);

    binson_parser_reset( &p );
    loop_blind_advance( &p, size, BINSON_PARSER_ADVANCE_N_SAME_DEPTH, 5, NULL, BINSON_ID_DOUBLE);

    binson_parser_reset( &p );
    loop_blind_advance( &p, size, BINSON_PARSER_ADVANCE_N_DEPTH | BINSON_PARSER_ADVANCE_ENSURE_TYPE, 1, NULL, BINSON_ID_BLOCK);

    binson_parser_reset( &p );
    loop_blind_advance( &p, size, BINSON_PARSER_ADVANCE_N_DEPTH, -1, NULL, BINSON_ID_UNKNOWN);
*/
    // string serialization
    binson_parser_reset( &p );
    binson_parser_to_string( &p, (uint8_t*)str, sizeof(str), false );

  return 0;
}
