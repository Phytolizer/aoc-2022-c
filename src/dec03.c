#include "aoc/dec03.h"

#include <limits.h>
#include <stdio.h>

#include "aoc/better_getline.h"
#include "aoc/buffer.h"

struct partitioned_string {
    struct string a;
    struct string b;
};

static struct partitioned_string partition(struct string s) {
    size_t middle = s.length / 2;
    return (struct partitioned_string){
        .a = STRING_SLICE(s, 0, middle),
        .b = STRING_SLICE(s, middle, s.length),
    };
}

static size_t bitset_idx(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        return letter - 'a';
    }
    if (letter >= 'A' && letter <= 'Z') {
        return letter - 'A' + 26;
    }
    return 0;
}

struct bitset {
    // a-zA-Z
    bool v[52];
};

DECLARE_BUFFER(bitset_buffer, struct bitset);

static struct bitset bitset_from_str(struct string s) {
    struct bitset bs = {0};
    for (size_t i = 0; i < s.length; i++) {
        bs.v[bitset_idx(s.data[i])] = true;
    }
    return bs;
}

static struct bitset bitset_product(struct bitset_buffer bss) {
    struct bitset bs = bss.data[0];
    for (size_t i = 1; i < bss.length; i++) {
        for (size_t j = 0; j < sizeof(bs.v); j++) {
            bs.v[j] *= bss.data[i].v[j];
        }
    }
    return bs;
}

static char bitset_to_priority(struct bitset bs) {
    for (size_t i = 0; i < sizeof(bs.v); i++) {
        if (bs.v[i]) {
            return i + 1;
        }
    }
    return 0;
}

struct string dec03_run(struct string path, size_t part) {
    FILE* f = fopen(path.data, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file: " STRING_FMT "\n", STRING_ARG(path));
        exit(1);
    }

    struct bitset groups[3] = {0};
    size_t total = 0;
    size_t group_idx = 0;
    struct string line = EMPTY_STRING;

    while (better_getline(&line, f)) {
        if (line.length == 0) {
            continue;
        }

        switch (part) {
            case 1: {
                struct partitioned_string ps = partition(line);
                struct bitset unique_left = bitset_from_str(ps.a);
                struct bitset unique_right = bitset_from_str(ps.b);
                struct bitset temp[] = {unique_left, unique_right};
                struct bitset intersection =
                    bitset_product((struct bitset_buffer)BUFFER_FROM_ARRAY(temp));
                total += bitset_to_priority(intersection);
            } break;
            case 2: {
                groups[group_idx] = bitset_from_str(line);
                group_idx++;
                if (group_idx == 3) {
                    struct bitset intersection =
                        bitset_product((struct bitset_buffer)BUFFER_FROM_ARRAY(groups));
                    total += bitset_to_priority(intersection);
                    group_idx = 0;
                }
            } break;
        }
    }

    STRING_FREE(line);
    fclose(f);

    return string_printf("%zu", total);
}
