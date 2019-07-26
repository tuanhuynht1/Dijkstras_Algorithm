#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <vector>
#include <iostream>

struct Vertex{
    std::string label;
    std::vector<Vertex*> neighbors;
    Vertex(std::string _label) : label(_label) {}

    void printNeighbors(){
        for (auto v: neighbors){
            std::cout << v->label << " ";
        }
    }

};

#endif