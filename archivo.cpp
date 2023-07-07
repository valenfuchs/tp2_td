#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <map>
#ifndef LEER_ARCHIVO_H
#define LEER_ARCHIVO_H




using namespace std;


pair<pair<vector<vector<int>>, vector<vector<float>>>, vector<int>> leer_archivo(const string& filename){

    vector<vector<float>> matriz_distancias; // Matriz de tamaño rows x cols
    vector<vector<float>> matriz_distancias_traspuesta;
    vector<vector<int>> matriz_demandas; // Matriz de tamaño rows x cols
    vector<vector<int>> matriz_demandas_traspuesta;
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
        

        for (; bloque < rows; ++bloque) {
            vector<float> fila;
            for (int j = 0; j < cols; ++j) {\
                float dato;
                if (file >> dato) {
                    
                    fila.push_back(dato);
                }
            }
            matriz_distancias_traspuesta.push_back(fila);
        }

        for (; bloque < 2*rows; ++bloque) {
            vector<int> fila;
            for (int j = 0; j < cols; ++j) {
                int dato;
                if (file >> dato) {
                    fila.push_back(dato);
                }
            }
            matriz_demandas_traspuesta.push_back(fila);
        }

            // for(; bloque < rows; ++bloque) {
            //     int dato;
            //     if (file >> dato) {
            //         capacidades.push_back(dato);
            //     }
            // }

        for (; bloque < 2*rows+rows; ++bloque) {
            int dato;
            if (file >> dato) {
                capacidades.push_back(dato);
            }
        }
        
            for (size_t i = 0; i < matriz_distancias_traspuesta[0].size(); ++i) {
                vector<float> fila_distancias;
                vector<int> fila_demandas;

                for (size_t j = 0; j < matriz_distancias_traspuesta.size(); ++j) {
                    fila_distancias.push_back(matriz_distancias_traspuesta[j][i]);
                }
                matriz_distancias.push_back(fila_distancias);

                for (size_t j = 0; j < matriz_demandas_traspuesta.size(); ++j) {
                    fila_demandas.push_back(matriz_demandas_traspuesta[j][i]);
                }
                matriz_demandas.push_back(fila_demandas);
            }
/*
            cout << "Matriz de distancias:" << endl;
            for (const auto& fila : matriz_distancias) {
                for (int dato : fila) {
                    cout << dato << " ";
                }
                cout << endl;
            }*/

            // for (int i = 0; i < capacidades.size(); ++i) {
            //     cout << capacidades[i] << " ";
            // }
            // cout << endl;

        file.close();
    }
    return make_pair(make_pair(matriz_demandas, matriz_distancias), capacidades);
}
#endif