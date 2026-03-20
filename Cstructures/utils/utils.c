#include "utils.h"

int find_min(Node* bin) {
    
    return minValue;
}

bool check_and_normalize(int index, int max_size, int* new_index) {
	if (abs(index) >= max_size) {
		printf("Index given greater than the size of the LinkedList!\n");
		return false;
	}

	if (index < 0) {
		*new_index = max_size + index;
	}

	return true;
}

