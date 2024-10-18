//
// Created by dav on 10/19/22.
//



/**
 * @class GestaoHorario
 *
 * calls testData on stuff (this should be appended to the class description)
 */
#include <iostream>
#include "../include/GestaoHorario.h"
#include <algorithm>
#include <limits.h>
#include <string>
#include <iomanip>
#include <utility>
#include <vector>
#include <limits>

GestaoHorario::GestaoHorario()= default;

std::vector<TurmaUc> GestaoHorario::getTurmasUc() {
    return m_codigosTU;
}
std::vector<Turma> GestaoHorario::getHorario(){
    return m_horario;
}
std::set<Estudante> GestaoHorario::getEstudantes(){
    return m_estudantes;
}

std::queue<Pedido> GestaoHorario::getPedidos(){
    return m_pedidos;
}

void GestaoHorario::lerClassesPerUc(){
    CsvLeitor leitor;
    std::vector<CsvLinha> linhas = CsvLeitor::ler("/Users/dsv_8/ClionProjects/Projeto-AED/dados/classes_per_uc.csv", true);

    for (CsvLinha linha : linhas) {
        TurmaUc turmaUc(linha.getString(1), linha.getString(0));
        m_codigosTU.push_back(turmaUc);
    }
}

void GestaoHorario::lerClassesHelper(const TurmaUc& codigo){
    std::list<Slot> slots;
    CsvLeitor leitor;
    std::vector<CsvLinha> linhas = CsvLeitor::ler("/Users/dsv_8/ClionProjects/Projeto-AED/dados/classes.csv", true);

    for(CsvLinha linha : linhas){
        TurmaUc codigoAtual(linha.getString(0), linha.getString(1));
        if (codigoAtual == codigo){
            Slot slot(linha.getString(2), linha.getDouble(3), linha.getDouble(4), linha.getString(5));
            slots.push_back(slot);
        }
    }
    Turma turma(codigo, slots);
    m_horario.push_back(turma);
}

void GestaoHorario::lerClasses(){
    for (TurmaUc codigo : m_codigosTU) {
        lerClassesHelper(codigo);
    }
}

void GestaoHorario::lerStudentIds(){
    CsvLeitor leitor;
    std::vector<CsvLinha> linhas = leitor.ler("/Users/dsv_8/ClionProjects/Projeto-AED/dados/students_classes.csv", true);

    for (CsvLinha linha : linhas) {
        CodigoNome codigoNome(linha.getString(0), linha.getString(1));
        m_codigosEstudante.insert(codigoNome);
    }
}

void GestaoHorario::lerStudentsClassesHelper(CodigoNome codigoNome){
    std::list<TurmaUc> turmasUc;
    CsvLeitor leitor;
    std::vector<CsvLinha> linhas = leitor.ler("/Users/dsv_8/ClionProjects/Projeto-AED/dados/students_classes.csv", true);

    for(CsvLinha linha : linhas){
        CodigoNome codigoNomeAtual(linha.getString(0), linha.getString(1));
        if (codigoNomeAtual == codigoNome){
            TurmaUc turmaUc(linha.getString(3), linha.getString(2));
            turmasUc.push_back(turmaUc);
        }
    }
    Estudante estudante(codigoNome.getCodigoEstudante(), codigoNome.getNome(), turmasUc);
    m_estudantes.insert(estudante);
}

void GestaoHorario::lerStudentsClasses() {
    lerStudentIds();
    for (CodigoNome codigoNome : m_codigosEstudante) {
        lerStudentsClassesHelper(codigoNome);
    }

}

void GestaoHorario::lerFicheiros() {
    lerClassesPerUc();
    lerClasses();
    lerStudentsClasses();
}

// -------------------------------------LISTAGENS----------------------------------------------------------------------------

bool GestaoHorario::contem(std::string x){
    for(auto i: m_estudantes){
        if (i.get_num()== x ){
            return true;
        }
    }
    return false;
}

void GestaoHorario::horarioEstudante() {
    std::string x;
    do {
        std::cout << "   Introduza o numero do estudante: ";
        std::cin >> x;
        if (not contem(x)) { std::cout << "Este número não se encontra nos dados" << std::endl; }
        else{break;}
    }while(true);

    std::cout <<  " " <<std::endl;
    std::cout << char(201) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(187)  <<std::endl;
    std::cout << char(186)<<"                                          Horario do Estudante " << x << "                                             "<<char(186) <<std::endl;
    std::cout << char(204) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(203) <<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)  <<  char(205)  <<  char(205)  <<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(185)  <<std::endl;
    std::cout << char(186)<< "    Dia da semana   "<<char(186)<<"     Codigo da UC    "<<char(186)<<"      Hora de Inicio      "<<char(186)<<"    Hora do fim    "<<char(186)<<"     Duracao     "<<char(186)<<"   Tipo  "<<char(186) <<std::endl;
    std::cout <<  char(204) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205) <<char (205)<<char (206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(185) << std::endl;

    int i = 0;

    for (auto const& ol : this->getEstudantes()) {
        Estudante ans = ol;
        if(ans.get_num()==x){
            std::list<TurmaUc> lis = ans.get_turmasUc();
            for(auto ita : lis){
            }
            for(Turma i :  this->getHorario()) {
                if (find(lis.begin(),lis.end(),i.getturmauc()) != lis.end()){
                    for(Slot o : i.gethorarioturma()){
                        if(o.get_diaSemana()=="Friday" || o.get_diaSemana()=="Monday" ) {
                            std::cout << char(186) <<"       " << o.get_diaSemana() << "       "<< char(186)<< std::left << std::setw(21)
                                                                                   << i.getturmauc().getCodigoUc() << char(186)<< std::left << std::setw(26) << o.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                                                                   << o.get_horaInicio() + o.get_duracao() <<  char(186)<< std::left << std::setw(17) << o.get_duracao() <<  char(186)<< std::left << std::setw(9)
                                                                                   << o.get_tipo() <<  char(186) << "\n";
                        }
                        if(o.get_diaSemana()=="Wednesday"  ) {
                            std::cout << char(186)<< "      " << o.get_diaSemana() <<  "     "<< char(186)<< std::left << std::setw(21)
                                                                        << i.getturmauc().getCodigoUc() <<  char(186)<< std::left << std::setw(26) << o.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                                                        << o.get_horaInicio() + o.get_duracao() <<  char(186)<< std::left << std::setw(17) << o.get_duracao() << char(186)<< std::left << std::setw(9)
                                                                        << o.get_tipo() <<  char(186) << "\n";
                        }
                        if(o.get_diaSemana()=="Tuesday"  ) {
                            std::cout << char(186) << "       " << o.get_diaSemana() << "      "<< char(186)<< std::left << std::setw(21)
                                      << i.getturmauc().getCodigoUc() <<  char(186)<< std::left << std::setw(26) << o.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                      << o.get_horaInicio() + o.get_duracao() <<  char(186)<< std::left << std::setw(17) << o.get_duracao() << char(186)<< std::left << std::setw(9)
                                      << o.get_tipo() <<  char(186) << "\n";
                        }
                        if(o.get_diaSemana()=="Thursday"  ) {
                            std::cout << char(186)<<"      " << o.get_diaSemana() << "      "<< char(186)<< std::left << std::setw(21)
                                                                        << i.getturmauc().getCodigoUc() << char(186)<< std::left << std::setw(26) << o.get_horaInicio() << char(186)<< std::left << std::setw(19)
                                                                        << o.get_horaInicio() + o.get_duracao() <<  char(186)<< std::left << std::setw(17) << o.get_duracao() <<  char(186)<< std::left << std::setw(9)
                                                                        << o.get_tipo() << char(186) << "\n";
                        }
                    }
                }
            }
            std::cout <<  char(200) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205) <<char (205)<<char (202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(188) << std::endl;
            break;
        }
    }
    }



