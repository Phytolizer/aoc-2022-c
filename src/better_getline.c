#include "aoc/better_getline.h"

#include <stdio.h>

bool better_getline(struct string* buffer, FILE* stream) {
    buffer->length = 0;

    ssize_t len = getline(&buffer->data, &buffer->capacity, stream);
    if (len < 0) {
        return false;
    }

    buffer->length = len - 1;
    return true;
}
