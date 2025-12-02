#include <stdlib.h>
#include <string.h>

#include "string_help.h"

list_t split(char *data, char delimeter) {
    const char *start = data;
    list_t list = create_list();

    while (start) {
        const char *end = strchr(start, delimeter);
        size_t len = end ? (size_t)(end - start) : strlen(start);
        char *token = malloc(len + 1);
        memcpy(token, start, len);
        token[len] = '\0';
        node_t node = create_node(token);
        list_push_back(&node, &list);
        free(token);
        start = end ? end + 1 : NULL;
    }

    return list;
}

char *substring(const char *string, size_t start, size_t end) {
    if (!string) return NULL;

    size_t len = strlen(string);
    if (start > end || end > len) return NULL;

    if (start == end) return strdup(string);

    size_t slice_len = end - start;
    char *substring = malloc(slice_len + 1);
    if (!substring) return NULL;

    memcpy(substring, string + start, slice_len);
    substring[slice_len] = '\0';
    return substring;
}
