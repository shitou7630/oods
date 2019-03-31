#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#endif // DIJKSTRA_H

#include "action.h"
#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <iostream>
using namespace std;

class Dijkstra {
public:
    Dijkstra();
    ~Dijkstra();

    bool dijkstra(Graph *pGraph, Vertex src, Vertex des, vector<Action>& actions, vector<Vertex>& path);
private:
    struct Node {
        Vertex v;
        int dist;
        Node(Vertex v, int dist) : v(v), dist(dist) {}
    };

    struct cmp {
        bool operator() (Node& a, Node& b) {
            return a.dist > b.dist;
        }
    };

    int vtoindex(Graph *pGraph, Vertex v);
    Vertex indextov(Graph *pGraph, int index);
};
