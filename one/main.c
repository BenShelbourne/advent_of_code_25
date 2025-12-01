#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file.h"

int rotate_left(int rotation, int *dial) {
    int password = 0;
    for (size_t i = 0; i < rotation; i++) {
        *dial -= 1;
        if (*dial > 99) {
            *dial = 0;
        } else if (*dial < 0) {
            *dial = 99;
        }

        if (*dial == 0 && i != rotation -1) {
            // printf("passed go %d\n", rotation);
            ++password;
        } 
    }
    return password;
}

int rotate_right(int rotation, int *dial) {
    int password = 0;
    for (size_t i = 0; i < rotation; i++) {
        (*dial)++;
        if (*dial > 99) {
            *dial = 0;
        } else if (*dial < 0) {
            *dial = 99;
        }

        if (*dial == 0 && i != rotation -1) {
            // printf("passed go %d: dial %d\n", rotation, *dial);
            ++password;
        } 
    }
    return password;
}

int main(void) {
    file_t file = read_file("input.txt");
    int dial = 50;
    int password = 0;

    if (!file.lines && file.line_count == 0) {
        fprintf(stderr, "Failed to read file\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < file.line_count; ++i) {
        line_t line = file.lines[i];
        if (line.length == 0) {
            continue;
        }
        char direction = line.data[0];
        char *copy = strdup(line.data);
        if (!copy) {
            continue;
        }

        memmove(copy, copy + 1, line.length);
        int rotation = atoi(copy);

        if (direction == 'L') {
            password += rotate_left(rotation, &dial);
        }
        else if (direction == 'R') {
            password += rotate_right(rotation, &dial);
        }

        free(copy);

        if (dial == 0) {
            password++;
        }
        printf("%d %c -> %d\n",dial, direction, rotation);
    }

    printf("Password: %d\n", password);

    free_file(&file);
}