#ifndef AOC_BETTER_FGETS_H_
#define AOC_BETTER_FGETS_H_

#include <stdbool.h>
#include <stdio.h>

#include "aoc/string.h"

bool better_getline(struct string* buffer, FILE* stream);

#endif  // AOC_BETTER_FGETS_H_
