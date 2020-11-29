/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Operadores.h
 * Author: Alberto
 *
 * Created on 10 de noviembre de 2020, 18:27
 */

#ifndef OPERADORES_H
#define OPERADORES_H
#include "random.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std; 

class Operadores {
public:
    void eliminarRepetidos(vector<int>& v,int tam);
    void reparacionConstruccionGreedy(vector<int>& v, int tam, int tamN, vector<vector<float>> distancias);
    void cruceDosPuntos(vector<int>& padre1, vector<int>& padre2, int tam, int tamN,vector<vector<float>> distancias);
    vector<int> hijoMPX(vector<int> padre1, vector<int> padre2, int tam, int tamN,vector<vector<float>> distancias); 
    void cruceMPX(vector<int>& padre1, vector<int>& padre2, int tam, int tamN,vector<vector<float>> distancias);
    void mutacion(vector<int>& genotipo, int j, int tamN, int tam);
    
    
};

#endif /* OPERADORES_H */

