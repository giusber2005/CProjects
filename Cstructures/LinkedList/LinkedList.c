#include "LinkedList.h"

bool add_last_impl(LinkedList* self, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error during the allocation of the new node to add\n");
        return false;
    }

    newNode->value = value;
    newNode->next = NULL;

    Node* pointer = self->head;
    if (pointer == NULL) {
        pointer = newNode;
    } else {
        while (pointer->next != NULL) {
            pointer = pointer->next;
        }
        pointer->next = newNode;
    }

    self->size++;
    return true;
}

bool add_first_impl(LinkedList* self, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error during the allocation of the new node to add\n");
        return false;
    }

    newNode->value = value;
    newNode->next = NULL;

    Node* pointer = self->head;
    if (pointer == NULL) {
        pointer = newNode;
    } else {
        self->head = newNode;
        self->head->next = pointer;
    }

    self->size++;
    return true;
}

int get_firstElement_impl(LinkedList* self) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return NULL;
    }

    return self->head->value;
}

int get_lastElement_impl(LinkedList* self) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return NULL;
    }

    Node* pointer = self->head;
    while (pointer->next != NULL) {
        pointer = pointer->next;
    }

    return pointer->value;
}

bool get_element_impl(LinkedList* self, int index, int* value) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return false;
    }

    if (abs(index) >= self->size) {
        printf("Absolute value of the index of the element greater than the size of the linked list");
        return false;
    }

    if (index < 0) {
        index = self->size + index;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (counter < index) {
        pointer = pointer->next;
        counter++;
    }

    *value = pointer->value;
    return true;
}

bool index_of_impl(LinkedList* self, int value, int* index) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return false;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (pointer->next != NULL) {
        if (pointer->value == value) {
            *index = counter;
            return true;
        }
        pointer = pointer->next;
        counter++;
    }

    return false;
}

bool last_index_of_impl(LinkedList* self, int value, int* index) {
    bool found = false;
    Node* pointer = self->head;
    int counter = 0;
    while (pointer->next != NULL) {
        if (pointer->value == value) {
            *index = counter;
            found = true;
        }
        pointer = pointer->next;
        counter++;
    }
    
    if (!found) {
        return false;
    } else {
        return true;
    }
}

//TODO
void sort_impl(LinkedList* self, bool order) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return;
    }

    Node* pointer = self->head;
    while (pointer->next != NULL) {
        int value;
        if (order) {
            value = find_min(pointer);
        } else {
            value = find_max(pointer);
        }

        pointer->value = value;
        pointer = pointer->next;
    }
}

// Option 1: Return dynamically allocated array, size via parameter
int* get_frequencies_impl(LinkedList* self, int* result_size) {
    if (!self || self->size == 0) {
        *result_size = 0;
        return NULL;
    }

    // Allocate for worst case: all unique elements
    int (*frequencies)[2] = malloc(sizeof(int[2]) * self->size);
    if (!frequencies) {
        printf("Memory allocation failed\n");
        *result_size = 0;
        return NULL;
    }

    Node* pointer = self->head;
    int unique_count = 0;
    
    while (pointer != NULL) {  // FIXED: was pointer->next != NULL
        bool found = false;
        
        // Check if value already exists in frequencies
        for (int i = 0; i < unique_count; i++) {
            if (frequencies[i][0] == pointer->value) {
                frequencies[i][1]++;
                found = true;
                break;  // FIXED: removed counter--
            }
        }

        // If not found, add new entry
        if (!found) {
            frequencies[unique_count][0] = pointer->value;
            frequencies[unique_count][1] = 1;  // FIXED: should start at 1, not increment
            unique_count++;
        }
        
        pointer = pointer->next;  // FIXED: was missing!
    }

    // Flatten 2D array to 1D for return
    int* result = malloc(sizeof(int) * unique_count * 2);
    if (!result) {
        free(frequencies);
        *result_size = 0;
        return NULL;
    }
    
    for (int i = 0; i < unique_count; i++) {
        result[i * 2] = frequencies[i][0];      // value
        result[i * 2 + 1] = frequencies[i][1];  // frequency
    }
    
    free(frequencies);
    *result_size = unique_count;
    return result;
}

