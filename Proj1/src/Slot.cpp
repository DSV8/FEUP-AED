//
// Created by dav on 10/17/22.
//

/**
 * @class Slot
 *
 *
 */
#include <utility>

#include "../include/Slot.h"

Slot::Slot(std::string diaSemana, double horaInicio, double duracao, std::string tipo)
                    : m_diaSemana(std::move(diaSemana)), m_horaInicio(horaInicio), m_duracao(duracao), m_tipo(std::move(tipo)){}

    std::string Slot::get_diaSemana(){
        return m_diaSemana;
    }
    double Slot::get_horaInicio() const{
        return m_horaInicio;
    }
    double Slot::get_duracao() const{
        return m_duracao;
    }
    std::string Slot::get_tipo(){
        return m_tipo;
    }
