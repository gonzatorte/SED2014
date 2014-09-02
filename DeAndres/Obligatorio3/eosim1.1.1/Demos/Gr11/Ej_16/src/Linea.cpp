#include "Linea.h"
#include "SistemaTransporte.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
        std::stringstream cantOmnibusPorLinea;
        switch (linea->getLinea()) {
        case 1:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea1.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[1].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 2:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea2.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[2].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 3:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea3.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[3].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 4:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea4.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[4].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 5:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea5.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[5].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 6:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea6.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[6].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 7:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea7.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[7].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 8:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea8.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[8].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 9:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea9.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[9].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 10:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea10.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[10].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 11:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea11.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[11].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        case 12:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea12.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[12].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        default:
                omnibus = new Omnibus(sistemaTransporte.display,linea->getLinea(), 0, 42, linea->getCantFlota());
                omnibus->imagen = eosim::graphic::Sprite(sistemaTransporte.display,"imagenes/linea13.jpeg",sistemaTransporte.pXY[linea->getRecorrido()[0]][0],sistemaTransporte.pXY[linea->getRecorrido()[0]][1]);
                omnibus->cantPasajeros = eosim::graphic::TextSprite(sistemaTransporte.display, "0",14, (sistemaTransporte.pXY[linea->getRecorrido()[0]][0]+15),(sistemaTransporte.pXY[linea->getRecorrido()[0]][1]+9), 1);
                cantOmnibusPorLinea << "Linea N " << linea->getLinea() << " Cant Omnibus: " << linea->getCantFlota();
                sistemaTransporte.referenciaLineasTexto[13].setText(cantOmnibusPorLinea.str().c_str());
                cantOmnibusPorLinea.str("");
                break;
        }
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
