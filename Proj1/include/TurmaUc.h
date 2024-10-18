//
// Created by dav on 10/17/22.
//

#ifndef PROJECT_1_TURMAUC_H
#define PROJECT_1_TURMAUC_H

#include <string>

class TurmaUc {
public:
    TurmaUc(std::string codigoTurma, std::string codigoUc);
    std::string getCodigoTurma();
    std::string getCodigoUc();

    friend std::ostream& operator<<(std::ostream &, const TurmaUc&);
    friend bool operator==(const TurmaUc& lhs, const TurmaUc&);
    friend bool operator!=(const TurmaUc& lhs, const TurmaUc& rhs);

private:
    std::string m_codigoTurma;
    std::string m_codigoUc;
};

#endif //PROJECT_1_TURMAUC_H
