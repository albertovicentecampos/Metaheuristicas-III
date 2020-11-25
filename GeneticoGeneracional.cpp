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

    elite.resize(tamElite);
    for (int i = 0; i < tamElite; i++) {
        elite[i];
    }

    peoresPosiciones.resize(tamElite);

    mejorIndividuoPoblacion = Individuo();
    mejorIndividuoGlobal = Individuo();
}

void GeneticoGeneracional::algoritmoGeneticoGeneracional() {
    generarPoblacion();
    evaluacion();
    l->escribirEnArchivo("");

    //            for (int i = 0; i < tamPoblacion; i++) {
    //                cout << "INDIVIDUO " + to_string(i) + ": ";
    //                for (int j = 0; j < tamM; j++) {
    //                    cout << poblacion[i].genotipo[j] << ' ';
    //                }
    //                cout << "Coste individuo " + to_string(i) + ": " << poblacion[i].GetCoste();
    //                cout << endl;
    //            }


    l->escribirEnArchivo("POBLACION INICIAL GENERADA");
    for (int i = 0; i < tamPoblacion; i++) {
        l->escribirEnArchivo("=================");
        l->escribirEnArchivo("Individuo" + to_string(i));
        l->escribirEnArchivo("-Coste: " + to_string(poblacion[i].GetCoste()));
        l->escribirEnArchivoVector("-Genotipo: ");
        for (int j = 0; j < tamM; j++) {
            l->escribirEnArchivoVector(to_string(poblacion[i].genotipo[j]) + ' ');
        }
    }

    l->escribirEnArchivo("=================");
    l->saltoLinea();


    while (contadorEvaluaciones < numEvaluaciones) {
        l->escribirEnArchivo("GENERACION: " + to_string(generacion));
        generacion++;
        mejorElite();
        seleccionTorneo();
        cruce();
        mutacion();
        evaluacion2();
        reemplazoElite();
        mejorIndividuo();
        poblacion = poblacionAux;

        l->escribirEnArchivo("Resultados generacion " + to_string(generacion));
        l->escribirEnArchivo("Coste del mejor individuo de la poblacion: " + to_string(mejorIndividuoPoblacion.GetCoste()));
        l->escribirEnArchivo("Coste del mejor individuo global: " + to_string(mejorIndividuoGlobal.GetCoste()));

    }

    l->escribirEnArchivo("****************RESULTADOS FINALES*****************");
    l->escribirEnArchivo("Datos del mejor individuo");

    l->escribirEnArchivoVector("Genotipo: ");

    for (int i = 0; i < tamM; i++) {
        l->escribirEnArchivoVector(to_string(mejorIndividuoGlobal.genotipo[i]) + " ");
    }
    l->saltoLinea();
    l->escribirEnArchivo("Coste: " + to_string(mejorIndividuoGlobal.GetCoste()));
    l->escribirEnArchivo("Generacion que se genero: " + to_string(mejorIndividuoGlobal.GetGeneracion()));
    l->saltoLinea();
    cout << "Coste del mejor individuo: " << mejorIndividuoGlobal.GetCoste() << endl;

    l->escribirEnArchivo("El numero total de generaciones: " + to_string(generacion) + " con un total de " + to_string(contadorEvaluaciones) + " evaluaciones");

}

void GeneticoGeneracional::generarPoblacion() {
    for (int i = 0; i < tamPoblacion; i++) {
        poblacion[i].genotipo.resize(tamM);
        Faux.GenotipoAleatorio(poblacion[i].genotipo, tamM, tamN);
    }
}

void GeneticoGeneracional::evaluacion() {
    for (int i = 0; i < tamPoblacion; i++) {
        evaluarIndividuo(poblacion[i]);
        contadorEvaluaciones++;
    }
}

void GeneticoGeneracional::evaluarIndividuo(Individuo& ind) {
    float coste = Faux.coste(distancias, tamM, ind.genotipo);
    ind.SetCoste(coste);
    ind.SetEvaluado(true);
    ind.SetMutadoAlterado(false);
    ind.SetGeneracion(generacion);
}

