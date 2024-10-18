//
// Created by dav on 10/31/22.
//

#ifndef PROJECT_1_CODIGONOME_H
#define PROJECT_1_CODIGONOME_H

#include <string>

class CodigoNome {
public:
    CodigoNome(std::string codigoEstudante, std::string nome);
    std::string getCodigoEstudante();
    std::string getNome();

    friend std::ostream& operator<<(std::ostream &, const CodigoNome&);
    friend bool operator==(const CodigoNome& lhs, const CodigoNome& rhs);
    friend bool operator< ( CodigoNome const& a, CodigoNome const& b);

private:
    std::string m_codigoEstudante;
    std::string m_nome;
};


#endif //PROJECT_1_CODIGONOME_H