bool crescente (std::pair <std::string,int> i,std::pair <std::string,int> j) {
    return (i.second < j.second);
}
bool decrescente (std::pair <std::string,int> i,std::pair <std::string,int> j) {
    return (i.second > j.second);
}

bool UC_ (std::pair <std::string,int> i,std::pair <std::string,int> j) {
    for(int it = 0; it < 8; it++){
        if(int(i.first[it]) != int(j.first[it])) return int(i.first[it]) < int(j.first[it]);
        else continue;
    }
    return true;
}

bool in(std::string a, std::vector<std::string> b){
    for (int i = 0; i < b.size(); ++i) {
        if( a == b[i]){
            return true;
        }
    }
    return false;
}

void GestaoHorario::ocupacao() {
    std::string x;
    do{
        std::cout << "\n"
                     "  +----------------------------------------------+\n"
                     "  | [1] Ocupação de uma UC                       |\n"
                     "  | [2] Ocupação de uma turma                    |\n"
                     "  | [3] Ocupação de um ano                       |\n"
                     "  | [V] Voltar                                   |\n"
                     "  |______________________________________________|"  << std::endl;
    std::cout << "\n";
    std::cout << "   Escreva aqui a sua opção: ";
    std::cin >> x;
    std::cout << "\n";

    if (x == "1") {
        std::vector<std::pair<std::string, int>> numdealunos;
        for (Estudante f: m_estudantes) {
            bool lock = true;
            for (TurmaUc i: f.get_turmasUc()) {
                for (int it = 0; it < numdealunos.size(); it++) {
                    if (i.getCodigoUc() == numdealunos[it].first) {
                        numdealunos[it].second += 1;
                        lock = false;
                    }
                }
                if (lock) {
                    std::pair<std::string, int> add(i.getCodigoUc(), 1);
                    numdealunos.push_back(add);
                }
            }
        }
        std::string tipo;
        do {
            std::cout << "\n";
            std::cout << "  +----------------------------------------------+\n"
                         "  | [D] Decrescente                              |\n"
                         "  | [C] Crescente                                |\n"
                         "  | [U] Por UC                                   |\n"
                         "  |______________________________________________|"  << std::endl;
            std::cout << "\n";
            std::cout << "   Escolha o Tipo de Sort: ";
            std::cin >> tipo;
            std::cout << "\n";

            if (tipo == "D") {
                std::sort(numdealunos.begin(), numdealunos.end(), decrescente);
                for (std::pair<std::string, int> it: numdealunos) {
                    std::cout << it.first << " - " << it.second << "\n";
                }
                break;

            } else if (tipo == "C") {
                std::sort(numdealunos.begin(), numdealunos.end(), crescente);
                for (std::pair<std::string, int> it: numdealunos) {
                    std::cout << it.first << " - " << it.second << "\n";
                }
                break;

            } else if (tipo == "U") {
                std::sort(numdealunos.begin(), numdealunos.end(), UC_);
                for (std::pair<std::string, int> it: numdealunos) {
                    std::cout << it.first << " - " << it.second << "\n";
                }
                break;
            }
            else{
                std::cout<< "O input é inválido, por favor tente outra vez! \n";
                std::cout << "\n";
            }
        }while(true);
        break;
    } else if (x == "3") {
        std::vector<std::pair<std::string, int>> numdealunos;
        std::pair<std::string, int> add1("1 ano", 0);
        std::pair<std::string, int> add2("2 ano", 0);
        std::pair<std::string, int> add3("3 ano", 0);
        numdealunos.push_back(add1);
        numdealunos.push_back(add2);
        numdealunos.push_back(add3);

        for (Estudante f: m_estudantes) {
            bool lock1 = true;
            bool lock2 = true;
            bool lock3 = true;
            for (TurmaUc i: f.get_turmasUc()) {
                if (i.getCodigoTurma()[0] == '1' && lock1) {
                    numdealunos[0].second += 1;
                    lock1 = false;
                }
                if (i.getCodigoTurma()[0] == '2' && lock2) {
                    numdealunos[1].second += 1;
                    lock2 = false;
                }
                if (i.getCodigoTurma()[0] == '3' && lock3) {
                    numdealunos[2].second += 1;
                    lock3 = false;
                }
            }
        }

        std::string tipo;
    do{
        std::cout << "\n";
        std::cout << "  +----------------------------------------------+\n"
                     "  | [D] Decrescente                              |\n"
                     "  | [C] Crescente                                |\n"
                     "  |______________________________________________|"  << std::endl;
        std::cout << "\n";
        std::cout << "   Escolha o Tipo de Sort: ";
        std::cin >> tipo;

        std::cout << "\n";

        if (tipo == "D") {
            std::sort(numdealunos.begin(), numdealunos.end(), decrescente);
            for (std::pair<std::string, int> it: numdealunos) {
                std::cout << it.first << " - " << it.second << "\n";
            }
            break;
        } else if (tipo == "C") {
            std::sort(numdealunos.begin(), numdealunos.end(), crescente);
            for (std::pair<std::string, int> it: numdealunos) {
                std::cout << it.first << " - " << it.second << "\n";
            }
            break;
        }
        else{
            std::cout<< "O input é inválido, por favor tente outra vez! \n";
            std::cout << "\n";
        }

    }while(true);
        break;
    } else if (x == "2") {
        std::vector<std::pair<std::string, int>> numdealunos;
        std::vector<std::string> locklist;
        for (Estudante f: m_estudantes) {
            locklist.clear();
            for (TurmaUc i: f.get_turmasUc()) {
                for (int it = 0; it < numdealunos.size(); it++) {
                    if (i.getCodigoTurma() == numdealunos[it].first && (not in(i.getCodigoTurma(), locklist))) {
                        numdealunos[it].second += 1;
                        locklist.push_back(numdealunos[it].first);
                    }
                }
                if (not in(i.getCodigoTurma(), locklist)) {
                    std::pair<std::string, int> add(i.getCodigoTurma(), 1);
                    numdealunos.push_back(add);
                }
            }
        }

        std::string tipo;
        do {
            std::cout << "\n";
            std::cout << "  +----------------------------------------------+\n"
                         "  |  [D] Decrescente                             |\n"
                         "  |  [C] Crescente                               |\n"
                         "  |  [T] Por Turma                               |\n"
                         "  |______________________________________________|\n" << std::endl;
            std::cout << "\n";
            std::cout << "   Escolha o Tipo de Sort: ";
            std::cin >> tipo;
            std::cout << "\n";

            if (tipo == "D") {
                std::sort(numdealunos.begin(), numdealunos.end(), decrescente);
                for (std::pair<std::string, int> it: numdealunos) {
                    std::cout << it.first << " - " << it.second << "\n";
                }
                break;

            } else if (tipo == "C") {
                std::sort(numdealunos.begin(), numdealunos.end(), crescente);
                for (std::pair<std::string, int> it: numdealunos) {
                    std::cout << it.first << " - " << it.second << "\n";
                }
                break;

            } else if (tipo == "T") {
                std::sort(numdealunos.begin(), numdealunos.end(), UC_);
                for (std::pair<std::string, int> it: numdealunos) {
                    std::cout << it.first << " - " << it.second << "\n";
                }
                break;
            }
            else{
                std::cout<< "O input é inválido, por favor tente outra vez! \n";
                std::cout << "\n";
            }
        }while(true);
        break;
    } else if (x == "V" || x == "v") {
        interfaceUtilizador();
        break;

    }
    else{
        std::cout<< "O input é inválido, por favor tente outra vez! \n";
        std::cout << "\n";
    }
    }while(true);
    }

