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

void escribirCSV1(const vector<string>& v, const vector<float>& v0, const vector<float>& v1, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        archivo << "código, distancia_total, tiempo" << ::endl;

        size_t longitudMaxima = max(max(v0.size(), v1.size()), v.size());

        for (size_t i = 0; i < longitudMaxima; i++) {
            if (i < v.size())
                archivo << v[i];
            archivo << ",";
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
    
    string folderPath = "instancias";  
    
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (fs::is_regular_file(entry)) {
        
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_dep_cercano = depositoMasCercano("instancias/" + entry.path().filename().string(), "deposito1.csv");
            dist_dep_cercano.push_back(res_dep_cercano.first.first);
            tiempo_dep_cercano.push_back(res_dep_cercano.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_menor_ratio = menorRatio("instancias/" + entry.path().filename().string(), "ratio1.csv");
            dist_menor_ratio.push_back(res_menor_ratio.first.first);
            tiempo_menor_ratio.push_back(res_menor_ratio.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_ven_cercano = vendedorMasCercano("instancias/" + entry.path().filename().string(), "vendedor1.csv");
            dist_ven_cercano.push_back(res_ven_cercano.first.first);
            tiempo_ven_cercano.push_back(res_ven_cercano.first.second);

            // relocate
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate1 = relocateGAP(res_dep_cercano, "instancias/" + entry.path().filename().string(), "relocate1.csv");
            relocate1.push_back(res_relocate1.first.first);
            tiempo_relocate1.push_back(res_relocate1.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate2 = relocateGAP(res_menor_ratio, "instancias/" + entry.path().filename().string(), "relocate2.csv");
            relocate2.push_back(res_relocate2.first.first);
            tiempo_relocate2.push_back(res_relocate2.first.second);
            
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate3 = relocateGAP(res_ven_cercano, "instancias/" + entry.path().filename().string(), "relocate3.csv");
            relocate3.push_back(res_relocate3.first.first);
            tiempo_relocate3.push_back(res_relocate3.first.second);
            
            // swap
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap1 = swapGAP(res_dep_cercano, "instancias/" + entry.path().filename().string(), "swap1.csv");
            swap1.push_back(res_swap1.first.first);
            tiempo_swap1.push_back(res_swap1.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap2 = swapGAP(res_menor_ratio, "instancias/" + entry.path().filename().string(), "swap2.csv");
            swap2.push_back(res_swap2.first.first);
            tiempo_swap2.push_back(res_swap2.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap3 = swapGAP(res_ven_cercano, "instancias/" + entry.path().filename().string(), "swap3.csv");
            swap3.push_back(res_swap3.first.first);
            tiempo_swap3.push_back(res_swap3.first.second);

            // grasp
            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp1 = grasp(100, "instancias/" + entry.path().filename().string(), "grasp1.csv");
            grasp1.push_back(res_grasp1.first.first);
            tiempo_grasp1.push_back(res_grasp1.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp2 = grasp(300, "instancias/" + entry.path().filename().string(), "grasp2.csv");
            grasp2.push_back(res_grasp2.first.first);
            tiempo_grasp2.push_back(res_grasp2.first.second);

            pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp3 = grasp(500, "instancias/" + entry.path().filename().string(), "grasp3.csv");
            grasp3.push_back(res_grasp3.first.first);
            tiempo_grasp3.push_back(res_grasp3.first.second);
            
        }
    }

    escribirCSV(dist_dep_cercano, tiempo_dep_cercano, "depMasCercano.csv");
    escribirCSV(dist_menor_ratio, tiempo_menor_ratio,"menorRatio.csv");
    escribirCSV(dist_ven_cercano, tiempo_ven_cercano, "venMasCercano.csv");

    escribirCSV(relocate1, tiempo_relocate1, "relocateDep.csv");
    escribirCSV(relocate2, tiempo_relocate2, "relocateRatio.csv");
    escribirCSV(relocate3, tiempo_relocate3, "relocateVen.csv");
    
    escribirCSV(swap1, tiempo_swap1, "swapDep.csv");
    escribirCSV(swap2, tiempo_swap2, "swapRatio.csv");
    escribirCSV(swap3, tiempo_swap3, "swapVen.csv");
    
    escribirCSV(grasp1, tiempo_grasp1, "grasp100.csv");
    escribirCSV(grasp2, tiempo_grasp2, "grasp300.csv");
    escribirCSV(grasp3, tiempo_grasp3, "grasp500.csv");


    // dejamos guardados los csv de asignaciones con la primera instancia

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_dep_cercano = depositoMasCercano("instancias/a05100", "asignaciones_inst1/deposito1.csv");
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_menor_ratio = menorRatio("instancias/a05100", "asignaciones_inst1/ratio1.csv");
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_ven_cercano = vendedorMasCercano("instancias/a05100", "asignaciones_inst1/vendedor1.csv");

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate1 = relocateGAP(res_dep_cercano, "instancias/a05100", "asignaciones_inst1/relocate1.csv");
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate2 = relocateGAP(res_menor_ratio, "instancias/a05100", "asignaciones_inst1/relocate2.csv");
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_relocate3 = relocateGAP(res_ven_cercano, "instancias/a05100", "asignaciones_inst1/relocate3.csv");
    
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap1 = swapGAP(res_dep_cercano, "instancias/a05100", "asignaciones_inst1/swap1.csv");
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap2 = swapGAP(res_menor_ratio, "instancias/a05100", "asignaciones_inst1/swap2.csv");
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_swap3 = swapGAP(res_ven_cercano, "instancias/a05100", "asignaciones_inst1/swap3.csv");
    
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp1 = grasp(100, "instancias/a05100", "asignaciones_inst1/grasp1.csv");
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp2 = grasp(300, "instancias/a05100", "asignaciones_inst1/grasp2.csv");
    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> res_grasp3 = grasp(500, "instancias/a05100", "asignaciones_inst1/grasp3.csv");

    

    // corremos las asignaciones para la instancia real

    // cada posicion del vector es una metodologia distinta

    
    vector<string> codigos;
    vector<float> dist_real;
    vector<float> tiempo_real;

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_dep_cercano = depositoMasCercano("instances/real/real_instance", "asignaciones_real/deposito1_real.csv");
    codigos.push_back("depositoMasCercano");
    dist_real.push_back(real_dep_cercano.first.first);
    tiempo_real.push_back(real_dep_cercano.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_menor_ratio = menorRatio("instances/real/real_instance", "asignaciones_real/ratio1_real.csv");
    codigos.push_back("menorRatio");
    dist_real.push_back(real_menor_ratio.first.first);
    tiempo_real.push_back(real_menor_ratio.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_ven_cercano = vendedorMasCercano("instances/real/real_instance", "asignaciones_real/vendedor1_real.csv");
    codigos.push_back("vendedorMasCercano");
    dist_real.push_back(real_ven_cercano.first.first);
    tiempo_real.push_back(real_ven_cercano.first.second);


    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_relocate1 = relocateGAP(real_dep_cercano, "instances/real/real_instance", "asignaciones_real/relocate1_real.csv");
    codigos.push_back("relocateDep");
    dist_real.push_back(real_relocate1.first.first);
    tiempo_real.push_back(real_relocate1.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_relocate2 = relocateGAP(real_menor_ratio, "instances/real/real_instance", "asignaciones_real/relocate2_real.csv");
    codigos.push_back("relocateRatio");
    dist_real.push_back(real_relocate2.first.first);
    tiempo_real.push_back(real_relocate2.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_relocate3 = relocateGAP(real_ven_cercano, "instances/real/real_instance", "asignaciones_real/relocate3_real.csv");
    codigos.push_back("relocateVen");
    dist_real.push_back(real_relocate3.first.first);
    tiempo_real.push_back(real_relocate3.first.second);


    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_swap1 = swapGAP(real_dep_cercano, "instances/real/real_instance", "asignaciones_real/swap1_real.csv");
    codigos.push_back("swapDep");
    dist_real.push_back(real_swap1.first.first);
    tiempo_real.push_back(real_swap1.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_swap2 = swapGAP(real_menor_ratio, "instances/real/real_instance", "asignaciones_real/swap2_real.csv");
    codigos.push_back("swapRatio");
    dist_real.push_back(real_swap2.first.first);
    tiempo_real.push_back(real_swap2.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_swap3 = swapGAP(real_ven_cercano, "instances/real/real_instance", "asignaciones_real/swap3_real.csv");
    codigos.push_back("swapVen");
    dist_real.push_back(real_swap3.first.first);
    tiempo_real.push_back(real_swap3.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_grasp1 = grasp(100, "instances/real/real_instance", "asignaciones_real/grasp1_real.csv");
    codigos.push_back("grasp100");
    dist_real.push_back(real_grasp1.first.first);
    tiempo_real.push_back(real_grasp1.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_grasp2 = grasp(300, "instances/real/real_instance", "asignaciones_real/grasp2_real.csv");
    codigos.push_back("grasp300");
    dist_real.push_back(real_grasp2.first.first);
    tiempo_real.push_back(real_grasp2.first.second);

    pair<pair<float, float>,pair<vector<vector<int>>,vector<int>>> real_grasp3 = grasp(500, "instances/real/real_instance", "asignaciones_real/grasp3_real.csv");
    codigos.push_back("grasp500");
    dist_real.push_back(real_grasp3.first.first);
    tiempo_real.push_back(real_grasp3.first.second);
    


    escribirCSV1(codigos, dist_real, tiempo_real, "instancia_real.csv");
    
}