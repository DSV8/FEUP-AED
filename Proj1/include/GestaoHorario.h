//
// Created by dav on 10/19/22.
//

#ifndef PROJECT_1_GESTAOHORARIO_H
#define PROJECT_1_GESTAOHORARIO_H



#include "CsvLinha.h"
#include "CsvLeitor.h"
#include "TurmaUc.h"
#include "Estudante.h"
#include "Turma.h"
#include "Pedido.h"
#include "CodigoNome.h"
#include <set>
#include <vector>
#include <queue>

class GestaoHorario {

public:
    GestaoHorario();

    void lerFicheiros();

    std::vector<TurmaUc> getTurmasUc();
    std::vector<Turma> getHorario();
    std::set<Estudante> getEstudantes();
    std::queue<Pedido> getPedidos();


    // ---------------------------Estudante-----------------------------------------
    void horarioEstudante();
    void listagemEstudantes();
    void ocupacao();
    void estudanteMaisNUc();
    void todosestudantes();
    // ---------------------------UC-----------------------------------------
    void ucstodas();
    void horariouc();
    // ---------------------------Turma-----------------------------------------
    void horarioTurma();
    void listagemTurmasEEstudantes();
    void turmastodas();
    void horarioturmauc();



    // ------------------Interface-------------------------------------------------------------
    void interfaceUtilizador();
    void menuEstudante();
    void menuUC();
    void menuTurma();
    void voltarmenu();


private:
    std::vector<TurmaUc> m_codigosTU;
    std::vector<Turma> m_horario;
    std::set<CodigoNome> m_codigosEstudante;
    std::set<Estudante> m_estudantes;
    std::queue<Pedido> m_pedidos;

    void lerClassesPerUc();

    void lerClassesHelper(const TurmaUc& codigo);
    void lerClasses();

    void lerStudentIds();
    void lerStudentsClassesHelper(CodigoNome codigoNome);
    void lerStudentsClasses();
    bool contem(std::string x);
};



#endif //PROJECT_1_GESTAOHORARIO_H
