#include "aoc/dec01.h"

#include <stdio.h>

#include "aoc/better_getline.h"

/// max must point to 3 elements
static void add_max(size_t* maxes, size_t num) {
    size_t min = maxes[0];
    size_t min_i = 0;
    for (size_t i = 1; i < 3; i++) {
        if (maxes[i] < min) {
            min = maxes[i];
            min_i = i;
        }
    }
    if (num > min) {
        maxes[min_i] = num;
    }
}

static size_t max_of(size_t* maxes) {
    size_t max = maxes[0];
    for (size_t i = 1; i < 3; i++) {
        if (maxes[i] > max) {
            max = maxes[i];
        }
    }
    return max;
}

struct string dec01_run(struct string path, size_t part) {
    struct string line = EMPTY_STRING;

    FILE* f = fopen(path.data, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file: " STRING_FMT "\n", STRING_ARG(path));
        exit(1);
    }

    size_t curr_total = 0;
    size_t maxes[3] = {0};

    while (better_getline(&line, f)) {
        if (line.length == 0) {
            add_max(maxes, curr_total);
            curr_total = 0;
            continue;
        }

        char* endp;
        long num = strtol(line.data, &endp, 10);
        if (endp - line.data != (ptrdiff_t)line.length) {
            fprintf(stderr, "Invalid number: %s\n", line.data);
            exit(1);
        }

        curr_total += num;
    }

    STRING_FREE(line);

    if (curr_total != 0) {
        add_max(maxes, curr_total);
    }

    fclose(f);

    switch (part) {
        case 1:
            return string_printf("%zu", max_of(maxes));
        case 2:
            return string_printf("%zu", maxes[0] + maxes[1] + maxes[2]);
        default:
            abort();
    }
}
