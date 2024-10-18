#include <iostream>
#include "include/GestaoHorario.h"
#include <algorithm>
#include "include/TurmaUc.h"

using namespace std;

int main() {

    GestaoHorario gestaoHorario;
    gestaoHorario.lerFicheiros();
    gestaoHorario.interfaceUtilizador();
    return 0;


}