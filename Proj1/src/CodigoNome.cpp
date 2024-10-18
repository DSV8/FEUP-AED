//
// Created by dav on 10/31/22.
//
/**
 * @class CodigoNome
 *
 *
 */

#include <utility>

#include "../include/CodigoNome.h"

CodigoNome::CodigoNome(std::string codigoEstudante, std::string nome) : m_codigoEstudante(std::move(codigoEstudante)), m_nome(std::move(nome)){}

std::string CodigoNome::getCodigoEstudante() {
    return m_codigoEstudante;
}

std::string CodigoNome::getNome() {
    return m_nome;
}

std::ostream& operator<<(std::ostream &os, const CodigoNome& obj){
    return os << obj.m_codigoEstudante + ' ' + obj.m_nome;
}

bool operator==(const CodigoNome& lhs, const CodigoNome& rhs) {
    return (lhs.m_codigoEstudante == rhs.m_codigoEstudante && lhs.m_nome == rhs.m_nome);
}

bool operator< ( CodigoNome const& a, CodigoNome const& b){
    return a.m_nome < b.m_nome;
}