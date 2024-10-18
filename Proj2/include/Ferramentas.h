//
// Created by gabri on 12/26/2022.
//

#ifndef PROJETO_AED_FERRAMENTAS_H
#define PROJETO_AED_FERRAMENTAS_H


#include "Coordenadas.h"
#include "Aeroporto.h"
#include <cmath>

//! Classe Ferramentas
//!
//! Esta classe fornece métodos estáticos para calcular a distância entre dois pontos e entre dois aeroportos.
class Ferramentas {
public:
    static double calculatedistancecoords(Coordenadas a, Coordenadas b);

    static double calculatedistanceairports(const Aeroporto& a, const Aeroporto& b);

};


#endif //PROJETO_AED_FERRAMENTAS_H
