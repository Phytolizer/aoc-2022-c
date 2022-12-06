#include "aoc/better_getline.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long SSize;

// https://stackoverflow.com/a/27369716
// Cross-platform getline() and getdelim() implementations.
static SSize nonstd_getdelim(char** linep, size_t* n, int delim, FILE* fp) {
    int ch;
    size_t i = 0;
    if (!linep || !n || !fp) {
        errno = EINVAL;
        return -1;
    }
    if (*linep == NULL) {
        if (NULL == (*linep = malloc(*n = 128))) {
            *n = 0;
            errno = ENOMEM;
            return -1;
        }
    }
    while ((ch = fgetc(fp)) != EOF) {
        if (i + 1 >= *n) {
            char* temp = realloc(*linep, *n + 128);
            if (!temp) {
                errno = ENOMEM;
                return -1;
            }
            *n += 128;
            *linep = temp;
        }
        (*linep)[i++] = (char)ch;
        if (ch == delim) break;
    }
    (*linep)[i] = '\0';
    return !i && ch == EOF ? -1 : (SSize)i;
}

static SSize nonstd_getline(char** linep, size_t* n, FILE* fp) {
    return nonstd_getdelim(linep, n, '\n', fp);
}

bool better_getline(struct string* buffer, FILE* stream) {
    SSize len = nonstd_getline(&buffer->data, &buffer->capacity, stream);
    if (len < 0) {
        return false;
    }

    if (len == 0) {
        return true;
    }

    buffer->length = len - 1;
    return true;
}
