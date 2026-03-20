#include "utils/utils.h"
#include "test/test.h"
#include "LinkedList/LinkedList.h"

srand(time(NULL));
int main() {
    printf("===========================================\n");
    printf("   LinkedList Structure Test Suite\n");
    printf("===========================================\n");
    
    test_creation_empty();
    test_creation_with_elements();
    test_function_pointers();
    test_single_element();
    
    printf("\n===========================================\n");
    printf("   All tests completed\n");
    printf("===========================================\n");
    
    return 0;
}
