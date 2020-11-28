/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Individuo.cpp
 * Author: Alberto
 * 
 * Created on 14 de noviembre de 2020, 9:51
 */

#include "Individuo.h"

Individuo::Individuo(): evaluado(false), coste(0), generacion(0), tamGenotipo(0), mutadoAlterado(false) 
{
    genotipo.resize(tamGenotipo, 0);
}

void Individuo::SetMutadoAlterado(bool mutadoAlterado) {
    this->mutadoAlterado = mutadoAlterado;
}

bool Individuo::IsMutadoAlterado() const {
    return mutadoAlterado;
}


void Individuo::SetGeneracion(int generacion) {
    this->generacion = generacion;
}

int Individuo::GetGeneracion() const {
    return generacion;
}

void Individuo::SetCoste(float coste) {
    this->coste = coste;
}

float Individuo::GetCoste() const {
    return coste;
}

void Individuo::SetEvaluado(bool evaluado) {
    this->evaluado = evaluado;
}

bool Individuo::IsEvaluado() const {
    return evaluado;
}

void Individuo::SetTamGenotipo(int tamGenotipo) {
    this->tamGenotipo = tamGenotipo;
}

int Individuo::GetTamGenotipo() const {
    return tamGenotipo;
}


