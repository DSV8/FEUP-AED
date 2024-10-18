

#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_set>
#include <climits>
#include <iostream>
#include "../include/Graph.h"
#include "../include/Ferramentas.h"
#include "../include/Voo.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir) {}
/**
 * Adiciona um nó ao grafo, representando um aeroporto.
 *
 * @param key Chave única para identificar o nó no grafo (codigo do aeroporto).
 * @param airport Instância de Aeroporto a ser armazenada no nó.
 * @Complexity O(1).
 * @return void
 */
void Graph::addNode(const std::string& key, Aeroporto &airport){
    nodes.insert({ key, { airport, {}, false } });
}
/**
 * Adiciona uma aresta ao grafo, representando uma rota aérea entre dois aeroportos.
 *
 * @param aeroporto_origem Chave do nó de origem (aeroporto).
 * @param aeroporto_destino Chave do nó de destino (aeroporto).
 * @param airline Nome da companhia aérea que opera a rota.
 * @Complexity O(1).
 * @return void
 */
void Graph::addEdge(std::string& aeroporto_origem, std::string& aeroporto_destino, std::string& airline){
    auto origem = nodes.find(aeroporto_origem);
    auto destino = nodes.find(aeroporto_destino);
    if( origem == destino || origem == nodes.end() || destino == nodes.end()) return;

    double distance = Ferramentas::calculatedistanceairports(origem->second.airport, destino->second.airport);

    origem->second.adj.push_back( { aeroporto_destino, airline, distance } );
}
/**
 * @brief Calcula os caminhos mais curtos entre os nós de origem e destino, considerando apenas as companhias aéreas especificadas.
 * @Complexity O(V+E+n) V: numero de nodes, E: numero de edges, numero total de paths construidos em buildPaths
 * @param startNodeKey Chave do nó de origem.
 * @param endNodeKey Chave do nó de destino.
 * @param airlines Conjunto de chaves das companhias aéreas a serem consideradas.
 * @return 2d vector
 */
vector<vector<Voo>> Graph::shortestPaths (const string& startNodeKey, const string& endNodeKey, const unordered_set<string>& airlines) {
    distanceBFS(startNodeKey);
    for(auto &node: nodes) node.second.visited = false;

    unordered_map<string, vector<Voo>> parents = getParents(startNodeKey, endNodeKey, airlines);
    vector<vector<Voo>> paths;
    vector<Voo> currPath;

    buildPaths(parents, paths, currPath, endNodeKey, startNodeKey);

    return paths;
}
/**
 * Calcula a distância de cada nó a partir de um nó de origem usando busca em largura.
 * @Complexity O(V+E) V: numero de nodes, E: numero de edges
 * @param v Chave do nó de origem.
 *
 * @note As distâncias são armazenadas no próprio nó, na variável nodeDist.
 * @return void
 */
void Graph::distanceBFS(const string& v) {
    for(auto &node: nodes) {
        node.second.visited = false;
        node.second.nodeDist = -1;
    }

    queue<string> q;
    q.push(v);
    nodes[v].nodeDist = 0;
    nodes[v]. visited = true;

    while (!q.empty()) {
        string u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            string w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].nodeDist = nodes[u].nodeDist + 1;
            }
        }
    }
}
/**
 * Calcula o diâmetro (ditância máxima) a partir de um nó de origem usando busca em largura.
 * @Complexity O(V+E) V: numero de nodes, E: numero de edges
 * @param v Chave do nó de origem.
 *
 * @note As distâncias são armazenadas no próprio nó, na variável nodeDist.
 * @return int
 */
int Graph::bfsDiameter(const string &v) {
    int max = 0;
    for (auto &node: nodes) {
        node.second.visited = false;
        node.second.nodeDist = -1;
    }
    queue<string> q;
    q.push(v);
    nodes[v]. visited = true;
    nodes[v].nodeDist = 0;
    while (!q.empty()) {
        string u = q.front();
        q.pop();
        for (const auto &e: nodes[u].adj) {
            string w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].nodeDist = nodes[u].nodeDist + 1;
                if(nodes[w].nodeDist > max){max = nodes[w].nodeDist;}
            }
        }
    }
    return max;
}

/**
 * Calcula o diâmetro (ditância máxima) a partir de um país usando busca em largura.
 * @Complexity O(V+E) V: numero de nodes, E: numero de edges
 * @param v Chave do nó de origem.
 *
 * @note As distâncias são armazenadas no próprio nó, na variável nodeDist.
 * @return int
 */
int Graph::bfsDiameterCountry(const string& v, string country) {
    int max = 0;
    for (auto &node: nodes) {
        node.second.visited = false;
        node.second.nodeDist = -1;
    }
    queue<string> q;
    q.push(v);
    nodes[v]. visited = true;
    nodes[v].nodeDist = 0;
    while (!q.empty()) {
        string u = q.front();
        q.pop();
        for (const auto &e: nodes[u].adj) {
            string w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].nodeDist = nodes[u].nodeDist + 1;
                if(nodes[w].nodeDist > max && nodes[w].airport.getpais() == country) {max = nodes[w].nodeDist;}
            }
        }
    }
    return max;
}
/**
 * Encontra todos os caminhos possíveis entre dois nós de um grafo, respeitando as restrições de companhias aéreas.
 * @Complexity O(V+E) V: numero de nodes, E: numero de edges
 * @param startNodeKey Chave do nó de origem.
 * @param endNodeKey Chave do nó de destino.
 * @param airlines Conjunto de códigos de companhias aéreas permitidas. Se vazio, qualquer companhia é permitida.
 *
 * @return unordered_map
 */
