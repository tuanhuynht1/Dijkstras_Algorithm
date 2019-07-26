#include "Menu.hpp"
using namespace std;

char Menu::options(){
    system("CLS");
    cout << "Dijkstra Algorithm" <<
    endl << "\nGenerate random sample graph - s" << 
    endl << "Add vertices - v" <<
    endl << "Remove vertices - r" <<
    endl << "Add an edge - e" <<
    endl << "Remove an edge - x" <<
    endl << "Print graph - p" <<
    endl << "Find shortest path - a" <<
    endl << "Quit program - q\n" <<
    endl << "Command: ";

    char c;
    cin >> c;
    cin.ignore(256,'\n');
    return c;
}

void Menu::parseCommand(char c){
    switch (c){
        case 's': generateRandomGraph(); break;
        case 'v': addVertices(); break;
        case 'r': removeVertices(); break;
        case 'e': addEdge(); break;
        case 'x': removeEdge(); break;
        case 'p': printGraph(); break;
        case 'a': shortestPath(); break;
        default: 
            cout << "Invalid command! Press ENTER and try again: ";
            cin.get();
    }
}

void Menu::addVertices(){
    string buffer, line;
    cout << "Enter vertices separated by spaces: ";
    getline(cin, line);
    istringstream ss(line);
    while(ss >> buffer){
        G.addVertex(buffer);
    }
    printGraph();
}

void Menu::removeVertices(){
    string buffer, line;
    cout << "Enter vertices separated by spaces: ";
    getline(cin, line);
    istringstream ss(line);
    while(ss >> buffer){
        G.removeVertex(buffer);
    }
    printGraph();
}

void Menu::addEdge(){
    string a,b;
    unsigned long w;
    cout << "Endpoint A: ";
    cin >> a;
    cout << "Endpoint B: ";
    cin >> b;
    cout << "Path Distance: ";
    cin >> w;
    G.addEdge(a,b,w);
    cin.ignore(256,'\n');
    printGraph();
}

void Menu::removeEdge(){
    string a,b;
    cout << "Endpoint A: ";
    cin >> a;
    cout << "Endpoint B: ";
    cin >> b;
    G.removeEdge(a,b);
    cin.ignore(256,'\n');
    printGraph();
}

void Menu::shortestPath(){
    vector<string> path;
    unsigned long distance;
    string start, end;
    cout << "Starting point: ";
    cin >> start;
    cout << "Endpoint: ";
    cin >> end;
    distance = G.shortestPath(start,end,path);
    cout <<"\nShortest distance: " << distance << endl;
    cout << "Path: ";
    for(int i = 0; i < path.size(); i++){
        if (i==0){
            cout << path[i];
        }
        else{
            cout << "-->" << path[i];
        }
    }
    cin.ignore(256,'\n');
    cout << "\n\npress Enter to continue: ";
    cin.get();
}

void Menu::printGraph(){
    char buffer;
    system("CLS");
    if (G.vertices.empty()){
        cout << "Graph is empty!" << endl;
    }
    else{
        cout << "Vertex  Edges(label A -(path distance)-> labelB)\n" << endl;
        for (auto v: G.vertices){
            cout << v->label + ": ";
            for (auto n: v->neighbors){
                cout << setw(7) << v->label + "-(" << G.getEdgeWeight(v->label, n->label) <<")->" + n->label +",";
            }
            cout << endl; 
        }
    }
    cout << "\npress Enter to continue: ";
    cin.get();
}


void Menu::generateRandomGraph(){
    G.vertices.clear(); G.edges.clear();
    struct EdgeStruct { string a; string b; unsigned long w; };

    vector<string> vertices1 { "1", "2", "3", "4", "5", "6" };
    vector<EdgeStruct> edges1 {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11},
        {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9}
    };

    vector<string> vertices2 { "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"};
    vector<EdgeStruct> edges2 {
        {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355}, {"SUN", "SUB", 1265},
        {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885},
        {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}
    };

    vector<string> vertices3 { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
    vector<EdgeStruct> edges3 {
        {"0", "1", 1}, {"0", "4", 1}, {"1", "2", 2}, {"1", "5", 2}, {"2", "6", 1}, {"2", "3", 1}, 
        {"3", "7", 2}, {"4", "8", 2}, {"5", "6", 1}, {"5", "10", 4}, {"6", "11", 2}, {"7", "12", 1}, 
        {"8", "9", 3}, {"9", "10", 1}, {"10", "11", 2}, {"11", "12", 5}
    };

    int seed = time(nullptr);
    srand(seed);
    int r = rand() % 3;

    vector<vector<string>> vertices {vertices1,vertices2,vertices3};
    vector<vector<EdgeStruct>> edges {edges1, edges2, edges3};

    for(const auto label: vertices[r]){
        G.addVertex(label);
    }
    for (const auto &e : edges[r]){
        G.addEdge(e.a, e.b, e.w);
    }
    printGraph();
}