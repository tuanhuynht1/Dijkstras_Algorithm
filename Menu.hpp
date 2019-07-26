#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>
#include "Graph.hpp"

class Menu{
    public:
        char options();
        void parseCommand(char c);
    private:
        Graph G;
        void generateRandomGraph();
        void addVertices();
        void removeVertices();
        void addEdge();
        void removeEdge();
        void printGraph();
        void shortestPath();
};

#endif