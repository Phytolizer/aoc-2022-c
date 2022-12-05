#ifndef AOC_STRING_H_
#define AOC_STRING_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct string {
    char* data;
    size_t length;
    size_t capacity;
    bool is_ref;
};

#define EMPTY_STRING \
    { NULL, 0, 0, false }

#define STRING_REF_C(str) \
    { (str), sizeof(str) - 1, sizeof(str) - 1, true }

#define STRING_REF(str) ((struct string)STRING_REF_C(str))

#define STRING_REF_FROM_C(str) ((struct string){(str), strlen(str), strlen(str), true})

#define STRING_REF_DATA(str, length) \
    { (str), (length), (length), true }

#define STRING_OWN_DATA(str, length) \
    { (str), (length), (length), false }

#define STRING_FREE(str) \
    do { \
        if (!(str).is_ref) { \
            free((str).data); \
        } \
        (str).data = NULL; \
        (str).length = 0; \
        (str).capacity = 0; \
    } while (0)

#define STRING_EQUAL(a, b) ((a).length == (b).length && memcmp((a).data, (b).data, (a).length) == 0)

struct string string_printf(const char* fmt, ...);

#define STRING_FMT "%.*s"
#define STRING_ARG(str) (int)(str).length, (str).data

#endif  // AOC_STRING_H_