void GestaoHorario::horarioTurma() {
    std::cout << "   Horário de determinada turma" << std::endl;

    int a, t;
    std::string str;

    do {
        std::cout << "   Escolha o número do ano (1 a 3), do qual pertence a turma em questão: ";
        std::cin >> a;

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if (a < 1 || a > 3) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            continue;
        }

        secondChoice:
        std::cout << "   Escolha o número da turma (1 a 16), da qual pretende saber o horário: ";
        std::cin >> t;

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto secondChoice;
        }
        else if (t < 1 || t > 16) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            goto secondChoice;
        }
        break;
    } while (true);

    if (t < 10) {str = std::to_string(a) + "LEIC0" + std::to_string(t);}
    else {str = std::to_string(a) + "LEIC" + std::to_string(t);}

std::cout << "\n";
    std::cout << char(201) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(187)  <<std::endl;
    std::cout << char(186)<<"                                            Horario do Turma " << str << "                                                 "<<char(186) <<std::endl;
    std::cout << char(204) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(203) <<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)  <<  char(205)  <<  char(205)  <<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(185)  <<std::endl;
    std::cout << char(186)<< "    Dia da semana   "<<char(186)<<"     Codigo da UC    "<<char(186)<<"      Hora de Inicio      "<<char(186)<<"    Hora do fim    "<<char(186)<<"     Duracao     "<<char(186)<<"   Tipo  "<<char(186) <<std::endl;
    std::cout <<  char(204) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205) <<char (205)<<char (206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(185) << std::endl;

    for (Turma horario : m_horario) {
        if (horario.getturmauc().getCodigoTurma() == str) {
            std::list<Slot> lst = horario.gethorarioturma();
            for (Slot slt : lst) {
                 if(slt.get_diaSemana()=="Friday" || slt.get_diaSemana()=="Monday" ) {
                            std::cout << char(186) <<"       " << slt.get_diaSemana() << "       "<< char(186)<< std::left << std::setw(21)
                                                                                   << horario.getturmauc().getCodigoUc() << char(186)<< std::left << std::setw(26) << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                                                                   << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() <<  char(186)<< std::left << std::setw(9)
                                                                                   << slt.get_tipo() <<  char(186) << "\n";
                        }
                        if(slt.get_diaSemana()=="Wednesday"  ) {
                            std::cout << char(186)<< "      " << slt.get_diaSemana() <<  "     "<< char(186)<< std::left << std::setw(21)
                                                                        << horario.getturmauc().getCodigoUc() <<  char(186)<< std::left << std::setw(26) << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                                                        << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() << char(186)<< std::left << std::setw(9)
                                                                        << slt.get_tipo() <<  char(186) << "\n";
                        }
                        if(slt.get_diaSemana()=="Tuesday"  ) {
                            std::cout << char(186) << "       " << slt.get_diaSemana() << "      "<< char(186)<< std::left << std::setw(21)
                                      << horario.getturmauc().getCodigoUc() <<  char(186)<< std::left << std::setw(26) << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                      << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() << char(186)<< std::left << std::setw(9)
                                      << slt.get_tipo() <<  char(186) << "\n";
                        }
                        if(slt.get_diaSemana()=="Thursday"  ) {
                            std::cout << char(186)<<"      " << slt.get_diaSemana() << "      "<< char(186)<< std::left << std::setw(21)
                                                                        << horario.getturmauc().getCodigoUc() << char(186)<< std::left << std::setw(26) << slt.get_horaInicio() << char(186)<< std::left << std::setw(19)
                                                                        << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() <<  char(186)<< std::left << std::setw(9)
                                                                        << slt.get_tipo() << char(186) << "\n";
                        }
            }
        }
        else {continue;}
    }
    std::cout <<  char(200) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205) <<char (205)<<char (202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(188) << std::endl;
}

