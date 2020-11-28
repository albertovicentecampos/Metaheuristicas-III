/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Individuo.h
 * Author: Alberto
 *
 * Created on 14 de noviembre de 2020, 9:51
 */

#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <vector>
using namespace std; 

class Individuo {
public:
    Individuo();
    void SetMutadoAlterado(bool mutadoAlterado);
    bool IsMutadoAlterado() const;
    void SetGeneracion(int generacion);
    int GetGeneracion() const;
    void SetCoste(float coste);
    float GetCoste() const;
    void SetEvaluado(bool evaluado);
    bool IsEvaluado() const;
    void SetTamGenotipo(int tamGenotipo);
    int GetTamGenotipo() const;
    vector<int> genotipo; 
    
private:
    bool evaluado;
    float coste; 
    int generacion; 
    int tamGenotipo;
    bool mutadoAlterado;
 
};

#endif /* INDIVIDUO_H */

