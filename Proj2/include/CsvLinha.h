
// Created by dav on 10/17/22.
//

#ifndef PROJECT_1_CSVLINHA_H
#define PROJECT_1_CSVLINHA_H

#include <string>
#include <sstream>
#include <vector>

/**
@brief Classe que representa uma linha de um arquivo CSV (Comma Separated Values).
*/
class CsvLinha {
private:
    std::vector<std::string> valores;
public:
    CsvLinha();

    CsvLinha(__attribute__((unused)) const CsvLinha& outro);

    CsvLinha& operator=(const CsvLinha& outro);

    ~CsvLinha()= default;;

    void parsear(const std::string& linha, char delimitador = ',');

    std::string getString(int coluna);

    double getDouble(int coluna);

    int getInt(int coluna);
    /**
    @brief Sobrecarga do operador de igualdade.
    Verifica se duas linhas CSV são iguais, comparando seus valores.
    @param lhs A primeira linha a ser comparada.
    @param rhs A segunda linha a ser comparada.
    @return true se as duas linhas têm os mesmos valores, false caso contrário.
    */
    friend bool operator==(const CsvLinha& lhs, const CsvLinha& rhs);
};


#endif //PROJECT_1_CSVLINHA_H