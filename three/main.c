#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "string_help.h"

char *int_to_buffer(int num) {
    char buf[12];
    int len = snprintf(buf, sizeof buf, "%d", num);
    if (len < 0) return NULL;
    char *res = malloc((size_t)len + 1);
    if (!res) return NULL;
    memcpy(res, buf, (size_t)len + 1);
    return res;
}

int buffer_to_int(const char *buffer) {
    if (!buffer) return 0;
    char *end = NULL;
    long val = strtol(buffer, &end, 10);
    return (end == buffer) ? 0 : (int)val;
}

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

    int total = 0;
    for (size_t i = 0; i < file.line_count; ++i) {
        line_t battery_pack = file.lines[i];
        char *first_search = substring(battery_pack.data, 0, battery_pack.length - 2);
        key_value_t first_num = find_highest_num(first_search);

        size_t cut = (size_t)buffer_to_int(first_num.key.data);
        // printf("\t\tcut=%lu key=%s val=%s\n", cut, first_num.key.data, first_num.value.data);
        char *second_search = substring(battery_pack.data, cut + 1, battery_pack.length);
        key_value_t second_num = find_highest_num(second_search);

        char buffer[4];
        int written = snprintf(buffer, sizeof buffer, "%s%s", first_num.value.data, second_num.value.data);
        if (written < 0 || written >= sizeof buffer) {
            fprintf(stderr, "check_valid: failed to convert int -> char.\n");
        }

        // printf("\tbuff=%s\n", buffer);
        total += atoi(buffer);

        free(first_search);
        free(second_search);
        free_key_value(&first_num);
        free_key_value(&second_num);
    }

    free_file(&file);

    printf("%d\n", total);
}