#ifndef FILE_H
#define FILE_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t length;
} line_t;

typedef struct {
    size_t line_count;
    line_t *lines;
} file_t;

file_t read_file(const char* file_loc);
void free_file(file_t *file);

#endif