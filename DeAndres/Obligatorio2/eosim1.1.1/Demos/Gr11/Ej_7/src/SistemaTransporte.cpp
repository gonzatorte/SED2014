#include <stdio.h>
#include "SistemaTransporte.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include <eosim/core/entity.hpp>
//#include <eosim/core/model.hpp>
using namespace eosim::core;

SistemaTransporte::SistemaTransporte() :
        crearOmnibus(*this),
        bajarPasajeros(*this),
        subirPasajeros(*this),
        crearPasajero(*this)
{

}

SistemaTransporte::~SistemaTransporte()
{

}

Linea* SistemaTransporte::getLinea(int linea) {
    return this->lineas[linea];
}

double SistemaTransporte::obtenerCosto(int paradaOrigen, int paradaDestino) {
    return (this->costos[paradaOrigen][paradaDestino]/(1000*13))*60;
}

void SistemaTransporte::imprimirFlotaPorLinea() {
    for (int i = 0; i<13; i++) {
        cout << "Linea numero " << lineas[i]->getLinea() << " tiene " << lineas[i]->getCantFlota() << " Omnibus." << endl;
        ofstream log;
        log.open("LogCasoDeEstudio.txt", ios::app);
        log << "Linea numero " << lineas[i]->getLinea() << " tiene " << lineas[i]->getCantFlota() << " Omnibus." << endl;
        log.close();
    }
}

void SistemaTransporte::init() {
    registerBEvent(&crearOmnibus);
	registerBEvent(&bajarPasajeros);
	registerBEvent(&subirPasajeros);
	registerBEvent(&crearPasajero);
}

void SistemaTransporte::doInitialSchedules() {

    // Creo Lineas
    string line;
    int anterior = -2;
    ifstream recorridos ("src/recorridos.txt");
    int numeroLinea;
    double frecuenciaLinea;
    int nodoLinea;
    int cantLineas = 0;

    vector<int> recorridoLinea;

    if (recorridos.is_open())
    {
        while ( getline (recorridos,line) )
        {
            std::istringstream iss(line);
            iss >> numeroLinea;
            iss >> frecuenciaLinea;
            iss >> nodoLinea;
            while (anterior != nodoLinea) {
                recorridoLinea.push_back(nodoLinea);
                anterior = nodoLinea;
                iss >> nodoLinea;
            }
            lineas[cantLineas] = new Linea(numeroLinea,1/frecuenciaLinea,recorridoLinea, 0);
            schedule(0.0, (Entity*) lineas[cantLineas], crearOm);
//            cout << "Linea numero " << cantLineas << endl;
//            for (int i = 0; i < recorridoLinea.size(); i++) {
//                cout << recorridoLinea[i] << endl;
//            }
            recorridoLinea.clear();
            anterior = -2;
            cantLineas++;

            //cout << lineas[cantLineas-1]->getRecorrido()[0] << lineas[cantLineas-1]->getRecorrido()[1] << lineas[cantLineas-1]->getRecorrido()[2] << lineas[cantLineas-1]->getRecorrido()[3] << endl;

        }
        recorridos.close();
    }
    // Creo Personas
    string lineMatriz;
    ifstream matrizOD ("src/matrizOD.txt");
    double frecuenciaPasajeros;
    int fila = 1;

    if (matrizOD.is_open())
    {
        while ( getline (matrizOD,lineMatriz) )
        {
            std::istringstream iss(lineMatriz);
            for (int columna = 1; columna < 85; columna ++){
                iss >> frecuenciaPasajeros;
                if (frecuenciaPasajeros > 0) {
                    Pasajero* p = new Pasajero(columna,fila,(1/frecuenciaPasajeros));
                    schedule(0, (Entity*) p, crearPa);
                }
            }
            fila++;

        }
        matrizOD.close();
    }

    // Creo Costos
    string lineCostos;
    ifstream conexiones ("src/conexiones.txt");
    double costo;
    int origen;
    int destino;
    for (int i = 0; i < 86; i++) {
        for (int j = 0; j < 86; j++) {
            costos[i][j] = 0;
        }
    }
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
        matrizOD.close();
    }
}



