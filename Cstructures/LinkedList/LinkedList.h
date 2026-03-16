#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../utils/utils.h"

typedef struct Node Node;
struct Node {
    int value;
    Node* next;
};


//LinkedList object that contains only int values
typedef struct LinkedList {
    Node* head;
    int size;
    
    // Function pointers (methods)
    bool (*add_first)(struct LinkedList* self, int value);
    bool (*add_last)(struct LinkedList* self, int value);
    bool (*add_index)(struct LinkedList* self, int index, int value);
    bool (*remove_index)(struct LinkedList* self, int index);
    bool (*set_index)(struct LinkedList* self, int index, int value);
    int (*get_firstElement)(struct LinkedList* self);
    bool (*get_element)(struct LinkedList* self, int index, int* value);
    bool (*index_of)(struct LinkedList* self, int value, int* index);
    bool (*last_index_of)(struct LinkedList* self, int value, int* index);
    void (*sort)(struct LinkedList* self, bool order);
    int* (*get_frequencies)(struct LinkedList* self, int* result_size);
    int* (*to_list)(struct LinkedList* self);
    int* (*to_list_unique)(struct LinkedList* self, int* unique_size);
    int (*max)(struct LinkedList* self);
    int (*min)(struct LinkedList* self);
    bool (*add_all)(struct LinkedList* self, int elements[], int count, int index);
    bool (*retain_all)(struct LinkedList* self, int elements[], int count);
    bool (*swap_elements)(struct LinkedList* self, int index1, int index2);
    bool (*clear)(struct LinkedList* self);
    bool (*contains)(struct LinkedList* self, int value);
    bool (*is_empty)(struct LinkedList* self);
    bool (*replace_all)(struct LinkedList* self, int (*replace_function)(int));
    void (*free_list)(struct LinkedList* self);
    void (*print_values)(struct LinkedList* self);
} LinkedList;


LinkedList* create_LinkedList_impl(int starters[]);
void free_LinkedList_impl(LinkedList* self);
bool add_first_impl(LinkedList* self, int value);
bool add_last_impl(LinkedList* self, int value);
int get_size_impl(LinkedList* self);
int get_firstElement_impl(LinkedList* self);
int get_lastElement_impl(LinkedList* self);
bool get_element_impl(LinkedList* self, int index, int* value);
bool index_of_impl(LinkedList* self, int value, int* index);
bool last_index_of_impl(LinkedList* self, int value, int* index);
void sort_impl(LinkedList* self, bool order);
int* get_frequencies_impl(LinkedList* self, int* result_size);
int* to_list_impl(LinkedList* self);
int* to_list_unique_impl(LinkedList* self, int* unique_size);
int max_impl(LinkedList* self);
int min_impl(LinkedList* self);
bool add_all_impl(LinkedList* self, int elements[], int count, int index);
bool retain_all_impl(LinkedList* self, int elements[], int count);
bool add_index_impl(LinkedList* self, int value, int index);
bool remove_index_impl(LinkedList* self, int index);
bool set_index_impl(LinkedList* self, int index, int value);
bool swap_elements_impl(LinkedList* self, int index1, int index2);
bool clear_impl(LinkedList* self);
bool contains_impl(LinkedList* self, int value);
bool is_empty_impl(LinkedList* self);
bool replace_all_impl(LinkedList* self, int (*replace_function)(int a));
void print_values(struct LinkedList* self);


LinkedList* generate_random_LinkedList(int size);

#endif // LINKEDLIST_H
