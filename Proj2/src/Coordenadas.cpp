//
// Created by gabri on 12/23/2022.
//


#include <utility>
#include "../include/Coordenadas.h"

Coordenadas::Coordenadas() = default;

Coordenadas::Coordenadas(float latitude_, float longitude_) : latitude(latitude_), longitude(longitude_) {}
/**
 * @brief Obtém a latitude das coordenadas.
 * @return float
 */
float Coordenadas::getlatitude() const {
    return latitude;
}

/**
 * @brief Obtém a longitude das coordenadas.
 * @return float
 */
float Coordenadas::getlongitude() const{
    return longitude;
}

std::ostream& operator<<(std::ostream &os, const Coordenadas& obj){
    return os <<  std::string ("   Coordenadas: (") << obj.latitude <<  std::string (" , ")  << obj.longitude << std::string (")");
}
