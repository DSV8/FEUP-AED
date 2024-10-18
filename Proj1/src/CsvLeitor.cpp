//
// Created by dav on 10/17/22.
//

/**
 * @class CsvLeitor
 *
 *
 */

#include "../include/CsvLeitor.h"

CsvLeitor::CsvLeitor()= default;

std::vector<CsvLinha> CsvLeitor::ler(const std::string& nomeFicheiro, bool temCabecalho){
    std::ifstream ficheiroInput;
    std::vector<CsvLinha> linhas;

    ficheiroInput.open(nomeFicheiro.c_str());

    std::string linha;
    if (temCabecalho) getline(ficheiroInput, linha);

    while(getline(ficheiroInput, linha)){
        CsvLinha csvLinha;
        csvLinha.parsear(linha);
        linhas.push_back(csvLinha);
    }

    return linhas;
}