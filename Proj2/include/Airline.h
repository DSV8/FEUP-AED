//
// Created by gabri on 12/23/2022.
//

#ifndef PROJETO_AED_AIRLINE_H
#define PROJETO_AED_AIRLINE_H

#include <string>

/**
@brief Classe que representa uma companhia aérea.
*/
class Airline {
public:
    Airline(std::string codigo_, std::string nome_, std::string callsign_, std::string pais_);
    /**
    @brief Sobrecarga do operador de inserção em stream.
    Permite imprimir a companhia aérea em stream, de forma legível para o usuário.
    @param os Stream de saída.
    @param obj A companhia aérea a ser impressa.
    @return A stream de saída, para permitir encadeamento.
    */
    friend std::ostream& operator<<(std::ostream &os, const Airline&obj);

    std::string getPais();
private:
    std::string codigo;
    std::string nome;
    std::string callsign;
    std::string pais;
};

#endif //PROJETO_AED_AIRLINE_H
