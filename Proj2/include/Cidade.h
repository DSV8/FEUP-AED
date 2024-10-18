//
// Created by gabri on 12/26/2022.
//

#ifndef PROJETO_AED_CIDADE_H
#define PROJETO_AED_CIDADE_H


#include <vector>
#include <string>
#include "Aeroporto.h"

/**
@brief Classe que representa uma cidade.
*/
class Cidade {
public:
    Cidade();
    Cidade(std::string nome_,std::string pais_);

    void addaeroporto(const Aeroporto& ap);
    /**
    @brief Sobrecarga do operador de menor.
    Compara duas cidades pelo nome, de forma alfabética.
    @param left A primeira cidade a ser comparada.
    @param right A segunda cidade a ser comparada.
    @return true se a primeira cidade tem nome "menor" que a segunda, false caso contrário.
    */
    friend bool operator< (const Cidade &left, const Cidade &right);
    /**
    @brief Sobrecarga do operador de igualdade.
    Verifica se duas cidades são iguais, comparando seus nomes.
    @param city A outra cidade a ser comparada.
    @return true se as duas cidades têm o mesmo nome, false caso contrário.
    */
    bool operator==(const Cidade& city) const;

    std::string getnome() const;

    std::string getpais() const;

    std::vector<Aeroporto> getaeroportos() const;
private:
    std::string nome;
    std::vector<Aeroporto> aeroportos;
    std::string pais;
};


#endif //PROJETO_AED_CIDADE_H
