// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

// Depth-First Search: example implementation
int Graph::dfs(int v, std::list<int>* order) {

    int counter = 1;

    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            counter += dfs(w, order);
    }
    if (order != nullptr)
        order->emplace_front(v);

    return counter;
}

// Depth-First Search: example implementation
int Graph::bfs(int v) {
    for (int v=1; v<=n; v++) {
        nodes[v].visited = false;
        nodes[v].distance = -1;
    }
    queue<int> q; // queue of unvisited nodes

    int biggestDistance = 0;

    q.push(v);
    this->nodes[v].distance = 0;
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                this->nodes[w].distance = this->nodes[u].distance + 1;

                if (this->nodes[w].distance > biggestDistance) 
                    biggestDistance = this->nodes[w].distance;
            }
        }
    }
    return biggestDistance;
}

// ----------------------------------------------------------
// Exercicio 1: Introdução a uma classe simplificada de grafos
// ----------------------------------------------------------

// ..............................
// a) Contando diferentes somas de pares
// TODO
int Graph::outDegree(int v) {
    return (!(1 <= v && v < this->nodes.size())) ? -1 : this->nodes.at(v).adj.size();
}

// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {

    int counter = 0;
    for (int v=1; v <=n; v++)
        nodes[v].visited = false;
    for (int v=1; v<=n; v++)
        if(!nodes[v].visited ) {
            counter++;
            dfs(v);
        }
    return counter;
}

// ..............................
// b) Componente gigante
// TODO
int Graph::giantComponent() {

    int biggestSize = -1;
    for (int v=1; v <=n; v++)
        nodes[v].visited = false;
    for (int v=1; v<=n; v++)
        if(!nodes[v].visited ) {
            int size = dfs(v);
            if (size > biggestSize)
                biggestSize = size;
        }
    return biggestSize;
}


// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<int> Graph::topologicalSorting() {
    list<int> order;
    order.clear();

    for (int i = 0; i < this->n; i++)
        this->nodes[i].visited = false;

    for (int i = 1; i <= this->n; i++)
        if (!this->nodes[i].visited)
            dfs(i, &order);

    return order;
}

// ----------------------------------------------------------
// Exercicio 4: Distancias em grafos nao pesados
// ----------------------------------------------------------

// ..............................
// a) Distancia entre dois nos
// TODO
int Graph::distance(int a, int b) {

    if (a == b) return 0;

    bfs(a);

    return this->nodes[b].distance;
}

// ..............................
// b) Diametro
// TODO
int Graph::diameter() {

    if (this->connectedComponents() > 1) return -1;

    int diameter = 0;

    for (int i = 1; i <= this->n; i++) {
        int dist = bfs(i);
        if (dist > diameter) diameter = dist;
    }

    return diameter;
}

bool Graph::cycleDFS(int v) {
    nodes[v].color = "gray";
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (nodes[w].color == "gray")
            return true;
        else if (nodes[w].color == "white")
            if (cycleDFS(w)) 
                return true;
    }

    nodes[v].color = "black";
    return false;
}

// ----------------------------------------------------------
// Exercicio 5: To or not be… a DAG!
// ----------------------------------------------------------
// TODO
bool Graph::hasCycle() {

    bool hasCycle = false;

    for (int i = 1; i <= this->n; i++) {
        nodes[i].color = "white";
    }

    for (int i = 1; i <= this->n; i++) {
        if (cycleDFS(i)) 
            return true; 
    }

    return false;
}
