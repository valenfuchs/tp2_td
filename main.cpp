#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <map>
#include <filesystem>
#include "heuristicas_golosas.cpp"
#include "busqueda_local.cpp"
#include "metaheuristica.cpp"

using namespace std;
namespace fs = std::filesystem;

void escribirCSV(const vector<float>& v0, const vector<float>& v1, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        archivo << "distancia_total, tiempo" << ::endl;

        size_t longitudMaxima = max(v0.size(), v1.size());

        for (size_t i = 0; i < longitudMaxima; i++) {
            if (i < v0.size())
                archivo << v0[i];
            archivo << ",";
            if (i < v1.size())
                archivo << v1[i];
            archivo << endl;
        }

        archivo.close();
        cout << "Archivo CSV creado exitosamente." << endl;
    } 
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

int main(int argc, char** argv) {

    // experimentación

    //cout << "Reading file " << filename << endl;
    
    vector<float>dist_dep_cercano;
    vector<float>dist_menor_ratio;
    vector<float>dist_ven_cercano;

    vector<float>tiempo_dep_cercano;
    vector<float>tiempo_menor_ratio;
    vector<float>tiempo_ven_cercano;

    vector<float> relocate1;
    vector<float> relocate2;
    vector<float> relocate3;
    vector<float> swap1;
    vector<float> swap2;
    vector<float> swap3;
    vector<float> grasp1;
    vector<float> grasp2;
    vector<float> grasp3;

    vector<float> tiempo_relocate1;
    vector<float> tiempo_relocate2;
    vector<float> tiempo_relocate3;
    vector<float> tiempo_swap1;
    vector<float> tiempo_swap2;
    vector<float> tiempo_swap3;
    vector<float> tiempo_grasp1;
    vector<float> tiempo_grasp2;
    vector<float> tiempo_grasp3;

    pair<int, int> n;
    // cantidad de depositos, cantidad de vendedores
    
    
    string folderPath = "instancias";  
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (fs::is_regular_file(entry)) {
            cout << entry.path().filename().string();/*
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_dep_cercano = depositoMasCercano(entry.path().filename().string(), "deposito1.csv");
            dist_dep_cercano.push_back(res_dep_cercano.first.first);
            tiempo_dep_cercano.push_back(res_dep_cercano.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_menor_ratio = menorRatio(entry.path().filename().string(), "ratio1.csv");
            dist_menor_ratio.push_back(res_menor_ratio.first.first);
            tiempo_menor_ratio.push_back(res_menor_ratio.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_ven_cercano = vendedorMasCercano(entry.path().filename().string(), "vendedor1.csv");
            dist_ven_cercano.push_back(res_ven_cercano.first.first);
            tiempo_ven_cercano.push_back(res_ven_cercano.first.second);

            // relocate
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate1 = relocateGAP(res_dep_cercano, entry.path().filename().string(), "relocate1.csv");
            relocate1.push_back(res_relocate1.first.first);
            tiempo_relocate1.push_back(res_relocate1.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate2 = relocateGAP(res_menor_ratio, entry.path().filename().string(), "relocate2.csv");
            relocate2.push_back(res_relocate2.first.first);
            tiempo_relocate2.push_back(res_relocate2.first.second);
            
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate3 = relocateGAP(res_ven_cercano, entry.path().filename().string(), "relocate3.csv");
            relocate3.push_back(res_relocate3.first.first);
            tiempo_relocate3.push_back(res_relocate3.first.second);
            
            // swap
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap1 = swapGAP(res_dep_cercano, entry.path().filename().string(), "swap1.csv");
            swap1.push_back(res_swap1.first.first);
            tiempo_swap1.push_back(res_swap1.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap2 = swapGAP(res_menor_ratio, entry.path().filename().string(), "swap2.csv");
            swap2.push_back(res_swap2.first.first);
            tiempo_swap2.push_back(res_swap2.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap3 = swapGAP(res_ven_cercano, entry.path().filename().string(), "swap3.csv");
            swap3.push_back(res_swap3.first.first);
            tiempo_swap3.push_back(res_swap3.first.second);

            // grasp
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp1 = grasp(100, entry.path().filename().string(), "grasp1.csv");
            grasp1.push_back(res_grasp1.first.first);
            tiempo_grasp1.push_back(res_grasp1.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp2 = grasp(300, entry.path().filename().string(), "grasp2.csv");
            grasp2.push_back(res_grasp2.first.first);
            tiempo_grasp2.push_back(res_grasp2.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp3 = grasp(500, entry.path().filename().string(), "grasp3.csv");
            grasp3.push_back(res_grasp3.first.first);
            tiempo_grasp3.push_back(res_grasp3.first.second);
            */
        }
    }

    escribirCSV(dist_dep_cercano, tiempo_dep_cercano, "depMasCercano.csv");
    escribirCSV(dist_menor_ratio, tiempo_menor_ratio,"menorRatio.csv");
    escribirCSV(dist_ven_cercano, tiempo_ven_cercano, "venMasCercano.csv");
}