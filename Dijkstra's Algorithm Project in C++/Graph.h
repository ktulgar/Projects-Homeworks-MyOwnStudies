#ifndef DIJKSTRA_S_ALGORITHM_PROJECT_GRAPH_H
#define DIJKSTRA_S_ALGORITHM_PROJECT_GRAPH_H

#include "Edge.h"
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <fstream>
#include <list>
#include <limits>
#include <utility>
#include <iterator>
#include <iostream>

using namespace std;

class Graph {

public:
    Graph(const string&);
    void addEdge(int,int,double);
    void deleteEdge(const string&,const string&);
    void edgeDown(const string&,const string&);
    void edgeUp(const string&,const string&);
    void print();
    void dfs(const string&);
    void bfs(const string&,const string&);
    void dijkstra(string,string);
    void vertexDown(const string&);
    void vertexUp(const string&);
    void reachable(const string&);


private:

   int NumberOfVertices;
   vector<Edge>  *adjList;
   void recursiveDfs(int,bool []);
   map<string,int> ids;
   map<int,string> names;
   map<string,vector<string>> edges;
   int findId(const string&);
   string findName(int);

};


#endif
