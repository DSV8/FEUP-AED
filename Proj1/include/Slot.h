//
// Created by dav on 10/17/22.
//

#ifndef PROJECT_1_SLOT_H
#define PROJECT_1_SLOT_H

#include <string>

class Slot {
public:
    Slot(std::string diaSemana, double horaInicio, double duracao, std::string tipo);

    std::string get_diaSemana();
    double get_horaInicio() const;
    double get_duracao() const;
    std::string get_tipo();

private:
    std::string m_diaSemana;
    double m_horaInicio;
    double m_duracao;
    std::string m_tipo;
};


#endif //PROJECT_1_SLOT_H
