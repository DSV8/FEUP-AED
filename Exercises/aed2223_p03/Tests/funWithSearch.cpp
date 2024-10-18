// AED 2022/2023 - Aula Pratica 03
// Pedro Ribeiro (DCC/FCUP) [ultimo update: 02/10/2022]

#include "funWithSearch.h"
#include <climits>
#include <algorithm>
#include <tclDecls.h>

// ----------------------------------------------------------
// Exercicio 1: Pesquisa Elementar
// ----------------------------------------------------------
// TODO
int FunWithSearch::search(const vector<int> & v, int key)
{
    int low = 0, high = (int)v.size() - 1;
    while (low <= high)
    {
        int middle = low + (high - low) / 2;
        if (key < v[middle]) high = middle - 1;
        else if (key > v[middle]) low = middle + 1;
        else return middle;
    }
    return -1;
}

// ----------------------------------------------------------
// Exercicio 2: Limite Inferior
// ----------------------------------------------------------
// TODO
int FunWithSearch::lowerBound(const vector<int> &v, int key)
{
    int low = 0, high = (int)v.size() - 1;
    while (low < high)
    {
        int middle = low + (high - low) / 2;
        if (v[middle] >= key) high = middle;
        else low = middle + 1;
    }
    if (v[low] >= key) return low;
    return -1;
}

// ----------------------------------------------------------
// Exercicio 3: Intervalos
// ----------------------------------------------------------
// TODO
int FunWithSearch::countRange(const vector<int> & v, int a, int b) {
    int i1 = lowerBound(v, a);
    int i2 = lowerBound(v, b + 1);
    if (i1 == -1) i1 = (int)v.size();
    if (i2 == -1) i2 = (int)v.size();
    return i2 - i1;
}

// ----------------------------------------------------------
// Exercicio 4a: Viagem de mochila às costas (isPossible)
// ----------------------------------------------------------
// TODO
bool FunWithSearch::isPossible(const vector<int> & v, int x, int k) {
    return false;
}

// ----------------------------------------------------------
// Exercicio 4b: Viagem de mochila às costas (partitions)
// ----------------------------------------------------------
// TODO
int FunWithSearch::partitions(const vector<int> & v, int k) {
    return 0;
}

// ----------------------------------------------------------
// Exercicio 5: Somas mais próximas
// ----------------------------------------------------------
// TODO
vector<int> FunWithSearch::closestSums(const vector<int> & v, const vector<int> & p) {
    vector<int> ans;
    return ans;
}

// ----------------------------------------------------------
// Exercicio 6: Jogo de strings
// ----------------------------------------------------------
// TODO
int FunWithSearch::stringGame(const string & a, const string & b, const vector<int> & p) {
    return 0;
}

// ----------------------------------------------------------
// Exercicio 7: Regras Quadriculadas
// ----------------------------------------------------------
// TODO
long long FunWithSearch::rules(int k, long long a, long long b) {
    return 0;
}