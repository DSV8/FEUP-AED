//
// Created by dav on 10/17/22.
//

/**
 * @class CsvLinha
 *
 *
 */

#include "../include/CsvLinha.h"

CsvLinha::CsvLinha(const CsvLinha& outro){
    valores = outro.valores;
}

CsvLinha CsvLinha::operator = (const CsvLinha& outro){
    valores = outro.valores;
}

void CsvLinha::parsear(const std::string& linha, char delimitador){

    std::stringstream linhaInput(linha);

    std::string colunaTemporaria;
    while (getline(linhaInput, colunaTemporaria, delimitador)){
        valores.push_back(colunaTemporaria);
    }
}

std::string CsvLinha::getString(int coluna){
    return valores[coluna];
}

double CsvLinha::getDouble(int coluna){
    return atof(valores[coluna].c_str());
}