int* to_list_impl(LinkedList* self) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return NULL;
    }

    int* list = (int*)malloc(sizeof(int) * self->size);
    if (list == NULL) {
        printf("Error during the allocation of memory for the list\n");
        return NULL;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (pointer->next != NULL) {
        list[counter] = pointer->value;
        pointer = pointer->next;
        counter++;
    }

    return list;
}

int* to_list_unique_impl(LinkedList* self, int* unique_size) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        *unique_size = 0;
        return NULL;
    }

    int frequencies_size;
    int* frequencies = self->get_frequencies(self, &frequencies_size);
    
    if (!frequencies) {
        *unique_size = 0;
        return NULL;
    }

    // First pass: count unique elements (frequency == 1)
    int unique_count = 0;
    for (int i = 0; i < frequencies_size; i++) {
        if (frequencies[i * 2 + 1] == 1) {  // FIXED: check frequency, not value
            unique_count++;
        }
    }

    // Allocate exact size needed (do it once, not in a loop)
    int* list_unique = (int*)malloc(sizeof(int) * unique_count);
    if (!list_unique) {
        printf("Error during the allocation of memory for the unique list\n");
        free(frequencies);
        *unique_size = 0;
        return NULL;
    }

    // Second pass: copy unique values
    int index = 0;
    for (int i = 0; i < frequencies_size; i++) {
        if (frequencies[i * 2 + 1] == 1) {  // frequency == 1
            list_unique[index] = frequencies[i * 2];  // copy the value
            index++;
        }
    }

    free(frequencies);  // FIXED: don't forget to free
    *unique_size = unique_count;
    return list_unique;
}

int max_impl(LinkedList* self) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return NULL;
    }

    int max = self->head->value;
    Node* pointer = self->head;
    while (pointer->next != NULL) {
        if (pointer->value > max) {
            max = pointer->value;
        }

        pointer = pointer->next;
    }

    return max;
}

int min_impl(LinkedList* self) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return NULL;
    }

    int min = self->head->value;
    Node* pointer = self->head;
    while (pointer->next != NULL) {
        if (pointer->value < min) {
            min = pointer->value;
        }

        pointer = pointer->next;
    }

    return min;
}

bool add_all_impl(LinkedList* self, int elements[], int count, int index) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (pointer->next != NULL) {
        pointer = pointer->next;
    }

    Node* start = (Node*)malloc(sizeof(Node));
    if (start == NULL) {
        printf("Error during the allocation of memory for the list of blocks, at the beginning\n");
        return false;
    }
    start->next = NULL;
    start->value = elements[0];

    Node*pointer2 = start;
    for (int i = 1; i < count; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (start == NULL) {
            printf("Error during the allocation of memory for the list of blocks\n");
            return false;
        }
        newNode->next = NULL;
        newNode->value = elements[i];

        pointer2->next = newNode;
    }

    Node* tmp = pointer->next;
    pointer->next = start;
    pointer2->next = tmp;

    self->size += count;
    return true;
}

bool retain_all_impl(LinkedList* self, int elements[], int count) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (pointer->next == NULL) {
        for (int i = 0; i < count; i++) {
            if (elements[i] == pointer->value) {
                if (!self->remove_index(self, counter)) {
                    printf("Error during removing index %i of the linked list", counter);
                }
            }
        }
        pointer = pointer->next;
        counter++;
    }

    self->size -= count;
    return true;
}

bool add_index_impl(LinkedList* self, int index, int value) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (pointer->next != NULL && counter < index) {
        pointer = pointer->next;
        counter++;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error during the allocation of a new node\n");
        return false;
    }

    newNode->value = value;
    newNode->next = NULL;

    Node* tmp = pointer->next;
    pointer->next = newNode;
    newNode->next = tmp;

    self->size++;
    return true;
}

bool remove_index_impl(LinkedList* self, int index) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (pointer->next != NULL && counter < index) {
        pointer = pointer->next;
    }

    Node* tmp = pointer->next->next;
    free(pointer->next);
    pointer->next = tmp;

    self->size--;
    return true;
}

