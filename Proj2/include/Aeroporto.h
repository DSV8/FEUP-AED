//
// Created by gabri on 12/23/2022.
//

#ifndef PROJETO_AED_AEROPORTO_H
#define PROJETO_AED_AEROPORTO_H

#include "Coordenadas.h"
#include <string>

/**
 * @brief Classe que representa um aeroporto.
 */
class Aeroporto {

public:
    Aeroporto();
    Aeroporto(std::string codigo_, std::string nome_, std::string cidade_, std::string pais_, Coordenadas coordenadas_);
    Coordenadas getcoordenadas() const;

    std::string getcodigo() const;

    std::string getnome() const;

    std::string getpais() const;

    std::string getcidade() const;
    /**
     * @brief Sobrecarga do operador de inserção em stream.
       Permite imprimir o aeroporto em stream, de forma legível para o usuário.
     * @param os Stream de saída.
     * @param aeroporto O aeroporto a ser impresso.
     * @return A stream de saída, para permitir encadeamento.
     */
    friend std::ostream& operator<<(std::ostream &, const Aeroporto&);
    /**
     * @brief Sobrecarga do operador de igualdade.
       Verifica se dois aeroportos são iguais, comparando seus códigos.
     * @param ap O outro aeroporto a ser comparado.
     * @return true se os dois aeroportos têm o mesmo código, false caso contrário.
     */
    bool operator==(const Aeroporto& ap) const;
private:
    std::string codigo;
    std::string nome;
    std::string cidade;
    std::string pais;
    Coordenadas coordenadas;

};


#endif //PROJETO_AED_AEROPORTO_H

