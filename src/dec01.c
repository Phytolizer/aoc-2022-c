#include "aoc/dec01.h"

#include <stdio.h>

#include "aoc/better_getline.h"

struct string dec01_run(struct string path, size_t part) {
    struct string line = EMPTY_STRING;

    FILE* f = fopen(path.data, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", path.data);
        exit(1);
    }

    size_t curr_total = 0;
    size_t max = 0;

    while (better_getline(&line, f)) {
        printf(STRING_FMT "\n", STRING_ARG(line));
        if (line.length == 0) {
            if (curr_total > max) {
                max = curr_total;
            }
            curr_total = 0;
            continue;
        }

        char* endp;
        long num = strtol(line.data, &endp, 10);
        if (*endp != 0) {
            fprintf(stderr, "Invalid number: %s\n", line.data);
            exit(1);
        }

        curr_total += num;
    }

    fclose(f);

    return string_printf("%zu", max);
}
