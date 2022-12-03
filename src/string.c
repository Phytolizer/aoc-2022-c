#include "aoc/string.h"

#include <stdarg.h>
#include <stdio.h>

struct string string_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int length = vsnprintf(0, 0, fmt, args);
    va_end(args);

    struct string str = {
        .data = malloc(length + 1),
        .length = length,
        .capacity = length + 1,
    };

    va_start(args, fmt);
    vsnprintf(str.data, str.capacity, fmt, args);
    va_end(args);

    str.length = length;

    return str;
}
