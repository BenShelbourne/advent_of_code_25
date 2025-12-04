#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "string_help.h"

key_value_t find_highest_num(char *input) {
    char highest_num = '0';
    int highest_idx = -1;
    for (size_t i = 0; i < strlen(input); ++i) {
        char current = input[i];
        if (current == '9') {
            char *idx = int_to_buffer(i);
            char *val = "9";
            node_t key = create_node(idx);
            free(idx);
            node_t value = create_node(val);
            key_value_t ret = create_key_value(key, value);
            return ret;
        }

        if (current > highest_num) {
            // printf("\t\t\tcurr=%c idx=%lu\n", current, i);
            highest_num = current;
            highest_idx = i;
        }
    }

    char *idx = int_to_buffer(highest_idx);
    char val[2] = {highest_num, '\0'};
    node_t key = create_node(idx);
    free(idx);
    node_t value = create_node(val);
    key_value_t ret = create_key_value(key, value);
    return ret;
}

int main(void) {
    file_t file = read_file("input.txt");

    unsigned long long total = 0;
    for (size_t i = 0; i < file.line_count; ++i) {
        int battery_size = 12;
        line_t battery_pack = file.lines[i];
        char buffer[battery_size + 1];
        size_t buffer_offset = 0;

        char *first_search = substring(battery_pack.data, 0, battery_pack.length - 1 - (battery_size - 1));
        key_value_t first_num = find_highest_num(first_search);
        size_t cut = (size_t)buffer_to_int(first_num.key.data);
        buffer[buffer_offset++] = first_num.value.data[0];

        printf("\t\tfirst_cut=%lu first_key=%s first_val=%s first_sub=%s\n", cut, first_num.key.data, first_num.value.data, first_search);


        size_t remaining = battery_size - 1;
        while(remaining--) {
            size_t start = cut + 1;
            char *search_string = substring(battery_pack.data, start, battery_pack.length - 1 - remaining);

            key_value_t search = find_highest_num(search_string);

            size_t cursor = (size_t)buffer_to_int(search.key.data);
            cut = start + cursor;
            buffer[buffer_offset++] = search.value.data[0];
            free(search_string);
            free_key_value(&search);            
        }

        free(first_search);
        free_key_value(&first_num);

        // buffer[buffer_offset++] = first_num.value.data[0];
        // free(first_search);
        // free_key_value(&first_num);

        // for (size_t j = battery_size -= 1; j > 0; --j) {
        //     char *search_string = substring(battery_pack.data, cut + 1, battery_pack.length - j);
        //     key_value_t search = find_highest_num(search_string);

        //     cut += (size_t)buffer_to_int(search.key.data) + 1;
        //     printf("\t\tcut=%lu key=%s val=%s sub=%s j=%lu\n", cut, search.key.data, search.value.data, search_string, j);
        //     buffer[buffer_offset++] = search.value.data[0];
        //     free(search_string);
        //     free_key_value(&search);
        // }

        buffer[buffer_offset] = '\0';

        // 987654321111111

        printf("\tbuff=%s\n", buffer);
        total += strtoul(buffer, NULL, 10);
    }

    free_file(&file);

    printf("%llu\n", total);
}