#ifndef STRING_HELP_H
#define STRING_HELP_H

#include "data_structures.h"

list_t split(char *data, char delimeter);
char *substring(const char *string, size_t start, size_t end);
char *int_to_buffer(int num);
int buffer_to_int(const char *buffer);

#endif
