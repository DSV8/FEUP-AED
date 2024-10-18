//
// Created by gabri on 12/23/2022.
//

#include "../include/Geral.h"
#include "../include/Ferramentas.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <limits>
#include <map>
#include <set>
#include <queue>

Geral::Geral()= default;
/**
 * @brief Retorna o vetor de objetos da classe Airline armazenados na classe Geral.
 * @return vector
*/
std::vector<Airline> Geral::getairlines() const{
    return airlines;
}
/**
 * @brief Retorna o vetor de objetos da classe Voo armazenados na classe Geral.
 * @return vector
*/
std::vector<Voo> Geral::getvoos() const{
    return voos;
}
/**
 * @brief Retorna o mapa de objetos da classe Cidade armazenados na classe Geral, com a string do nome da cidade como chave.
 * @return unordered_map
*/
std::unordered_map<string, Cidade> Geral::getcidades() const{
    return cidades;
}

bool cmp(pair<string, int>& a, pair<string, int>& b){return a.second > b.second;}

vector<pair<string, int>> sort(map<string, int>& m) {
    vector<pair<string, int> > vec;

    for (auto& it : m) {vec.emplace_back(it);}
    sort(vec.begin(), vec.end(), cmp);
    return vec;
}
/**
 * @brief Lê os dados de aeroportos de um arquivo CSV e armazena em um vetor de Aeroporto.
 * @details Esta função lê o arquivo "../dados/airports.csv", usando a classe CsvLeitor para obter as linhas do arquivo em formato de vetor de CsvLinha. Em seguida, cria um objeto Coordenadas com as coordenadas geográficas de cada aeroporto e um objeto Aeroporto com as informações da linha. Adiciona cada objeto Aeroporto no vetor de Aeroporto e também adiciona o país de cada aeroporto a um conjunto de países. Além disso, adiciona o aeroporto à cidade correspondente em uma hashtable de Cidade, ou cria uma nova Cidade se ainda não existir na hashtable. Finalmente, adiciona o aeroporto ao grafo info.
 * @Complexity A complexidade deste codigo é O(n), onde n representa o numero de linhas do ficheiro airports.csv.
 * @return void
 */
void Geral::leraeroportos(){
    std::vector<CsvLinha> linhas = CsvLeitor::ler("../dados/airports.csv", true);

    for (CsvLinha linha : linhas) {
        string cityName = linha.getString(2);
        std::transform(cityName.begin(), cityName.end(), cityName.begin(), ::toupper);

        Coordenadas coordenadas(std::stof(linha.getString(4)),std::stof(linha.getString(5)));
        Aeroporto aeroporto(linha.getString(0), linha.getString(1), cityName, linha.getString(3),coordenadas);
        paises.insert(linha.getString(3));
        aeroportos.push_back(aeroporto);
        if(cidades.find(cityName) != cidades.end()){
            cidades[cityName].addaeroporto(aeroporto);
        }
        else{
            Cidade city(cityName,linha.getString(3));
            city.addaeroporto(aeroporto);
            cidades.insert({cityName, city});
        }
        info.addNode(aeroporto.getcodigo(),aeroporto);
    }
}

/**
 * @brief Lê os dados de companhias aéreas de um arquivo CSV e armazena em um vetor de Airline.
 * @details Esta função lê o arquivo "../dados/airlines.csv", usando a classe CsvLeitor para obter as linhas do arquivo em formato de vetor de CsvLinha. Em seguida, cria um objeto Airline para cada linha e adiciona no vetor de Airline. Além disso, adiciona o código e o nome de cada companhia aérea em conjuntos específicos.
 * @Complexity A complexidade deste codigo é O(n), onde n representa o numero de linhas do ficheiro airlines.csv.
 * @return void
 */
void Geral::lerairlines() {
    std::vector<CsvLinha> linhas = CsvLeitor::ler("../dados/airlines.csv", true);

    for (CsvLinha linha : linhas) {
        Airline airline(linha.getString(0), linha.getString(1), linha.getString(2), linha.getString(3));
        airlines.push_back(airline);
        airlineCodes.insert(linha.getString(0));
        airlineNames.insert(linha.getString(1));
    }
}
/**
 * @brief Lê os dados de voo de um arquivo CSV e armazena em um vetor de Voo.
 * @details Esta função lê o arquivo "../dados/flights.csv", usando a classe CsvLeitor para obter as linhas do arquivo em formato de vetor de CsvLinha. Em seguida, cria um objeto Voo para cada linha e adiciona no vetor de Voo. Além disso, adiciona as informações de cada voo no grafo info.
 * @Complexity A complexidade deste codigo é O(n), onde n representa o numero de linhas do ficheiro flights.csv .
 * @return void
 */
