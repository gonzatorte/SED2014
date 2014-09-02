#include "Linea.h"
#include "SistemaTransporte.h"
#include <iostream>
#include <fstream>

using namespace eosim::core;

//Linea::Linea() : Entity() {}

Linea::Linea(int l_linea, double l_frecuencia, vector<int> l_recorrido, int l_cantFlota) : Entity(), linea(l_linea), frecuencia(l_frecuencia), recorrido(l_recorrido), cantFlota(l_cantFlota)
{

}

Linea::~Linea() {}

int Linea::getLinea() {
    return this->linea;
}

vector<int> Linea::getRecorrido() {
    return this->recorrido;
}

double Linea::getFrecuencia() {
    return this->frecuencia;
}

int Linea::getCantFlota() {
    return this->cantFlota;
}

void Linea::setCantFlota(int cFlota) {
    this->cantFlota = cFlota;
}

CrearOmnibus::CrearOmnibus(Model& model) : BEvent(crearOm, model) {}

CrearOmnibus::~CrearOmnibus() {}

void CrearOmnibus::eventRoutine(Entity* who) {

	Linea* linea = dynamic_cast<Linea*>(who);

	SistemaTransporte& sistemaTransporte = dynamic_cast<SistemaTransporte&>(owner);
    Omnibus* omnibus;
    if (linea->omnibusDisponibles.empty()) {
        linea->setCantFlota(linea->getCantFlota()+1);
        omnibus = new Omnibus(linea->getLinea(), 0, 42, linea->getCantFlota());
//        cout << "Se crea nuevo Omnibus con ID " << omnibus->getID() << " de la Linea " << omnibus->getLinea() << " en tiempo " << omnibus->getClock() << endl;
//        ofstream log;
//        log.open("LogCasoDeEstudio.txt", ios::app);
//        log << "Se crea nuevo Omnibus con ID " << omnibus->getID() << " de la Linea " << omnibus->getLinea() << " en tiempo " << omnibus->getClock() << endl;
//        log.close();
    }
    else {
        omnibus = (Omnibus*) linea->omnibusDisponibles.pop();
//        cout << "Se obtiene Omnibus con ID " << omnibus->getID() << " de la Linea " << omnibus->getLinea() << " en tiempo " << omnibus->getClock() << endl;
//        ofstream log;
//        log.open("LogCasoDeEstudio.txt", ios::app);
//        log << "Se obtiene Omnibus con ID " << omnibus->getID() << " de la Linea " << omnibus->getLinea() << " en tiempo " << omnibus->getClock() << endl;
//        log.close();
    }

    sistemaTransporte.schedule(0, (Entity*) omnibus, bajarPa);
    sistemaTransporte.schedule(linea->getFrecuencia(), (Entity*) linea, crearOm);
//    cout << "Se pone en circulacion el Omnibus" << endl;
//    ofstream log;
//    log.open("LogCasoDeEstudio.txt", ios::app);
//    log << "Se pone en circulacion el Omnibus" << endl;
//    log.close();

}