bool set_index_impl(LinkedList* self, int index, int value) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (counter < index) {
        counter += 1;
        pointer = pointer->next;
    }

    pointer->value = value;
    return true;
}

bool swap_elements_impl(LinkedList* self, int index1, int index2) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (counter < index1) {
        counter += 1;
        pointer = pointer->next;
    }
    int value = pointer->value;

    while (counter < index2) {
        counter += 1;
        pointer = pointer->next;
    }
    int value2 = pointer->value;
    pointer->value = value;

    if (!self->set_index(self, index1, value2)) {
        return false;
    }
    return true;
}

bool clear_impl(LinkedList* self) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    while (pointer->next != NULL) {
        pointer->value = 0;
        pointer = pointer->next;
    }

    return true;
}

bool contains_impl(LinkedList* self, int value) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    while (pointer->next != NULL) {
        if (pointer->value == value) {
            return true;
        }

        pointer = pointer->next;
    }

    return false;
}

bool is_empty_impl(LinkedList* self) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    return (self->size = 0) ? true : false;
}

bool replace_all_impl(LinkedList* self, int (*replace_function)(int a)) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    Node* pointer = self->head;
    while (pointer->next != NULL) {
        pointer->value = replace_function(pointer->value);
        pointer = pointer->next;
    }

    return false;
}

LinkedList* create_LinkedList(int starters[], int size_of_starters) {
    LinkedList* newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
    if (newLinkedList == NULL) {
        printf("Error during the allocation of the new LinkedList\n");
        return NULL;
    }
    newLinkedList->head = NULL;
    newLinkedList-> size = 0;

    Node* pointer = newLinkedList->head;
    for (int i = 0; i < size_of_starters; i++) {
        pointer = (Node*)malloc(sizeof(Node));
        if (pointer == NULL) {
            printf("Error during the allocation of the starters\n");
            return NULL;
        }
        pointer->value = starters[i];
        pointer = pointer->next;
    }
    pointer->next = NULL;

    newLinkedList->add_first = add_first_impl;
    newLinkedList->add_last = add_last_impl;
    newLinkedList->add_index = add_index_impl;
    newLinkedList->remove_index = remove_index_impl;
    newLinkedList->set_index = set_index_impl;
    newLinkedList->get_firstElement = get_firstElement_impl;
    newLinkedList->get_element = get_element_impl;
    newLinkedList->index_of = index_of_impl;
    newLinkedList->last_index_of = last_index_of_impl;
    newLinkedList->sort = sort_impl;
    newLinkedList->get_frequencies = get_frequencies_impl;
    newLinkedList->to_list = to_list_impl;
    newLinkedList->to_list_unique = to_list_unique_impl;
    newLinkedList->max = max_impl;
    newLinkedList->min = min_impl;
    newLinkedList->add_all = add_all_impl;
    newLinkedList->retain_all = retain_all_impl;
    newLinkedList->swap_elements = swap_elements_impl;
    newLinkedList->clear = clear_impl;
    newLinkedList->contains = contains_impl;
    newLinkedList->is_empty = is_empty_impl;
    newLinkedList->replace_all = replace_all_impl;
    newLinkedList->free_list = free_LinkedList_impl;
    
    return newLinkedList;
}

void free_LinkedList_impl(LinkedList *self) {
    Node* pointer = self->head;
    while (pointer != NULL) {
        Node* tmp = pointer->next;
        free(pointer);
        pointer = pointer->next;
    }

    free(self);
}

void print_values(struct LinkedList* self) {
    if (!self) {
        printf("LinkedList doesn't exists\n");
        return;
    }

    printf("Values of the Linked List: \n");
    Node* pointer = self->head;
    while (pointer->next != NULL) {
        printf("%i ", pointer->value);
        pointer = pointer->next;
    }
    printf("\n");

}

LinkedList* generate_random_LinkedList(int size) {
    if (size <= 0) {
        printf("Invalid size!\n");
        return NULL;
    }

    int starters[size];
    for (int i = 0; i < size; i++) {
        starters[i] = rand() % POOL;
    }

    LinkedList* result = create_LinkedList(starters, size);
    if (result == NULL) {
       printf("Error during the allocation of memory for the LinkedList");
       return NULL;
    }

    return result;
}

