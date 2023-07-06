#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <map>
#include "heuristicas_golosas.cpp"
#include "busqueda_local.cpp"

using namespace std;

int main(int argc, char** argv) {
    string filename = "instances/gap/gap_a/a05100"; 
    cout << "Reading file " << filename << endl;
    
    pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> resultado = depositoMasCercano(matriz_distancias, matriz_demandas, capacidades);
    int distancia_total = resultado.first.first;
    float tiempo = resultado.first.second;
    cout << distancia_total << " " << tiempo << endl;
/*
    pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> resultado2 = menorRatio(matriz_distancias, matriz_demandas, capacidades);
    int distancia_total2 = resultado2.first.first;
    float tiempo2 = resultado2.first.second;
    cout << distancia_total2 << " " << tiempo2 << endl;

    pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> resultado3 = vendedorMasCercano(matriz_distancias, matriz_demandas, capacidades);
    int distancia_total3 = resultado3.first.first;
    float tiempo3 = resultado3.first.second;
    cout << distancia_total3 << " " << tiempo3 << endl;
*/
/*



    pair<pair<int, float>,pair<vector<vector<int>>, vector<int>>> sol_relocate = relocateGAP(resultado3, matriz_distancias, matriz_demandas);
    int distancia_total2 = sol_relocate.first.first;
    float tiempo2 = sol_relocate.first.second;
    cout << distancia_total2 << " " << tiempo2 << endl;
*/
    pair<pair<int, float>,pair<vector<vector<int>>, vector<int>>> sol_swap = swapGAP(resultado, matriz_distancias, matriz_demandas);
    int distancia_total2 = sol_swap.first.first;
    float tiempo2 = sol_swap.first.second;
    cout << distancia_total2 << " " << tiempo2 << endl;

    // map<int, vector<int>> depositoOrdenado = ordenar(matriz_distancias, 0, capacidades);
    // std::cout << "Diccionario ordenado: " << std::endl;
    // for (const auto& elemento : depositoOrdenado) {
    //     std::cout << "Clave: " << elemento.first << ", Valores: ";
    //     const std::vector<int>& vectorValores = elemento.second;
    //     for (const auto& valor : vectorValores) {
    //         std::cout << valor << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}