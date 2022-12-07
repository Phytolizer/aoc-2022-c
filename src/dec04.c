#include "aoc/dec04.h"

#include <stdio.h>

#include "aoc/better_getline.h"

struct range {
    int min;
    int max;
};

static bool range_contains(struct range a, struct range b) {
    // return whether a fully contains b, or b fully contains a
    return (a.min <= b.min && a.max >= b.max) || (b.min <= a.min && b.max >= a.max);
}

static bool range_overlaps(struct range a, struct range b) {
    // return whether a and b overlap
    return (a.min <= b.min && a.max >= b.min) || (b.min <= a.min && b.max >= a.min);
}

static int parse_int(struct string* s) {
    int result = 0;
    size_t i = 0;
    while (i < s->length && s->data[i] >= '0' && s->data[i] <= '9') {
        result *= 10;
        result += s->data[i] - '0';
        i++;
    }
    *s = STRING_SLICE(*s, i, s->length);
    return result;
}

struct string dec04_run(struct string path, size_t part) {
    FILE* f = fopen(path.data, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file " STRING_FMT "\n", STRING_ARG(path));
        exit(1);
    }

    size_t total = 0;

    struct string line = EMPTY_STRING;
    while (better_getline(&line, f)) {
        if (line.length == 0) {
            continue;
        }
        struct range a;
        struct range b;
        struct string parser = line;
        a.min = parse_int(&parser);
        parser = STRING_SLICE(parser, 1, parser.length);
        a.max = parse_int(&parser);
        parser = STRING_SLICE(parser, 1, parser.length);
        b.min = parse_int(&parser);
        parser = STRING_SLICE(parser, 1, parser.length);
        b.max = parse_int(&parser);

        if (part == 1) {
            total += range_contains(a, b);
        } else {
            total += range_overlaps(a, b);
        }
    }

    STRING_FREE(line);
    fclose(f);

    return string_printf("%zu", total);
}