void GestaoHorario::listagemEstudantes() {
    int opc;

    std::cout << "\n";
    std::cout << "  +----------------------------------------------+\n"
                 "  | Pretende saber a lista de estudantes por:    |\n"
                 "  +----------------------------------------------+\n"
                 "  | [1] Turma                                    |\n"
                 "  | [2] UC                                       |\n"
                 "  | [3] Ano                                      |\n"
                 "  |______________________________________________|"<< std::endl;
    std::cout << "\n";

    do {
        std::cout << "\n";
        std::cout << "   Escolha o número da opção que pretende: ";
        std::cin >> opc;
        std::cout << "\n";

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } else if (opc < 1 || opc > 3) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            continue;
        }
        break;
    } while (true);

    if (opc == 1) {
        int a, t;
        std::string str;

        do {
            std::cout << "   Escolha o número do ano (1 a 3), do qual pertence a turma em questão: ";
            std::cin >> a;
            std::cout << "\n";

            if (!std::cin) {
                std::cout << "É esperado um valor numérico" << std::endl << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else if (a < 1 || a > 3) {
                std::cout << "Valor fora de alcance" << std::endl << std::endl;
                continue;
            }

            secondChoice:
            std::cout << "   Escolha o número da turma (1 a 16), da qual pretende saber a lista de estudantes : ";
            std::cin >> t;

            if (!std::cin) {
                std::cout << "É esperado um valor numérico" << std::endl << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                goto secondChoice;
            }
            else if (t < 1 || t > 16) {
                std::cout << "Valor fora de alcance" << std::endl << std::endl;
                goto secondChoice;
            }
            break;
        } while (true);

        if (t < 10) {str = std::to_string(a) + "LEIC0" + std::to_string(t);}
        else {str = std::to_string(a) + "LEIC" + std::to_string(t);}

        std::set<Estudante> s;

        for (Estudante e : m_estudantes) {
            for (TurmaUc t : e.get_turmasUc()) {
                if (t.getCodigoTurma() == str) {
                    s.insert(e);
                }
            }
        }

        std::cout << "\n";
        for (auto est : s) {
            std::cout << est << std::endl;
        }
    }

    else if (opc == 2) {
        int u;
        std::string str;

        do {
            std::cout << "   Escolha o número da UC que pretende de 1 a 25 (0 para Projeto UP): ";
            std::cin >> u;

            if (!std::cin) {
                std::cout << "É esperado um valor numérico" << std::endl << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            } else if (u < 0 || u > 25) {
                std::cout << "Valor fora de alcance" << std::endl << std::endl;
                continue;
            }
            else if(( (u > 5 && u < 15) || (u>15 && u<25))){
                std::cout << "Essa UC não se encontra nos dados" << std::endl << std::endl;
                continue;
            }
            break;
        } while(true);

        if (u < 10 && u != 0) {str = "L.EIC00" + std::to_string(u);}
        else if (u==0) {str = "UP001";}
        else {str = "L.EIC0" + std::to_string(u);}

        std::set<Estudante> s;

        for (Estudante e : m_estudantes) {
            for (TurmaUc t : e.get_turmasUc()) {
                if (t.getCodigoUc() == str) {
                    s.insert(e);
                }
            }
        }

        for (auto est : s) {
            std::cout << est << std::endl;
        }
    }

    else if (opc == 3) {
        int a;
        std::string str;

        std::set<Estudante> s;

        do {
            std::cout << "   Escolha o número do ano que pertence (1 a 3): ";
            std::cin >> a;

            if (!std::cin) {
                std::cout << "É esperado um valor numérico" << std::endl << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else if (a < 1 || a > 3) {
                std::cout << "Valor fora de alcance" << std::endl << std::endl;
                continue;
            }
            break;
        } while(true);

        for (int t = 1; t < 17; t++) {
            if (t < 10) {
                str = std::to_string(a) + "LEIC0" + std::to_string(t);

                for (Estudante e : m_estudantes) {
                    for (TurmaUc t : e.get_turmasUc()) {
                        if (t.getCodigoTurma() == str) {
                            s.insert(e);
                        }
                    }
                }
            }
            else {
                str = std::to_string(a) + "LEIC" + std::to_string(t);

                for (Estudante e : m_estudantes) {
                    for (TurmaUc t : e.get_turmasUc()) {
                        if (t.getCodigoTurma() == str) {
                            s.insert(e);
                        }
                    }
                }
            }
        }

        for (auto est : s) {
            std::cout << est << std::endl;
        }
    }
}

void GestaoHorario::listagemTurmasEEstudantes() {
    int u, opc;
    std::string str;

    do {
        std::cout << "   Escolha o número da UC que pretende de 1 a 25 (0 para Projeto UP): ";
        std::cin >> u;

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if (u < 0 || u > 25) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            continue;
        }
        else if(( (u > 5 && u < 15) || (u>15 && u<25))){
            std::cout << "Essa UC não se encontra nos dados" << std::endl << std::endl;
            continue;
        }
        break;
    } while(true);

    if (u < 10 && u !=0) {str = "L.EIC00" + std::to_string(u);}
    else if(u==0){str= "UP001";}
    else {str = "L.EIC0" + std::to_string(u);}

    std::cout << "\n";
    std::cout << "  +----------------------------------------------+\n"
                 "  | Pretende saber ________ que têm a UC:        |\n"
                 "  +----------------------------------------------+\n"
                 "  | [1] Turmas                                   |\n"
                 "  | [2] Estudantes de uma turma em concreto      |\n"
                 "  |______________________________________________|"<< std::endl;
    std::cout << "\n";

    do {
        std::cout << "   Escolha o número da opção que pretende: ";
        std::cin >> opc;

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if (opc < 1 || opc > 2) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            continue;
        }
        break;
    } while (true);

    std::cout << "\n";
    if (opc == 1) {
        std::set<std::string> s;
        for (TurmaUc turmaUc : m_codigosTU) {
            if (str == turmaUc.getCodigoUc()) {
                s.insert(turmaUc.getCodigoTurma());
            }
        }

        if (s.size() != 0) {
            for (auto el : s) {
                std::cout << el << std::endl;
            }
        }
        else if ((s.size() == 0) && ((u >= 7 && u <= 10) || (u >= 16 && u <= 20))){std::cout << "Esta UC não se encontra nos ficheiros de dados fornecidos!" << std::endl;}
    }

    else if (opc == 2) {
        int a, t;
        std::string strng;
        std::set<Estudante> s;

        do {
            std::cout << "   Escolha o número do ano (1 a 3), do qual pertence a turma em questão: ";
            std::cin >> a;

            if (!std::cin) {
                std::cout << "É esperado um valor numérico" << std::endl << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else if (a < 1 || a > 3) {
                std::cout << "Valor fora de alcance" << std::endl << std::endl;
                continue;
            }


            secondChoice:
            std::cout << "   Escolha o número da turma (1 a 16), da qual pretende saber a lista de estudantes: ";
            std::cin >> t;

            if (!std::cin) {
                std::cout << "É esperado um valor numérico" << std::endl << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                goto secondChoice;
            }
            else if (t < 1 || t > 16) {
                std::cout << "Valor fora de alcance" << std::endl << std::endl;
                goto secondChoice;
            }
            break;
        } while (true);

        std::cout << "\n";

        if (t < 10) {strng = std::to_string(a) + "LEIC0" + std::to_string(t);}
        else {strng = std::to_string(a) + "LEIC" + std::to_string(t);}

        for (Estudante e : m_estudantes) {
            for (TurmaUc t : e.get_turmasUc()) {
                if ((t.getCodigoTurma() == strng) && (str == t.getCodigoUc())) {
                    s.insert(e);
                }
            }
        }

        if (s.size() != 0) {
            for (auto el : s) {
                std::cout << el << std::endl;
            }
        }
        else if ((s.size() == 0) && ((u >= 7 && u <= 10) || (u >= 16 && u <= 20))){std::cout << "Esta UC não se encontra nos ficheiros de dados fornecidos!" << std::endl;}
        else {std::cout << "Esta turma em concreto não tem esta UC!" << std::endl;}
    }
}

