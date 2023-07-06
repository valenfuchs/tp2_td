#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <map>
#include "heuristicas_golosas.cpp"
#include "busqueda_local.cpp"
#include "metaheuristica.cpp"

using namespace std;

int main(int argc, char** argv) {
    string filename = "instances/gap/gap_a/a05100"; 
    cout << "Reading file " << filename << endl;
    /*
    pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> resultado1 = depositoMasCercano(filename, "deposito1.csv");
    int distancia_total1 = resultado1.first.first;
    float tiempo1 = resultado1.first.second;
    cout << distancia_total1 << " " << tiempo1 << endl;

    pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> resultado2 = menorRatio(filename, "ratio1.csv");
    int distancia_total2 = resultado2.first.first;
    float tiempo2 = resultado2.first.second;
    cout << distancia_total2 << " " << tiempo2 << endl;

    pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> resultado3 = vendedorMasCercano(filename, "vendedor1.csv");
    int distancia_total3 = resultado3.first.first;
    float tiempo3 = resultado3.first.second;
    cout << distancia_total3 << " " << tiempo3 << endl;


    pair<pair<int, float>,pair<vector<vector<int>>, vector<int>>> sol_relocate1 = relocateGAP(resultado1, filename, "relocate1.csv");
    int distancia_relocate1 = sol_relocate1.first.first;
    float tiempo_relocate1 = sol_relocate1.first.second;
    cout << distancia_relocate1 << " " << tiempo_relocate1 << endl;

    pair<pair<int, float>,pair<vector<vector<int>>, vector<int>>> sol_swap1 = swapGAP(resultado1, filename, "swap1.csv");
    int distancia_swap1 = sol_swap1.first.first;
    float tiempo_swap1 = sol_swap1.first.second;
    cout << distancia_swap1 << " " << tiempo_swap1 << endl;
*/

    pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> resultado1 = depositoMasCercano(filename, "deposito1.csv");
    int distancia_total1 = resultado1.first.first;
    float tiempo1 = resultado1.first.second;
    cout << distancia_total1 << " " << tiempo1 << endl;


}