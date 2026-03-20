#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "../LinkedList/LinkedListStruct.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define POOL 100

int find_min(Node* bin);
int check_and_normalize(int index);
