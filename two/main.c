#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures.h"
#include "file.h"

list_t string_split(char *data, char delimeter) {
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

char *string_substring(const char *string, size_t start, size_t end) {
    if (!string) return NULL;

    size_t len = strlen(string);
    if (start > end || end > len) return NULL;

    if (start == end) return string;

    size_t slice_len = end - start;
    char *substring = malloc(slice_len + 1);
    if (!substring) return NULL;

    memcpy(substring, string + start, slice_len);
    substring[slice_len] = '\0';
    return substring;
}

// IDIOT MISREAD THE QUESTION!!!!!
// int check_one_id(const node_t *product_id) {
//     if (!product_id || product_id->size <= 1) return 0;

//     const char *data = product_id->data;
//     if (!data || data[0] == '0') return 0;
    
//     char *invalid_id = calloc(product_id->size + 1, 1);
//     if (!invalid_id) {
//         fprintf(stderr, "check_one_id: could not create buffer.\n");
//         return 0;
//     }

//     for (size_t i = 1; i < product_id->size; i++) {
//         if (data[i-1] == data[i]) {
//             if (i == 1) {
//                 invalid_id[0] = data[0];
//                 invalid_id[1] = data[1];
//             } else {
//                 invalid_id[i] = data[i];
//             }
//         }
//     }

//     int result = invalid_id[0] ? atoi(invalid_id) : 0;
//     free(invalid);
//     return result;
// }

// int check_two_ids(const node_t *first_prod, const node_t *second_prod) {
//     if (!first_prod || !second_prod)
// }

// int check_valid(node_t first, node_t second) {
//     return check_one_id(&first) + check_one_id(&second) + check_two_ids(&first, &second);
// }

bool check_one_id(const char *id) {
    size_t len = strlen(id);
    if (len % 2 == 0) {
        int midpoint = len/2;
        char *first_half = string_substring(id, 0, midpoint);
        char *second_half = string_substring(id, midpoint, len);

        if (first_half[0] == 0 || second_half[0] == 0) {
            return 0;
        }

        // printf("\t%lu/%d: %s - %s\n",len, midpoint, first_half, second_half);
        return strcmp(first_half, second_half) == 0;
    }
    return false;
}

unsigned long long check_valid(const node_t *first, const node_t *second) {
    unsigned long long start = strtoull(first->data, NULL, 10);
    unsigned long long end = strtoull(second->data, NULL, 10);
    unsigned long long total = 0;

    printf("%llu-%llu\n", start, end);

    for (unsigned long long value = start; value <= end; ++value) {
        char buffer[32];
        int written = snprintf(buffer, sizeof buffer, "%llu", value);
        if (written < 0 || written >= sizeof buffer) {
            fprintf(stderr, "check_valid: failed to convert int -> char.\n");
        }

        if (check_one_id(buffer)) {
            printf("\t\t%llu\n", value);
            total += value;
        }
    }

    return total;
}

int main(void) {
    file_t file = read_file("input.txt");
    
    // input guaranteed to be single line
    line_t input = file.lines[0];

    list_t ranges = string_split(input.data, ',');

    unsigned long long result = 0;

    for (size_t i = 0; i < ranges.length; i++) {
        list_t ids = string_split(ranges.nodes[i].data, '-');
        if (ids.length != 2) {
            fprintf(stderr, "More than 2 ids!\n");
            continue;
        }

        result += check_valid(&ids.nodes[0], &ids.nodes[1]);
        free_list(&ids);
    }

    free_list(&ranges);
    free_file(&file);

    printf("%llu\n", result);
}