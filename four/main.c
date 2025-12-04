#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "string_help.h"

void remove_movable_rolls(const map_t *map, file_t *file) {
    for (size_t i = 0; i < map->length; ++i) {
        size_t y = buffer_to_int(map->data[i].key.data);
        size_t x = buffer_to_int(map->data[i].value.data);
        printf("\t\trewrite: x=%lu y=%lu\n", x, y);
        line_t *row = &file->lines[y];
        row->data[x] = 'x';
    }
}

key_value_t create_coordinate(size_t x, size_t y) {
    char *x_ordinate = int_to_buffer((int)x);
    char *y_ordinate = int_to_buffer((int)y);
    key_value_t kvt = create_key_value(create_node(y_ordinate), create_node(x_ordinate));
    free(x_ordinate);
    free(y_ordinate);
    return kvt;
}

bool is_roll(char pos) {
    return pos == '@';
}

bool is_movable(file_t file, size_t columns, size_t x, size_t y) {
    bool spaceRight = false;
    bool spaceLeft = false;
    size_t rolls_found = 0;
    size_t rows = file.line_count;

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
    size_t subtotal = 0;

    while (true) {
        map_t rewrite = create_empty_map();
        for (size_t i = 0; i < file.line_count; ++i) {
            line_t line = file.lines[i];
            for (size_t j = 0; j < line.length; ++j) {
                if (is_roll(line.data[j])) {
                    bool move = is_movable(file, line.length, j, i);
                    if (move) {
                        subtotal++;
                        key_value_t kv = create_coordinate(j, i);
                        map_push_back(&kv, &rewrite);
                    }
                }
            }
        }
        printf("\tsubtotal=%lu map_size=%lu\n", subtotal, rewrite.length);
        remove_movable_rolls(&rewrite, &file);

        free_map(&rewrite);
        total += subtotal;
        printf("\ttotal=%lu subtotal=%lu\n", total, subtotal);
        if (subtotal == 0) break;
        subtotal = 0;
    }

    free_file(&file);

    printf("%lu\n", total);
}