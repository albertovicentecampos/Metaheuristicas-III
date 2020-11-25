/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Alberto
 *
 * Created on 23 de septiembre de 2020, 11:40
 */

#include <cstdlib>
#include <vector>
#include "FuncionesAux.h"
#include "random.h"
#include "timer.h"
#include "Log.h"
#include "GeneticoGeneracional.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    string registro = "registro.txt";
    vector<string> archivos;
    vector<string> algoritmos;
    vector<int> elite;
    int semilla;
    float probabilidadCruce;
    float probabilidadMutacion;
    int tamPoblacion;
    int numEvaluaciones;


    FuncionesAux Faux;

    //Cargamos los datos
    Faux.cargaParametrizacion(registro, archivos, algoritmos, elite, semilla, probabilidadCruce, probabilidadMutacion, tamPoblacion, numEvaluaciones);

    Set_random(semilla);
    
    for(int i = 0; i< archivos.size(); i++){
        
        vector<vector<float>> distancias; 
        int n;
        int m; 
        
        for(int j = 0; j<algoritmos.size(); j++){
            for(int k = 0; k<elite.size(); k++){
                Faux.cargaFichero(archivos[i], distancias, n, m);                
                Log *l = new Log(archivos[i],semilla,algoritmos[j],elite[k]);
                l->crearArchivo();
                l->escribirEnArchivo("ARCHIVO "+archivos[i]+" CON SEMILLA " + to_string(semilla) + "UTILIZANDO EL ALGORITMO "+algoritmos[j]+" Y UNA ELITE DE "+to_string(elite[k]));
                l->saltoLinea();
                
                cout <<"Archivo "+archivos[i]+ " con semilla "+to_string(semilla)+ " Utilizando el algoritmo " + algoritmos[j] + " y una elite de "+ to_string(elite[k]) << endl;
                GeneticoGeneracional g(n,m,distancias, elite[k], tamPoblacion, numEvaluaciones, probabilidadCruce,probabilidadMutacion,l,algoritmos[j]);
                
                l->escribirEnArchivo("**RESULTADOS**");
                l->saltoLinea();
                
                start_timers();
                g.algoritmoGeneticoGeneracional();
                elapsed_time();
                
                l->escribirEnArchivo("Tiempo en realizar el algoritmo: "+to_string(elapsed_time())+" segundos");
                l->cerrarArchivo();
                
                cout<<"Tiempo en realizar el algoritmo: "<<to_string(elapsed_time())+" segundos" << endl;
            }
        }
    }



    return 0;
}