void GestaoHorario::estudanteMaisNUc() {

    std::cout << "   Estudantes com mais de n Ucs" << std::endl << std::endl;

    int n;
    bool keepTrying1;
    do {
        keepTrying1 = false;
        std::cout << "   Escolha um número de entre os valores possíveis (0 a 6): ";
        std::cin >> n;
        if (!std::cin){
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            keepTrying1 = true;
        }
        else if (n<0 || n>6){
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            keepTrying1 = true;
        }
    } while (keepTrying1);

    std::cout << std::endl << std::endl;

    int ordenacao;
    bool keepTrying2;
    do {
        keepTrying2 = false;
        std::cout << "\n";
        std::cout << "  +----------------------------------------------+\n"
                     "  | [1] Alfabética                               |\n"
                     "  | [2] Código de estudante                      |\n"
                     "  | [3] Número de Ucs                            |\n"
                     "  |______________________________________________|"<<std::endl;

        std::cout << "\n";
        std::cout << "   Escolha um tipo de ordenação (1 a 3): " ;
        std::cin >> ordenacao;
        std::cout << "\n";
        if (!std::cin){
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            keepTrying2 = true;
        }
        else if (ordenacao < 1 || ordenacao > 3){
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            keepTrying2 = true;
        }
    } while (keepTrying2);

    std::cout << std::endl << std::endl;

    int formato;
    bool keepTrying3;
    do {
        keepTrying3 = false;

        std::cout << "\n";
        std::cout << "  +----------------------------------------------+\n"
                     "  |[1]Crescente                                  |\n"
                     "  |[2]Decrescente                                |\n"
                     "  |______________________________________________|\n";
        std::cout << "\n";

        std::cout << "   Escolha um formato para a ordenação (1 ou 2): " ;
        std::cin >> formato;
        std::cout << "\n";
        if (!std::cin){
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            keepTrying3 = true;
        }
        else if (formato < 1 || formato > 2){
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            keepTrying3 = true;
        }
    } while (keepTrying3);


    if (ordenacao == 1){

        if (formato == 1) {

            std::set<Estudante> estudantesAceites;

            for (Estudante estudante : m_estudantes) {
                size_t numeroUcs = estudante.get_turmasUc().size();
                if (numeroUcs > n) estudantesAceites.insert(estudante);
            }
            for (const Estudante& estudanteAceite : estudantesAceites) {
                std::cout << estudanteAceite << std::endl;
            }

        }
        else if (formato == 2){

            auto cmp = [](Estudante a, Estudante b) { return a.getNome() >= b.getNome(); };
            std::set<Estudante, decltype(cmp)> estudantesAceites(cmp);

            for (Estudante estudante : m_estudantes) {
                size_t numeroUcs = estudante.get_turmasUc().size();
                if (numeroUcs > n) estudantesAceites.insert(estudante);
            }
            for (const Estudante& estudanteAceite : estudantesAceites) {
                std::cout << estudanteAceite << std::endl;
            }
        }
    }

    else if(ordenacao == 2){

        if(formato == 1){

            auto cmp = [](Estudante a, Estudante b) { return std::stoi(a.get_num()) <= std::stoi(b.get_num()); };
            std::set<Estudante, decltype(cmp)> estudantesAceites(cmp);

            for (Estudante estudante : m_estudantes) {
                size_t numeroUcs = estudante.get_turmasUc().size();
                if (numeroUcs > n) estudantesAceites.insert(estudante);
            }
            for (const Estudante& estudanteAceite : estudantesAceites) {
                std::cout << estudanteAceite << std::endl;
            }

        }
        else if (formato == 2){

            auto cmp = [](Estudante a, Estudante b) { return std::stoi(a.get_num()) >= std::stoi(b.get_num()); };
            std::set<Estudante, decltype(cmp)> estudantesAceites(cmp);

            for (Estudante estudante : m_estudantes) {
                size_t numeroUcs = estudante.get_turmasUc().size();
                if (numeroUcs > n) estudantesAceites.insert(estudante);
            }
            for (const Estudante& estudanteAceite : estudantesAceites) {
                std::cout << estudanteAceite << std::endl;
            }
        }
    }

    else if (ordenacao == 3){

        if(formato == 1){

            auto cmp = [](Estudante a, Estudante b) { return a.get_turmasUc().size() <= b.get_turmasUc().size(); };
            std::set<Estudante, decltype(cmp)> estudantesAceites(cmp);

            for (Estudante estudante : m_estudantes) {
                size_t numeroUcs = estudante.get_turmasUc().size();
                if (numeroUcs > n) estudantesAceites.insert(estudante);
            }
            for (const Estudante& estudanteAceite : estudantesAceites) {
                std::cout << estudanteAceite << std::endl;
            }

        }
        else if (formato == 2){

            auto cmp = [](Estudante a, Estudante b) { return a.get_turmasUc().size() >= b.get_turmasUc().size(); };
            std::set<Estudante, decltype(cmp)> estudantesAceites(cmp);

            for (Estudante estudante : m_estudantes) {
                size_t numeroUcs = estudante.get_turmasUc().size();
                if (numeroUcs > n) estudantesAceites.insert(estudante);
            }
            for (const Estudante& estudanteAceite : estudantesAceites) {
                std::cout << estudanteAceite << std::endl;
            }
        }
    }
}

