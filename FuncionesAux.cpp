/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncionesAux.cpp
 * Author: Alberto
 * 
 * Created on 23 de septiembre de 2020, 11:44
 */

#include <set>
#include "FuncionesAux.h"

void FuncionesAux::cargaFichero(string nombre, vector<vector<float>> &matriz, int& n, int& m) {
    string linea;

    fstream fe(nombre.c_str(), ios::in);
    if (!fe) {
        throw errorFichero();
    }

    fe>>n;
    fe>>m;

    getline(fe, linea);
    matriz.resize(n, vector<float>(n));

    while (!fe.eof()) {
        float num1 = 0;
        float num2 = 0;
        float valor = 0.0;

        fe>>num1;
        fe>>num2;
        fe >> matriz[num1][num2];

        getline(fe, linea);
    }

    fe.close();
}

void FuncionesAux::cargaParametrizacion(string nombreArchivo, vector<string>& archivos, vector<string>& nombreAlg, vector<int>& elite, vector<int>& semillas, float& probCruce, float& probMutacion, int& tamPoblacion, int& nEvaluaciones) {

    ifstream archivo_entrada;
    string linea;
    int i = 0;
    int numCampos = 0;

    archivo_entrada.open(nombreArchivo);
    while (getline(archivo_entrada, linea)) {
        numCampos++;
    };
    string* datos = new string [numCampos];

    archivo_entrada.clear();
    archivo_entrada.seekg(0, archivo_entrada.beg);

    while (getline(archivo_entrada, linea)) {
        datos[i] = linea;
        i++;
    };

    string arch = datos[0];
    string alg = datos[1];
    string elit = datos[2];
    string sem = datos[3];
    string probc = datos[4];
    string probm = datos[5];
    string tamPob = datos[6];
    string nEval = datos[7];

    //ARCHIVOS
    istringstream isstream1(arch);
    string palabra1;
    while (isstream1 >> palabra1) {
        archivos.push_back(palabra1);
    }
    archivos.erase(archivos.begin());


    //ALGORITMOS
    istringstream isstream2(alg);
    string palabra2;
    while (isstream2 >> palabra2) {
        nombreAlg.push_back(palabra2);
    }
    nombreAlg.erase(nombreAlg.begin());


    //ELITE
    istringstream isstream3(elit);
    string palabra3;
    while (isstream3 >> palabra3) {
        elite.push_back(atoi(palabra3.c_str()));
    }
    elite.erase(elite.begin());


    //SEMILLA
    //vector<string> semi;
    istringstream isstream4(sem);
    string palabra4;
    while (isstream4 >> palabra4) {
        semillas.push_back(atoi(palabra4.c_str()));
    }
    semillas.erase(semillas.begin());
    //semilla = stof(semi[0].c_str());


    //PROBABILIDAD CRUCE
    vector<string> prc;
    istringstream isstream5(probc);
    string palabra5;
    while (isstream5 >> palabra5) {
        prc.push_back(palabra5);
    }
    prc.erase(prc.begin());
    probCruce = stof(prc[0].c_str());


    //PROBABILIDAD MUTACION
    vector<string> prm;
    istringstream isstream6(probm);
    string palabra6;
    while (isstream6 >> palabra6) {
        prm.push_back(palabra6);
    }
    prm.erase(prm.begin());
    probMutacion = stof(prm[0].c_str());


    //TAMAÑO DE LA POBLACION
    vector<string> tpob;
    istringstream isstream7(tamPob);
    string palabra7;
    while (isstream7 >> palabra7) {
        tpob.push_back(palabra7);
    }
    tpob.erase(tpob.begin());
    tamPoblacion = stof(tpob[0].c_str());


    //NUMERO MAXIMO DE EVALUACIONES
    vector<string> nEv;
    istringstream isstream8(nEval);
    string palabra8;
    while (isstream8 >> palabra8) {
        nEv.push_back(palabra8);
    }
    nEv.erase(nEv.begin());
    nEvaluaciones = stof(nEv[0].c_str());

}

void FuncionesAux::solucionAleatoria(vector<int>& sol, vector<bool>& noSeleccionados, int tamM, int tamN){
    
    sol.resize(tamM,0);
    noSeleccionados.resize(tamN,false);
    
    int numAleatorio = 0; 
    for(int i = 0; i < tamM; i++){
        numAleatorio = Randint(0,tamN-1);
        while(noSeleccionados[numAleatorio] == true){
            numAleatorio = Randint(0,tamN-1);
        }
        sol[i] = numAleatorio;
        noSeleccionados[numAleatorio] = true; 
    }
    
    
}


void FuncionesAux::GenotipoAleatorio(vector<int>& sol,int tamM, int tamN){
   
    sol.resize(tamM,0);
    vector<bool> noSeleccionados;
    noSeleccionados.resize(tamN,false);
    
    int numAleatorio = 0; 
    for(int i = 0; i < tamM; i++){
        numAleatorio = Randint(0,tamN-1);
        while(noSeleccionados[numAleatorio] == true){
            numAleatorio = Randint(0,tamN-1);
        }
        sol[i] = numAleatorio;
        noSeleccionados[numAleatorio] = true; 
    }
}


float FuncionesAux::coste(vector<vector<float>> matrizDistancias, int m, vector<int> seleccionados) {
    float coste = 0.0;
    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (seleccionados[i] < seleccionados[j]) {
                coste += matrizDistancias[seleccionados[i]][seleccionados[j]];
            } else {
                coste += matrizDistancias[seleccionados[j]][seleccionados[i]];
            }
        }
    }

    return coste;
}

void FuncionesAux::visualizaMatriz(vector<vector<float>> matrizDistancias, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrizDistancias[i][j] << ' ';
        }
        cout << endl;
    }
}

void FuncionesAux::visualizaSeleccionados(vector<int> seleccionados, int m) {
    for (int i = 0; i < m; i++) {
        cout << seleccionados[i] << ' ';
    }
}



