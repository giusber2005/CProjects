#include "test.h"

void test_creation_empty() {
    printf("\n=== Test 1: Creating empty list ===\n");
    LinkedList* list = create_LinkedList(NULL, 0);
    
    if (list == NULL) {
        printf("FAIL: List creation returned NULL\n");
        return;
    }
    
    printf("List created successfully\n");
    printf("Size: %d (expected: 0)\n", list->size);
    printf("Head: %s (expected: NULL)\n", list->head == NULL ? "NULL" : "NOT NULL");
    printf("is_empty: %s (expected: true)\n", list->is_empty(list) ? "true" : "false");
    
    list->free_list(list);
    printf("PASS\n");
}

void test_creation_with_elements() {
    printf("\n=== Test 2: Creating list with initial elements ===\n");
    int starters[] = {10, 20, 30, 40, 50};
    int size = 5;
    
    LinkedList* list = create_LinkedList(starters, size);
    
    if (list == NULL) {
        printf("FAIL: List creation returned NULL\n");
        return;
    }
    
    printf("List created successfully\n");
    printf("Size: %d (expected: %d)\n", list->size, size);
    print_list(list);
    
    // Verify values
    Node* current = list->head;
    bool correct = true;
    for (int i = 0; i < size; i++) {
        if (current == NULL) {
            printf("FAIL: List shorter than expected\n");
            correct = false;
            break;
        }
        if (current->value != starters[i]) {
            printf("FAIL: Element %d is %d, expected %d\n", i, current->value, starters[i]);
            correct = false;
        }
        current = current->next;
    }
    
    if (current != NULL) {
        printf("FAIL: List longer than expected\n");
        correct = false;
    }
    
    if (correct) {
        printf("PASS: All elements match\n");
    }
    
    list->free_list(list);
}

void test_function_pointers() {
    printf("\n=== Test 3: Function pointers assigned ===\n");
    int starters[] = {1, 2, 3};
    LinkedList* list = create_LinkedList(starters, 3);
    
    if (list == NULL) {
        printf("FAIL: List creation returned NULL\n");
        return;
    }
    
    bool all_assigned = true;
    
    if (list->add_first == NULL) { printf("FAIL: add_first not assigned\n"); all_assigned = false; }
    if (list->add_last == NULL) { printf("FAIL: add_last not assigned\n"); all_assigned = false; }
    if (list->get_size == NULL) { printf("FAIL: get_size not assigned\n"); all_assigned = false; }
    if (list->is_empty == NULL) { printf("FAIL: is_empty not assigned\n"); all_assigned = false; }
    if (list->free_list == NULL) { printf("FAIL: free_list not assigned\n"); all_assigned = false; }
    
    if (all_assigned) {
        printf("PASS: All function pointers assigned\n");
        
        // Test calling some functions
        printf("\nTesting function calls:\n");
        int size = list->get_size(list);
        printf("get_size returned: %d\n", size);
        
        list->add_first(list, 99);
        list->add_last(list, 88);
    }
    
    list->free_list(list);
}

void test_single_element() {
    printf("\n=== Test 4: Creating list with single element ===\n");
    int starters[] = {42};
    LinkedList* list = create_LinkedList(starters, 1);
    
    if (list == NULL) {
        printf("FAIL: List creation returned NULL\n");
        return;
    }
    
    printf("Size: %d (expected: 1)\n", list->size);
    print_list(list);
    
    if (list->head != NULL && list->head->value == 42 && list->head->next == NULL) {
        printf("PASS\n");
    } else {
        printf("FAIL: Single element not correctly set\n");
    }
    
    list->free_list(list);
}