//
// Created by dav on 10/17/22.
//

#ifndef PROJECT_1_CSVLEITOR_H
#define PROJECT_1_CSVLEITOR_H

#include "CsvLinha.h"
#include <vector>
#include <string>
#include <fstream>

/**
@brief Classe que lê um arquivo CSV (Comma Separated Values) e armazena os valores em um vetor de CsvLinha.
*/
class CsvLeitor {
public:
    CsvLeitor();
    /**
    @brief Lê o arquivo CSV especificado e armazena os valores em um vetor de CsvLinha.
    @param nomeFicheiro O nome do arquivo CSV a ser lido.
    @param temCabecalho Indica se o arquivo possui um cabeçalho que deve ser ignorado.
    @return O vetor de CsvLinha com os valores do arquivo CSV.
    */
    static std::vector<CsvLinha> ler(const std::string& nomeFicheiro, bool temCabecalho = false);
};


#endif //PROJECT_1_CSVLEITOR_H
