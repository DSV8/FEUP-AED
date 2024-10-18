//
// Created by gabri on 12/26/2022.
//

#include <utility>
#include "../include/Cidade.h"

Cidade::Cidade() = default;

Cidade::Cidade(std::string nome_, std::string pais_){
    pais=std::move(pais_);
    nome=std::move(nome_);
}
/**
 * @brief Obtém o nome da cidade.
 * @return string
 */
std::string Cidade::getnome() const{
    return nome;
}
/**
 * @brief Obtém o país onde a cidade está localizada.
 * @return string
 */
std::string Cidade::getpais() const{
    return pais;
}

bool operator< (const Cidade &left, const Cidade &right)
{
    return true;
}
/**
 * @brief Obtém a lista de aeroportos da cidade.
 * @return A lista de aeroportos da cidade.
 */
std::vector<Aeroporto> Cidade::getaeroportos() const{
    return aeroportos;
}
/**
 * @brief Adiciona um aeroporto à cidade.
 * @param ap O aeroporto a ser adicionado.
 */
void Cidade::addaeroporto(const Aeroporto& ap) {
    aeroportos.push_back(ap);
}

bool Cidade::operator==(const Cidade& city) const{
    return city.getnome() == this->nome && city.getpais() == this->pais;
}
