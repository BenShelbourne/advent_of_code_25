#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t size;
} node_t;

typedef struct linked_node {
    char *data;
    struct linked_node *next;
    size_t size;
} linked_node_t;

typedef struct double_linked_node {
    char *data;
    struct double_linked_node *next;
    struct double_linked_node *prev;
    size_t size;
} double_linked_node_t;

typedef struct {
    node_t key;
    node_t value;
} key_value_t;

typedef struct {
    node_t *nodes;
    size_t length;
    size_t capacity;
} list_t;

typedef struct {
    key_value_t *data;
    size_t length;
    size_t capacity;
} map_t;

typedef struct {
    list_t *rows;
    size_t row_count;
} matrix_t;

node_t create_node(const char *data);

key_value_t create_key_value(const node_t key, const node_t value);

list_t create_list();
void push_back(node_t node, list_t *list);
node_t pop(list_t *list);
int get_index(node_t node, list_t list);
void free_list(list_t list);

map_t create_empty_map();
void push_back(key_value_t node, map_t *map);
key_value_t remove_item_from_map(int idx, map_t *map);
key_value_t remove_item_from_map(key_value_t node, map_t *map);
key_value_t pop(map_t *map);
void free_map(map_t *map);

matrix_t create_matrix();
void add_row(list_t row, matrix_t *matrix);
key_value_t find_item(node_t search, matrix_t matrix);
void free_matrix(matrix_t *matrix);


#endif