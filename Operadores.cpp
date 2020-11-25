/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Operadores.cpp
 * Author: Alberto
 * 
 * Created on 10 de noviembre de 2020, 18:27
 */


#include "Operadores.h"

void Operadores::eliminarRepetidos(vector<int>& v, int tam) {

    for (int i = 0; i < tam - 1; i++) {
        for (int j = i + 1; j < tam; j++) {
            if (v[i] == v[j]) {
                v[j] = -1;
            }
        }
    }


}

void Operadores::reparacionConstruccionGreedy(vector<int>& v, int tam, int tamN, vector<vector<float>> distancias) {
    vector<bool> noSeleccionados;
    noSeleccionados.resize(tamN, false);

    vector<float> vDistancia;
    vector<pair<int, float>> distMayor;


    for (int i = 0; i < tam; i++) {
        if (v[i] != -1) {
            noSeleccionados[v[i]] = true;
        }
    }

    //Comprobamos si tiene -1 (ha habido repetidos)

    for (int i = 0; i < tam; i++) {
        if (v[i] == -1) {
            for (int j = 0; j < tamN; j++) {
                if (noSeleccionados[j] == false) {
                    vDistancia.resize(tamN, 0);
                    for (int k = 0; k < tam; k++) {
                        if (v[k] != -1) {
                            if (j < v[k]) {
                                vDistancia[j] += distancias[j][v[k]];
                            } else {
                                vDistancia[j] += distancias[v[k]][j];
                            }
                        }
                    }

                }
            }

            distMayor.resize(tamN);
            for (int t = 0; t < tamN; t++) {
                distMayor[t].first = t;
                distMayor[t].second = vDistancia[t];
            }

            //Lo ordenamos
            pair<int, float> temporal;
            for (int k = 0; k < tamN; k++) {
                for (int t = k + 1; t < tamN; t++) {
                    if (distMayor[k].second < distMayor[t].second) {
                        temporal = distMayor[k];
                        distMayor[k] = distMayor[t];
                        distMayor[t] = temporal;
                    }
                }
            }

            v[i] = distMayor[0].first;
            noSeleccionados[distMayor[0].first] = true;

        }
    }


    //cout << "HA HECHO REPARACION" << endl;
}

void Operadores::cruceDosPuntos(vector<int>& padre1, vector<int>& padre2, int tam, int tamN, vector<vector<float>> distancias) {

    int a = 0;
    int b = 0;
    vector<int> padre1generado;
    padre1generado.resize(tam);
    vector<int> padre2generado;
    padre2generado.resize(tam);


    b = Randint(2, tam - 1);
    a = Randint(1, tam - 1);

    while (a >= b) {
        a = Randint(1, tam - 1);
    };


    //cout << "a: " << a << " b: " << b << endl;

    for (int i = 0; i < a; i++) {
        padre1generado[i] = padre1[i];
        padre2generado[i] = padre2[i];
    }

    for (int j = a; j < b; j++) {
        padre1generado[j] = padre2[j];
        padre2generado[j] = padre1[j];
    }

    for (int k = b; k < tam; k++) {
        padre1generado[k] = padre1[k];
        padre2generado[k] = padre2[k];
    }

    eliminarRepetidos(padre1generado, tam);
    eliminarRepetidos(padre2generado, tam);


    reparacionConstruccionGreedy(padre1generado, tam, tamN, distancias);
    reparacionConstruccionGreedy(padre2generado, tam, tamN, distancias);

    padre1 = padre1generado;
    padre2 = padre2generado;


    //cout << "fin" << endl;
}

