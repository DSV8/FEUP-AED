// AED 2022/2023 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [last update: 04/12/2022]

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
// Exercicio 1: DFS e grafos bipartidos
// ----------------------------------------------------------
// TODO
bool Graph::bipartite() {
    for (int v = 1; v <= n; v++) nodes[v].visited = false;
    return dfs_bipartite(1, true);
}

bool Graph::dfs_bipartite(int v, bool c) {
    if (nodes[v].visited) return (c == nodes[v].color);
    nodes[v].visited = true;
    nodes[v].color = c;
    for (auto e : nodes[v].adj)
        if (!dfs_bipartite(e.dest, !c))
            return false;
    return true;
};

// ----------------------------------------------------------
// Exercicio 2.a: Contando componentes fortemente conexos.
// ----------------------------------------------------------
// TODO
int Graph::countSCCs() {
    return 0;
}

// ----------------------------------------------------------
// Exercicio 2.b: Listando componentes fortemente conexos
// ----------------------------------------------------------
// TODO
list<list<int>> Graph::listSCCs() {
    list<list<int>> answer;
    return answer;
}

// ----------------------------------------------------------
// Exercicio 3: Pontos de articulação
// ----------------------------------------------------------
// TODO
list<int> Graph::articulationPoints() {
    list<int> answer;
    return answer;
}
