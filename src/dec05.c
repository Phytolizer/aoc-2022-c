#include "aoc/dec05.h"

#include <stdio.h>

#include "aoc/better_getline.h"
#include "aoc/buffer.h"

DECLARE_BUFFER(unparsed_row, char);
DECLARE_BUFFER(unparsed_crates, struct unparsed_row);
DECLARE_BUFFER(crates, char);

struct string dec05_run(struct string path, size_t part) {
    FILE* f = fopen(path.data, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file " STRING_FMT "\n", STRING_ARG(path));
        exit(1);
    }

    struct unparsed_crates raw_crates = BUFFER_NEW;

    struct string line = EMPTY_STRING;
    while (better_getline(&line, f)) {
        if (line.length == 0) {
            continue;
        }

        struct unparsed_row raw_row = BUFFER_NEW;

        for (size_t i = 1; i < line.length; i += 4) {
            BUFFER_PUSH(raw_row, line.data[i]);
        }

        BUFFER_PUSH(raw_crates, raw_row);
    }

    for (size_t i = 0; i < raw_crates.length; i++) {
        BUFFER_FREE(raw_crates.data[i]);
    }
    BUFFER_FREE(raw_crates);

    STRING_FREE(line);
    fclose(f);
    return STRING_REF("");
}
