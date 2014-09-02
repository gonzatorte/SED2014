#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "SistemaTransporte.h"
#include <windows.h>

#include <iostream>
#include <fstream>
const unsigned int repeticiones = 5;
int main () {


        std::string s;
        using namespace eosim::core;
        //repito el experimento una cierta cantidad de veces
        ofstream log;
        log.open("LogCasoDeEstudio.txt", ios::trunc);
        log << "Log de Caso de Estudio Ejercicio 13.\n";
        log.close();

        for (int i = 0; i < 5; i ++) {
            std::cout << "Arranco ...\n";
            char buffer[50];
            sprintf(buffer, "LogCasoDeEstudio%d.txt" , i);
            log.open(buffer, ios::app);
            log << "Arranco ...\n";
            log.close();
            SistemaTransporte sistemaTransporte;
            Experiment e;
            sistemaTransporte.connectToExp(&e);
            e.setSeed((unsigned long) i + 129);
            sistemaTransporte.setearSemillasAHuevo(i+129);
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
