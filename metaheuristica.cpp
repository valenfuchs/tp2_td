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

// utilizamos swap como funcion auxiliar
pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> swap(pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> solucion_inicial, const string& input, const string& output) {
    auto inicio = chrono::steady_clock::now(); 

    pair<pair<vector<vector<int>>, vector<vector<float>>>, vector<int>> datos = leer_archivo(input);
    vector<vector<int>> demandas = datos.first.first;
    vector<vector<float>> distancias = datos.first.second;

    vector<vector<int>> solucion = solucion_inicial.second.first;
    vector<int> capacidades_modif = solucion_inicial.second.second;
    int vendedor1;
    int vendedor2;
    int capacidad_j1;
    int capacidad_j2;
    float mejor_distancia = solucion_inicial.first.first;
    float distancia_actual;
    pair<pair<int, int>,pair<int, int>> cambio_optimo;              // guardamos <<j1, j2>, <i1, i2>>
    pair<int, int> vendedores;

    for(int j1 = 0; j1 < solucion.size(); ++j1) {                 //recorremos los depositos1
        for(int i1 = 0; i1 < solucion[j1].size(); ++i1) {         //recorremos los vendedores1
            vendedor1 = solucion[j1][i1];
            for(int j2 = j1+1; j2 < solucion.size(); ++j2) {                 //recorremos los depositos2
                distancia_actual = solucion_inicial.first.first;               
                for(int i2 = 0; i2 < solucion[j2].size(); ++i2) {            //recorremos los vendedores2
                    vendedor2 = solucion[j2][i2];
                    capacidad_j1 = capacidades_modif[j1] + demandas[vendedor1][j1];
                    capacidad_j2 = capacidades_modif[j2] + demandas[vendedor2][j2];
                    if (capacidad_j1 >= demandas[vendedor2][j1]  && capacidad_j2 >= demandas[vendedor1][j2]){
                        distancia_actual += distancias[vendedor1][j2];
                        distancia_actual -= distancias[vendedor1][j1];
                        distancia_actual += distancias[vendedor2][j1];
                        distancia_actual -= distancias[vendedor2][j2];
                        if (distancia_actual < mejor_distancia){
                            mejor_distancia = distancia_actual;
                            cambio_optimo.first = make_pair(j1, j2);
                            cambio_optimo.second = make_pair(i1, i2);
                            vendedores.first = vendedor1;
                            vendedores.second = vendedor2;
                        }
                    }
                }
            }
        }
    }

    //swap
    if (mejor_distancia != solucion_inicial.first.first){
        //  sacamos los vendedores de los depositos
        solucion[cambio_optimo.first.first].erase(solucion[cambio_optimo.first.first].begin()+cambio_optimo.second.first); 
        solucion[cambio_optimo.first.second].erase(solucion[cambio_optimo.first.second].begin()+cambio_optimo.second.second); 
        
        // agregamos los vendedores a sus nuevos depositos
        solucion[cambio_optimo.first.first].push_back(vendedores.second);
        solucion[cambio_optimo.first.second].push_back(vendedores.first);

        // actualizamos las capacidades de cada deposito
        capacidades_modif[cambio_optimo.first.first] += demandas[vendedor1][cambio_optimo.first.first];
        capacidades_modif[cambio_optimo.first.first] -= demandas[vendedor2][cambio_optimo.first.first];

        capacidades_modif[cambio_optimo.first.second] += demandas[vendedor2][cambio_optimo.first.second];
        capacidades_modif[cambio_optimo.first.second] -= demandas[vendedor1][cambio_optimo.first.second];
    }

    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    //armamos la nueva solucion
    return make_pair(make_pair(mejor_distancia, tiempo), make_pair(solucion, capacidades_modif));
}


// funcion auxiliar
// es igual a la heuristica de deposito mas cercano solo que recorre los vendedores de forma random
pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> random_depositoMasCercano(const string& input, const string& output) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    
    pair<pair<vector<vector<int>>, vector<vector<float>>>, vector<int>> datos = leer_archivo(input);
    // leemos el archivo input para obtener las demandas, distancias y capacidades
    vector<vector<int>> demandas = datos.first.first;
    vector<vector<float>> distancias = datos.first.second;
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
    float distancia_total = 0.0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());

    for(int k = 0; k < i_random.size(); ++k) {    // distancias.size() es la cantidad de vendedores
        i = i_random[k];
        int masCercano;                 // guardamos el índice del depósito más cercano hasta el momento
        float distMin = 999999.0;
        float distMax = -1.0;
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
    guardarCSV(asignaciones, output);
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 

    return make_pair(make_pair(distancia_total, tiempo),make_pair(asignaciones, capacidades));
}




pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> grasp(int n_iter, const string& input, const string& output) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    // leemos el archivo input para obtener las demandas, distancias y capacidades
    pair<pair<vector<vector<int>>, vector<vector<float>>>, vector<int>> datos = leer_archivo(input);
    vector<vector<int>> demandas = datos.first.first;
    vector<vector<float>> distancias = datos.first.second;
    vector<int> capacidades = datos.second;

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> sol_random;
    float mejor_distancia=999999.0;
    vector<vector<int>> mejor_asignacion(capacidades.size(), vector<int>());
    vector<int> mejor_capacidades = datos.second;

    // realizamos n iteraciones
    for (int n=0; n < n_iter; n++) {

        // construimos la solucion golosa con un componente random
        // para eso, utilizamos la funcion auxiliar random_depositoMasCercano
        // en la que aleatorizamos el orden en que recorremos la lista de vendedores
        sol_random = random_depositoMasCercano(input, output);

        // le aplicamos a esa solucion el operador de busqueda local swap
        pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> sol_swap = swap(sol_random, input, output);

        // guardamos esta nueva solución
        float distancia_swap = sol_swap.first.first;
        vector<vector<int>> asignacion_swap = sol_swap.second.first;
        vector<int> capacidades_swap = sol_swap.second.second;

        // comparamos nuestra nueva solucion con la que tenemos guardada como la mejor encontrada hasta el momento
        if (distancia_swap < mejor_distancia){
            // si es menor la distancia total recorrida (que es lo que queremos minimizar), reemplazamos la mejor solucion por la actual
            mejor_distancia = distancia_swap;
            mejor_asignacion = asignacion_swap;
            mejor_capacidades = capacidades_swap;
        }
    }

    //guardarCSV(mejor_asignacion, output);
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    
    return make_pair(make_pair(mejor_distancia, tiempo),make_pair(mejor_asignacion, mejor_capacidades));
}