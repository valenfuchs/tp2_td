#pragma once
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>
#include "archivo.cpp"

using namespace std;

void guardarCSV(const vector<vector<int>>& matriz, const string& filename) {
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
}

pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> depositoMasCercano(const string& input, const string& output) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    
    pair<pair<vector<vector<int>>, vector<vector<float>>>, vector<int>> datos = leer_archivo(input);
    vector<vector<int>> demandas = datos.first.first;
    vector<vector<float>> distancias = datos.first.second;
    vector<int> capacidades = datos.second;
    
    int i, j;       // i recorrerá las filas (vendedores), j las columnas (depósitos)
    float distancia_total = 0.0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());

    for(int i = 0; i < distancias.size(); ++i) {    // distancias.size() es la cantidad de vendedores
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

pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> menorRatio(const string& input, const string& output) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer

    pair<pair<vector<vector<int>>, vector<vector<float>>>, vector<int>> datos = leer_archivo(input);
    vector<vector<int>> demandas = datos.first.first;
    vector<vector<float>> distancias = datos.first.second;
    vector<int> capacidades = datos.second;

    int i, j;       // i recorrerá las filas (vendedores), j las columnas (depósitos)
    float distancia_total = 0.0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());

    for(i = 0; i < distancias.size(); ++i) {    // distancias.size() es la cantidad de depositos
        int masCercano;                 // guardamos el índice del depósito más cercano hasta el momento
        float distMin = 999999.0;
        float distMax = -1.0;
        bool asignado = false;
        
        for(j = 0; j < distancias[i].size(); ++j) {
            if(distancias[i][j]/demandas[i][j] <= distMin  && demandas[i][j] <= capacidades[j]) {
                distMin = distancias[i][j];
                masCercano = j;
                asignado = true;
            }
            if(distancias[i][j]/demandas[i][j] >= distMax) {
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

// funcion auxiliar
map<float, vector<int>> ordenarDeposito(vector<vector<float>> distancias, int j, vector<int> capacidades) {
    vector<float> dist;
    vector<float> dist_ordenada;
    map<float, vector<int>> indicesDepositoOrdenado;  
    // ordenamos de menor a mayor las distancias de todos los vendedores a ese deposito
    // mapeamos cada distancia a la posicion original del vendedor/es a la que corresponde

    
    for(int i = 0; i < distancias.size(); i++){
        dist.push_back(distancias[i][j]);
        dist_ordenada.push_back(distancias[i][j]);
    }

    sort(dist_ordenada.begin(), dist_ordenada.end());

    for(int i = 0; i < dist_ordenada.size(); i++){
        indicesDepositoOrdenado[dist_ordenada[i]] = vector<int>();
    }

    for(int i = 0; i < dist.size(); i++){
        indicesDepositoOrdenado[dist[i]].push_back(i);
    }

    return indicesDepositoOrdenado;
}

pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> vendedorMasCercano(const string& input, const string& output) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer

    pair<pair<vector<vector<int>>, vector<vector<float>>>, vector<int>> datos = leer_archivo(input);
    vector<vector<int>> demandas = datos.first.first;
    vector<vector<float>> distancias = datos.first.second;
    vector<int> capacidades = datos.second;

    float distancia_total = 0.0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());
    vector<map<float, vector<int>>> depositosOrdenados;
    vector<int> vendedores_asignados;
    float distMax = -1.0;

    for(int j = 0; j < capacidades.size(); j++) {
        depositosOrdenados.push_back(ordenarDeposito(distancias, j, capacidades));
    }

    for(int i = 0; i < depositosOrdenados.size(); ++i) {
        for(int j = 0; j < depositosOrdenados[i].size(); ++j) {
            for(auto it = depositosOrdenados[i].begin(); it != depositosOrdenados[i].end(); ++it){
                float distancia = it->first;
                vector<int> vendedores = it->second;
                for(int k = 0; k < vendedores.size(); ++k){
                    if(demandas[vendedores[k]][i] <= capacidades[i]) {
                        auto esta_asignado = find(vendedores_asignados.begin(), vendedores_asignados.end(), vendedores[k]);
                        if(esta_asignado == vendedores_asignados.end()){
                            vendedores_asignados.push_back(vendedores[k]);
                            distancia_total += distancia;
                            capacidades[i] -= demandas[vendedores[k]][i];
                            asignaciones[i].push_back(vendedores[k]);
                        }
                    }
                }
                if(distancia > distMax) {
                    distMax = distancia;
                }
            }
        }
    }
    if(vendedores_asignados.size() != distancias.size()) {
        distancia_total += 3*distMax*(distancias.size()-vendedores_asignados.size());
    }
    guardarCSV(asignaciones, output);
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    
   return make_pair(make_pair(distancia_total, tiempo),make_pair(asignaciones, capacidades));
}

