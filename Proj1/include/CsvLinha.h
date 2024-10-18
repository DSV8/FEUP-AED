//
// Created by dav on 10/17/22.
//

#ifndef PROJECT_1_CSVLINHA_H
#define PROJECT_1_CSVLINHA_H

#include <string>
#include <sstream>
#include <vector>

class CsvLinha {
private:
    std::vector<std::string> valores;
public:
    CsvLinha()= default;

    CsvLinha(const CsvLinha& outro);

    CsvLinha operator = (const CsvLinha& outro);

    ~CsvLinha()= default;;

    void parsear(const std::string& linha, char delimitador = ',');
    std::string getString(int coluna);
    double getDouble(int coluna);
};


#endif //PROJECT_1_CSVLINHA_H