void GestaoHorario::turmastodas(){
    std::set<std::string> codturmas;
    for(int i =0; i<m_codigosTU.size() ;i++){
        codturmas.insert(m_codigosTU[i].getCodigoTurma());
    }
    for(auto i :codturmas){
       std::cout << i << "\n";
    }
}

void GestaoHorario::ucstodas(){
    std::set<std::string> codturmas;
    for(int i =0; i<m_codigosTU.size() ;i++){
        codturmas.insert(m_codigosTU[i].getCodigoUc());
    }
    for(auto i :codturmas){
        std::cout << i << "\n";
    }
}

void GestaoHorario::todosestudantes(){
    for(auto i :m_codigosEstudante){
        std::cout << i.getCodigoEstudante() << " - " << i.getNome() << "\n";
    }
}

void GestaoHorario::horarioturmauc(){
    int a, t;
    std::string s;

    do {
        std::cout << "   Escolha o número do ano (1 a 3), do qual pertence a turma em questão: ";
        std::cin >> a;

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if (a < 1 || a > 3) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            continue;
        }

        secondChoice:
        std::cout << "   Escolha o número da turma (1 a 16), da qual pretende saber a lista de estudantes : ";
        std::cin >> t;

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto secondChoice;
        }
        else if (t < 1 || t > 16) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            goto secondChoice;
        }
        break;
    } while (true);

    if (t < 10) {s = std::to_string(a) + "LEIC0" + std::to_string(t);}
    else {s = std::to_string(a) + "LEIC" + std::to_string(t);}


    int b;
    std::string str;

    do {
        std::cout << "   Escolha o número da UC que pretende de 1 a 25 (0 para Projeto UP): ";
        std::cin >> b;

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } else if ((b < 0) || b>25 ) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            continue;
        }
        else if(( (b > 5 && b < 15) || (b>15 && b<25))){
            std::cout << "Essa UC não se encontra nos dados" << std::endl << std::endl;
            continue;
        }
        break;
    } while(true);

    if (b < 10 && b != 0 ) {str = "L.EIC00" + std::to_string(b);}
    else if(b ==0){ str ="UP001";}
    else {str = "L.EIC0" + std::to_string(b);}



std::cout << "\n";

    std::cout << char(201) << char(205) <<  char(205) <<  char(205)<<  char(205)<<  char(205)<<  char(205)<< char(205)<< char(205)<<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(187)  <<std::endl;
    std::cout << char(186)<<"                            Horario da UC " << str << " da Turma "<< s<<"                            "<<char(186) <<std::endl;
    std::cout << char(204) <<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(203) <<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)  <<  char(205)  <<  char(205)  <<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(185)  <<std::endl;
    std::cout << char(186)<< "    Dia da semana   " <<char(186)<< "      Hora de Inicio      "<<char(186)<<"    Hora do fim    "<<char(186)<<"     Duracao     "<<char(186)<<"   Tipo  "<<char(186) <<std::endl;
    std::cout <<  char(204) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char (206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(185) << std::endl;


    for (Turma horario : m_horario) {
        if (horario.getturmauc().getCodigoTurma() == s) {
            std::list<Slot> lst = horario.gethorarioturma();
            for (Slot slt : lst) {
                if (horario.getturmauc().getCodigoUc()==str) {
                    if(slt.get_diaSemana()=="Friday" || slt.get_diaSemana()=="Monday" ) {
                        std::cout << char(186) <<"       " << slt.get_diaSemana() << "       "<< char(186)<< std::left << std::setw(26)
                                  << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                  << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() <<  char(186)<< std::left << std::setw(9)
                                  << slt.get_tipo() <<  char(186) << "\n";
                    }
                    if(slt.get_diaSemana()=="Wednesday"  ) {
                        std::cout << char(186)<< "      " << slt.get_diaSemana() <<  "     "<< char(186)<< std::left << std::setw(26)
                                  << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                  << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() << char(186)<< std::left << std::setw(9)
                                  << slt.get_tipo() <<  char(186) << "\n";
                    }
                    if(slt.get_diaSemana()=="Tuesday"  ) {
                        std::cout << char(186) << "       " << slt.get_diaSemana() << "      "<< char(186)<< std::left << std::setw(26)
                                  << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                                  << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() << char(186)<< std::left << std::setw(9)
                                  << slt.get_tipo() <<  char(186) << "\n";
                    }
                    if(slt.get_diaSemana()=="Thursday"  ) {
                        std::cout << char(186)<<"      " << slt.get_diaSemana() << "      "<< char(186)<< std::left << std::setw(26)
                                  << slt.get_horaInicio() << char(186)<< std::left << std::setw(19)
                                  << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() <<  char(186)<< std::left << std::setw(9)
                                  << slt.get_tipo() << char(186) << "\n";
                    }
                }
            }
        }
        else {continue;}
    }
    std::cout <<  char(200) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205) << char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(188) << std::endl;

}

