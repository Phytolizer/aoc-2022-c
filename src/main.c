#include <stdio.h>

#include "aoc/buffer.h"
#include "aoc/dec01.h"
#include "aoc/string.h"

DECLARE_BUFFER(string_buffer, char*);

int main(int argc, char** argv) {
    struct string_buffer args = BUFFER_REF(argv, argc);

    if (args.length != 3) {
        fprintf(stderr, "Usage: %s <day> <part>\n", args.data[0]);
        return 1;
    }

    struct string day_str = STRING_REF_FROM_C(args.data[1]);
    struct string part_str = STRING_REF_FROM_C(args.data[2]);

    char* endp;
    long day = strtol(day_str.data, &endp, 10);
    if (*endp != 0) {
        fprintf(stderr, "Invalid day: %s\n", day_str.data);
        return 1;
    }

    long part = strtol(part_str.data, &endp, 10);
    if (*endp != 0) {
        fprintf(stderr, "Invalid part: %s\n", part_str.data);
        return 1;
    }

    if (day < 1 || day > 25) {
        fprintf(stderr, "Day must be between 1 and 25\n");
        return 1;
    }

    if (part < 1 || part > 2) {
        fprintf(stderr, "Part must be 1 or 2\n");
        return 1;
    }

    struct string day_path = string_printf("input/dec%02ld-full.txt", day);

    switch (day) {
        case 1: {
            struct string result = dec01_run(day_path, part);
            printf(STRING_FMT "\n", STRING_ARG(result));
            STRING_FREE(result);
        } break;
        default:
            fprintf(stderr, "Day %ld not implemented yet\n", day);
            return 1;
    }

    STRING_FREE(day_path);
}
