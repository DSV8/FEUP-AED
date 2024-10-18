//
// Created by gabri on 12/23/2022.
//

#ifndef PROJETO_AED_VOO_H
#define PROJETO_AED_VOO_H


#include <string>

/**
@brief Classe que representa um voo entre dois aeroportos.
*/
class Voo {
public:
    Voo( std::string origem_, std::string destino_, std::string airline_ );
    /**
    @brief Sobrecarga do operador de inserção em stream.
    Permite imprimir o voo em stream, de forma legível para o usuário.
    @param os Stream de saída.
    @param obj O voo a ser impresso.
    @return A stream de saída, para permitir encadeamento.
    */
    friend std::ostream& operator<<(std::ostream &, const Voo&);

    std::string getOrigem();

    std::string getDestino();

    std::string getAirline();
private:
    std::string origem;
    std::string destino;
    std::string airline;

};

#endif //PROJETO_AED_VOO_H
