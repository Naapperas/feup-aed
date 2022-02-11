// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"
#include <set>
#include <functional>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

bool Graph::Edge::operator<(const Edge& e) const {
    return this->weight < e.weight;
}

// ----------------------------------------------------------
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
// TODO
int Graph::prim(int r) {

    MinHeap<int, int> primHeap(this->n, -1);

    for (auto& node : this->nodes) {
        node.parent = -1;
        node.distance = 999999999;
    }

    this->nodes[r].distance = 0;

    for (int node = 1; node <= this->n; node++)
        primHeap.insert(node, this->nodes[node].distance);

    int sum = 0;

    while (primHeap.getSize()) {
        auto u = primHeap.removeMin();
        sum += this->nodes[u].distance; // already found min, add distance

        for (auto& edge : this->nodes[u].adj) {

            auto& neighbourIndex = edge.dest;
            auto& neighbour = this->nodes[neighbourIndex];

            if (primHeap.hasKey(neighbourIndex) && edge.weight < neighbour.distance) {
                neighbour.distance = edge.weight;
                primHeap.decreaseKey(neighbourIndex, edge.weight);
                neighbour.parent = u;
            }
        }
    }

    return sum;
}

bool operator<(const pair<int, Graph::Edge> a, const pair<int, Graph::Edge>& b) {
    return a.second < b.second;
}

// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
int Graph::kruskal() {

    DisjointSets<int> forest;

    set<pair<int, Graph::Edge>> edges;

    int sum = 0;

    for (int i = 1; i <= this->n; i++) {
        forest.makeSet(i);
        for (const auto& edge : this->nodes[i].adj)
            edges.insert({i, edge});
    }

    for (auto itr = edges.begin(); itr != edges.end(); itr++) {
        if (forest.find(itr->first) != forest.find(itr->second.dest)) {
            sum += itr->second.weight;
            forest.unite(itr->first, itr->second.dest);
        }
    }

    return sum;
}
