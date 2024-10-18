//
// Created by gabri on 12/23/2022.
//

#include "../include/Aeroporto.h"

Aeroporto::Aeroporto() = default;

Aeroporto::Aeroporto(std::string codigo_, std::string nome_, std::string cidade_, std::string pais_, Coordenadas coordenadas_) :
codigo(std::move(codigo_)),  nome(std::move(nome_)), cidade(std::move(cidade_)), pais(std::move(pais_)),
coordenadas(coordenadas_) {}
/**
@brief Obtém as coordenadas geográficas do aeroporto
@return Coordenadas
*/
Coordenadas Aeroporto::getcoordenadas() const {return coordenadas;}
/**
@brief Obtém o código do aeroporto
@return string
*/
std::string Aeroporto::getcodigo() const {return codigo;}
/**
@brief Obtém o nome do aeroporto
@return string
*/
std::string Aeroporto::getnome() const {return nome;}
/**
@brief Obtém o país em que o aeroporto está localizado
@return string
*/
std::string Aeroporto::getpais() const {return pais;}
/**
@brief Obtém a cidade em que o aeroporto está localizado
@return string
*/
std::string Aeroporto::getcidade() const{return cidade;}

bool Aeroporto::operator==(const Aeroporto& ap) const{
    return ap.getcodigo() == this->codigo;
}

std::ostream& operator<<(std::ostream &os, const Aeroporto& obj){
    return os <<  std::string (" CODIGO: ") << obj.codigo <<  std::string ("   NOME: ")  << obj.nome << std::string ("   CIDADE: ") << obj.cidade << std::string ("   PAÍS: ") << obj.pais << obj.coordenadas ;
}