void GeneticoGeneracional::mejorElite() {
    set<pair<float, int>> ordenados;
    for (int i = 0; i < tamPoblacion; i++) {
        pair<float, int> p(poblacion[i].GetCoste(), i);
        ordenados.insert(p);
    }

    set<pair<float, int>>::iterator it = ordenados.begin();
    l->escribirEnArchivo("MEJORES " + to_string(tamElite) + " INDIVIDUOS");
    for (int i = 0; i < tamElite; i++) {
        l->escribirEnArchivo("---------------------------------");
        l->escribirEnArchivo("Individuo " + to_string(it->second));
        l->escribirEnArchivo("-Coste: " + to_string(poblacion[it->second].GetCoste()));
        elite[i] = poblacion[it->second];
        //        elite[i].SetCoste(it->first);
        //        elite[i].genotipo = poblacion[it->second].genotipo;
        it++;
    }

    l->escribirEnArchivo("---------------------------------");
    l->saltoLinea();

}

void GeneticoGeneracional::seleccionTorneo() {
    int num1 = 0;
    int num2 = 0;
    l->escribirEnArchivo("TORNEO");
    for (int i = 0; i < tamPoblacion; i++) {
        num1 = Randint(0, tamPoblacion - 1);
        num2 = Randint(0, tamPoblacion - 1);

        while (num1 == num2) {
            num2 = Randint(0, tamPoblacion - 1);
        }

        l->escribirEnArchivo("---------------------------------");
        l->escribirEnArchivo("INDIVIDUO " + to_string(num1) + " con coste " + to_string(poblacion[num1].GetCoste()) + " || " + " INDIVIDUO " + to_string(num2) + " con coste " + to_string(poblacion[num2].GetCoste()));
        if (poblacion[num1].GetCoste() < poblacion[num2].GetCoste()) {

            l->escribirEnArchivo("Individuo escogido: " + to_string(num2));
            l->escribirEnArchivo("---------------------------------");
            poblacionAux[i] = poblacion[num2];
        } else {

            l->escribirEnArchivo("Individuo escogido: " + to_string(num1));
            l->escribirEnArchivo("---------------------------------");
            poblacionAux[i] = poblacion[num1];
        }
    }

    l->saltoLinea();
}

void GeneticoGeneracional::cruce() {

    l->escribirEnArchivo("CRUCE");
    for (int i = 0; i < tamPoblacion; i += 2) {
        int num = Randfloat(0, 1);
        if (num < probCruce) {

            if (nombreOperador == "dospuntos") {

                if (generacion < 30) {

                    l->saltoLinea();
                    l->escribirEnArchivo("Generacion: " + to_string(generacion));
                    l->escribirEnArchivoVector("Padre 1 antes de ser cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Padre 2 antes de ser cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i + 1].genotipo[j]) + " ");
                    }
                    l->saltoLinea();

                } else if (generacion % 10 == 0) {

                    l->saltoLinea();
                    l->escribirEnArchivo("Generacion: " + to_string(generacion));
                    l->escribirEnArchivoVector("Padre 1 antes de ser cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Padre 2 antes de ser cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i + 1].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                }

                op.cruceDosPuntos(poblacionAux[i].genotipo, poblacionAux[i + 1].genotipo, tamM, tamN, distancias);

                if (generacion < 30) {
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Hijo 1 cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Hijo 2 cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i + 1].genotipo[j]) + " ");
                    }
                    l->saltoLinea();

                } else if (generacion % 10 == 0) {
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Hijo 1 cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Hijo 2 cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i + 1].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                }

                poblacionAux[i].SetMutadoAlterado(true);
                poblacionAux[i + 1].SetMutadoAlterado(true);

            } else if (nombreOperador == "MPX") {

                if (generacion < 30) {

                    l->saltoLinea();
                    l->escribirEnArchivo("Generacion: " + to_string(generacion));
                    l->escribirEnArchivoVector("Padre 1 antes de ser cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Padre 2 antes de ser cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i + 1].genotipo[j]) + " ");
                    }
                    l->saltoLinea();

                } else if (generacion % 10 == 0) {

                    l->saltoLinea();
                    l->escribirEnArchivo("Generacion: " + to_string(generacion));
                    l->escribirEnArchivoVector("Padre 1 antes de ser cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Padre 2 antes de ser cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i + 1].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                }

                op.cruceMPX(poblacionAux[i].genotipo, poblacionAux[i + 1].genotipo, tamM, tamN, distancias);

                if (generacion < 30) {
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Hijo 1 cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Hijo 2 cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i + 1].genotipo[j]) + " ");
                    }
                    l->saltoLinea();

                } else if (generacion % 10 == 0) {
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Hijo 1 cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                    l->escribirEnArchivoVector("Hijo 2 cruzado: ");
                    for (int j = 0; j < tamM; j++) {
                        l->escribirEnArchivoVector(to_string(poblacionAux[i + 1].genotipo[j]) + " ");
                    }
                    l->saltoLinea();
                }

                poblacionAux[i].SetMutadoAlterado(true);
                poblacionAux[i + 1].SetMutadoAlterado(true);

            }
        }
    }

}

