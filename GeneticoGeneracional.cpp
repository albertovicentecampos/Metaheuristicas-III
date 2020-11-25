/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeneticoGeneracional.cpp
 * Author: Alberto
 * 
 * Created on 14 de noviembre de 2020, 9:57
 */

#include "GeneticoGeneracional.h"
#include "FuncionesAux.h"

GeneticoGeneracional::GeneticoGeneracional(int n, int m, vector<vector<float>> d, int tamEli, int tamPob, int numEval, float probC, float probM, Log* log, string nomOp) :
tamN(n), tamM(m), distancias(d), tamElite(tamEli), tamPoblacion(tamPob), numEvaluaciones(numEval), probCruce(probC), probMut(probM), l(log), contadorEvaluaciones(0), generacion(0), nombreOperador(nomOp) {

    poblacion.resize(tamPoblacion);
    poblacionAux.resize(tamPoblacion);
    for (int i = 0; i < tamPoblacion; i++) {
        poblacion[i];
        poblacionAux[i];
    }
}

void GeneticoGeneracional::algoritmoGeneticoGeneracional() {
    generarPoblacion();
    evaluacion();

    //            for (int i = 0; i < tamPoblacion; i++) {
    //                cout << "INDIVIDUO " + to_string(i) + ": ";
    //                for (int j = 0; j < tamM; j++) {
    //                    cout << poblacion[i].genotipo[j] << ' ';
    //                }
    //                cout << "Coste individuo " + to_string(i) + ": " << poblacion[i].GetCoste();
    //                cout << endl;
    //            }


    //while (contadorEvaluaciones < numEvaluaciones) {
    generacion++;
    //mejorElite();
    seleccionTorneo();
    cruce();
    mutacion();
    //}


}

void GeneticoGeneracional::generarPoblacion() {
    for (int i = 0; i < tamPoblacion; i++) {
        poblacion[i].genotipo.resize(tamM);
        Faux.GenotipoAleatorio(poblacion[i].genotipo, tamM, tamN);
    }
}

void GeneticoGeneracional::evaluacion() {
    for (int i = 0; i < tamPoblacion; i++) {
        float coste = Faux.coste(distancias, tamM, poblacion[i].genotipo);
        poblacion[i].SetCoste(coste);
        poblacion[i].SetEvaluado(true);
        poblacion[i].SetMutadoAlterado(false);
        poblacion[i].SetGeneracion(generacion);

        contadorEvaluaciones++;
    }
}

void GeneticoGeneracional::mejorElite() {

}

void GeneticoGeneracional::seleccionTorneo() {
    int num1 = 0;
    int num2 = 0;

    for (int i = 0; i < tamPoblacion; i++) {
        num1 = Randint(0, tamPoblacion - 1);
        num2 = Randint(0, tamPoblacion - 1);

        while (num1 == num2) {
            num2 = Randint(0, tamPoblacion - 1);
        }

        if (poblacion[num1].GetCoste() < poblacion[num2].GetCoste()) {
            poblacionAux[i] = poblacion[num2];
        } else {
            poblacionAux[i] = poblacion[num1];
        }
    }
}

void GeneticoGeneracional::cruce() {

    for (int i = 0; i < tamPoblacion; i += 2) {
        int num = Randfloat(0, 1);
        if (num < probCruce) {

            if (nombreOperador == "dospuntos") {

//                cout << "Padre 1: ";
//                for (int j = 0; j < tamM; j++) {
//                    cout << poblacionAux[i].genotipo[j] << ' ';
//                }
//                cout << endl;
//                cout << "Padre 2: ";
//                for (int k = 0; k < tamM; k++) {
//                    cout << poblacionAux[i + 1].genotipo[k] << ' ';
//                }
//                cout << endl;

                op.cruceDosPuntos(poblacionAux[i].genotipo, poblacionAux[i + 1].genotipo, tamM, tamN, distancias);

//                cout << "Padre 1 cambiado: ";
//                for (int j = 0; j < tamM; j++) {
//                    cout << poblacionAux[i].genotipo[j] << ' ';
//                }
//
//                cout << endl;
//                cout << "Padre 2 cambiado: ";
//                for (int k = 0; k < tamM; k++) {
//                    cout << poblacionAux[i + 1].genotipo[k] << ' ';
//                }
//                cout << endl;

            } else if (nombreOperador == "MPX") {

//                cout << "Padre 1: ";
//                for (int j = 0; j < tamM; j++) {
//                    cout << poblacionAux[i].genotipo[j] << ' ';
//                }
//                cout << endl;
//                cout << "Padre 2: ";
//                for (int k = 0; k < tamM; k++) {
//                    cout << poblacionAux[i + 1].genotipo[k] << ' ';
//                }
//                cout << endl;

                op.cruceMPX(poblacionAux[i].genotipo, poblacionAux[i+1].genotipo, tamM, tamN, distancias);
//
//                cout << "Hijo 1: ";
//                for (int j = 0; j < tamM; j++) {
//                    cout << poblacionAux[i].genotipo[j] << ' ';
//                }
//
//                cout << endl;
//                cout << "Hijo 2: ";
//                for (int k = 0; k < tamM; k++) {
//                    cout << poblacionAux[i + 1].genotipo[k] << ' ';
//                }
//                cout << endl;

            }
        }
    }

}

void GeneticoGeneracional::mutacion() {

}
