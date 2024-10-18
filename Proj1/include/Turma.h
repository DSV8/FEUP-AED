//
// Created by dav on 10/17/22.
//

#ifndef PROJECT_1_TURMA_H
#define PROJECT_1_TURMA_H

#include <string>
#include <list>
#include "TurmaUc.h"
#include "Slot.h"

class Turma {
public:
    Turma(TurmaUc turmaUc, std::list<Slot> horarioTurma);
    TurmaUc getturmauc();
    std::list<Slot> gethorarioturma();
    friend std::ostream& operator<<(std::ostream &, const Turma&);
private:
    TurmaUc m_turmaUc;
    std::list<Slot> m_horarioTurma;

};


#endif //PROJECT_1_TURMA_H