void Geral::lervoos() {
    std::vector<CsvLinha> linhas = CsvLeitor::ler("../dados/flights.csv", true);

    for (CsvLinha linha : linhas) {
        Voo voo(linha.getString(0), linha.getString(1), linha.getString(2));
        voos.push_back(voo);
        info.addEdge((string &) std::move(linha.getString(0)), (string &) std::move(linha.getString(1)),
                     (string &) std::move(linha.getString(2)));
    }
}
/**
 * @brief Obtém o caminho mais curto entre dois locais escolhidos pelo usuário.
 * @details Esta função permite que o usuário escolha entre três tipos de locais: aeroportos, cidades ou coordenadas geográficas. Em seguida, o usuário deve inserir os dois locais de partida e chegada. A função encontra o caminho mais curto entre os aeroportos correspondentes aos locais inserido usando os algoritmos implementados na class Graph de pesquisa em largura e, opcionalmente, filtra as rotas pelas companhias aéreas escolhidas pelo usuário. Finalmente, a função exibe o caminho mais curto encontrado e as informações de cada voo na rota.
 * @return void
 */
void Geral::getShortestPaths() {
    vector<pair<string, string>> aeroportosEscolhidos;
    int escolhaLocal;
    unordered_set<string> companhiasEscolhidas;
    string escolhaCompanhia;

    while (true) {
        cout << "[1]Aeroporto em especifico" << endl;
        cout << "[2]Cidade" << endl;
        cout << "[3]Coordenadas" << endl;
        cout << "Escolha que tipo de local quer: ";
        cin >> escolhaLocal;
        if (cin.fail()) {
            cout << "\nINPUT INVALIDO\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (escolhaLocal < 1 or escolhaLocal > 3) {
            cout << "\nESCOLHA INVALIDA\n" << endl;
        } else break;
    }

    if (escolhaLocal == 1) {
        string aeroportoPartida;
        string aeroportoChegada;

        while (true) {
            cout << "\nInsira o codigo do aeroporto de partida: ";
            cin >> aeroportoPartida;
            std::transform(aeroportoPartida.begin(), aeroportoPartida.end(), aeroportoPartida.begin(), ::toupper);

            if (aeroportoPartida.length() != 3) {
                cout << "\nCODIGO INVALIDO" << endl;
            }
            else if (info.nodes.find(aeroportoPartida) == info.nodes.end()) {
                cout << "\nAEROPORTO NAO EXISTE" << endl;
            } else break;
        }
        while (true) {
            cout << "Insira o codigo do aeroporto de chegada: ";
            cin >> aeroportoChegada;
            std::transform(aeroportoChegada.begin(), aeroportoChegada.end(), aeroportoChegada.begin(), ::toupper);

            if (aeroportoChegada.length() != 3) {
                cout << "\nCODIGO INVALIDO\n" << endl;
            }
            else if (info.nodes.find(aeroportoChegada) == info.nodes.end()) {
                cout << "\nAEROPORTO NAO EXISTE\n" << endl;
            }
            else if(aeroportoChegada == aeroportoPartida) {
                cout << "\nAEROPORTO DE CHEGADA TEM DE SER DIFERENTE DO DE PARTIDA\n" << endl;
            } else break;
        }

        aeroportosEscolhidos.emplace_back(aeroportoPartida, aeroportoChegada);
    }
    else if (escolhaLocal == 2) {
        string nomePartida;
        string nomeChegada;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while(true) {
            cout << "\nInsira o nome da cidade de partida: ";
            getline(cin, nomePartida);
            std::transform(nomePartida.begin(), nomePartida.end(), nomePartida.begin(), ::toupper);

            if (cidades.find(nomePartida) == cidades.end()) {
                cout << "\nCIDADE NAO EXISTE" << endl;
            } else break;
        }
        while (true) {
            cout << "Insira o nome da cidade de chegada: ";
            getline(cin, nomeChegada);
            std::transform(nomeChegada.begin(), nomeChegada.end(), nomeChegada.begin(), ::toupper);

            if (cidades.find(nomeChegada) == cidades.end()) {
                cout << "\nCIDADE NAO EXISTE\n" << endl;
            }
            else if(nomeChegada == nomePartida) {
                cout << "\nCIDADE DE CHEGADA TEM DE SER DIFERENTE DA DE PARTIDA\n" << endl;
            } else break;
        }

        Cidade cidadePartida = cidades[nomePartida];
        Cidade cidadeChegada = cidades[nomeChegada];

        for (const auto& aeroportoPartida : cidadePartida.getaeroportos()) {
            for (const auto& aeroportoChegada : cidadeChegada.getaeroportos()) {
                aeroportosEscolhidos.emplace_back(aeroportoPartida.getcodigo(), aeroportoChegada.getcodigo());
            }
        }
    }
    else if (escolhaLocal == 3) {
        int searchRadius = 75;

        vector<Aeroporto> aeroportosPartida;
        vector<Aeroporto> aeroportosChegada;

        float latPartida;
        float longPartida;

        float latChegada;
        float longChegada;

        cout << "\nVAO SER CONSIDERADOS TODOS OS AEROPORTOS NUM RAIO DE 75 KM DAS COORDENADAS FORNECIDAS" << endl;
        cout << "\nCoordenadas de partida" << endl;
        while (true) {
            cout << "Latitude: ";
            cin >> latPartida;

            if (cin.fail()) {
                cout << "\nINPUT INVALIDO\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (latPartida < -90 or latPartida > 90) {
                cout << "\nLATITUDE INVALIDA\n" << endl;
            } else break;
        }
        while (true) {
            cout << "Longitude: ";
            cin >> longPartida;

            if (cin.fail()) {
                cout << "\nINPUT INVALIDO\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (longPartida < -180 or longPartida > 180) {
                cout << "\nLONGITUDE INVALIDA\n" << endl;
            } else break;
        }

        cout << "\nCoordenadas de chegada" << endl;

        arrivalCoords:
        while (true) {
            cout << "Latitude: ";
            cin >> latChegada;

            if (cin.fail()) {
                cout << "\nINPUT INVALIDO\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (latChegada < -90 or latChegada > 90) {
                cout << "\nLATITUDE INVALIDA\n" << endl;
            } else break;
        }
        while (true) {
            cout << "Longitude: ";
            cin >> longChegada;

            if (cin.fail()) {
                cout << "\nINPUT INVALIDO\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (longChegada < -180 or longChegada > 180) {
                cout << "\nLONGITUDE INVALIDA\n" << endl;
            } else break;
        }

        Coordenadas coordsPartida(latPartida, longPartida);
        Coordenadas coordsChegada(latChegada, longChegada);

        double testDistance  = Ferramentas::calculatedistancecoords(coordsPartida, coordsChegada);

        if (testDistance <= 75) {
            cout << "\nCOORDENADA FORNECIDA CORRESPONDE A UM LOCAL A MENOS DE 75 KM DO LOCAL DE PARTIDA\n" << endl;
            goto arrivalCoords;
        }

        double distanceToCoordsPartida;
        double distanceToCoordsChegada;
        for (const Aeroporto& aeroporto : aeroportos) {
            distanceToCoordsPartida =
                    Ferramentas::calculatedistancecoords(aeroporto.getcoordenadas(), coordsPartida);
            distanceToCoordsChegada =
                    Ferramentas::calculatedistancecoords(aeroporto.getcoordenadas(), coordsChegada);

            if (distanceToCoordsPartida <= searchRadius)
                aeroportosPartida.push_back(aeroporto);
            else if (distanceToCoordsChegada <= searchRadius) {
                aeroportosChegada.push_back(aeroporto);
            }
        }

        if (aeroportosPartida.empty()) {
            cout << "\nNAO FORAM ENCONTRADOS AEROPORTOS NUM RAIO DE 75 KM DAS COORDENADAS DE PARTIDA FORNECIDAS";
            return;
        }
        if (aeroportosChegada.empty()) {
            cout << "\nNAO FORAM ENCONTRADOS AEROPORTOS NUM RAIO DE 75 KM DAS COORDENADAS DE CHEGADA FORNECIDAS";
            return;
        }

        for (const auto& aeroportoPartida : aeroportosPartida) {
            for (const auto& aeroportoChegada : aeroportosChegada) {
                aeroportosEscolhidos.emplace_back(aeroportoPartida.getcodigo(), aeroportoChegada.getcodigo());
            }
        }
    }

    int companhiaNum = 1;
    while (true) {
        if (companhiaNum == 1) {
            cout << "\nIndique, uma a uma, o código das companhias aereas que quer utilizar." << endl;
            cout << "Quando tiver inserido todos os códigos desejados, registe 'q', inves de um codigo, para prosseguir." << endl;
            cout << "(Se nao inserir nenhum codigo e escolher proseguir logo, e assumido que qualquer escolhaCompanhia aerea pode ser utilizada na procura pelo menor percurso)\n" << endl;
        }
        cout << "Companhia " << companhiaNum << ": ";
        cin >> escolhaCompanhia;
        std::transform(escolhaCompanhia.begin(), escolhaCompanhia.end(), escolhaCompanhia.begin(), ::toupper);

        if (escolhaCompanhia == "Q") break;
        else if (escolhaCompanhia.length() != 3) {
            cout << "\nCODIGO INVALIDO\n" << endl;
        } else if (airlineCodes.find(escolhaCompanhia) == airlineCodes.end()) {
            cout << "\nCOMPANHIA NAO EXISTE\n" << endl;
        } else{
            companhiasEscolhidas.insert(escolhaCompanhia);
            companhiaNum++;
        }
    }

    string tempInput;
    cout << "\nIRAO SER APRESENTADOS TODOS OS PERCURSOS COM MENOR NUMERO DE VOOS ENCONTRADOS" << endl << "PARA CADA VOO, AS DIFERENTES COMPANHIAS AEREAS UTILIZADAS SERAO APRESENTADAS DENTRO DE []" << endl << "(Press ENTER to continue)" << endl;
    cin.ignore();
    getline(cin, tempInput);

    if (escolhaLocal == 1) {
        cout << "\nOs percursos mais pequenos entre os 2 aeroportos, tendo em conta as companhias fornecidas, foram:\n" << endl;

        vector<vector<Voo>> shortestPaths = info.shortestPaths(aeroportosEscolhidos[0].first, aeroportosEscolhidos[0].second, companhiasEscolhidas);
        displayShortestPaths(shortestPaths);
    }
    else {
        if (escolhaLocal == 2) {
            cout << "\nOs percursos mais pequenos entre todas as combinacoes possiveis de aeroportos, tendo em conta as cidades e companhias fornecidas, foram:\n" << endl;
        }
        else if (escolhaLocal == 3) {
            cout << "\nOs percursos mais pequenos entre todas as combinacoes possiveis de aeroportos, tendo em conta as coordenadas e companhias fornecidas, foram:\n" << endl;
        }

        for (const auto& aeroporto : aeroportosEscolhidos) {
            cout << "Partida->" << info.nodes[aeroporto.first].airport << endl;
            cout << "Chegada->" << info.nodes[aeroporto.second].airport << endl;
            vector<vector<Voo>> shortestPaths = info.shortestPaths(aeroporto.first, aeroporto.second, companhiasEscolhidas);
            displayShortestPaths(shortestPaths);
            cout << endl;
        }
    }
    voltarmenu();
}

