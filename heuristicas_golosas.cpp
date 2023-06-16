#include <string>
#include <iostream>
#include <list>
#include <vector>
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

// vecto<vector<int>> ordenar_demandas(const vector<vector<int>>& distancias, const vector<vector<int>>& demandas) {
//     for(int i = 0; i < distancias.size(); ++i) {
//         for(int j = 0; j < distancias[i].size(); ++j) {
//             int med = 
//         }
//     }
// }

pair<pair<int, float>, vector<vector<int>>> depositoMasCercano(vector<vector<int>> distancias, vector<vector<int>> demandas, vector<int> capacidades) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    int i, j;       // i recorrerá las filas (vendedores), j las columnas (depósitos)
    int distancia_total = 0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());

    for(i = 0; i < distancias.size(); ++i) {    // distancias.size() es la cantidad de depositos
        int masCercano = 0;                 // guardamos el índice del depósito más cercano hasta el momento
        int distMin = 999999;
        int distMax = -1;
        bool asignado = false;
        
        for(j = 0; j < distancias[i].size(); ++j) {
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
    
    return make_pair(make_pair(distancia_total, tiempo), asignaciones);
}

pair<int, float> menorRatio(vector<vector<int>> distancias, vector<vector<int>> demandas, vector<int> capacidades) {
    auto inicio = chrono::steady_clock::now();      // iniciamos un timer
    int i, j;       // i recorrerá las filas (vendedores), j las columnas (depósitos)
    int distancia_total = 0;
    vector<vector<int>> asignaciones(capacidades.size(), vector<int>());

    for(i = 0; i < distancias.size(); ++i) {    // distancias.size() es la cantidad de depositos
        int masCercano = 0;                 // guardamos el índice del depósito más cercano hasta el momento
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

