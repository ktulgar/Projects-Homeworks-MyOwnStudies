#include "Edge.h"


Edge::Edge(int source,int dest, double weight) {
    this->source = source;
    this->destination = dest;
    this->weight = weight;
    this->status = "Up";
}

int Edge::getDest() {
    return this->destination;
}

int Edge::getSource() {
    return this->source;
}

double Edge::getWeight() {
    return this->weight;
}

void Edge::setStatus(string status) {
    this->status = status;
}

string Edge::getStatus() {
    return this->status;
}