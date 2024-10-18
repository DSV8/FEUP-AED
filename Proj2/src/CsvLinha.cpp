#include "../include/CsvLinha.h"

CsvLinha::CsvLinha() = default;

CsvLinha::CsvLinha(__attribute__((unused)) const CsvLinha& outro){
    valores = outro.valores;
}

CsvLinha& CsvLinha::operator=(const CsvLinha& outro) = default;
/**
 * @brief Divide a linha em colunas.
 * @param linha A linha a ser dividida.
 * @param delimitador O delimitador das colunas.
 * @return void
 */
void CsvLinha::parsear(const std::string& linha, char delimitador){

    std::stringstream linhaInput(linha);

    std::string colunaTemporaria;
    while (getline(linhaInput, colunaTemporaria, delimitador)){
        valores.push_back(colunaTemporaria);
    }
}
/**
 * @brief Obtém um valor da linha como string.
 * @param coluna A coluna a ser lida.
 * @return string.
 */
std::string CsvLinha::getString(int coluna){
    return valores[coluna];
}
/**
 * @brief Obtém um valor da linha como double.
 * @param coluna A coluna a ser lida.
 * @return double.
 */
double CsvLinha::getDouble(int coluna){
    return std::stof(valores[coluna]);
}
/**
 * @brief Obtém um valor da linha como int.
 * @param coluna A coluna a ser lida.
 * @return int.
 */
int CsvLinha::getInt(int coluna){
    return std::stoi(valores[coluna]);
}

bool operator==(const CsvLinha& lhs, const CsvLinha& rhs){
    return (lhs.valores == rhs.valores);
}
