#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>

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

pair<int, float> depositoMasCercano(vector<vector<int>> distancias, vector<vector<int>> demandas, vector<int> capacidades) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    int i, j;       // i recorrerá las filas (vendedores), j las columnas (depósitos)
    int distancia_total = 0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());

    for(int i = 0; i < distancias.size(); ++i) {    // distancias.size() es la cantidad de vendedores
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
    guardarCSV(asignaciones, "asignaciones.csv");
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    
    return make_pair(distancia_total, tiempo);
}

pair<int, float> menorRatio(vector<vector<int>> distancias, vector<vector<int>> demandas, vector<int> capacidades) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    int i, j;       // i recorrerá las filas (vendedores), j las columnas (depósitos)
    int distancia_total = 0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());

    for(i = 0; i < distancias.size(); ++i) {    // distancias.size() es la cantidad de depositos
        int masCercano;                 // guardamos el índice del depósito más cercano hasta el momento
        int distMin = 999999;
        int distMax = -1;
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
    guardarCSV(asignaciones, "asignaciones_ratio.csv");
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    
    return make_pair(distancia_total, tiempo);
}

map<int, vector<int>> ordenarDeposito(vector<vector<int>> distancias, int j, vector<int> capacidades) {
    vector<int> dist;
    vector<int> dist_ordenada;
    map<int, vector<int>> indicesDepositoOrdenado;

    
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

pair<int, float> vendedorMasCercano(vector<vector<int>> distancias, vector<vector<int>> demandas, vector<int> capacidades) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    int distancia_total = 0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());
    vector<map<int, vector<int>>> depositosOrdenados;
    vector<int> vendedores_asignados;
    int distMax = -1;

    for(int j = 0; j < capacidades.size(); j++) {
        depositosOrdenados.push_back(ordenarDeposito(distancias, j, capacidades));
    }

    for(int i = 0; i < depositosOrdenados.size(); ++i) {
        for(int j = 0; j < depositosOrdenados[i].size(); ++j) {
            for(auto it = depositosOrdenados[i].begin(); it != depositosOrdenados[i].end(); ++it){
                int distancia = it->first;
                vector<int> vendedores = it->second;
                for(int k = 0; k < vendedores.size(); ++k){
                    if(demandas[vendedores[k]][i] <= capacidades[i]) {
                        auto esta_asignado = find(vendedores_asignados.begin(), vendedores_asignados.end(), vendedores[k]);
                        if(esta_asignado == vendedores_asignados.end()){
                            vendedores_asignados.push_back(vendedores[k]);
                            distancia_total += distancia;
                            capacidades[i] -= 
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
    guardarCSV(asignaciones, "asignaciones_vendedores.csv");
    auto final = chrono::steady_clock::now();   // finalizamos el timer
    float tiempo = chrono::duration_cast<chrono::microseconds>(final-inicio).count(); // obtenemos el tiempo de ejecucion 
    
    return make_pair(distancia_total, tiempo);
}

