#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "file.h"

file_t read_file(const char* file_loc) {
    file_t result = {.line_count = 0, .lines = NULL};
    FILE *file_ptr = fopen(file_loc, "r");

    if (!file_ptr) {
        return result;
    }

    line_t *lines = NULL;
    size_t line_count = 0;
    size_t capacity = 0;

    char *buffer = NULL;
    size_t bufcap = 0;
    ssize_t read;

    while((read = getline(&buffer, &bufcap, file_ptr)) != -1) {
        if (line_count == capacity) {
            size_t new_capacity = capacity == 0 ? 8 : capacity * 2;
            line_t *tmp = realloc(lines, new_capacity * sizeof *lines);
            if (!tmp) {
                fclose(file_ptr);
                free(buffer);
                return result;
            }
            lines = tmp;
            capacity = new_capacity;
        }

        char *copy = malloc((size_t)read + 1);
        if (!copy) {
            fclose(file_ptr);
            free(buffer);
            return result;
        }

        memcpy(copy, buffer, (size_t)read);
        copy[read] = '\0';

        lines[line_count].data = copy;
        lines[line_count].length = (size_t)read;
        line_count++;
    }

    fclose(file_ptr);
    free(buffer);

    result.line_count = line_count;
    result.lines = lines;
    return result;
}

void free_file(file_t *file) {
    if (!file || !file->lines) {
        return;
    }

    for(size_t i = 0; i < file->line_count; ++i) {
        free(file->lines[i].data);
    }

    free(file->lines);
    file->lines = NULL;
    file->line_count = 0;
}