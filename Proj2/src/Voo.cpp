//
// Created by gabri on 12/23/2022.
//

#include "../include/Voo.h"


Voo::Voo(std::string origem_, std::string destino_, std::string airline_) :
        origem(std::move(origem_)),  destino(std::move(destino_)), airline(std::move(airline_)) {}

std::ostream& operator<<(std::ostream &os, const Voo& obj){
    return os <<  std::string ("   ORIGEM: ") << obj.origem <<  std::string ("   DESTINO: ")  << obj.destino << std::string ("   AIRLINE: ") << obj.airline;
}
/**
 * @brief Obtém o aeroporto de origem do voo.
 * @return string
 */
std::string Voo::getOrigem() {return origem;}
/**
 * @brief Obtém o aeroporto de destino do voo.
 * @return string
 */
std::string Voo::getDestino() {return destino;}
/**
 * @brief Obtém a companhia aérea responsável pelo voo.
 * @return string
 */
std::string Voo::getAirline() {return airline;}
