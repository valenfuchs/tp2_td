#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "heuristicas_golosas.cpp"

using namespace std;


pair<pair<int, float>,vector<vector<int>>> relocateGAP(pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> solucion_inicial, vector<vector<int>> distancias, vector<vector<int>> demandas) {
    auto inicio = chrono::steady_clock::now(); 
    vector<vector<int>> solucion = solucion_inicial.second.first;
    vector<int> capacidades_modif = solucion_inicial.second.second;
    int mejor_distancia = solucion_inicial.first.first; //inicializamos la mejor distancia como la inicial //inicializamos la mejor distancia como la inicial
    vector<vector<int>> asignaciones(solucion.size(), vector<int>()); 
    int distancia_actual;
    pair<pair<int, int>,pair<int, int>> cambio_optimo;  // guardamos el vendedor, en que deposito esta y a cual cambiarlo
    //cada vector es un deposito, con los vendedores asignados como elementos
    int vendedor;
    for(int j = 0; j < solucion.size(); ++j) {                 //recorremos los depositos
        for(int i = 0; i < solucion[j].size(); ++i) {          //recorremos los vendedores asignados al deposito j
            vendedor = solucion[j][i];
            for(int k = 0; k < solucion.size(); ++k){
                distancia_actual = solucion_inicial.first.first;              //guardamos la distancia para este relocate
                if(j!=k && capacidades_modif[k]>=demandas[vendedor][k]){      // si la demanda de ese vendedor entra en ese deposito
                    if (distancias[vendedor][k] < distancias[vendedor][j]){   // si es optimo cambiar ese vendedor de deposito
                        distancia_actual -= distancias[vendedor][k];          
                        distancia_actual += distancias[vendedor][j];
                        if (distancia_actual < mejor_distancia){              // si es optimo realizar el cambio con respecto al optimo hasta ahora
                            mejor_distancia = distancia_actual;
                            cambio_optimo.first = make_pair(i, vendedor);
                            cambio_optimo.second = make_pair(j, k);
                        }
                    }
                }
            }
        }
    }
    //relocate
    solucion[cambio_optimo.second.first].erase(solucion[cambio_optimo.second.first].begin()+cambio_optimo.first.first); 
    solucion[cambio_optimo.second.second].push_back(cambio_optimo.first.second);

    guardarCSV(asignaciones, "relocate.csv");
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    //armamos la nueva solucion
    return make_pair(make_pair(mejor_distancia, tiempo), solucion);
}