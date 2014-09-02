#include "Omnibus.h"
#include "SistemaTransporte.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace eosim::core;
using namespace eosim::graphic;

bool estaEnRecorrido(int paradaActual, int paradaDestino, vector<int> recorrido) {
    bool esta = false;
    int i = paradaActual+1;
    while (!esta && i<recorrido.size() && recorrido[i] != -1 )
    {
        esta = (paradaDestino == recorrido[i]);
        i++;
    }
    return esta;
}

Omnibus::Omnibus(eosim::graphic::Display& dis, int o_linea, int o_paradaActual, int o_cantLugares, int o_ID)  : Entity(), linea(o_linea), paradaActual(o_paradaActual), lugares(o_cantLugares, o_cantLugares), ID(o_ID)
{

}

Omnibus::~Omnibus()
{
    //dtor
}

int Omnibus::getLinea() {
    return this->linea;
}

int Omnibus::getParadaActual()
{
    return this->paradaActual;
}

int Omnibus::getID() {
    return this->ID;
}

void Omnibus::setParadaActual(int parada)
{
    this->paradaActual = parada;
}

BajarPasajeros::BajarPasajeros(Model& model) : BEvent(bajarPa, model) {}

BajarPasajeros::~BajarPasajeros() {}

void BajarPasajeros::eventRoutine(Entity* who) {


	Omnibus* omnibus = dynamic_cast<Omnibus*>(who);

	SistemaTransporte& sistemaTransporte = dynamic_cast<SistemaTransporte&>(owner);
    vector<int> recorrido = sistemaTransporte.getLinea(omnibus->getLinea()-1)->getRecorrido();

//    cout << "--BajarPasajeros: Parada " << recorrido[omnibus->getParadaActual()] << "--" << endl;
//    cout << "{" << endl;
//    ofstream log;
//    log.open("LogCasoDeEstudio.txt", ios::app);
//    log << "--BajarPasajeros: Parada " << recorrido[omnibus->getParadaActual()] << "--" << endl << "{" << endl;
//    log.close();
    while (!omnibus->pasajeros[recorrido[omnibus->getParadaActual()]].empty()) {
        Pasajero* p = dynamic_cast<Pasajero*>(omnibus->pasajeros[recorrido[omnibus->getParadaActual()]].pop());
        int j = p->getParadaDestino();
        delete p;
//        cout << "Baja pasajero del Omnibus " << omnibus->getID() << " de la Linea " << omnibus->getLinea() << " en tiempo " << omnibus->getClock() << endl;
//        ofstream log;
//        log.open("LogCasoDeEstudio.txt", ios::app);
//        log << "Baja pasajero del Omnibus " << omnibus->getID() << " de la Linea " << omnibus->getLinea() << " en tiempo " << omnibus->getClock() << endl;
//        log.close();
        int x = omnibus->pasajeros[recorrido[omnibus->getParadaActual()]].size();
        omnibus->lugares.returnBin(1);
    }
//    cout << "}" << endl;
//    log.open("LogCasoDeEstudio.txt", ios::app);
//    log << "}" << endl;
//    log.close();
    if (sistemaTransporte.getSimTime() > 18)
    {
        int i = 0;
        i ++;
    }

    sistemaTransporte.schedule(0,(Entity*) omnibus, subirPa);
}

SubirPasajeros::SubirPasajeros(Model& model) : BEvent(subirPa, model) {}

SubirPasajeros::~SubirPasajeros() {}

