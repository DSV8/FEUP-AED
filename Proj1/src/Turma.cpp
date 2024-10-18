//
// Created by dav on 10/17/22.
//

/**
 * @class Turma
 *
 *
 */

#include <utility>

#include "../include/Turma.h"

Turma::Turma(TurmaUc turmaUc, std::list<Slot> horarioTurma) : m_turmaUc(std::move(turmaUc)), m_horarioTurma(std::move(horarioTurma)){}

std::ostream& operator<<(std::ostream &os, const Turma& obj){
    return os << obj.m_turmaUc;
}


TurmaUc Turma::getturmauc(){
    return m_turmaUc;
}

std::list<Slot> Turma::gethorarioturma(){
    return m_horarioTurma;
}