#include "Pasajero.h"
#include "SistemaTransporte.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace eosim::core;

Pasajero::Pasajero(int p_paradaDestino, int p_paradaOrigen, double p_pasajeroFrecuencia) : Entity(), paradaDestino(p_paradaDestino), paradaOrigen(p_paradaOrigen), pasajeroFrecuencia(p_pasajeroFrecuencia)
{

}

Pasajero::~Pasajero()
{

}

int Pasajero::getParadaDestino() {
    return this->paradaDestino;
}

int Pasajero::getParadaOrigen() {
    return this->paradaOrigen;
}

double Pasajero::getPasajeroFrecuencia() {
    return this->pasajeroFrecuencia;
}

CrearPasajero::CrearPasajero(Model& model) : BEvent(crearPa, model) {}

CrearPasajero::~CrearPasajero() {}

void CrearPasajero::eventRoutine(Entity* who) {

	Pasajero* pasajero = dynamic_cast<Pasajero*>(who);

	SistemaTransporte& sistemaTransporte = dynamic_cast<SistemaTransporte&>(owner);

    sistemaTransporte.paradaPasajeros[pasajero->getParadaOrigen()].push((Entity*) pasajero);

//    cout << "Se crea nuevo Pasajero con ParadaOrigen " << pasajero->getParadaOrigen() << " y ParadaDestino " << pasajero->getParadaDestino() << " en tiempo " << pasajero->getClock() << endl;
//    ofstream log;
//    log.open("LogCasoDeEstudio.txt", ios::app);
//    log << "Se crea nuevo Pasajero con ParadaOrigen " << pasajero->getParadaOrigen() << " y ParadaDestino " << pasajero->getParadaDestino() << " en tiempo " << pasajero->getClock() << endl;
//    log.close();

    double valor = sistemaTransporte.m[pasajero->getParadaOrigen()*84 + pasajero->getParadaDestino()]->sample();
    Pasajero* pNuevo = new Pasajero(pasajero->getParadaDestino(), pasajero->getParadaOrigen(), valor);
    if (sistemaTransporte.muestraDisplay) {
        std::stringstream valorPasajero;
        valorPasajero << pasajero->getParadaOrigen() << " - " << sistemaTransporte.paradaPasajeros[pasajero->getParadaOrigen()].size();
        sistemaTransporte.referenciaParadas[pasajero->getParadaOrigen()].setText(valorPasajero.str().c_str());
    }
    //sistemaTransporte.schedule(pasajero->getPasajeroFrecuencia(), (Entity*) pNuevo, crearPa);
    sistemaTransporte.schedule(sistemaTransporte.funcionThinning(sistemaTransporte.getSimTime(), pasajero->getParadaOrigen(), pasajero->getParadaDestino()), (Entity*) pNuevo, crearPa);
}
