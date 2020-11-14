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

GeneticoGeneracional::GeneticoGeneracional(int n, int m, vector<vector<float>> d, int tamEli, int tamPob, int numEval, float probC, float probM, Log* log) :
tamN(n), tamM(m), distancias(d), tamElite(tamEli), tamPoblacion(tamPob), numEvaluaciones(numEval), probCruce(probC), probMut(probM), l(log), contadorEvaluaciones(0), generacion(0) {

    poblacion.resize(tamPoblacion);
    poblacionAux.resize(tamPoblacion);
    for (int i = 0; i < tamPoblacion; i++) {
        poblacion.at(i);
        poblacionAux.at(i);
    }
}

void GeneticoGeneracional::algoritmoGeneticoGeneracional() {
    generarPoblacion();
    evaluacion();

    //    for (int i = 0; i < tamPoblacion; i++) {
    //        cout << "INDIVIDUO " + to_string(i) + ": ";
    //        for (int j = 0; j < tamM; j++) {
    //            cout << poblacion.at(i).genotipo[j] << ' ';
    //        }
    //        cout << "Coste individuo " + to_string(i) + ": " << poblacion.at(i).GetCoste();
    //        cout << endl;
    //    }


    while (contadorEvaluaciones < numEvaluaciones) {
        generacion++;
        mejorElite();
        seleccionTorneo();
        cruce();
        mutacion();
    }


}

void GeneticoGeneracional::generarPoblacion() {
    for (int i = 0; i < tamPoblacion; i++) {
        poblacion.at(i).genotipo.resize(tamM);
        Faux.GenotipoAleatorio(poblacion.at(i).genotipo, tamM, tamN);
    }
}

void GeneticoGeneracional::evaluacion() {
    for (int i = 0; i < tamPoblacion; i++) {
        float coste = Faux.coste(distancias, tamM, poblacion.at(i).genotipo);
        poblacion.at(i).SetCoste(coste);
        poblacion.at(i).SetEvaluado(true);
        poblacion.at(i).SetMutadoAlterado(false);
        poblacion.at(i).SetGeneracion(generacion);

        contadorEvaluaciones++;
    }
}

void GeneticoGeneracional::mejorElite() {

}

void GeneticoGeneracional::seleccionTorneo() {

}

void GeneticoGeneracional::cruce() {

}

void GeneticoGeneracional::mutacion() {

}
