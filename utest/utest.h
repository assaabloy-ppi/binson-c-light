#ifndef _utest_H_
#define _utest_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file utest.h.h
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include <stdbool.h>
#include <stdio.h>

/*======= Public macro definitions ==========================================*/

#define VERIFY(x) if (!(x)) return false
#define ASSERT(x) do {                                      \
        if (!(x)) {                                         \
            printf("Assertion failed at line %d: %s\r\n",   \
                   __LINE__, #x);                           \
            FAIL();											\
            return;                                         \
        }                                                   \
    } while (0)
#define ASSERT_TRUE(x)  ASSERT((x))
#define ASSERT_FALSE(x) ASSERT(!(x))

#define TEST(test_name) static void test_name(void)

#define RUN_TEST(test_name) do {                                            \
        __FILE__ ## __num_tests++;                                          \
        __FILE__ ## __passed = true;                                        \
        test_name();                                                        \
        if (__FILE__ ## __passed) {                                         \
            printf("== PASSED ==: %s\r\n", #test_name);                     \
            __FILE__ ## __num_passed++;                                     \
        } else {                                                            \
            printf("== FAILED ==: %s, see message above.\r\n", #test_name); \
        }                                                                   \
    } while(0)

#define PRINT_RESULT() do {                                             \
        printf("Summary: %d of %d tests passed.\r\n",                   \
               __FILE__ ## __num_passed, __FILE__ ## __num_tests);		\
        if (__FILE__ ## __num_passed != __FILE__ ## __num_tests) {		\
            return -1;                                                  \
        }                                                               \
        return 0;                                                       \
    } while(0)

#define DEF_DATA() 							\
    static bool __FILE__##__passed;			\
    static int __FILE__##__num_passed = 0;	\
    static int __FILE__##__num_tests = 0

#define FAIL() \
    __FILE__ ## __passed = false


DEF_DATA();

/*======= Type Definitions and declarations =================================*/
/*======= Public variable declarations ======================================*/
/*======= Public function declarations ======================================*/

#ifdef __cplusplus
}
#endif

#endif /* _utest_H_ */