vector<int> Operadores::hijoMPX(vector<int> padre1, vector<int> padre2, int tam, int tamN, vector<vector<float>> distancias) {

    float porcentaje = 0.0;
    porcentaje = Randfloat(0.2, 0.8);

    vector<int> hijo1;
    vector<int> hijo2;
    hijo1.resize(tam, -1); //METEMOS UN PORCENTAJE DE ELEMENTOS DEL PADRE 1 
    hijo2.resize(tam, -1); //METEMOS LOS RESTANTES NO REPETIDOS DEL PADRE 2

    int numElementos = 0;
    numElementos = porcentaje*tam;

    for (int i = 0; i < numElementos; i++) {
        hijo1[i] = padre1[i];
    }

    int t = 0;
    for (int i = 0; i < tam; i++) {
        bool esta = false;
        for (int j = 0; j < numElementos; j++) {
            if (padre2[i] == hijo1[j]) {
                esta = true;
                break;
            }
        }

        if (!esta) {
            hijo2[t] = padre2[i];
            t++;
        }
    }

    //contamos el número de elementos que tenemos
    int cont = 0;
    for (int i = 0; i < tam; i++) {
        if (hijo1[i] != -1) {
            cont++;
        }

        if (hijo2[i] != -1) {
            cont++;
        }
    }

//    cout << cont << endl;


    vector<int> reparar;
    reparar.resize(cont, -1);

    int u = 0;
    int i = 0;
    int treparar = 0;


    while (hijo1[u] != -1 && u < tam) {
        reparar[treparar] = hijo1[u];
        u++;
        treparar++;

    }

    while (hijo2[i] != -1 && i < tam) {
        reparar[treparar] = hijo2[i];
        i++;
        treparar++;

    }

    

    while (cont > tam) {

        vector<float> vDistancia;
        vDistancia.resize(tamN, 0);

        for (int i = 0; i < cont; i++) {
            for (int j = 0; j < cont; j++) {
                if (reparar[i] < reparar[j]) {
                    vDistancia[reparar[i]] += distancias[reparar[i]][reparar[j]];
                } else {
                    vDistancia[reparar[i]] += distancias[reparar[j]][reparar[i]];
                }
            }
        }

        vector<pair<int, float>> distMayor;
        distMayor.reserve(cont);

        for (int i = 0; i < cont; i++) {
            distMayor[i].first = reparar[i];
            distMayor[i].second = vDistancia[reparar[i]];
        }

        //Ordenamos de mayor a menor  y cogemos el último porque es el menor aporte nos da
        pair<int, float> temporal;
        for (int i = 0; i < cont; i++) {
            for (int j = i + 1; j < cont; j++) {
                if (distMayor[i].second < distMayor[j].second) {
                    temporal = distMayor[i];
                    distMayor[i] = distMayor[j];
                    distMayor[j] = temporal;
                }
            }
        }

        //Buscamos este elemento en el vector de reparacion y lo eliminamos

        for (int i = 0; i < cont; i++) {
            if (distMayor[cont - 1].first == reparar[i]) {
                reparar.erase(reparar.begin() + i);
                cont--;
                break;
            }
        }
    }

    return reparar;

}

void Operadores::cruceMPX(vector<int>& padre1, vector<int>& padre2, int tam, int tamN, vector<vector<float>> distancias) {

    vector<int> hijo1;
    vector<int> hijo2;

    hijo1.resize(tam, 0);
    hijo2.resize(tam, 0);


    hijo1 = hijoMPX(padre1, padre2, tam, tamN, distancias);
    hijo2 = hijoMPX(padre2, padre1, tam, tamN, distancias);

    padre1 = hijo1;
    padre2 = hijo2;

}


void Operadores::mutacion(vector<int> genotipo, int j, int tamN, int tam){
    
    vector<bool> noSeleccionados;
    noSeleccionados.resize(tamN, false);
    
    for(int i = 0; i< tam; i++){
        noSeleccionados[genotipo[i]] = true;
    }
    
    int posAleatoria = 0;
    posAleatoria = Randint(0,tamN-1);
    
    while(noSeleccionados[posAleatoria] == true){
        posAleatoria = Randint(0,tamN-1);
    }
    
    genotipo[j] = posAleatoria;
    
}