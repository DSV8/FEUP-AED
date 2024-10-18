cmake_minimum_required(VERSION 3.23)
project(Project_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_1 src/Slot.cpp include/Slot.h src/TurmaUc.cpp include/TurmaUc.h src/Estudante.cpp include/Estudante.h src/Turma.cpp include/Turma.h src/CsvLeitor.cpp include/CsvLeitor.h src/CsvLinha.cpp include/CsvLinha.h main.cpp src/GestaoHorario.cpp include/GestaoHorario.h src/Pedido.cpp include/Pedido.h src/CodigoNome.cpp include/CodigoNome.h)
