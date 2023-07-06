#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
//#include "heuristicas_golosas.cpp"

using namespace std;

/*void guardarCSV(const vector<vector<int>>& matriz, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& fila : matriz) {
            for (int i = 0; i < fila.size(); ++i) {
                file << fila[i];
                if (i != fila.size() - 1) {
                    file << ",";
                }
            }
            file << endl;
        }
        file.close();
        cout << "La matriz de asignaciones se ha guardado en el archivo " << filename << endl;
    }
}*/

pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> relocateGAP(pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> solucion_inicial, vector<vector<int>> distancias, vector<vector<int>> demandas) {
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
                        distancia_actual += distancias[vendedor][k];          
                        distancia_actual -= distancias[vendedor][j];
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
    if (mejor_distancia != solucion_inicial.first.first){
        solucion[cambio_optimo.second.first].erase(solucion[cambio_optimo.second.first].begin()+cambio_optimo.first.first); 
        solucion[cambio_optimo.second.second].push_back(cambio_optimo.first.second);
        capacidades_modif[cambio_optimo.second.first] += demandas[cambio_optimo.first.second][cambio_optimo.second.first];
        capacidades_modif[cambio_optimo.second.second] -= demandas[cambio_optimo.first.second][cambio_optimo.second.second];
    }

    guardarCSV(solucion, "relocate.csv");
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    //armamos la nueva solucion
    return make_pair(make_pair(mejor_distancia, tiempo), make_pair(solucion, capacidades_modif));
}




pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> swapGAP(pair<pair<int, float>,pair<vector<vector<int>>,vector<int>>> solucion_inicial, vector<vector<int>> distancias, vector<vector<int>> demandas) {
    auto inicio = chrono::steady_clock::now(); 
    vector<vector<int>> solucion = solucion_inicial.second.first;
    vector<int> capacidades_modif = solucion_inicial.second.second;
    int vendedor1;
    int vendedor2;
    int capacidad_j1;
    int capacidad_j2;
    int mejor_distancia = solucion_inicial.first.first;
    int distancia_actual;
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


    guardarCSV(solucion, "swap.csv");
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    //armamos la nueva solucion
    return make_pair(make_pair(mejor_distancia, tiempo), make_pair(solucion, capacidades_modif));
}