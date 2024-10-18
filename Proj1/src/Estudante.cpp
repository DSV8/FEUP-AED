//
// Created by dav on 10/17/22.
//

/**
 * @class Estudante
 *
 *
 */

#include <utility>

#include "../include/Estudante.h"

Estudante::Estudante(){

}

Estudante::Estudante(std::string codigoEstudante, std::string nome, std::list<TurmaUc> turmasUc) : m_codigoEstudante(std::move(codigoEstudante)), m_nome(std::move(nome)), m_turmasUc(std::move(turmasUc)){}

bool operator< (Estudante const& a, Estudante const& b){
    return a.m_nome < b.m_nome;
}

std::ostream& operator<<(std::ostream &os, const Estudante& obj){
    return os << obj.m_codigoEstudante << std::string (" - ") << obj.m_nome;
}

std::string Estudante::get_num() const {
    return m_codigoEstudante;
}

std::string Estudante::getNome() {return m_nome;}

std::list<TurmaUc> Estudante::get_turmasUc() const{
    return m_turmasUc;
}
