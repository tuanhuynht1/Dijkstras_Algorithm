#ifndef EDGE_H
#define EDGE_H
#include <string>

//includes label for each endpoint and weight of edge
struct Edge{
    std::string u;
    std::string v;
    unsigned long weight;
    Edge(std::string u, std::string v, unsigned long weight){this->u = u; this->v = v; this->weight = weight;}
};

#endif