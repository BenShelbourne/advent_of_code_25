#include <stdbool.h>
#include <stdio.h>

#include "file.h"

bool is_roll(char pos) {
    return pos == '@';
}

bool is_movable(file_t file, size_t columns, size_t x, size_t y) {
    bool spaceRight = false;
    bool spaceLeft = false;
    size_t rolls_found = 0;
    size_t rows = file.line_count;

    // printf("\tis_movable: x=%lu y=%lu\n", x, y);
    if (x + 1 < columns) {
        spaceRight = true;
        if (is_roll(file.lines[y].data[x+1])) rolls_found++;
    }

    if (x > 0) {
        spaceLeft = true;
        if (is_roll(file.lines[y].data[x-1])) rolls_found++;
    }

    if (y + 1 < rows) {
        if (is_roll(file.lines[y+1].data[x])) rolls_found++;
        if (spaceLeft) {
            if (is_roll(file.lines[y+1].data[x-1])) rolls_found++;
        }
        if (spaceRight) {
            if (is_roll(file.lines[y+1].data[x+1])) rolls_found++;
        }
    }

    if (y > 0) {
        if (is_roll(file.lines[y-1].data[x])) rolls_found++;
        if (spaceLeft) {
            if (is_roll(file.lines[y-1].data[x-1])) rolls_found++;
        }
        if (spaceRight) {
            if (is_roll(file.lines[y-1].data[x+1])) rolls_found++;
        }
    }

    return rolls_found < 4;
}

int main(void) {
    file_t file = read_file("input.txt");
    size_t total = 0;

    for (size_t i = 0; i < file.line_count; ++i) {
        line_t line = file.lines[i];
        for (size_t j = 0; j < line.length; ++j) {
            if (is_roll(line.data[j])) {
                bool move = is_movable(file, line.length, j, i);
                if (move) total++;
            }
        }
    }

    free_file(&file);

    printf("%lu\n", total);
}