//
// Created by gabri on 12/26/2022.
//

#include <cmath>
#include "../include/Ferramentas.h"

//* Calcula a distância entre duas coordenadas
//!
//! Esta função usa a fórmula Haversine para calcular a distância em metros entre duas coordenadas geográficas.
//!
//! @param a Coordenadas da primeira posição
//! @param b Coordenadas da segunda posição
//! @return double
double Ferramentas::calculatedistancecoords(Coordenadas a, Coordenadas b) {
    float lat1 = a.getlatitude();
    float lat2 = b.getlatitude();
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (b.getlongitude() - a.getlongitude()) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double temp = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * std::cos(lat1) * std::cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(temp));
    return rad * c;
}

//! Calcula a distância entre dois aeroportos
//!
//! Esta função usa as coordenadas dos aeroportos para calcular a distância entre eles em metros.
//!
//! @param a O primeiro aeroporto
//! @param b O segundo aeroporto
//! @return double
double Ferramentas::calculatedistanceairports(const Aeroporto& a, const Aeroporto& b) {
    float lat1 = a.getcoordenadas().getlatitude();
    float lat2 = b.getcoordenadas().getlatitude();
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (b.getcoordenadas().getlongitude() - a.getcoordenadas().getlongitude()) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double temp = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * std::cos(lat1) * std::cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(temp));
    return rad * c;
}