#include <aoc2022_config.h>
#include <stdio.h>
#include <string.h>

#include "aoc/dec01.h"
#include "aoc/dec02.h"
#include "aoc/string.h"

const char* example_inputs[2] = {
    "simple",
    "full",
};

#define BASE_DIR PROJECT_DIR "/input/dec"
#define INPUT_LEN (sizeof(BASE_DIR) + 100)

#define AOC_TEST(day, expected1s, expected1f, expected2s, expected2f) \
    do { \
        char input[INPUT_LEN] = {0}; \
        struct string expected[] = { \
            STRING_REF_C(expected1s), \
            STRING_REF_C(expected1f), \
            STRING_REF_C(expected2s), \
            STRING_REF_C(expected2f), \
        }; \
        for (int i = 0; i < 4; i++) { \
            snprintf(input, INPUT_LEN, BASE_DIR #day "-%s.txt", example_inputs[i % 2]); \
            struct string actual = dec##day##_run(STRING_REF_FROM_C(input), i / 2 + 1); \
            tests++; \
            if (!STRING_EQUAL(actual, expected[i])) { \
                fprintf( \
                    stderr, \
                    #day ".%d.%-6s: expected " STRING_FMT ", got " STRING_FMT "\n", \
                    i / 2 + 1, \
                    example_inputs[i % 2], \
                    STRING_ARG(expected[i]), \
                    STRING_ARG(actual) \
                ); \
                failures++; \
            } \
            STRING_FREE(actual); \
        } \
    } while (0)

int main(void) {
    int tests = 0;
    int failures = 0;
    AOC_TEST(01, "24000", "69289", "45000", "205615");
    AOC_TEST(02, "15", "14531", "12", "11258");

    if (failures) {
        fprintf(stderr, "%d tests failed\n", failures);
        return 1;
    }
    printf("All %d tests passed\n", tests);
    return 0;
}
