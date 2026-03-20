#include "LinkedList.h"

bool add_last_impl(LinkedList* self, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error during the allocation of the new node to add\n");
        return false;
    }

    newNode->value = value;
    newNode->next = NULL;

    if (self->tail == NULL) {
	    self->tail = newNode;
	    self->head = newNode;
    } else {
	    self->tail->next = newNode;
	    self->tail = newNode;
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
    newNode->next = self->head;
    self->head = newNode;

    self->size++;
    return true;
}

bool get_firstElement_impl(LinkedList* self, int* value) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return false;
    }

    *value = self->head->value;
    return false;
}

bool get_lastElement_impl(LinkedList* self, int* value) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return false;
    }

    *value = self->tail->value;
    return true;
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
    if (!self) {
        printf("Linked list doesn't exist\n");
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
    if (!self) {
	    printf("Linked List doesn't exist!\n");
	    return false;
    }

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

    return found;
}

bool indexes_of_impl(LinkedList* self, int value, int** indexes) {
	if (!self) {
		printf("Linked List doesn't exist!\n");
		return false;
	}

	bool found = false;
	int* indexesPointer = NULL;
	Node* listPointer = self->head;
	int counter = 0;
	int size = 0;
	while (listPointer != NULL) {
		if (listPointer->value == value) {
			size++;
			int* tmp = realloc(indexesPointer, sizeof(int)*size);
			if (tmp == NULL) {
				printf("Error during allocation for the indexesPointer in indexesOf\n");
				free(indexesPointer);
				return false;
			}

			indexesPointer = tmp;
			indexesPointer[size - 1] = counter;
			found = true;
		}

		counter++;
		listPointer = listPointer->next;
	}

	*indexes = indexesPointer;
	return found;
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
    while (pointer != NULL) {
        list[counter] = pointer->value;
        pointer = pointer->next;
        counter++;
    }

    return list;
}

int* to_list_singleton_impl(LinkedList* self, int* singleton_size) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        *singleton_size = 0;
        return NULL;
    }
    int frequencies_size;
    int* frequencies = self->get_frequencies(self, &frequencies_size);
    if (!frequencies) {
        *singleton_size = 0;
        return NULL;
    }

    // First pass: count singletons
    int count = 0;
    for (int i = 0; i < frequencies_size; i++) {
        if (frequencies[i * 2 + 1] == 1) {
            count++;
        }
    }

    if (count == 0) {
        free(frequencies);
        *singleton_size = 0;
        return NULL;
    }

    int* list_singleton = (int*)malloc(sizeof(int) * count);
    if (!list_singleton) {
        printf("Error during the allocation of memory for the singleton list\n");
        free(frequencies);
        *singleton_size = 0;
        return NULL;
    }

    // Second pass: copy singleton values
    int index = 0;
    for (int i = 0; i < frequencies_size; i++) {
        if (frequencies[i * 2 + 1] == 1) {
            list_singleton[index] = frequencies[i * 2];
            index++;
        }
    }

    free(frequencies);
    *singleton_size = count;
    return list_singleton;
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

   int* list_unique = (int*)malloc(sizeof(int) * frequencies_size);
   if (!list_unique) {
   	printf("Error during the allocation of memory for the unique list\n");
   	free(frequencies);
   	*unique_size = 0;
   	return NULL;
   }

   for (int i = 0; i < frequencies_size; i++) {
	   list_unique[i] = frequencies[i * 2];
   }
	
   free(frequencies);
   *unique_size = frequencies_size;
   return list_unique;
}

bool max_impl(LinkedList* self, int* maxn) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return false;
    }

    int max = self->head->value;
    Node* pointer = self->head;
    while (pointer != NULL) {
        if (pointer->value > max) {
            max = pointer->value;
        }

        pointer = pointer->next;
    }

    *maxn = max;
    return true;
}

bool min_impl(LinkedList* self, int* minn) {
    if (!self || self->size == 0) {
        printf("Linked list doesn't exist or it has a size equal to 0\n");
        return false;
    }

    int min = self->head->value;
    Node* pointer = self->head;
    while (pointer != NULL) {
        if (pointer->value < min) {
            min = pointer->value;
        }

        pointer = pointer->next;
    }

    *minn = min;
    return true;
}

bool add_all_impl(LinkedList* self, int elements[], int count, int index) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    if (abs(index) >= self->size) {
	    printf("Index selected is greater than the total size of the Linked List!\n!");
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

    for (int i = 0; i < count; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (start == NULL) {
            printf("Error during the allocation of memory for the list of blocks\n");
	    self->size += i;
            return false;
        }
        newNode->next = pointer->next;
        newNode->value = elements[i];
        pointer->next = newNode;

	if (newNode->next == NULL) {
		self->tail = newNode;
	}

	pointer = pointer->next;
    }

    self->size += count;
    return true;
}

bool retain_all_impl(LinkedList* self, int elements[], int count) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    int counter = 0;
    Node* pointer = self->head;
    while (pointer != NULL) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (elements[i] == pointer->value) {
                found = true;
                break;
            }
        }
        Node* next = pointer->next;  // save before potential removal
        if (!found) {
            if (!self->remove_index(self, counter)) {
                printf("Error during removing index %i of the linked list\n", counter);
                return false;
            }
            // don't increment counter since indices shifted down
        } else {
            counter++;
        }
        pointer = next;
    }
    return true;
}

bool add_index_impl(LinkedList* self, int index, int value) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    if (abs(index) >= self->size) {
	    printf("Index given greater the the size of the Linked List!\n");
	    return false;
    }

    if (index < 0) {
	    index += self->size;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (counter < index - 1) {
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

    if (newNode->next == NULL) {
	    self->tail = NewNode;
    }

    self->size++;
    return true;
}

bool remove_index_impl(LinkedList* self, int index) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    if (abs(index) >= self->size) {
	    printf("Index given greater than the size of the Linked List!\n");
	    return false;
    }

    if (index < 0) {
	    index += self->size;
    }

    Node* toFree;
    if (index == 0) {
     	   toFree = self->head;
        	self->head = self->head->next;
      	   if (self->head == NULL) {
            self->tail = NULL;  // list is now empty
           }
        free(toFree);
    } else {
        Node* pointer = self->head;
        int counter = 0;
        while (counter < index - 1) {
            pointer = pointer->next;
            counter++;
        }
        toFree = pointer->next;
        pointer->next = toFree->next;
        if (pointer->next == NULL) {
            self->tail = pointer;
        }
        free(toFree);
    }

    self->size--;
    return true;
}

bool set_index_impl(LinkedList* self, int index, int value) {
    if (!self) {
        printf("Linked list doesn't exist\n");
        return false;
    }

    if (abs(index) >= self->size) {
	    printf("Index given greater than the total size of the Linked List!\n");
	    return false;
    } 

    if (index < 0) {
	    index += self->size;
    }

    Node* pointer = self->head;
    int counter = 0;
    while (counter < index) {
        counter++;
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

    if (!check_and_normalize(index1, self->size, index1)) {
	    return false;
    }

    if (!check_and_normalize(index2, self->size, index2)) {
	    return false;
    }

    if (index1 == index2) {
	    return true; //nothing to do
    }

    Node* pointer = self->head;
    int counter = 0;
    while (counter < index1) {
        counter += 1;
        pointer = pointer->next;
    }
    int value = pointer->value;

    pointer = self->head;
    counter = 0;
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

