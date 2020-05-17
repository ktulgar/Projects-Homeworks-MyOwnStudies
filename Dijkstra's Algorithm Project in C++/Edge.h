#ifndef DIJKSTRA_S_ALGORITHM_PROJECT_EDGE_H
#define DIJKSTRA_S_ALGORITHM_PROJECT_EDGE_H

#include <string>

using namespace std;

class Edge {


public:
       Edge(int,int,double);
       int getDest();
       int getSource();
       double getWeight();
       void setStatus(string);
       string getStatus();

private:
    int destination;
    int source;
    double weight;
    string status;
};


#endif
