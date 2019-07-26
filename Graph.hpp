#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "HeapQue.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <limits.h>
#include <vector>
#include <stack>
#include <tuple>
#include <map>

//tuple used to associate certain values to a vertex, useful for Dijkstra Algorithm
struct DijkstraTuple{
    std::string label;
    std::string prev;
    unsigned long min;
    Vertex* vertex;
    //comparator class for the HeapQueue
    class Compare{
        public:
            Compare(bool lessThan = true) : lessThan(lessThan) {};
            bool operator()(const DijkstraTuple &n1, const DijkstraTuple &n2) const;
            bool operator()(const DijkstraTuple *n1, const DijkstraTuple *n2) const;
        private:
            bool lessThan;
    };
};


//Graph class 
class Graph: public GraphBase{

    public:
        void addVertex(std::string label) override;
        void removeVertex(std::string label) override;
        void addEdge(std::string label1, std::string label2, unsigned long weight) override;
        void removeEdge(std::string label1, std::string label2) override;
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) override;
    private:
        //list of edges and vertices
        std::vector<Vertex*> vertices;
        std::vector<Edge*> edges; 
        //utility functions
        void setTuples(std::string start, std::vector<DijkstraTuple*>& tuplelist);
        unsigned long getEdgeWeight(std::string u, std::string v);
        std::vector<std::string> retracePath(std::stack<DijkstraTuple*>& stack);
    friend class Menu;
};


#endif