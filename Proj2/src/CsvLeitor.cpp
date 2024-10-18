

#include "../include/CsvLeitor.h"

CsvLeitor::CsvLeitor()= default;
/**
 * @brief Lê as linhas de um arquivo CSV.
 * @param nomeFicheiro O nome do arquivo a ser lido.
 * @param temCabecalho Indica se o arquivo tem cabeçalho.
 * @return vector
 */
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