void GestaoHorario::horariouc(){
    int a;
    std::string str;

    do {
        std::cout << "   Escolha o número da UC que pretende de 1 a 25 (0 para Projeto UP): ";
        std::cin >> a;

        if (!std::cin) {
            std::cout << "É esperado um valor numérico" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if ( (a > 5 && a < 15) || (a>15 && a<25)) {std::cout << "Esta UC não se encontra nos ficheiros de dados fornecidos!" << std::endl  << std::endl ; continue;}
        else if (a < 0 || a > 25) {
            std::cout << "Valor fora de alcance" << std::endl << std::endl;
            continue;
        }
        break;
    } while(true);



    if (a < 10 && a !=0) {str = "L.EIC00" + std::to_string(a);}
    else if(a==0){str="UP001";}
    else {str = "L.EIC0" + std::to_string(a);}

    std::cout << "\n";
    std::cout << char(201) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(187)  <<std::endl;
    std::cout << char(186)<<"                                               Horario da UC " << str << "                                                "<<char(186) <<std::endl;
    std::cout << char(204) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(203) <<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205)<<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)  <<  char(205)  <<  char(205)  <<  char(205) <<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205)<<  char(205) <<  char(203) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(205) <<  char(185)  <<std::endl;
    std::cout << char(186)<< "    Dia da semana   "<<char(186)<<"   Codigo da Turma   "<<char(186)<<"      Hora de Inicio      "<<char(186)<<"    Hora do fim    "<<char(186)<<"     Duracao     "<<char(186)<<"   Tipo  "<<char(186) <<std::endl;
    std::cout <<  char(204) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205) <<char (205)<<char (206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(206)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(185) << std::endl;


    for (Turma horario : m_horario) {
        if (horario.getturmauc().getCodigoUc() == str) {
            std::list<Slot> lst = horario.gethorarioturma();
            for (Slot slt : lst) {
                if(slt.get_diaSemana()=="Friday" || slt.get_diaSemana()=="Monday" ) {
                    std::cout << char(186) <<"       " << slt.get_diaSemana() << "       "<< char(186)<< std::left << std::setw(21)
                              << horario.getturmauc().getCodigoTurma() << char(186)<< std::left << std::setw(26) << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                              << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() <<  char(186)<< std::left << std::setw(9)
                              << slt.get_tipo() <<  char(186) << "\n";
                }
                if(slt.get_diaSemana()=="Wednesday"  ) {
                    std::cout << char(186)<< "      " << slt.get_diaSemana() <<  "     "<< char(186)<< std::left << std::setw(21)
                              << horario.getturmauc().getCodigoTurma() <<  char(186)<< std::left << std::setw(26) << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                              << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() << char(186)<< std::left << std::setw(9)
                              << slt.get_tipo() <<  char(186) << "\n";
                }
                if(slt.get_diaSemana()=="Tuesday"  ) {
                    std::cout << char(186) << "       " << slt.get_diaSemana() << "      "<< char(186)<< std::left << std::setw(21)
                              << horario.getturmauc().getCodigoTurma() <<  char(186)<< std::left << std::setw(26) << slt.get_horaInicio() <<  char(186)<< std::left << std::setw(19)
                              << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() << char(186)<< std::left << std::setw(9)
                              << slt.get_tipo() <<  char(186) << "\n";
                }
                if(slt.get_diaSemana()=="Thursday"  ) {
                    std::cout << char(186)<<"      " << slt.get_diaSemana() << "      "<< char(186)<< std::left << std::setw(21)
                              << horario.getturmauc().getCodigoTurma() << char(186)<< std::left << std::setw(26) << slt.get_horaInicio() << char(186)<< std::left << std::setw(19)
                              << slt.get_horaInicio() + slt.get_duracao() <<  char(186)<< std::left << std::setw(17) << slt.get_duracao() <<  char(186)<< std::left << std::setw(9)
                              << slt.get_tipo() << char(186) << "\n";
                }
            }
        }
        else {continue;}
    }

   std::cout <<  char(200) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202) << char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205) <<char (205)<<char (202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(202)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(205)<< char(188) << std::endl;

}

// ------------------------------INTERFACE DO UTILIZADOR---------------------------------------------------------------------

