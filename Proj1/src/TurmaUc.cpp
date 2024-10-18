//
// Created by dav on 10/17/22.
//

/**
 * @class TurmaUc
 *
 *
 */

#include <utility>

#include "../include/TurmaUc.h"

TurmaUc::TurmaUc(std::string codigoTurma, std::string codigoUc) : m_codigoTurma(codigoTurma), m_codigoUc(codigoUc){}

std::string TurmaUc::getCodigoTurma(){
    return m_codigoTurma;
}

std::string TurmaUc::getCodigoUc(){
    return m_codigoUc;
}

std::ostream& operator<<(std::ostream &os, const TurmaUc& obj){
    return os << obj.m_codigoUc << std::string (" ") << obj.m_codigoTurma;
}

bool operator==(const TurmaUc& lhs, const TurmaUc& rhs){
    return (lhs.m_codigoTurma == rhs.m_codigoTurma) && (lhs.m_codigoUc == rhs.m_codigoUc);
}

bool operator!=(const TurmaUc& lhs, const TurmaUc& rhs){
    return (lhs.m_codigoTurma != rhs.m_codigoTurma) || (lhs.m_codigoUc != rhs.m_codigoUc);
}

