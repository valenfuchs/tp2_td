#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include "heuristicas_golosas.cpp"
#include "busqueda_local.cpp"

using namespace std;

int main(int argc, char** argv) {
    string filename = "instances/gap/gap_a/a05100"; 
    cout << "Reading file " << filename << endl;

    vector<vector<int>> matriz_distancias; // Matriz de tamaño rows x cols
    vector<vector<int>> matriz_demandas; // Matriz de tamaño rows x cols
    vector<int> capacidades;

    // Abrir el archivo de datos
    ifstream file(filename);

    if (file.is_open()) {
        int rows, cols = 0;
        file >> rows;
        file >> cols;

        // Leemos los datos y descartamos la primera fila
        string line;
        getline(file, line);
        int bloque = 0;

        // for (; bloque < rows; ++bloque) {
        //     vector<int> fila;
        //     for (int j = 0; j < cols; ++j) {
        //         int dato;
        //         if (file >> dato) {
        //             fila.push_back(dato);
        //         }
        //     }
        //     matriz_distancias.push_back(fila);
        // }

        // for (; bloque < rows*2; ++bloque) {
        //     vector<int> fila;
        //     for (int j = 0; j < cols; ++j) {
        //         int dato;
        //         if (file >> dato) {
        //             fila.push_back(dato);
        //         }
        //     }
        //     matriz_demandas.push_back(fila);
        // }

        for (int j = 0; j < cols; ++j) {
            vector<int> columna_distancias;
            vector<int> columna_demandas;

            for (int bloque = 0; bloque < rows; ++bloque) {
                int dato;
                if (file >> dato) {
                columna_distancias.push_back(dato);
            }
        }
        matriz_distancias.push_back(columna_distancias);

        for (int bloque = 0; bloque < rows; ++bloque) {
            int dato;
            if (file >> dato) {
                columna_demandas.push_back(dato);
            }
        }
        matriz_demandas.push_back(columna_demandas);
    }

        for(int i=0; i < rows; ++i) {
            int dato;
            if (file >> dato) {
                capacidades.push_back(dato);
            }
        }

        // cout << "Matriz de distancias:" << endl;
        // for (const auto& fila : matriz_distancias) {
        //     for (int dato : fila) {
        //         cout << dato << " ";
        //     }
        //     cout << endl;
        // }

        file.close();
    }
    
    pair<pair<int, float>, vector<vector<int>>> resultado = depositoMasCercano(matriz_distancias, matriz_demandas, capacidades);
    int distancia_total = resultado.first.first;
    float tiempo = resultado.first.second;
    vector<vector<int>> asignaciones = resultado.second;
    cout << distancia_total << " " << tiempo << endl;
    for (const auto& fila : asignaciones) {
        for (const auto& elemento : fila) {
            std::cout << elemento << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}