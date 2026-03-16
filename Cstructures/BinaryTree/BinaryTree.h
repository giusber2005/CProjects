#include "../utils/utils.h"

typedef struct BinaryTree BinaryTree;

//BinaryTree object with only int values
struct BinaryTree {
    int val;
    BinaryTree* left;
    BinaryTree* right;

    int (*get_levels_size)(BinaryTree* self);
    int (*get_size)(BinaryTree* self);
    int (*get_sum)(BinaryTree* self);
    int (*max)(BinaryTree* self);
    int (*min)(BinaryTree* self);
    
};