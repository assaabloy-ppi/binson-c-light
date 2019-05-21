/**
 * @file main_entry.c
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*======= Local Macro Definitions ===========================================*/

#define FUZZ_TOOL_NONE          (0)
#define FUZZ_TOOL_AFL           (1)
#define FUZZ_TOOL_LIBFUZZER     (2)

#ifndef AFL_MAX_SIZE
    #define AFL_MAX_SIZE 8192U
#endif

#ifndef FUZZ_TOOL
    #define FUZZ_TOOL FUZZ_TOOL_NONE
#endif

extern bool fuzz_one_input(const uint8_t *data, size_t size);

#if FUZZ_TOOL == FUZZ_TOOL_NONE || FUZZ_TOOL == FUZZ_TOOL_AFL

static uint8_t tmp_buffer[AFL_MAX_SIZE];
static size_t fuzz_read(uint8_t **data)
{
    *data = NULL;
    ssize_t size = read(0, tmp_buffer, sizeof(tmp_buffer));
    if (size <= 0)
    {
        return 0;
    }
    *data = (uint8_t *) malloc(size);
    if (NULL == *data)
    {
        return 0;
    }
    memcpy(*data, tmp_buffer, size);
    return (size_t) size;
}

static bool read_and_execute(void)
{
    size_t size;
    uint8_t *data;
    bool ret;
    size = fuzz_read(&data);
    if ((NULL == data) || (0 == size))
    {
        return false;
    }
    ret = fuzz_one_input(data, size);
    free(data);
    return ret;
}

int main(void)
{
    #ifdef __AFL_LOOP
    while (__AFL_LOOP(1000))
    {
        (void) read_and_execute();
    }
    return 0;
    #else
    return read_and_execute() ? 0 : -1;
    #endif
}

#elif FUZZ_TOOL == FUZZ_TOOL_LIBFUZZER

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    (void) fuzz_one_input(data, size);
    return 0;
}

#else
#error Wrong fuzzing tool defined.
#endif
