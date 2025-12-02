#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data_structures.h"

node_t create_node(const char *data) {
    if (data == NULL) {
        fprintf(stderr, "create_node: NULL data\n");
        return (node_t){0};
    }

    node_t node = { .data = strdup(data), .size = strlen(data)};
    return node;
}

void free_node(node_t *node) {
    if (!node) return;
    free(node->data);
    node->data = NULL;
    node->size = 0;
}

key_value_t create_key_value(const node_t key, const node_t value) {
    key_value_t kvt = { .key = key, .value = value};
    return kvt;
}

void free_key_value(key_value_t *kvt) {
    free_node(&kvt->key);
    free_node(&kvt->value);
}

list_t create_list() {
    const size_t init_capacity = 4;
    list_t list = {0};

    list.nodes = malloc(init_capacity * sizeof *list.nodes);

    if (!list.nodes) {
        fprintf(stderr, "create_list: out of memory.\n");
        return list;
    }

    list.capacity = init_capacity;
    list.length = 0;
    return list;
}

bool list_push_back(const node_t *value, list_t *list) {
    if (!list || !value) return false;

    if (list->length == list->capacity) {
        size_t new_capacity = list->capacity ? list->capacity * 2 : 4;
        node_t *tmp = realloc(list->nodes, new_capacity * sizeof *tmp);
        if (!tmp) {
            fprintf(stderr, "list_push_back: realloc failed.\n");
            return false;
        }
        list->nodes = tmp;
        list->capacity = new_capacity;
    }

    list->nodes[list->length++] = *value;
    return true;
}

node_t list_pop(list_t *list) {
    if (!list || list->length == 0) return (node_t){0};
    node_t node = list->nodes[--list->length];
    list->nodes[list->length] = (node_t){0};
    return node;
}

int get_list_index(node_t node, list_t list) {
    printf("get_list_index: Not implemented.\n");
    return -1;
}

void free_list(list_t *list) {
    if (!list) return;
    for (size_t i = 0; i < list->length; i++) {
        free_node(&list->nodes[i]);        
    }
    free(list->nodes);
    *list = (list_t){0};
}

map_t create_empty_map() {
    const size_t init_capacity = 8;
    map_t map = {0};

    map.data = malloc(init_capacity * sizeof *map.data);
    if (!map.data) {
        fprintf(stderr, "create_empty_map: out of memory.\n");
        return map;
    }

    map.length = 0;
    map.capacity = init_capacity;
    return map;
}

bool map_push_back(const key_value_t *value, map_t *map) {
    if (!map || !value) return false;

    if (map->length == map->capacity) {
        size_t new_capacity = map->capacity ? map->capacity * 2 : 4;
        key_value_t *tmp = realloc(map->data, new_capacity * sizeof *tmp);
        if (!tmp) {
            fprintf(stderr, "list_push_back: realloc failed.\n");
            return false;
        }
        map->data = tmp;
        map->capacity = new_capacity;
    }

    map->data[map->length++] = *value;
    return true;
}

key_value_t map_pop(map_t *map) {
    if (!map || map->length == 0) return (key_value_t){0};
    key_value_t value = map->data[--map->length];
    map->data[map->length] = (key_value_t){0};
    return value;
}

void free_map(map_t *map) {
    if (!map) return;

    for (size_t i = 0; i < map->length; i++) {
        free_key_value(&map->data[i]);
    }
    free(map);
    *map = (map_t){0};
}

// matrix_t create_matrix();
// void add_row(list_t row, matrix_t *matrix);
// key_value_t find_item(node_t search, matrix_t matrix);
// void free_matrix(matrix_t *matrix);