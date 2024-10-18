// AED 2022/2023 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [last update: 27/11/2022]

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
void Graph::dfs(int v) {
    // show node order
    // cout << v << " ";
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}


// ----------------------------------------------------------
// Exercicio 1: Introdução a uma classe simplificada de grafos
// ----------------------------------------------------------

// ..............................
// a) Devolvendo o grau
// TODO
int Graph::outDegree(int v) {
    if (v >= 1 && v < (int) nodes.size()) {return (int) nodes[v].adj.size();}
    else {return -1;}
}

// ..............................
// b) Devolvendo o grau... pesado
// TODO
int Graph::weightedOutDegree(int v) {
    if (v < 1 || v > n) {return -1;}
    int sum = 0;
    for (auto e : nodes[v].adj) {
        sum += e.weight;
    }
    return sum;
}

// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {
    int counter = 0;
    for (int v = 1; v <= n; v++) {nodes[v].visited = false;}

    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited) {
            counter++;
            dfs(v);
        }
    }
    return counter;
}

// ..............................
// b) Componente gigante
// TODO
int Graph::giantComponent() {
    for (int v = 1; v <= n; v++) nodes[v].visited = false;
        int giant = 0;
        for (int v = 1; v <= n; v++)
            if (!nodes[v].visited) {
                int count = dfsGC(v);
                if (count > giant) {giant = count;}
    }
    return giant;
}

int Graph::dfsGC(int v){
    nodes[v].visited = true;
    int count = 1;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            count += dfsGC(w);
    }
    return count;
}

// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<int> Graph::topologicalSorting() {
    list<int> order;
    for (int v = 1; v <= n; v++) nodes[v].visited = false;

    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited) {
            dfsTopo(v, order);
        }
    }
    return order;
}

void Graph::dfsTopo(int v, list<int>& order) {
    list<int> oreder;
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfsTopo(w, order);
    }
    order.push_front(v);
}

// ----------------------------------------------------------
// Exercicio 4: To be or not be… a DAG!
// ----------------------------------------------------------
// TODO
bool Graph::hasCycle() {
    for (int v = 1; v <= n; v++) nodes[v].color = 0;
    int count = 0;
    for (int v = 1; v <= n; v++)
        if (nodes[v].color == 0)
            dfsCycle(v, count);
    return (count > 0);
}

void Graph::dfsCycle(int v, int& count) {
    nodes[v].color = 1;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (nodes[w].color == 1) count++;
        else if (nodes[w].color == 0) dfsCycle(w, count);
    }
    nodes[v].color = 2;
}
