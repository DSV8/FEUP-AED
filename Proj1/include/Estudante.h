//
// Created by dav on 10/17/22.
//

#ifndef PROJECT_1_ESTUDANTE_H
#define PROJECT_1_ESTUDANTE_H

#include <string>
#include <list>
#include "TurmaUc.h"

class Estudante {
public:
    Estudante();
    Estudante(std::string codigoEstudante, std::string nome, std::list<TurmaUc> turmasUc);

    friend bool operator< (Estudante const& a, Estudante const& b);
    friend std::ostream& operator<<(std::ostream &, const Estudante&);
    std::string get_num() const;
    std::list<TurmaUc> get_turmasUc() const;
    std::string getNome();

private:
    std::string m_codigoEstudante;
    std::string m_nome;
    std::list<TurmaUc> m_turmasUc; //TurmaUc
};


#endif //PROJECT_1_ESTUDANTE_H