void SubirPasajeros::eventRoutine(Entity* who) {

	Omnibus* omnibus = dynamic_cast<Omnibus*>(who);
	SistemaTransporte& sistemaTransporte = dynamic_cast<SistemaTransporte&>(owner);
    vector<int> recorrido = sistemaTransporte.getLinea(omnibus->getLinea()-1)->getRecorrido();
    int aux = 0;
    int saize = sistemaTransporte.paradaPasajeros[recorrido[omnibus->getParadaActual()]].size();
//    cout << "--SubirPasajeros: Parada " << recorrido[omnibus->getParadaActual()] << "--" << endl;
//    cout << "{" << endl;
//    ofstream log;
//    log.open("LogCasoDeEstudio.txt", ios::app);
//    log << "--SubirPasajeros: Parada " << recorrido[omnibus->getParadaActual()] << "--" << endl << "{" << endl;
//    log.close();
    while (omnibus->lugares.isAvailable(1) && !sistemaTransporte.paradaPasajeros[recorrido[omnibus->getParadaActual()]].empty() && (aux < saize) ) {
        Pasajero* p = dynamic_cast<Pasajero*> (sistemaTransporte.paradaPasajeros[recorrido[omnibus->getParadaActual()]].pop());
        if (estaEnRecorrido(omnibus->getParadaActual(), p->getParadaDestino(), recorrido)){
            omnibus->lugares.acquire(1);
            sistemaTransporte.histTEsperaGlobal.log(sistemaTransporte.getSimTime() - p->getClock());
            omnibus->pasajeros[p->getParadaDestino()].push((Entity*) p);
//            cout << "Sube pasajero al Omnibus " << omnibus->getID() << " de la Linea " << omnibus->getLinea() << " con ParadaDestino " << p->getParadaDestino() << " en tiempo " << omnibus->getClock() << endl;
//            ofstream log;
//            log.open("LogCasoDeEstudio.txt", ios::app);
//            log << "Sube pasajero al Omnibus " << omnibus->getID() << " de la Linea " << omnibus->getLinea() << " con ParadaDestino " << p->getParadaDestino() << " en tiempo " << omnibus->getClock() << endl;
//            log.close();
        }
        else{
            sistemaTransporte.paradaPasajeros[recorrido[omnibus->getParadaActual()]].push((Entity*) p);
        }
        aux++;
    }
//    cout << "}" << endl;
//    log.open("LogCasoDeEstudio.txt", ios::app);
//    log << "}" << endl;
//    log.close();
    std::stringstream valorPasajero;
    valorPasajero << recorrido[omnibus->getParadaActual()] << " - " << sistemaTransporte.paradaPasajeros[recorrido[omnibus->getParadaActual()]].size();
    sistemaTransporte.referenciaParadas[recorrido[omnibus->getParadaActual()]].setText(valorPasajero.str().c_str());

    if (omnibus->getParadaActual() == recorrido.size()-1){

        omnibus->setParadaActual(0);
        Linea* linea = sistemaTransporte.getLinea(omnibus->getLinea()-1);
        linea->omnibusDisponibles.push(omnibus);
    }
    else {
        int paradaOrigen = recorrido[omnibus->getParadaActual()];
        if (recorrido[omnibus->getParadaActual()+1] != -1) {
            omnibus->setParadaActual(omnibus->getParadaActual()+1);
        }
        else {
            omnibus->setParadaActual(omnibus->getParadaActual()+2);
        }
        int paradaDestino = recorrido[omnibus->getParadaActual()];
        double valor;
        if (paradaDestino == paradaOrigen)
        {
            valor = 0;
        }
        else
        {
            valor = sistemaTransporte.d[paradaOrigen*84 + paradaDestino]->sample();
            for(; valor < 0; valor = sistemaTransporte.d[paradaOrigen*84 + paradaDestino]->sample());
        }

        std::stringstream pasajerosEnOmnibus;
        pasajerosEnOmnibus << (42 - omnibus->lugares.getQuantity());
        omnibus->cantPasajeros.setText(pasajerosEnOmnibus.str().c_str());
        omnibus->imagen.setMoves(move(sistemaTransporte.pXY[recorrido[omnibus->getParadaActual()]][0], sistemaTransporte.pXY[recorrido[omnibus->getParadaActual()]][1], (valor/(1000*13))*60));
        omnibus->cantPasajeros.setMoves(move(sistemaTransporte.pXY[recorrido[omnibus->getParadaActual()]][0], sistemaTransporte.pXY[recorrido[omnibus->getParadaActual()]][1], (valor/(1000*13))*60));
        sistemaTransporte.schedule((valor/(1000*13))*60,(Entity*) omnibus, bajarPa);
    }
}



