#pragma once
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#include <algorithm>
#include "archivo.cpp"

using namespace std;

pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> random_depositoMasCercano(const string& input, const string& output) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    
    pair<pair<vector<vector<int>>, vector<vector<int>>>, vector<int>> datos = leer_archivo(input);
    vector<vector<int>> demandas = datos.first.first;
    vector<vector<int>> distancias = datos.first.second;
    vector<int> capacidades = datos.second;
    vector<int> i_random;
     // randomizamos el orden en que recorremos los vendedores
    for (int r=0; r < demandas.size(); r++){
        i_random.push_back(r);
    }
    random_device rd;
    mt19937 gen(rd());
    shuffle(i_random.begin(), i_random.end(), gen);

    int i, j;       // i recorrerá las filas (vendedores), j las columnas (depósitos)
    int distancia_total = 0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());

    for(int i = 0; i < i_random.size(); ++i) {    // distancias.size() es la cantidad de vendedores
        i = i_random[i];
        int masCercano;                 // guardamos el índice del depósito más cercano hasta el momento
        int distMin = 999999;
        int distMax = -1;
        bool asignado = false;
        
        for(int j = 0; j < distancias[i].size(); j++) {
            if(distancias[i][j] <= distMin  && demandas[i][j] <= capacidades[j]) {
                distMin = distancias[i][j];
                masCercano = j;
                asignado = true;
            }
            if(distancias[i][j] >= distMax) {
                distMax = distancias[i][j];
            }
        }
        if(!asignado) {
            distancia_total += 3*distMax;
        }
        else {
            capacidades[masCercano] -= demandas[i][masCercano];
            distancia_total += distMin;
            asignaciones[masCercano].push_back(i);
        }
    }
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    
    return make_pair(make_pair(distancia_total, tiempo),make_pair(asignaciones, capacidades));
}




pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> grasp(int n_iter, const string& input, const string& output) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    pair<pair<vector<vector<int>>, vector<vector<int>>>, vector<int>> datos = leer_archivo(input);
    vector<vector<int>> demandas = datos.first.first;
    vector<vector<int>> distancias = datos.first.second;
    vector<int> capacidades = datos.second;
    pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> sol_random;
    int mejor_distancia=999999;
    vector<vector<int>> mejor_asignacion(capacidades.size(), vector<int>());
    vector<int> mejor_capacidades = datos.second;

    for (int n=0; n < n_iter; n++) {

        sol_random = random_depositoMasCercano(input, output);

        pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> sol_swap = swapGAP(sol_random, input, output);

        int distancia_swap = sol_swap.first.first;
        vector<vector<int>> asignacion_swap = sol_swap.second.first;
        vector<int> capacidades_swap = sol_swap.second.second;

        if (distancia_swap < mejor_distancia){
            mejor_distancia = distancia_swap;
            mejor_asignacion = asignacion_swap;
            mejor_capacidades = capacidades_swap;
        }
    }

    guardarCSV(mejor_asignacion, output);
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    
    return make_pair(make_pair(mejor_distancia, tiempo),make_pair(mejor_asignacion, mejor_capacidades));
}