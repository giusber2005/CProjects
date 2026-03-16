#include "../utils/utils.h"

typedef struct NodesNetwork NodesNetwork;

//NodesNetwork with only int values;
struct NodesNetwork {
    int value;
    Node* NetworkHead;

    int (*max)(NodesNetwork* self);
    int (*min)(NodesNetwork* self);
    int (*max_connections)(NodesNetwork* self);
    int (*get_loops)(NodesNetwork* self);
    int (*get_blind_spots)(NodesNetwork* self);
    int* (*get_connections)(NodesNetwork* self, int* connections_size);
    int* (*clear_network)(NodesNetwork* self);
    
};

typedef struct Node Node;

struct Node {
    int size;
    Node** connections;
};

//Extend the class to create NodesNetworks living in 2d, 3d, nd planes
    //Random Network genetors algorithms
    //Building path calculators
//Functions like distance between two nodes, 2d arrays calculating density, variability of the Network
//Calculating things like momentum, and the center of mass
//Try to see the structures graphically