#include "aoc/dec02.h"

#include <assert.h>
#include <stdio.h>

#include "aoc/better_getline.h"

typedef enum {
    SHAPE_ROCK = 1,
    SHAPE_PAPER = 2,
    SHAPE_SCISSORS = 3,
} Shape;

typedef enum {
    GR_LOSS = 0,
    GR_DRAW = 3,
    GR_WIN = 6,
} GameResult;

static const Shape text_to_shape[256] = {
    ['A'] = SHAPE_ROCK,
    ['B'] = SHAPE_PAPER,
    ['C'] = SHAPE_SCISSORS,
    ['X'] = SHAPE_ROCK,
    ['Y'] = SHAPE_PAPER,
    ['Z'] = SHAPE_SCISSORS,
};

static const GameResult text_to_game_result[256] = {
    ['X'] = GR_LOSS,
    ['Y'] = GR_DRAW,
    ['Z'] = GR_WIN,
};

static GameResult play(Shape a, Shape b) {
    if (a == b) {
        return GR_DRAW;
    }

    Shape winner = a % 3 + 1;
    if (b == winner) {
        return GR_WIN;
    } else {
        return GR_LOSS;
    }
}

static Shape optimal_shape(Shape a, GameResult desired) {
    if (desired == GR_DRAW) {
        return a;
    }

    Shape winner = a % 3 + 1;
    if (desired == GR_WIN) {
        return winner;
    } else {
        return winner % 3 + 1;
    }
}

struct string dec02_run(struct string path, size_t part) {
    FILE* f = fopen(path.data, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file: " STRING_FMT "\n", STRING_ARG(path));
        exit(1);
    }

    struct string line = EMPTY_STRING;

    size_t total = 0;
    while (better_getline(&line, f)) {
        if (line.length == 0) {
            continue;
        }

        assert(line.length == 3);
        char a = line.data[0];
        char b = line.data[2];

        Shape shape_a = text_to_shape[(size_t)a];
        assert(shape_a != 0);
        switch (part) {
            case 1: {
                Shape shape_b = text_to_shape[(size_t)b];
                assert(shape_b != 0);
                GameResult result = play(shape_a, shape_b);
                total += result + shape_b;
            } break;
            case 2: {
                GameResult desired = text_to_game_result[(size_t)b];
                Shape shape_b = optimal_shape(shape_a, desired);
                assert(shape_b != 0);
                total += desired + shape_b;
            }
        }
    }

    fclose(f);
    STRING_FREE(line);

    return string_printf("%zu", total);
}