void GeneticoGeneracional::mutacion() {
    l->escribirEnArchivo("MUTACION");
    for (int i = 0; i < tamPoblacion; i++) {

        if (generacion < 30) {
            l->escribirEnArchivo("Generacion: " + to_string(generacion));
            l->escribirEnArchivo("Mutando el individuo numero " + to_string(i));
            l->escribirEnArchivoVector("Genotipo antes de ser mutado: ");

            for (int z = 0; z < tamM; z++) {
                l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[z]) + " ");
            }

        } else if (generacion % 10 == 0) {
            l->escribirEnArchivo("Generacion: " + to_string(generacion));
            l->escribirEnArchivo("Mutando el individuo numero " + to_string(i));
            l->escribirEnArchivoVector("Genotipo antes de ser mutado: ");

            for (int z = 0; z < tamM; z++) {
                l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[z]) + " ");
            }
        }

        for (int j = 0; j < tamM; j++) {
            float x = Randfloat(0, 1);
            if (x < probMut) {

                op.mutacion(poblacionAux[i].genotipo, j, tamN, tamM);
                poblacionAux[i].SetMutadoAlterado(true);
            }
        }

        if (generacion < 30) {
            l->saltoLinea();
            l->escribirEnArchivoVector("Genotipo mutado: ");
            for (int z = 0; z < tamM; z++) {
                l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[z]) + " ");
            }

        } else if (generacion % 10 == 0) {
            l->saltoLinea();
            l->escribirEnArchivoVector("Genotipo mutado: ");
            for (int z = 0; z < tamM; z++) {
                l->escribirEnArchivoVector(to_string(poblacionAux[i].genotipo[z]) + " ");
            }
        }

    }

}

void GeneticoGeneracional::evaluacion2() {
    l->escribirEnArchivo("SEGUNDA EVALUACION");
    for (int i = 0; i < tamPoblacion; i++) {
        if (poblacionAux[i].IsMutadoAlterado()) {
            evaluarIndividuo(poblacionAux[i]);
            contadorEvaluaciones++;
            poblacionAux[i].SetGeneracion(generacion);
            l->escribirEnArchivo("Individuo "+to_string(i));
            l->escribirEnArchivo("-Coste: "+to_string(poblacionAux[i].GetCoste()));
            l->escribirEnArchivo("-Generacion: "+to_string(poblacionAux[i].GetGeneracion()));
        }
    }
}

void GeneticoGeneracional::reemplazoElite() {
    l->escribirEnArchivo("REEMPLAZO LOS "+to_string(tamElite)+" PEORES INDIVIDUOS DE LA POBLACION POR LOS MEJORES DE LA ELITE");
    set<pair<float, int>> orden;
    for (int i = 0; i < tamPoblacion; i++) {
        pair<float, int> p(poblacionAux[i].GetCoste(), i);
        orden.insert(p);
    }
    set<pair<float, int>>::iterator it = orden.end();
    for (int i = 0; i < tamElite; i++) {
        --it;
        //peoresPosiciones[i] = it->second;
        l->escribirEnArchivo("Reemplazo el individuo "+to_string(it->second)+" que tiene un coste de "+to_string(poblacionAux[it->second].GetCoste())+" por el de la elite que tiene un coste de "+to_string(elite[i].GetCoste()));
        poblacionAux[it->second] = elite[i];
    }
}

void GeneticoGeneracional::mejorIndividuo() {

    //Mejor Individuo  de la poblacion
    for (int i = 0; i < tamPoblacion; i++) {
        if (poblacionAux[i].GetCoste() > mejorIndividuoPoblacion.GetCoste()) {
            mejorIndividuoPoblacion = poblacionAux[i];
        }
    }
    
    l->escribirEnArchivo("Mejor individuo de la poblacion tiene un coste de: "+to_string(mejorIndividuoPoblacion.GetCoste()));

    //Mejor Individuo global
    if (mejorIndividuoPoblacion.GetCoste() > mejorIndividuoGlobal.GetCoste()) {
        mejorIndividuoGlobal = mejorIndividuoPoblacion;
    }

    l->escribirEnArchivo("Mejor individuo global tiene un coste de: "+to_string(mejorIndividuoGlobal.GetCoste()));


}