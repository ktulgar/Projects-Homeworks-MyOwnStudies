#include "Graph.h"

using namespace std;

Graph::Graph(const string& location) {  // The constructor takes a parameter.It is location of txt file that contains edges.

    ifstream fin;
    fin.open(location);
    string line;
    int id = 0;

    map<string,vector<string>>::iterator edgesIter;
    map<string,int>::iterator idsIter;

    while(true) {

        getline(fin,line);
        istringstream iss(line);
        string source,dest,weight;
        stringstream ss;

        iss >> source;
        iss >> dest;
        iss >> weight;

        idsIter = ids.find(source);
        if(idsIter == ids.end()) {
            ids.insert(make_pair(source, id));
            id++;

        }

        idsIter = ids.find(dest);
        if(idsIter == ids.end()) {
            ids.insert(make_pair(dest, id));
            id++;

        }

        edgesIter = edges.find(source);
        if(edgesIter == edges.end()) {
            vector<string> infos;
            infos.push_back(dest);
            infos.push_back(weight);
            edges.insert(make_pair(source,infos));
        }
        else {
            edgesIter->second.push_back(dest);
            edgesIter->second.push_back(weight);
        }

        if(fin.eof())
            break;

    }

    fin.close();

    map<string,int>::iterator iter;
    for(iter = ids.begin() ; iter != ids.end() ; iter++) {
        names.insert(make_pair(iter->second,iter->first));
    }


    this->NumberOfVertices = ids.size()   ;
    this->adjList = new vector<Edge>[NumberOfVertices];

    map<string,vector<string>>::iterator iterEdge;
    vector<string>::iterator iterInfos;
    for(iterEdge = edges.begin() ; iterEdge != edges.end() ; iterEdge++) {

        string source = iterEdge->first;
        int  sourceId = findId(source);
        iterInfos = iterEdge->second.begin();

        while(iterInfos != iterEdge->second.end()) {
            string dest = *iterInfos;
            int destId  = findId(dest);
            advance(iterInfos,1);
            string stringWeight = *iterInfos;
            stringstream ss1(stringWeight);
            double weight;
            ss1 >> weight;
            advance(iterInfos,1);

            addEdge(sourceId,destId,weight);
        }

    }
}

int Graph::findId(const string& city) {
    map<string,int>::iterator iter;
    iter = ids.find(city);
    int id = iter->second;
    return id;
}

void Graph::addEdge(int source, int dest, double weight) {
    Edge edge1(source,dest,weight);
    Edge edge2(dest,source,weight);
    adjList[source].push_back(edge1);
    adjList[dest].push_back(edge2);
}

void Graph::deleteEdge(const string& source,const string& dest) {
    int sourceId = findId(source);
    int destId = findId(dest);
    vector<Edge>::iterator  iter;
    int i = 0;
    for( iter = adjList[sourceId].begin() ; iter != adjList[sourceId].end() ; iter++ ) {
        if(iter->getDest() == destId )
            break;

        i++;
    }
    iter = adjList[sourceId].begin();
    advance(iter,i);
    adjList[sourceId].erase(iter);

    i = 0;
    for( iter = adjList[destId].begin() ; iter != adjList[destId].end() ; iter++ ) {
        if(iter->getDest() == sourceId )
            break;

        i++;
    }
    iter = adjList[destId].begin();
    advance(iter,i);
    adjList[destId].erase(iter);
}


void Graph::edgeUp(const string& source, const string& dest) {

    int sourceId = findId(source);
    int destId = findId(dest);
    vector<Edge>::iterator iter;

    for( iter = adjList[sourceId].begin() ; iter != adjList[sourceId].end() ; iter++ ) {
        if(iter->getDest() == destId) {
             iter->setStatus("Up");
             break;
        }

    }

    for( iter = adjList[destId].begin() ; iter != adjList[destId].end() ; iter++ ) {
        if(iter->getDest() == sourceId) {
            iter->setStatus("Up");
            break;
        }

    }
}

void Graph::edgeDown(const string& source, const string& dest) {

    int sourceId = findId(source);
    int destId = findId(dest);
    vector<Edge>::iterator iter;

    for( iter = adjList[sourceId].begin() ; iter != adjList[sourceId].end() ; iter++ ) {
        if(iter->getDest() == destId) {
            iter->setStatus("Down");
            break;
        }

    }

    for( iter = adjList[destId].begin() ; iter != adjList[destId].end() ; iter++ ) {
        if(iter->getDest() == sourceId) {
            iter->setStatus("Down");
            break;
        }

    }
}

