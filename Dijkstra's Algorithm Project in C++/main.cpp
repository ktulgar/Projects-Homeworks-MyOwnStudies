#include "Graph.h"

using namespace std;

int main() {


    Graph graph("network.txt");
    graph.edgeDown("Belk","Duke");
    graph.reachable("Woodward");
    cout << endl;
    graph.dijkstra("Belk","Education");
    graph.vertexDown("Grigg");
    cout << endl;
    graph.reachable("Belk");
    cout << endl;
    graph.print();


}