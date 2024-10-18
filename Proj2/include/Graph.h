
#ifndef PROJETO_AED_GRAPH_H
#define PROJETO_AED_GRAPH_H


#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "Aeroporto.h"
#include "Voo.h"

using namespace std;

class Graph {
public:
    /**
     * @brief Representa uma aresta em um grafo de voos.
       Uma aresta conecta dois nós em um grafo e tem uma distância associada.
     * @var Edge::dest
     * @brief Destino da aresta.
     * @var Edge::airline
     * @brief Companhia aérea responsável pela rota.
     * @var Edge::edgeDist
     * @brief Distância da aresta.
     */
    struct Edge {
        string dest; // Destination node
        string airline;
        double edgeDist;
    };
    /**
     * @brief Representa um nó em um grafo de voos.
       Cada nó representa um aeroporto e tem uma lista de arestas que apontam para outros nós.
     * @var Node::airport
     * @brief Dados do aeroporto.
     * @var Node::adj
     * @brief Lista de arestas que saem desse nó.
     * @var Node::visited
     * @brief Indica se o nó já foi visitado durante uma busca.
     * @var Node::low
     * @brief Variável usada durante a detecção de ciclos.
     * @var Node::num
     * @brief Variável usada durante a detecção de ciclos.
     * @var Node::ciclo
     * @brief Indica se o nó está em um ciclo.
     * @var Node::parent
     * @brief Nó pai na árvore geradora mínima.
     * @var Node::nodeDist
     * @brief Distância até o nó pai na árvore geradora mínima.
     */
    struct Node {
        Aeroporto airport;
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited; // As the node been visited on a search?
        int low;
        int num;
        bool ciclo;
        int parent;
        int nodeDist;
    };

    /**
     * @brief Tamanho do grafo (os vértices são numerados de 1 a n).
     */
    int n;
    /**
     * @brief Indica se o grafo é direcionado ou não.
     * Se false, o grafo é não direcionado. Se true, o grafo é direcionado.
     */
    bool hasDir;
    /**
     * @brief Mapa que mapeia os nomes dos aeroportos para os nós correspondentes.
     */
    unordered_map<string, Node> nodes;

    explicit Graph(int nodes, bool dir = false);
    /**
     * @brief Adiciona um nó ao grafo.
     * @param key Chave para o mapa de nós.
     * @param airport Dados do aeroporto a ser adicionado.
     */
    void addNode(const string& key, Aeroporto &airport);

    /**
     * @brief Adiciona uma aresta ao grafo.
     * @param aeroporto_origem Aeroporto de origem da aresta.
     * @param aeroporto_destino Aeroporto de destino da aresta.
     * @param airline Companhia aérea responsável pela rota.
     */
    void addEdge(string& aeroporto_origem, string& aeroporto_destino, string& airline);

    vector<vector<Voo>> shortestPaths (const string& startNodeKey, const string& endNodeKey, const unordered_set<string>& airlines);

    void restart();
    void dfs(const string& v);
    void bfs(const string& v);
    void distanceBFS(const string& v);
    int bfsDiameter(const string& v);
    int bfsDiameterCountry(const string& v, string country);
    void dfs_articulation_points(const string& v, int &order, list<string> &l, vector<string> airline);
private:

    unordered_map<string, vector<Voo>> getParents (const string& startNodeKey, const string& endNodeKey, const unordered_set<string>& airlines);
    void buildPaths(unordered_map<string, vector<Voo>>& parents, vector<vector<Voo>>& paths, vector<Voo>& currPath, const string& p, const string& destination);
};


#endif //PROJETO_AED_GRAPH_H
