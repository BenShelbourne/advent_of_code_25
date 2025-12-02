#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures.h"
#include "file.h"
#include "string_help.h"

// PART 1
// bool check_one_id(const char *id) {
//     size_t len = strlen(id);
//     if (len % 2 == 0) {
//         int midpoint = len/2;
//         char *first_half = substring(id, 0, midpoint);
//         char *second_half = substring(id, midpoint, len);

//         if (first_half[0] == 0 || second_half[0] == 0) {
//             return 0;
//         }

//         // printf("\t%lu/%d: %s - %s\n",len, midpoint, first_half, second_half);
//         return strcmp(first_half, second_half) == 0;
//     }
//     return false;
// }

list_t get_chunks(const char *id, int chunks) {
    size_t len = strlen(id);
    size_t chunk_size = len / chunks;
    list_t chunk_list = create_list();

    for (size_t i = 0; i < len; i+=chunk_size) {
        node_t chunk = create_node(substring(id, i, i+chunk_size));
        list_push_back(&chunk, &chunk_list);
    }

    return chunk_list;
}

bool check_one_id(const char *id) {
    bool isValid = false;
    size_t len = strlen(id);
    for (size_t i = 2; i <= 10; ++i) {
        if (len % i == 0) {
            list_t chunks = get_chunks(id, i);
            
            isValid = true;
            for (size_t j = 1; j < chunks.length; ++j) {
                // printf("comparing %s with %s\n", chunks.nodes[0].data, chunks.nodes[j].data);
                if (strcmp(chunks.nodes[0].data, chunks.nodes[j].data) != 0) {
                    isValid = false;
                    break;
                }
            }
            
            free_list(&chunks);
            if(isValid) return true;
        }
    }

    return isValid;
}

unsigned long long check_valid(const node_t *first, const node_t *second) {
    unsigned long long start = strtoull(first->data, NULL, 10);
    unsigned long long end = strtoull(second->data, NULL, 10);
    unsigned long long total = 0;

    // printf("%llu-%llu\n", start, end);

    for (unsigned long long value = start; value <= end; ++value) {
        char buffer[32];
        int written = snprintf(buffer, sizeof buffer, "%llu", value);
        if (written < 0 || written >= sizeof buffer) {
            fprintf(stderr, "check_valid: failed to convert int -> char.\n");
        }

        if (check_one_id(buffer)) {
            // printf("\t\t%llu\n", value);
            total += value;
        }
    }

    return total;
}

int main(void) {
    file_t file = read_file("input.txt");
    
    // input guaranteed to be single line
    line_t input = file.lines[0];

    list_t ranges = split(input.data, ',');

    unsigned long long result = 0;

    for (size_t i = 0; i < ranges.length; i++) {
        list_t ids = split(ranges.nodes[i].data, '-');
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