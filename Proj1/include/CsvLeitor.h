//
// Created by dav on 10/17/22.
//

#ifndef PROJECT_1_CSVLEITOR_H
#define PROJECT_1_CSVLEITOR_H

#include "CsvLinha.h"
#include <vector>
#include <string>
#include <fstream>

class CsvLeitor {
public:
    CsvLeitor();
    static std::vector<CsvLinha> ler(const std::string& nomeFicheiro, bool temCabecalho = false);
};


#endif //PROJECT_1_CSVLEITOR_H