unordered_map<string, vector<Voo>> Graph::getParents (const string& startNodeKey, const string& endNodeKey, const unordered_set<string>& airlines) {
    unordered_map<string , vector<Voo>> parents;
    queue<string> q;

    q.push(startNodeKey);
    nodes[startNodeKey].visited = true;


    while (!q.empty()) {
        string u = q.front();
        q.pop();
        if (u == endNodeKey) break;
        for (const auto &e: nodes[u].adj) {
            string w = e.dest;
            if ((nodes[w].nodeDist == nodes[u].nodeDist + 1) && (airlines.empty() || airlines.find(e.airline) != airlines.end())) {
                if (!nodes[w].visited) {
                    nodes[w].visited = true;
                    q.push(w);
                    parents[w].emplace_back(u, w, e.airline);
                } else {
                    string parentW = parents[w].back().getOrigem();
                    if (nodes[u].nodeDist == nodes[parentW].nodeDist) {
                        parents[w].emplace_back(u, w, e.airline);
                    }
                }
            }
        }
    }
    return parents;
}
/**
 * Constroi todos os caminhos possíveis entre dois nós de um grafo a partir de um mapa de nós-pais.
 * @Complexity O(n) n: numero total de caminhos
 * @param parents Mapa de nós-pais, onde cada chave é um nó e o valor é uma lista de voos que o levaram até lá.
 * @param paths Lista de caminhos encontrados, onde cada caminho é uma lista de voos.
 * @param currPath Caminho atual sendo construído.
 * @param p Nó atual.
 * @param destination Nó de destino.
 * @return void
 */
void Graph::buildPaths(unordered_map<string, vector<Voo>>& parents, vector<vector<Voo>>& paths, vector<Voo>& currPath, const string& p, const string& destination) {
    if (p == destination) {
        paths.push_back(currPath);
        return;
    }

    for (auto voo : parents[p]) {
        currPath.insert(currPath.begin(), voo);
        buildPaths(parents, paths, currPath, voo.getOrigem(), destination);
        currPath.erase(currPath.begin());
    }
}
/**
 * Executa uma busca em profundidade a partir de um nó de origem, marcando os nós visitados como parte de um ciclo.
 * @Complexity O(V+E) V: numero de nodes, E: numero de edges
 * @param v Chave do nó de origem.
 * @return void
 */
void Graph::dfs(const string& v) {
    nodes[v].ciclo = true;
    for (const auto& e : nodes[v].adj) {
        string w = e.dest;
        if (!nodes[w].ciclo)
            dfs(w);
    }
}
/**
 * Executa uma busca em largura a partir de um nó de origem, atualizando as distâncias dos nós visitados.
 * @Complexity O(V+E) V: numero de nodes, E: numero de edges
 * @param v Chave do nó de origem.
 * @return void
 */
void Graph::bfs(const string& v) {
    restart();
    dfs(v);
    queue<string> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].nodeDist = 0;
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        string u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            string w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].nodeDist = nodes[u].nodeDist + 1;
            }
        }
    }
}
/**
 * Reinicia os valores de visibilidade, distância e informações de ponte e componente para todos os nós do grafo.
 * @return void
 */
void Graph::restart(){
    for(auto &node: nodes) {
        node.second.visited = false;
        node.second.nodeDist = -1;
        node.second.num = INT_MAX;
        node.second.low = INT_MAX;
    }
}
/**
 * Executa uma busca em profundidade a partir de um nó de origem, encontrando pontos de articulação e adicionando-os a uma lista.
 * @Complexity O(V+E) V: numero de nodes, E: numero de edges
 * @param v Chave do nó de origem.
 * @param order Variável para controlar a ordem de visitação dos nós.
 * @param l Lista de pontos de articulação encontrados.
 * @param airline Vetor de strings com as companhias aéreas a que se quer encontrar os pontos de articulação.
 * @return void
 */
void Graph::dfs_articulation_points(const string& v, int &order, list<string> &l, vector<string> airline) {
    nodes[v].visited = true;
    nodes[v].num = nodes[v].low = order++;

    int children = 0;
    bool articulation = false;

    for (const Edge& e : nodes[v].adj) {
        string w = e.dest;
        if (!nodes[w].visited) {
            children++;
            dfs_articulation_points(w, order, l,airline);
            nodes[v].low = min(nodes[v].low, nodes[w].low);
            if(!airline.empty()){
                if ((nodes[w].low >= nodes[v].num) && find(airline.begin(),airline.end(),e.airline)!=airline.end() ) articulation = true;
            }
            else{
            if ((nodes[w].low >= nodes[v].num)) articulation = true;
            }
        }
        else{
            nodes[v].low = min(nodes[v].low, nodes[w].num);
        }
    }
    if ((nodes[v].num == 1 && children > 1) || (nodes[v].num > 1 && articulation)){
        l.push_front(v);
    }
}