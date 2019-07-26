#include "Graph.hpp"
#include <iostream>
using namespace std;

///***** GENERAL GRAPH FUNCTIONS *******************************///


//add vertex to list of vertices
void Graph::addVertex(string label){
    //checks if the label already exists
    for(auto v: vertices){
        if (v->label == label){
            cout << "Vertex already exist!" << endl;
            return;
        }
    }
    //adds vertex to the graph
    vertices.push_back(new Vertex(label));
}


//remove vertex from list of vertices
void Graph::removeVertex(string label){
    Vertex* v;

    for (auto i = vertices.begin(); i != vertices.end(); i++){
        v = *i; //saves a reference to the vertex before removing it from list of vertices
        if(v->label == label){
            vertices.erase(i);
            break;
        }
    }
    //remove v from each of its neighbors list of neighbors
    for(auto i = v->neighbors.begin(); i != v->neighbors.end(); i++){
        Vertex* adj = *i;
        for(auto j = adj->neighbors.begin(); j != adj->neighbors.end(); j++){
            if(*j == v){
                adj->neighbors.erase(j);
                break;
            }
        }
    }
    //remove all edges that include vertex v
    for (auto i = edges.begin(); i != edges.end(); i++){
        Edge* e = *i;
        if(e->u == label || e->v == label){
            edges.erase(i);
            i = edges.begin()-1;
            delete e;
        }
    }
    //delete v from memory
    delete v;
}


//adds edge to the list of edges
void Graph::addEdge(string label1, string label2, unsigned long weight){
    //checks if the edge already exists
    for (auto e: edges){
        if( (e->u == label1 && e->v == label2) || (e->u == label2 && e->v == label1)){
            cout << "Edge already exist!" << endl;
            return;
        }
    }
    Vertex* u = nullptr;
    Vertex* v = nullptr;
    
    for (auto i: vertices){
        if(i->label == label1){
            u = i;  //find vertex associated with label 1
        }
        else if(i->label == label2){
            v = i; //find vertex associated with label 2
        }
    }
    //check if vertex not found
    if(u == nullptr || v == nullptr){
        cout << "Vertex not found!" << endl; 
        return;
    }

    u->neighbors.push_back(v);  //add v to neighbor of v
    v->neighbors.push_back(u);  //add u to neighbor of v

    edges.push_back(new Edge(label1,label2,weight));    //add edge going from u to v
    edges.push_back(new Edge(label2,label1,weight));    //add edge going from v to u
}


//remove an edge and its inverse from list of edges
void Graph::removeEdge(string label1, string label2){
    for(auto i = edges.begin(); i != edges.end(); i++){
        Edge* e = *i;
        //finds the edge or its inverse direction
        if((e->u == label1 && e->v == label2) ||(e->u == label2 && e->v == label1)){
            edges.erase(i); //erase from list
            i = edges.begin()-1; //reiterate to find its compliment
            delete e; //delete edge
        }
    }
    //find vertex of start label and remove the end vertex from its list of neighbors
    for(auto i = vertices.begin(); i != vertices.end(); i++){
        Vertex* vertex = *i;

        if(vertex->label == label1){
            for(auto j = vertex->neighbors.begin(); j != vertex->neighbors.end(); j++){
                Vertex* u = *j;
                if (u->label == label2){
                    vertex->neighbors.erase(j);
                    break;
                }
            }
        }
        //find vertex of end label and remove the start vertex from its list of neighbors
        if (vertex->label == label2){
            for (auto j = vertex->neighbors.begin(); j != vertex->neighbors.end(); j++){
                Vertex* v = *j;
                if(v->label == label1){
                    vertex->neighbors.erase(j);
                    break;
                }
            }
        }
    }
}









///***** DIJKSTRA ALGORITHM  ***************************************************///


