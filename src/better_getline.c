#include "aoc/better_getline.h"

#include <stdio.h>

bool better_getline(struct string* buffer, FILE* stream) {
    ssize_t len = getline(&buffer->data, &buffer->capacity, stream);
    if (len < 0) {
        return false;
    }

    if (len == 0) {
        return true;
    }

    buffer->length = len - 1;
    return true;
}
