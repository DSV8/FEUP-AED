//
// Created by gabri on 12/23/2022.
//

#ifndef PROJETO_AED_GERAL_H
#define PROJETO_AED_GERAL_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include "../include/CsvLeitor.h"
#include "Aeroporto.h"
#include "Airline.h"
#include "Voo.h"
#include "Graph.h"
#include "Cidade.h"

class Geral {
public:
    Geral();
    void leraeroportos();
    void lerairlines();
    void lervoos();

    std::vector<Airline> getairlines() const;
    std::vector<Voo> getvoos() const;
    std::unordered_map<string, Cidade> getcidades() const;

    std::vector<Aeroporto> aeroportos;

    void getShortestPaths();

    void estatisticasGlobais();

    size_t numvoos(const string& codigoaeroporto);
    size_t numvoosairline(const string& codigoaeroporto);
    size_t numvoosdestino(const string& codigoaeroporto);
    size_t numvoospais(const string& codigoaeroporto);
    vector<size_t> nummaxvoos( const string& codigoaeroporto, int y);

    list<string> articulationPoints( const vector<string>& airline);
    //menu
    void menuprincipal();
    void voltarmenu();

private:
    /**
     * @brief Grafo que representa a rede de voos.
     * O grafo tem 3019 vértices e é direcionado.
     */
    Graph info = Graph(3019, true);
    /**
     * @brief Vetor de estruturas de dados que armazenam informações sobre as companhias aéreas.
     */
    std::vector<Airline> airlines;
    /**
     * @brief Conjunto de códigos de companhias aéreas.
     */
    std::unordered_set<string> airlineCodes;
    /**
     * @brief Conjunto de nomes de companhias aéreas.
     */
    std::unordered_set<string> airlineNames;
    /**
     * @brief Vetor de estruturas de dados que armazenam informações sobre os voos.
     */
    std::vector<Voo> voos;
    /**
     * @brief Mapa que mapeia os nomes das cidades para as estruturas de dados que armazenam informações sobre elas.
     */
    std::unordered_map<string, Cidade> cidades;
    /**
     * @brief Conjunto de nomes de países.
     */
    std::unordered_set<string> paises;

    static void displayShortestPaths(const vector<vector<Voo>>& shortestPaths);
};


#endif //PROJETO_AED_GERAL_H
