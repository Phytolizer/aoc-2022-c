#include "aoc/dec01.h"

#include <stdio.h>

#include "aoc/better_getline.h"

static void add_max(size_t max[static 3], size_t num) {
    for (size_t i = 0; i < 3; i++) {
        if (num > max[i]) {
            for (size_t j = 2; j > i; j--) {
                max[j] = max[j - 1];
            }
            max[i] = num;
            break;
        }
    }
}

struct string dec01_run(struct string path, size_t part) {
    struct string line = EMPTY_STRING;

    FILE* f = fopen(path.data, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file: " STRING_FMT "\n", STRING_ARG(path));
        exit(1);
    }

    size_t curr_total = 0;
    size_t max[3] = {0};

    while (better_getline(&line, f)) {
        if (line.length == 0) {
            add_max(max, curr_total);
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

    if (curr_total != 0) {
        add_max(max, curr_total);
    }

    fclose(f);

    switch (part) {
        case 1:
            return string_printf("%zu", max[0]);
        case 2:
            return string_printf("%zu", max[0] + max[1] + max[2]);
        default:
            abort();
    }
}