void GestaoHorario::interfaceUtilizador() {
    char opc,opc1;
    std::string str;
    do {


        std::cout<< "  __  __ ______ _   _ _    _\n"
                   " |  \\/  |  ____| \\ | | |  | |\n"
                   " | \\  / | |__  |  \\| | |  | |\n"
                   " | |\\/| |  __| | . ` | |  | |\n"
                   " | |  | | |____| |\\  | |__| |\n"
                   " |_|  |_|______|_| \\_|\\____/" << std::endl;
        std::cout << "\n";
        std::cout << "\n";

        std::cout << "  +----------------------------------------------+\n"
                     "  | Pretende realizar um(a):                     |\n"
                     "  +----------------------------------------------+\n"
                     "  | [1] Listagens                                |\n"
                     "  | [2] Pedidos                                  |\n"
                     "  | [Q] Sair                                     |\n"
                     "  |______________________________________________|"<< std::endl;
        std::cout << "\n";
        std::cout << "   Escreva aqui a sua opção: ";
        std::cin >> opc;
        std::cout << "\n";

        if (opc == '1') {
            do {
                std::cout << "\n";
                std::cout << "  +----------------------------------------------+\n"
                             "  |Pretende obter informações sobre:             |\n"
                             "  +----------------------------------------------+\n"
                             "  | [1] Estudante                                |\n"
                             "  | [2] Turma                                    |\n"
                             "  | [3] UC                                       |\n"
                             "  | [V] Voltar ao Menu                           |\n"
                             "  |______________________________________________|"<< std::endl;
                std::cout << "\n";
                std::cout << "   Escreva aqui a sua opção: ";
                std::cin >> opc1;
                std::cout << "\n";
                if (opc1 == '1') {
                    menuEstudante();
                    break;
                }
                else if (opc1 == '2') {
                    menuTurma();
                    break;
                }
                else if (opc1 == '3') {
                    menuUC();
                    break;
                }
               else if (opc1 == 'V' || opc1 == 'v') {
                    interfaceUtilizador();
                    break;
                }
               else{
                   std::cout<< "O input é inválido, por favor tente outra vez! \n";
                    std::cout << "\n";
               }
            }while(true);
            break;
        }

        //else if(opc=='2'){}
        else if (opc == 'Q' || opc=='q' ) { return; }
        else{
            std::cout<< "O input é inválido, por favor tente outra vez! \n";
            std::cout << "\n";
        }
    }while(true);
    }

void GestaoHorario::menuEstudante(){
    char opc,opc1;
    do {
        std::cout << "\n";
        std::cout << "  +----------------------------------------------+\n"
                     "  | [1] Horário Estudante                        |\n"
                     "  | [2] Listar Estudantes                        |\n"
                     "  | [3] Ocupação                                 |\n"
                     "  | [V] Voltar ao Menu                           |\n"
                     "  |______________________________________________|"<< std::endl;
        std::cout << "\n";
        std::cout << "   Escreva aqui a sua opção: ";
        std::cin >> opc;
        std::cout << "\n";

        if (opc == '1') {
            horarioEstudante();
            voltarmenu();
            break;
        }
        else if (opc == '2') {
            do {
                std::cout << "\n";
                std::cout << "  +----------------------------------------------+\n"
                             "  | [1] Ano/Turma/UC                             |\n"
                             "  | [2] Com mais de N UC's                       |\n"
                             "  | [3] Todos                                    |\n"
                             "  | [V] Voltar ao Menu                           |\n"
                             "  |______________________________________________|"<< std::endl;
                std::cout << "\n";
                std::cout << "   Escreva aqui a sua opção: ";
                std::cin >> opc1;
                std::cout << "\n";
                if (opc1 == '1') {
                    listagemEstudantes();
                    voltarmenu();
                    break;
                }
                else if (opc1 == '2') {
                    estudanteMaisNUc();
                    voltarmenu();
                    break;
                }
                else if (opc1 == '3') {
                    todosestudantes();
                    voltarmenu();
                    break;
                }
                else if (opc1 == 'V' || opc1 == 'v') {
                    interfaceUtilizador();
                    break;
                }
                else{
                    std::cout<< "O input é inválido, por favor tente outra vez! \n";
                    std::cout << "\n";
                }
            }while(true);
            break;
        }
        else if (opc == '3') {
            ocupacao();
            voltarmenu();
            break;
        }
        else if (opc == 'V' || opc == 'v') {
            interfaceUtilizador();
            break;
        }
        else{
            std::cout<< "O input é inválido, por favor tente outra vez! \n";
            std::cout << "\n";
        }
    }while(true);
}


void GestaoHorario::menuTurma(){
    char opc;
    do {
        std::cout << "\n";
        std::cout << "  +----------------------------------------------+\n"
                     "  | [1] Horário Turma                            |\n"
                     "  | [2] Listar Turmas/Estudantes de uma turma    |\n"
                     "  | [3] Listar todas as turmas                   |\n"
                     "  | [4] Horários de Turma de uma UC              |\n"
                     "  | [V] Voltar ao Menu                           |\n"
                     "  |______________________________________________|"<< std::endl;
        std::cout << "\n";
        std::cout << "   Escreva aqui a sua opção: ";
        std::cin >> opc;
        std::cout << "\n";

        if (opc == '1') {
            horarioTurma();
            voltarmenu();
            break;
        }
        else if (opc == '2') {
            listagemTurmasEEstudantes();
            voltarmenu();
            break;
        }
        else if (opc == '3') {
            turmastodas();
            voltarmenu();
            break;
        }
        else if (opc == '4') {
            horarioturmauc();
            voltarmenu();
            break;
        }
        else if (opc == 'V' || opc == 'v') {
            interfaceUtilizador();
            break;
        }
        else{
            std::cout<< "O input é inválido, por favor tente outra vez! \n";
            std::cout << "\n";
        }
    }while(true);
}

void GestaoHorario::menuUC(){
    char opc;
    do {
        std::cout << "\n";
        std::cout << "  +----------------------------------------------+\n"
                     "  | [1] Listar todas as UC's                     |\n"
                     "  | [2] Horário de uma UC                        |\n"
                     "  | [V] Voltar ao Menu                           |\n"
                     "  |______________________________________________|" << std::endl;
        std::cout << "\n";
        std::cout << "   Escreva aqui a sua opção: ";
        std::cin >> opc;
        std::cout << "\n";

        if (opc == '1') {
            ucstodas();
            voltarmenu();
            break;
        }
        else if (opc == '2') {
            horariouc();
            voltarmenu();
            break;
        }
        else if (opc == 'V' || opc == 'v') {
            interfaceUtilizador();
            break;
        }
        else{
            std::cout<< "O input é inválido, por favor tente outra vez! \n";
            std::cout << "\n";
        }
    }while (true);
}

void GestaoHorario::voltarmenu(){
    char var;
    do {
        std::cout << "\n";
        std::cout << "Pressione V para voltar menu: ";
        std::cin >> var;
        std::cout << "\n";
        if (var == 'V' || var == 'v') {
            interfaceUtilizador();
            break;
        } else {
            std::cout << "O input é inválido, por favor tente outra vez! \n";
            std::cout << "\n";
        }
    }while(true);
}
