cmake_minimum_required(VERSION 3.23)
project(Projeto_AED)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_AED main.cpp src/Aeroporto.cpp include/Aeroporto.h src/Coordenadas.cpp include/Coordenadas.h src/Geral.cpp include/Geral.h src/Airline.cpp include/Airline.h src/Voo.cpp include/Voo.h src/CsvLeitor.cpp include/CsvLeitor.h src/CsvLinha.cpp include/CsvLinha.h src/Graph.cpp include/Graph.h src/Cidade.cpp include/Cidade.h src/Ferramentas.cpp include/Ferramentas.h)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
