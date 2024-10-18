//
// Created by gabri on 12/23/2022.
//

#ifndef PROJETO_AED_COORDENADAS_H
#define PROJETO_AED_COORDENADAS_H


#include <ostream>

/**
@brief Classe que representa uma set of geographical coordinates.
*/
class Coordenadas {

public:
    Coordenadas();
    Coordenadas(float latitude_, float longitude_);

    float getlatitude() const;

    float getlongitude() const;
    /**
    @brief Sobrecarga do operador de inserção em stream.
    Permite imprimir a coordenada em stream, de forma legível para o usuário.
    @param os Stream de saída.
    @param obj A coordenada a ser impressa.
    @return A stream de saída, para permitir encadeamento.
    */
    friend std::ostream& operator<<(std::ostream &, const Coordenadas&);

private:
    float latitude{};
    float longitude{};

};


#endif //PROJETO_AED_COORDENADAS_H
