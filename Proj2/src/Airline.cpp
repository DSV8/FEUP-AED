//
// Created by gabri on 12/23/2022.
//

#include "../include/Airline.h"

Airline::Airline(std::string codigo_, std::string nome_, std::string callsign_, std::string pais_) :
        codigo(std::move(codigo_)),  nome(std::move(nome_)), callsign(std::move(callsign_)), pais(std::move(pais_)) {}

/**
 * @brief Obtém o país da companhia aérea.
 * @return string
 */
std::string Airline::getPais() {return pais;}

std::ostream& operator<<(std::ostream &os, const Airline& obj) {
    return os << std::string("   CODIGO: ") << obj.codigo << std::string("   NOME: ") << obj.nome
              << std::string("   CALLSIGN: ") << obj.callsign << std::string("   PAÍS: ") << obj.pais;
}
