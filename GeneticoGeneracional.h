/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeneticoGeneracional.h
 * Author: Alberto
 *
 * Created on 14 de noviembre de 2020, 9:57
 */

#ifndef GENETICOGENERACIONAL_H
#define GENETICOGENERACIONAL_H
#include "Individuo.h"
#include "Log.h"
#include "FuncionesAux.h"

using namespace std;

class GeneticoGeneracional {
public:
    GeneticoGeneracional(int n, int m, vector<vector<float>> d,int tamEli, int tamPob, int numEval, float probCruce, float probMutacion, Log* log);
    void algoritmoGeneticoGeneracional();
    void generarPoblacion();
    void evaluacion(); 
    void mejorElite();
    void seleccionTorneo();
    void cruce();
    void mutacion();
    
    
private:
    FuncionesAux Faux; 
    Log *l;
    int tamN; 
    int tamM; 
    int tamElite; 
    int tamPoblacion; 
    int numEvaluaciones; 
    float probCruce;
    float probMut;
    vector<vector<float>> distancias; 
    
    vector<Individuo> poblacion; 
    vector<Individuo> poblacionAux;
    int contadorEvaluaciones; 
    int generacion; 
    

};

#endif /* GENETICOGENERACIONAL_H */

