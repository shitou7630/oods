#include "dijkstra.h"

Dijkstra::Dijkstra() {

}

Dijkstra::~Dijkstra() {

}

bool Dijkstra::dijkstra(Graph *pGraph, Vertex src, Vertex des, vector<Action> &actions, vector<Vertex>& path) {
    if (!actions.empty()) actions.clear();
    if (!path.empty()) path.clear();
    int nv = pGraph->nRows * pGraph->nCols;
    int *dist = new int[nv];
    fill(dist, dist + nv, NO_VALUE);
    bool *collected = new bool[nv];
    fill(collected, collected + nv, false);
    int *pre = new int[nv];
    int src_index = vtoindex(pGraph, src);
    int des_index = vtoindex(pGraph, des);
    dist[src_index] = 0;
    priority_queue<Node, vector<Node>, cmp> q;
    q.push(Node(src, dist[src_index]));
    while (!q.empty()) {
        //Pop the vertex with minimum dist from the priority queue
        Vertex minV = q.top().v;
        q.pop();
        int minV_index = vtoindex(pGraph, minV);
        if (collected[minV_index]) continue;
        collected[minV_index] = true;
        //Action: collect minV
        actions.push_back(Action(minV, COLLECT));
        if (minV_index == des_index) {
            //Reach the destination
            break;
        }
        //Get vertexes around
        AdjIter adjIter(pGraph, minV);
        for (Vertex v = adjIter.getNext(); adjIter.hasNext(); v = adjIter.getNext()) {
            adjIter.update();
            if (v.row == NO_VALUE) continue; //v is blocked or out of the board matrix
            int v_index = vtoindex(pGraph, v);            
            if (!collected[v_index]) {
                if (dist[minV_index] + 1 < dist[v_index] || dist[v_index] == NO_VALUE) {
                    dist[v_index] = dist[minV_index] + 1;
                    q.push(Node(v, dist[v_index]));
                    pre[v_index] = minV_index;
                    //Action: update v
                    actions.push_back(Action(v, UPDATE));
                }
            }     
        }
    }//while
    while (!q.empty()) {
        q.pop();
    }
    bool result = collected[des_index];
    cout << dist[des_index] << endl;
    free(dist);
    free(collected);
    if (result) {    
        //Get the path from src to des
        stack<int> s;
        for (; des_index != src_index; des_index = pre[des_index])
            s.push(des_index);
        path.push_back(indextov(pGraph, src_index));
        while (!s.empty()) {
            path.push_back(indextov(pGraph, s.top()));
            s.pop();
        }
    }
    free(pre);
    return result;
}

int Dijkstra::vtoindex(Graph *pGraph, Vertex v){
    return pGraph->nCols * v.row + v.col;
}

Vertex Dijkstra::indextov(Graph *pGraph, int index) {
    return Vertex(index / pGraph->nCols, index % pGraph->nCols);
}