void Graph::print() {

    vector<Edge>::iterator iter;

   cout << "Source -> Destinations" << endl;

    for(int i=0 ; i<NumberOfVertices ; i++) {

        string source = findName(i);
        cout << source ;
        for(iter = this->adjList[i].begin() ; iter!=this->adjList[i].end() ; iter++) {
            cout << " -> " <<  findName(iter->getDest()) << " " ;
        }
        cout << endl;
    }
}


void Graph::dfs(const string& source) {
                                     // If graph is directed then this algorithm shows where you can reach from given vertex .
    int sourceId = findId(source);

    cout << "Starting -> ";
    bool visited[NumberOfVertices];
    recursiveDfs(sourceId,visited);
    cout << "Ending" << endl;
}

void Graph::recursiveDfs(int sourceId, bool visited[]) {
    vector<Edge>::iterator iter;
    cout << sourceId << " -> ";
    visited[sourceId] = true;
    for(iter = adjList[sourceId].begin() ; iter != adjList[sourceId].end() ; iter++) {
        int y = iter->getDest();
        string status = iter->getStatus();
        if(!visited[y] && (status == "Up")) {
            recursiveDfs(y,visited);
        }
    }
}

void Graph::bfs(const string& source,const string& dest) {

    int sourceId = findId(source);  // Actually it is same as dijkstra's algorithm.The only difference is edge's weight is 1.
    int destId = findId(dest);      // If the graph is unweighted then this algorithm can be used for shortest path.


    vector<Edge>::iterator iter;
    list<int> queue;
    bool visited[NumberOfVertices];
    int dist[NumberOfVertices];
    visited[sourceId] = true;
    dist[sourceId] = 0;
    queue.push_back(sourceId);

    while(!queue.empty()) {
        sourceId = queue.front();
       queue.erase(queue.begin());
       for(iter = adjList[sourceId].begin() ; iter != adjList[sourceId].end() ; iter++) {
           int y = iter->getDest();
           string status = iter->getStatus();
           if(!visited[y] && (status == "Up")){
               dist[y] = dist[sourceId] + 1;
               queue.push_back(y);
               visited[y] = true;
           }
       }
    }

    cout << "The path from " << source << " to " << dest << " is " << dist[destId] << endl;
}


void Graph::dijkstra(string source,string dest) {

    int sourceId = findId(source);
    int destId = findId(dest);

    vector<Edge>::iterator iter;
    double dist[NumberOfVertices];
    for(int i=0 ; i< NumberOfVertices ; i++) {
        dist[i] = numeric_limits<double>::infinity();
    }

    dist[sourceId] = 0;
    list<int> queue;

    queue.push_back(sourceId);

    while(!queue.empty()) {
        sourceId = queue.front();
        queue.erase(queue.begin());
        for(iter = adjList[sourceId].begin() ; iter != adjList[sourceId].end() ; iter++) {
            if(iter->getStatus() == "Up") {
                int y = iter->getDest();
                if(dist[y] > dist[sourceId] + iter->getWeight()) {
                    dist[y] = dist[sourceId] + iter->getWeight();
                    queue.push_back(y);
                }
            }
        }
    }


    cout << "The shortest path from " << source << " to " << dest << " is " << dist[destId] << endl;


}


void Graph::vertexDown(const string& vertex) {
    int vertexId = findId(vertex);
    vector<Edge>::iterator iter;
    for(iter = adjList[vertexId].begin() ; iter != adjList[vertexId].end() ; iter++) {
        iter->setStatus("Down");
        int destId = iter->getDest();
        vector<Edge>::iterator iter2;
        for(iter2 = adjList[destId].begin() ; iter2 != adjList[destId].end() ; iter2++) {
            if(iter2->getDest() == vertexId)
                iter2->setStatus("Down");
        }
    }
}


void Graph::vertexUp(const string& vertex) {
    int vertexId = findId(vertex);
    vector<Edge>::iterator iter;
    for(iter = adjList[vertexId].begin() ; iter != adjList[vertexId].end() ; iter++) {
        iter->setStatus("Up");
        int destId = iter->getDest();
        vector<Edge>::iterator iter2;
        for(iter2 = adjList[destId].begin() ; iter2 != adjList[destId].end() ; iter2++) {
            if(iter2->getDest() == vertexId)
                iter2->setStatus("Up");
        }
    }
}

string Graph::findName(int id) {
map<int,string>::iterator iter;
iter = names.find(id);
return iter->second;
}

void Graph::reachable(const string& source) {
 int sourceId = findId(source);
 vector<Edge>::iterator iter;
 for(iter = adjList[sourceId].begin() ; iter != adjList[sourceId].end() ; iter++) {
     if(iter->getStatus() == "Up")
         cout << findName(iter->getDest()) << " " ;
 }
 cout << endl;
}