//find shortest path and construct path using the a vector of strings
unsigned long Graph::shortestPath(string startLabel, string endLabel, vector<string> &path){
    
    //PQ to sort by min value
    HeapQueue<DijkstraTuple*, DijkstraTuple::Compare> PQ;
    //vector of tuples representing all the unvisited vertices
    vector<DijkstraTuple*> unvisited;
    //stack to hold all the visited vertices
    std::stack<DijkstraTuple*> stack;

    //associate vertices with a tuple, set all vertices to unvisited, all values except the the start to infinity
    setTuples(startLabel,unvisited);
    path.clear();   //clear path to repopulate it after algorithm
    
    while(true){

        //at the start of every loop, sort vertices by min value
        for(auto i : unvisited){
            PQ.insert(i);
        }

        //if the end vertice is the min value, path is complete, break from loop
        if(PQ.min()->label == endLabel){
            stack.push(PQ.min());
            PQ.clear();
            break;
        }

        //use the vertex with min value as current vertex
        DijkstraTuple* current = PQ.min();
        Vertex* vx = current->vertex;

        //check all its unvisited neighbors
        for(auto neighbor : vx->neighbors){
            for (auto tuple : unvisited){
                if (neighbor->label == tuple->label){
                    //add current vertex's value with distance of edge between its neighbor
                    unsigned long distance = current->min + getEdgeWeight(vx->label, neighbor->label);
                    // if distance is less, update that neighbors min val and change its path of shortest distance to current vertex
                    if (distance < tuple->min){
                        tuple->min = distance;
                        tuple->prev = current->label;
                        break;
                    }
                }
            }
        }

        //push current vertex to stack of visited vertices
        for (auto i = unvisited.begin(); i != unvisited.end(); i++){
            if((*i)->label == current->label){
                stack.push(*i);
                unvisited.erase(i);
                break;
            }
        }
        PQ.clear();
    }

    unsigned long shortestDistance = stack.top()->min; //return the min distance it would take to reach end vertex
    path = retracePath(stack); //flip the stack to find path starting from the begining vertex
    return shortestDistance;
}








///***** UTILITY FUNCTIONS FOR DIJKSTRA ALGORITHM *******************************///

//associate every vertex with a tuple
void Graph::setTuples(string start, vector<DijkstraTuple*>& tuplelist){
    for(auto v : vertices){
        if(v->label == start){
            tuplelist.push_back(new DijkstraTuple{v->label,"",0,v});    //start vertice has a min value of 0
        }
        else{
            tuplelist.push_back(new DijkstraTuple{v->label,"",ULONG_MAX,v});    //initiate all other values as infinty or unsigned long max limit
        }
    }
}


//find weight of edge between two adjacent vertices
unsigned long Graph::getEdgeWeight(string u, string v){
    for(auto edge : edges){
        if((edge->u == u && edge->v == v) || (edge->u == v && edge->v == u)){
            return edge->weight;
        }
    }
    return 0;
}

//return path by unstacking the stack of visited vertices, also delete tuples from stack to prevent mem leaks
vector<string> Graph::retracePath(std::stack<DijkstraTuple*>& stack){
    vector<string> path;
    std::stack<string> S;
    string next = stack.top()->label;
    while(!stack.empty()){
        DijkstraTuple* top = stack.top();
        if(top->label == next){
            S.push(top->label);
            next = top->prev;
        }
        DijkstraTuple* p = stack.top();
        stack.pop();
        delete p;
    }
    while(!S.empty()){
        path.push_back(S.top());
        S.pop();
    }
    return path;
}






///***** COMPARE METHODS FOR PRIORITY QUEUE *******************************///



bool DijkstraTuple::Compare::operator()(const DijkstraTuple &n1, const DijkstraTuple &n2) const
{
  if (n1.min == n2.min) {
    return lessThan ? n1.label < n2.label : n1.label >= n2.label;
  } else {
    return lessThan ? n1.min < n2.min : n1.min >= n2.min;
  }
  
}



bool DijkstraTuple::Compare::operator()(const DijkstraTuple *n1, const DijkstraTuple *n2) const
{
  return operator()(*n1, *n2);
}