void Geral::displayShortestPaths(const vector<vector<Voo>>& shortestPaths) {
    for (const auto& path : shortestPaths) {
        cout << "{  ";
        for (Voo voo : path) {
            cout << voo.getOrigem() << "->" << voo.getDestino() << " [" << voo.getAirline() << "]  ";
        }
        cout << "}";
        cout << endl;
    }
}

/**
 * @brief Calcula estatísticas globais sobre um país, companhia aérea ou voos.
 * @details Esta função permite que o usuário escolha entre três tipos de entidades: países, companhias aéreas ou voos. Em seguida, o usuário deve inserir o nome de um país ou a sigla de uma companhia aérea. A função exibe uma lista de opções de estatísticas a serem calculadas e o usuário deve escolher uma. As opções incluem o número de aeroportos, voos ou companhias aéreas em um país, o diâmetro da rede de voos de um país, ou o top-k de aeroportos ou companhias aéreas com o maior número de voos em um país. Se a entidade escolhida for uma companhia aérea, a função também exibe informações sobre os voos da companhia.
 * @return void
 */
void Geral::estatisticasGlobais() {
    int escolha1;

    while (true) {
        cout << "\n"
                "  +-------------------------------------------------------+\n"
                "  | Pretende calcular estatísticas:                       |\n"
                "  +-------------------------------------------------------+\n"
                "  | [1] Globais da Rede                                   |\n"
                "  | [2] País                                              |\n"
                "  | [3] Companhia Aérea                                   |\n"
                "  | [4] Voos                                              |\n"
                "  +-------------------------------------------------------+\n" << endl;

        cout << "\nEscreva aqui a opção que pretende: ";
        cin >> escolha1;

        if (cin.fail()) {
            cout << "\nErro: Input Inválido\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (escolha1 < 1 or escolha1 > 4) {
            cout << "\nErro: Opção não existente\n" << endl;
        } else break;
    }
    if (escolha1 == 1) {
        int escolha2;

        while (true) {
            cout << "\n"
                    "  +-------------------------------------------------------+\n"
                    "  | Pretende saber:                                       |\n"
                    "  |-------------------------------------------------------|\n"
                    "  | [1] Nº de aeroportos                                  |\n"
                    "  | [2] Nº de voos                                        |\n"
                    "  | [3] Nº de companhias aéreas                           |\n"
                    "  | [4] Diâmetro                                          |\n"
                    "  | [5] Top-k de aeroportos com mais voos e/ou companhias |\n"
                    "  +-------------------------------------------------------+" << endl;

            cout << "\n   Escreva aqui a opção que pretende: ";
            cin >> escolha2;

            if (cin.fail()) {
                cout << "\nErro: Input Inválido\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else if (escolha2 < 1 or escolha2 > 5) {
                cout << "\nErro: Opção não existente\n" << endl;
            } else { break; }
        }
        if (escolha2 == 1) {
            int count = 0;

            for (auto a : aeroportos) {
                count++;
            }
            cout << "\n   Nº de aeroportos: " << count << endl;
            voltarmenu();
        }
        else if (escolha2 == 2) {
            int count = 0;

            for (auto v : voos) {
                count++;
            }
            cout << "\n   Nº de voos: " << count << endl;
            voltarmenu();
        }
        else if (escolha2 == 3) {
            int count = 0;

            for (auto a : airlines) {
                count++;
            }
            cout << "\n   Nº de companhias aéreas: " << count << endl;
            voltarmenu();
        }
        else if (escolha2 == 4) {
            int max = 0;
            int count;
            for (auto n : info.nodes) {
                count = info.bfsDiameter(n.second.airport.getcodigo());
                if(count > max) {max = count;}
            }
            cout << "\n   Diametro: " << max << endl;
            voltarmenu();
        }
        //Ainda falta fazer esta opção
        else if (escolha2 == 5) {cout << "\nAinda não está implementado";}
    }
    else if (escolha1 == 2) {
        string pais;

        while (true) {
            cout << "\n   Escreva aqui o nome do País do qual pretende obter dados: ";
            cin >> pais;

            if (paises.find(pais) == paises.end()) {
                cout << "\nErro: O país indicado não se encontra na base de dados\n" << endl;
            }
            else {break;}
        }
        int escolha2;

        while (true) {
            cout << "\n"
                    "  +-------------------------------------------------------+\n"
                    "  | Pretende saber:                                       |\n"
                    "  |-------------------------------------------------------|\n"
                    "  | [1] Nº de aeroportos                                  |\n"
                    "  | [2] Nº de voos                                        |\n"
                    "  | [3] Nº de companhias aéreas                           |\n"
                    "  | [4] Diâmetro                                          |\n"
                    "  | [5] Top-k de aeroportos com mais voos e/ou companhias |\n"
                    "  +-------------------------------------------------------+" << endl;

            cout << "\n   Escreva aqui a opção que pretende: ";
            cin >> escolha2;

            if (cin.fail()) {
                cout << "\nErro: Input Inválido\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (escolha2 < 1 or escolha2 > 5) {
                cout << "\nErro: Opção não existente\n" << endl;
            }
            else {break;}
        }
        if (escolha2 == 1) {
            int count = 0;

            for (const auto& a : aeroportos) {
                if (a.getpais() == pais) {count++;}
            }
            cout << "\n   Nº de aeroportos em " << pais << ": " << count << endl;
            voltarmenu();
        }
        else if (escolha2 == 2) {
            int count = 0;
            vector<string> aux;

            for (const auto& a : aeroportos) {
                if (a.getpais() == pais) {aux.push_back(a.getcodigo());}
            }
            for (auto v : voos) {
                if ((find(aux.begin(), aux.end(), v.getOrigem()) != aux.end()) || (find(aux.begin(), aux.end(), v.getDestino()) != aux.end())) {count++;}
            }
            cout << "\n   Nº de voos em " << pais << ": " << count << endl;
            voltarmenu();
        }
        else if (escolha2 == 3) {
            int count = 0;

            for (auto a : airlines) {
                if (a.getPais() == pais) {count++;}
            }

            cout << "\n   Nº de companhias aéreas a operar em " << pais << ": " << count << endl;
            voltarmenu();
        }
        else if (escolha2 == 4) {
            int count = 0;
            int max = 0;
            for (auto n : info.nodes) {
                if (n.second.airport.getpais() == pais) {
                    count = info.bfsDiameterCountry(n.first, pais);
                    if (count > max) {max = count;}
                }
            }
            string res;
            if (max < 10) {res = "0" + to_string(max);}
            else {res = to_string(max);}

            cout << "\n+----------+\n"
                    "| DIAMETER |\n"
                    "+----------+\n";
            cout << "|    " << res << "    |\n";
            cout << "+----------+\n";
        }
        else if (escolha2 == 5) {
            int escolha3;

            while (true) {
                cout << "\n"
                        "  +-------------------------------------------------------+\n"
                        "  | Pretende saber:                                       |\n"
                        "  +-------------------------------------------------------+\n"
                        "  | [1] Top-k de aeroportos com mais voos                 |\n"
                        "  | [2] Top-k de aeroportos com mais companhias           |\n"
                        "  | [3] Top-k de aeroportos com mais voos e companhias    |\n"
                        "  +-------------------------------------------------------+" << endl;

                cout << "\n   Escreva aqui a opção que pretende: ";
                cin >> escolha3;

                if (cin.fail()) {
                    cout << "\nErro: Input Inválido\n" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (escolha3 < 1 or escolha3 > 3) {
                    cout << "\nErro: Opção não existente\n" << endl;
                }
                else {break;}
            }
            if (escolha3 == 1) {
                int k;

                while (true) {
                    cout << "\n   Insira k: ";
                    cin >> k;
                    cout << "\n";

                    if (cin.fail()) {
                        cout << "\nErro: Input Inválido\n" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else {break;}
                }
                map<string, int> aux;

                for (const auto& a : aeroportos) {
                    if (a.getpais() == pais) {aux.insert({a.getcodigo(), 0});}
                }
                for (auto v : voos) {
                    auto pos = aux.find(v.getOrigem());
                    if (pos == aux.end()) {}
                    else {aux[v.getOrigem()] += 1;}

                    pos = aux.find(v.getDestino());
                    if (pos == aux.end()) {}
                    else {aux[v.getDestino()] += 1;}
                }
                vector<pair<string, int>> res = sort(aux);
                auto it = res.begin();
                for (int i = 0; i < k; i++) {
                    string a_name;
                    for (const auto& a_ : aeroportos) {
                        if (a_.getcodigo() == it->first) {a_name = a_.getnome();}
                    }
                    cout << it->first << ", " << a_name << endl;
                    it++;
                }
                voltarmenu();
            }
            else if (escolha3 == 2) {
                int k;

                while (true) {
                    cout << "\n   Insira k: ";
                    cin >> k;
                    cout << "\n";

                    if (cin.fail()) {
                        cout << "\nErro: Input Inválido\n" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else {break;}
                }
                map<string, int> aux;
                set<pair<string, string>> aux2;

                for (const auto& a : aeroportos) {
                    if (a.getpais() == pais) {aux.insert({a.getcodigo(), 0});}
                }
                for (auto v : voos) {
                    auto pos = aux.find(v.getOrigem());
                    if (pos == aux.end()) {}
                    else {aux2.insert(pair<string,string>(v.getOrigem(),v.getAirline()));}

                    pos = aux.find(v.getDestino());
                    if (pos == aux.end()) {}
                    else {aux2.insert(pair<string,string>(v.getDestino(),v.getAirline()));}
                }
                for (const auto& i : aux2) {
                    auto pos = aux.find(i.first);
                    if (pos == aux.end()) {}
                    else {aux[i.first] += 1;}
                }
                vector<pair<string, int>> res = sort(aux);
                auto it = res.begin();
                for (int i = 0; i < k; i++) {
                    string a_name;
                    for (const auto& a_ : aeroportos) {
                        if (a_.getcodigo() == it->first) {a_name = a_.getnome();}
                    }
                    cout << it->first << ", " << a_name << endl;
                    it++;
                }
                voltarmenu();
            }
                //Ainda falta fazer esta opção
            else if (escolha3 == 3) {cout << "Ainda não está feito";}
        }
    }
    else if (escolha1 == 3) {
        string companhia;

        while (true) {
            cout << "\n   Escreva aqui o código ou nome da Companhia Aérea da qual pretende obter dados: ";
            cin >> companhia;

            if (companhia.length() != 3) {
                cout << "\nErro:O código inserido é inválido\n" << endl;
            }
            else if (airlineCodes.find(companhia) == airlineCodes.end()) {
                cout << "\nErro: A companhia aérea indicada não se encontra na base de dados\n" << endl;
            }
            else {break;}
        }
        int escolha2;

        while (true) {
            cout << "\n"
                    "  +-------------------------------------------------------+\n"
                    "  | Pretende saber:                                       |\n"
                    "  +-------------------------------------------------------+\n"
                    "  | [1] Nº de aeroportos                                  |\n"
                    "  | [2] Nº de voos                                        |\n"
                    "  | [3] Top-k de aeroportos com mais voos                 |\n"
                    "  +-------------------------------------------------------+\n" << endl;

            cout << "\n   Escreva aqui a opção que pretende: ";
            cin >> escolha2;

            if (cin.fail()) {
                cout << "\nErro: Input Inválido\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (escolha2 < 1 or escolha2 > 3) {
                cout << "\nErro: Opção não existente\n" << endl;
            } else {break;}

        }
        if (escolha2 == 1) {
            int count = 0;
            unordered_set<string> aux;

            for (auto v : voos) {
                if (v.getAirline() == companhia) {
                    aux.insert(v.getOrigem());
                    aux.insert(v.getDestino());
                }
            }

            for (auto a : aux) {count++;}

            cout << "\n   Nº de aeroportos que têm a companhia aérea " << companhia << ": " << count << endl;
            voltarmenu();
        }
        else if (escolha2 == 2) {
            int count = 0;

            for (auto v : voos) {
                if (v.getAirline() == companhia) {count++;}
            }
            cout << "\n   Nº de voos da companhia aérea " << companhia << ": " << count << endl;
            voltarmenu();
        }
        else if (escolha2 == 3) {
            int k;

            while (true) {
                cout << "\n   Insira k: ";
                cin >> k;
                cout << "\n";

                if (cin.fail()) {
                    cout << "\nErro: Input Inválido\n" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {break;}
            }
            map<string, int> aux;
            for (auto v : voos) {
                if (v.getAirline() == companhia) {
                    aux.insert({v.getOrigem(),0});
                    aux.insert({v.getDestino(),0});
                }
            }
            for (auto v : voos) {
                if (v.getAirline() == companhia) {
                    auto pos = aux.find(v.getOrigem());
                    if (pos == aux.end())  {}
                    else {aux[v.getOrigem()] += 1;}

                    pos = aux.find(v.getDestino());
                    if (pos == aux.end()) {}
                    else {aux[v.getDestino()] += 1;}
                }
            }
            vector<pair<string, int>> res = sort(aux);
            auto it = res.begin();
            for (int i = 0; i < k; i++) {
                string a_name;
                for (const auto& a_ : aeroportos) {
                    if (a_.getcodigo() == it->first) {a_name = a_.getnome();}
                }
                cout << it->first << ", " << a_name << endl;
                it++;
            }
            voltarmenu();
        }
    }
    else if (escolha1 == 4) {

        std::cout << "\n"<<
                  "  +------------------------------------------------+\n"
                  "  | VOOS                                           |\n"
                  "  +------------------------------------------------+\n"
                  "  | [1] Numero de voos a partir de um aeroporto    |\n"
                  "  |    [2] De companhias aéras diferentes          |\n"
                  "  |    [3] Para destinos diferentes                |\n"
                  "  |    [4] De países diferentes                    |\n"
                  "  | [5] Aeroportos atingíveis num maximo de X voos |\n"
                  "  | [6] Cidades atingíveis num maximo de X voos    |\n"
                  "  | [7] Paises atingíveis num maximo de X voos     |\n"
                  "  | [0] Voltar ao menu                             |\n"
                  "  |________________________________________________|";
        std::cout << "\n";
        std::cout << "   Escreva aqui a sua opção: ";

        int n;
        bool keepTrying;
        do {
            keepTrying = false;
            std::cout << "Escolha uma das opções: ";
            std::cin >> n;
            if (!std::cin){
                std::cout << "É esperado um valor numérico" << std::endl << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                keepTrying = true;
            }
            else if (n<0 || n>7){
                std::cout << "Valor fora de alcance" << std::endl << std::endl;
                keepTrying = true;
            }
        } while (keepTrying);

        if (n == 1){
            string aeroporto;
            std::cout << "Escolha um aeroporto:  \n";
            std::cin >> aeroporto;
            cout <<" Existem " << numvoos(aeroporto) << " voos a partir do aeroporto " << aeroporto;
            voltarmenu();

        }
        if (n == 2){
            string aeroporto;
            std::cout << "Escolha um aeroporto:  \n";
            std::cin >> aeroporto;
            cout <<" Existem " << numvoosairline(aeroporto) << " voos a partir do aeroporto " << aeroporto << " de companhias aereas diferentes";
            voltarmenu();

        }
        if (n == 3){
            string aeroporto;
            std::cout << "Escolha um aeroporto:  \n";
            std::cin >> aeroporto;
            cout <<" Existem " << numvoosdestino(aeroporto) << " voos a partir do aeroporto " << aeroporto << " para destinos diferentes";
            voltarmenu();

        }
        if (n == 4){
            string aeroporto;
            std::cout << "Escolha um aeroporto:  \n";
            std::cin >> aeroporto;
            cout <<" Existem " << numvoospais(aeroporto) << " voos a partir do aeroporto " << aeroporto << " de paises diferentes ";
            voltarmenu();

        }
        if (n == 5){
            string aeroporto;
            int i;
            std::cout << "Escolha um aeroporto:  \n";
            std::cin >> aeroporto;
            std::cout << "Escolha o numero de voos:  \n";
            std::cin >> i;
            cout << "São atingiveis " << nummaxvoos(aeroporto, i)[0] << " aeroportos com " << i << " voos";
            voltarmenu();

        }
        if (n == 6){
            string aeroporto;
            int i;
            std::cout << "Escolha um aeroporto:  \n";
            std::cin >> aeroporto;
            std::cout << "Escolha o numero de voos:  \n";
            std::cin >> i;
            cout << "São atingiveis " << nummaxvoos(aeroporto, i)[1] << " cidades com " << i << " voos";
            voltarmenu();

        }
        if (n == 7){
            string aeroporto;
            int i;
            std::cout << "Escolha um aeroporto:  \n";
            std::cin >> aeroporto;
            std::cout << "Escolha o numero de voos:  \n";
            std::cin >> i;
            cout << "São atingiveis " << nummaxvoos(aeroporto, i)[2] << " paises com " << i << " voos";
            voltarmenu();

        }

    }

}
/**
 * @brief Retorna o número de voos partindo do aeroporto com o código especificado.
 * @param codigoaeroporto O código do aeroporto para o qual se deseja contar o número de voos.
 * @return size_t
 */
size_t Geral::numvoos(const string& codigoaeroporto) {
    return info.nodes[codigoaeroporto].adj.size();
}

/**
 * @brief Retorna o número de voos de cada companhia aérea partindo do aeroporto com o código especificado.
 * @param codigoaeroporto O código do aeroporto para o qual se deseja contar o número de voos de cada companhia aérea.
 * @return size_t
 */
size_t Geral::numvoosairline(const string& codigoaeroporto) {
    vector<std::string> save;
    for(const auto& it : info.nodes[codigoaeroporto].adj){
        if(std::find(save.begin(), save.end(), it.airline) == save.end()) {
            save.push_back(it.airline);
        }
    }
    return save.size();
}
/**
 * @brief Retorna o número de destinos diferentes para os quais há voos partindo do aeroporto com o código especificado.
 * @param codigoaeroporto O código do aeroporto para o qual se deseja contar o número de destinos diferentes.
 * @return size_t
 */
size_t Geral::numvoosdestino(const string& codigoaeroporto) {
    vector<std::string> save;
    for(const auto& it : info.nodes[codigoaeroporto].adj){
        if(std::find(save.begin(), save.end(), it.dest) == save.end()) {
            save.push_back(it.dest);
        }
    }
    return save.size();
}
/**
 * @brief Retorna o número de países diferentes para os quais há voos partindo do aeroporto com o código especificado.
 * @param codigoaeroporto O código do aeroporto para o qual se deseja contar o número de países diferentes.
 * @return size_t
 */
size_t Geral::numvoospais(const string& codigoaeroporto) {
    vector<std::string> save;
    for(const auto& it : info.nodes[codigoaeroporto].adj){
        if(std::find(save.begin(), save.end(), info.nodes[it.dest].airport.getpais()) == save.end()) {
            save.push_back(info.nodes[it.dest].airport.getpais());
        }
    }
    return save.size();
}
/**
 * @brief Retorna um vetor com o número de aeroportos, cidades e países alcançáveis a partir do aeroporto com o código especificado, com viagens de no máximo y etapas.
 * @param codigoaeroporto O código do aeroporto a partir do qual se deseja contar o número de aeroportos, cidades e países alcançáveis.
 * @param y O número máximo de etapas permitido nas viagens.
 * @return vector
 */
vector<size_t> Geral::nummaxvoos( const string& codigoaeroporto, int y) {
    vector<std::string> aer;
    set<pair<string,string>>  citys;
    set<std::string> countries;

    info.bfs(codigoaeroporto);

    for (auto& node : info.nodes) {
        if(node.second.ciclo && node.second.nodeDist <=y && node.second.nodeDist >=0){
            aer.push_back(node.second.airport.getcodigo());
            auto p1 = make_pair( node.second.airport.getcidade(),node.second.airport.getpais());
            citys.insert(p1);
            countries.insert(node.second.airport.getpais());
        }
    }
    return {aer.size(),citys.size(),countries.size()};
}
/**
 * @brief Retorna uma lista com os códigos dos aeroportos que são pontos de articulação no grafo de voos, limitando a busca a voos da(s) companhia(s) aérea(s) especificada(s).
 * @param airline Vetor com os códigos das companhias aéreas para as quais se deseja limitar a busca de pontos de articulação.
 * @return list
 */
list<string> Geral::articulationPoints(const vector<string>& airline) {
    list<string> answer;
    for (auto &node : info.nodes) {
        node.second.visited = false;
        node.second.parent = -1;
        node.second.low = 0;
        node.second.num = 0;
    }
    int order = 1;
    for (const auto& it : info.nodes){
        if (!it.second.visited){
            info.dfs_articulation_points(it.first, order, answer,airline);
        }
    }
    return answer;
}
/**
 * @brief Exibe o menu principal do programa e permite ao utilizador escolher
 * uma das opções disponíveis.
 * @return void
 */
void Geral::menuprincipal() {
    char opc,opc1;
    std::string str;
    do {


        std::cout<< "    __  __ ______ _   _ _    _\n"
                    "   |  \\/  |  ____| \\ | | |  | |\n"
                    "   | \\  / | |__  |  \\| | |  | |\n"
                    "   | |\\/| |  __| | . ` | |  | |\n"
                    "   | |  | | |____| |\\  | |__| |\n"
                    "   |_|  |_|______|_| \\_|\\____/" << std::endl;
        std::cout << "\n";
        std::cout << "\n";

        std::cout << "  +----------------------------------------------+\n"
                     "  | Pretende realizar um(a):                     |\n"
                     "  +----------------------------------------------+\n"
                     "  | [1] Calcular melhor percurso                 |\n"
                     "  | [2] Estatisticas Globais                     |\n"
                     "  | [3] Pontos de articulacao                    |\n"
                     "  | [Q] Sair                                     |\n"
                     "  |______________________________________________|"<< std::endl;
        std::cout << "\n";
        std::cout << "   Escreva aqui a sua opcao: ";
        std::cin >> opc;
        std::cout << "\n";

        if (opc == '1') {
            getShortestPaths();
        }

        else if(opc=='2'){
            estatisticasGlobais();
            break;
        }
        else if(opc=='3'){
            string in;
            vector<string> ail;
            cout << "\nIndique, uma a uma, o código das companhias aereas que quer utilizar para calcular os pontos de articulacao de esse subconjunto." << endl;
            cout << "Quando tiver inserido todos os códigos desejados, registe 'C', inves de um codigo, para prosseguir." << endl;
            cout << "(Se escolher proseguir logo, escreva logo 'C' e os pontos irão ser calculados na rede toda.)\n \n" << endl;

            while (true){
                while(true) {
                    cout << "\n Companhia:  ";
                    cin >> in;
                    if(in=="C" || in=="c" && ail.empty()){
                        break;
                    }
                    else if (find(airlineCodes.begin(), airlineCodes.end(), in) != airlineCodes.end()) {
                        break;
                    }
                    else{
                        cout << "Essa companhia aérea não existe.";
                    }
                }
                if(in=="C" || in=="c" && ail.empty()){
                    cout << "A rede tem " << articulationPoints(ail).size() << " pontos de articulacao. \n";
                    for(const auto& it :articulationPoints(ail)){
                        cout<< it<< "  -  ";
                    }
                    break;
                }
                if((in=="C" || in=="c") && !ail.empty()){
                    cout << "O subconjunto tem " << articulationPoints(ail).size()  << " pontos de articulacao. \n";
                    for(const auto& it :articulationPoints(ail)){
                        cout<< it<<  "  -  ";
                    }
                    break;
                }
                else{
                    ail.push_back(in);
                }
            }

            voltarmenu();
            break;
        }

        else if (opc == 'Q' || opc=='q' ) { return; }
        else{
            std::cout<< "O input é inválido, por favor tente outra vez! \n";
            std::cout << "\n";
        }
    }while(true);
}

/**
 * @brief Volta para o menu principal
 * Esta função é utilizada para retornar ao menu principal após a realização de uma operação.
 * Ela solicita ao usuário que pressione "V" para retornar ao menu principal.
 * Se o usuário inserir qualquer outro caractere, a função é chamada novamente até que o usuário insira "V" corretamente.
 * @return void
 */
void Geral::voltarmenu(){
    char var;
    do {
        std::cout << "\n";
        std::cout << "Pressione V para voltar menu: ";
        std::cin >> var;
        std::cout << "\n";
        if (var == 'V' || var == 'v') {
            menuprincipal();
            break;
        } else {
            std::cout << "O input é inválido, por favor tente outra vez! \n";
            std::cout << "\n";
        }
    }while(true);
}