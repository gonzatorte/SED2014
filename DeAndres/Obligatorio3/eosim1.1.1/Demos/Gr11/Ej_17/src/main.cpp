#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "SistemaTransporte.h"
#include <windows.h>

#include <iostream>
#include <fstream>
#include <sstream>
const unsigned int repeticiones = 5;

int main () {

        std::string s;
        using namespace eosim::core;
        //repito el experimento una cierta cantidad de veces
        ofstream log;
        log.open("LogCasoDeEstudio.txt", ios::trunc);
        log << "Log de Caso de Estudio Ejercicio 13.\n";
        log.close();
        double*** frecuencias = new double**[85];
        double** costos = new double*[85];
        for (int i = 0; i < 85; i++ ){
            frecuencias[i] = new double *[85];
            costos[i] = new double [85];
            for (int j = 0; j < 85; j++) {
                frecuencias[i][j] = new double[5];
                costos[i][j] = 0;
                for (int k = 0; k < 5; k++) {
                    frecuencias[i][j][k] = 0;

                }
            }
        }
        // Creo Costos
        string lineCostos;
        ifstream conexiones ("src/conexiones.txt");
        double costo;
        int origen;
        int destino;

        if (conexiones.is_open())
        {
            while ( getline (conexiones,lineCostos) )
            {
                std::istringstream iss(lineCostos);
                iss >> origen;
                iss >> destino;
                iss >> costo;
                costos[origen][destino] = costo;
            }
            conexiones.close();
        }

        // Creo Personas
        string lineMatriz;
        string lineMatriz1;
        string lineMatriz2;
        ifstream matrizOD ("src/matrizOD.txt");
        ifstream matrizOD1 ("src/matrizOD_hp1.txt");
        ifstream matrizOD2 ("src/matrizOD_hp2.txt");
        double frecuenciaPasajeros;
        double frecuenciaPasajeros1;
        double frecuenciaPasajeros2;
        int fila = 1;
        if (matrizOD.is_open() && matrizOD1.is_open() && matrizOD2.is_open())
        {
            while ( getline (matrizOD,lineMatriz) && getline(matrizOD1,lineMatriz1) && getline(matrizOD2,lineMatriz2) )
            {
                std::istringstream iss(lineMatriz);
                std::istringstream iss1(lineMatriz1);
                std::istringstream iss2(lineMatriz2);
                for (int columna = 1; columna < 85; columna ++){
                    iss >> frecuenciaPasajeros;
                    iss1 >> frecuenciaPasajeros1;
                    iss2 >> frecuenciaPasajeros2;
                    frecuencias[fila][columna][1] = frecuenciaPasajeros;
                    frecuencias[fila][columna][2] = frecuenciaPasajeros1;
                    frecuencias[fila][columna][3] = frecuenciaPasajeros2;

                    frecuenciaPasajeros = max(frecuenciaPasajeros,frecuenciaPasajeros1);
                    frecuenciaPasajeros = max(frecuenciaPasajeros,frecuenciaPasajeros2);
                    frecuencias[fila][columna][4] = frecuenciaPasajeros;
                    if (frecuenciaPasajeros > 0) {
                        frecuencias[fila][columna][0] = 1/frecuenciaPasajeros;
                    }
                }
                fila++;
            }
            matrizOD.close();
        }


        std::cout << "Desea que se muestre la interfaz? (S/N)" << endl;
        char salida;
        std::cin >> salida;
        bool muestroInterfaz = false;
        if (salida == 'S')
            muestroInterfaz = true;


        for (int i = 0; i < 5; i ++) {
            std::cout << "Arranco ...\n";
            char buffer[50];
            sprintf(buffer, "LogCasoDeEstudio%d.txt" , i);
            log.open(buffer, ios::trunc);
            log << "Arranco ...\n";
            log.close();
            SistemaTransporte sistemaTransporte(frecuencias,costos, muestroInterfaz);
            Experiment e;
            sistemaTransporte.connectToExp(&e);
            e.setSeed((unsigned long) i + 129);
//            sistemaTransporte.setearSemillasAHuevo(i+129);
            e.run(960.0);
            std::cout << "Termine ...\n\n\n";
            sprintf(buffer, "LogCasoDeEstudio%d.txt" , i);
            log.open(buffer, ios::app);
            log << "Termine ...\n\n\n";
            log.close();
            sistemaTransporte.imprimirFlotaPorLinea(i);
            sprintf(buffer, "tiempoEsperaGlobal%d.txt" , i);
            sistemaTransporte.histTEsperaGlobal.table(100,buffer);
            system("PAUSE");
        }

}
