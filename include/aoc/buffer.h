#ifndef AOC_BUFFER_H_
#define AOC_BUFFER_H_

#include <stddef.h>
#include <stdlib.h>

#define DECLARE_BUFFER(Name, T) \
    struct Name { \
        T* data; \
        size_t length; \
        size_t capacity; \
    }

#define BUFFER_NEW \
    { .data = NULL, .length = 0, .capacity = 0, }

#define BUFFER_INIT(Name, T) ((struct Name)BUFFER_NEW)

#define BUFFER_PUSH(Buf, Value) \
    do { \
        if ((Buf).length == (Buf).capacity) { \
            (Buf).capacity = (Buf).capacity == 0 ? 1 : (Buf).capacity * 2; \
            (Buf).data = realloc((Buf).data, (Buf).capacity * sizeof(*(Buf).data)); \
        } \
        (Buf).data[(Buf).length++] = (Value); \
    } while (0)

#define BUFFER_POP(Buf) ((Buf).length == 0 ? (abort(), (Buf).data[0]) : (Buf).data[--(Buf).length])

#define BUFFER_FREE(Buf) \
    do { \
        free((Buf).data); \
        (Buf).data = NULL; \
        (Buf).length = 0; \
        (Buf).capacity = 0; \
    } while (0)

#define BUFFER_REF(Ptr, Length) \
    { .data = (Ptr), .length = (Length), .capacity = (Length), }

#define BUFFER_FROM_ARRAY(Array) \
    { \
        .data = (Array), .length = sizeof(Array) / sizeof(*(Array)), \
        .capacity = sizeof(Array) / sizeof(*(Array)), \
    }

#endif  // AOC_BUFFER_H_
