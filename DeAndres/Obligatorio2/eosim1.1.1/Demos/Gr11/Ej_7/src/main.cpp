#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "SistemaTransporte.h"

#include <iostream>
#include <fstream>

int main () {
	std::string s;
    using namespace eosim::core;
    //repito el experimento una cierta cantidad de veces
    ofstream log;
    log.open("LogCasoDeEstudio.txt", ios::trunc);
    log << "Log de Caso de Estudio Ejercicio 7.\n";
    log.close();
    SistemaTransporte* sistemaTransporte = new SistemaTransporte();
    Experiment e;
    std::cout << "Arranco ...\n";
    log.open("LogCasoDeEstudio.txt", ios::app);
    log << "Arranco ...\n";
    log.close();
    sistemaTransporte->connectToExp(&e);
    e.setSeed((unsigned long) 1 + 129);
    e.run(960.0);
    std::cout << "Termine ...\n\n\n";
    log.open("LogCasoDeEstudio.txt", ios::app);
    log << "Termine ...\n\n\n";
    log.close();
    sistemaTransporte->imprimirFlotaPorLinea();
}
