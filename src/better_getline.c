#include "aoc/better_getline.h"

bool better_getline(struct string* buffer, FILE* stream) {
    buffer->length = 0;

    while (true) {
        int c = fgetc(stream);
        if (c == EOF) {
            return false;
        }
        if (c == '\n') {
            return true;
        }

        if (buffer->length == buffer->capacity) {
            buffer->capacity *= 2;
            char* temp = realloc(buffer->data, buffer->capacity);
            if (!temp) {
                return false;
            }
            buffer->data = temp;
        }

        buffer->data[buffer->length++] = c;
    }
}
