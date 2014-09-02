#include <stdio.h>
#include "SistemaTransporte.h"
#include <iostream>
#include <fstream>
#include <sstream>

//#include <eosim/core/entity.hpp>
//#include <eosim/core/model.hpp>
using namespace eosim::core;


SistemaTransporte::SistemaTransporte(double** s_frecuencias, double** s_costos) :
        crearOmnibus(*this),
        bajarPasajeros(*this),
        subirPasajeros(*this),
        crearPasajero(*this),
        display(950,542),
        refreshDisplay(*this, display),
        histTEsperaGlobal("Tiempo Espera Global")
{
    NegexpDist* negexp;
    NormalDist* normalDist;
    frecuencias = s_frecuencias;
    costos = s_costos;
    for (int i = 0; i<85; i++) {
        for (int j = 0; j<85; j++) {
            negexp = new NegexpDist(MT19937, frecuencias[i][j]);
            normalDist = new NormalDist(MT19937,costos[i][j], costos[i][j]/5);
            m.insert(make_pair((i*84+j),negexp));
            d.insert(make_pair((i*84+j),normalDist));
        }
    }

    display.setSpeed(0.6);
}

SistemaTransporte::~SistemaTransporte()
{

}

Linea* SistemaTransporte::getLinea(int linea) {
    return this->lineas[linea];
}

void SistemaTransporte::setearSemillasAHuevo(int seed) {
//    for ( int i = 0; i < 85; i++) {
//        for (int j = 0; j < 85; j++) {
//            if (this->m[i][j] != NULL) {
//                this->m[i][j]->setSeed(seed);
//            }
//            if (this->d[i][j] != NULL) {
//                this->d[i][j]->setSeed(seed);
//            }
//        }
//    }
}

double SistemaTransporte::obtenerCosto(int paradaOrigen, int paradaDestino) {
    return (this->costos[paradaOrigen][paradaDestino]/(1000*13))*60;
}

void SistemaTransporte::imprimirFlotaPorLinea(int numero) {
    for (int i = 0; i<13; i++) {
        cout << "Linea numero " << lineas[i]->getLinea() << " tiene " << lineas[i]->getCantFlota() << " Omnibus." << endl;
        ofstream log;
        char buffer[50];
        sprintf(buffer, "LogCasoDeEstudio%d.txt" , numero);
        log.open(buffer, ios::app);
        log << "Linea numero " << lineas[i]->getLinea() << " tiene " << lineas[i]->getCantFlota() << " Omnibus." << endl;
        log.close();
    }
}

void SistemaTransporte::init() {
    registerBEvent(&crearOmnibus);
	registerBEvent(&bajarPasajeros);
	registerBEvent(&subirPasajeros);
	registerBEvent(&crearPasajero);
	// Registro del Evento para el dibujado

    for (int i = 1; i < 85; i++ ) {
        for (int j = 1; j < 85; j++) {
            registerDist(m[i*84+j]);
            registerDist(d[i*84+j]);
        }
    }
    registerCEvent(&refreshDisplay);
//	registerDist(&m);
}

void SistemaTransporte::doInitialSchedules() {
    display.setBackground("imagenes/MiddleEarth1.jpeg");

    // Creo Lineas
    string line;
    int anterior = -2;
    ifstream recorridos ("src/recorridos.txt");
    int numeroLinea;
    double frecuenciaLinea;
    int nodoLinea;
    int cantLineas = 0;
    std::stringstream refLineaT;

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
            refLineaT << "imagenes/linea" << numeroLinea << ".jpeg";
            referenciaLineasSprite[numeroLinea] = eosim::graphic::Sprite(display,refLineaT.str().c_str(),750,numeroLinea*22 - 10);
            refLineaT.str("");
            refLineaT << "Linea N " << numeroLinea << " Cant Omnibus: 0";
            referenciaLineasTexto[numeroLinea] = eosim::graphic::TextSprite(display,refLineaT.str().c_str(),14,780,numeroLinea*22 - 10, 0);
            refLineaT.str("");
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
    for (int i = 1; i < 85; i++) {
        for (int j = 1 ; j < 85; j++) {
            if (this->frecuencias[i][j] > 0) {
                Pasajero* p = new Pasajero(j,i,m[i*84+j]->sample());
                schedule(0, (Entity*) p, crearPa);
            }
        }
    }

    string lineParadas;
    ifstream paradas ("src/paradas.txt");
    double x;
    double y;
    int i;
    double rX = 1;
    double rY = 1;
    std::stringstream indice;

    if (paradas.is_open())
    {
        while ( getline (paradas,lineParadas) )
        {
            std::istringstream iss(lineParadas);
            iss >> i;
            iss >> x;
            iss >> y;
            x = ((x - 31000) * 950/11050);
            y = ((y - 17000) * 500/6028);
            pXY[i][0] = x;
            pXY[i][1] = y;
            indice << i;
            this->paradas[i] = eosim::graphic::TextSprite(display,indice.str().c_str(),14,x,y, 0);
            indice << " - 0";
            this->referenciaParadas[i] = eosim::graphic::TextSprite(display,indice.str().c_str(),14,rX*50-35,rY*15 - 10, 0);
            rY++;
            if (rY > 15) {
                rX++;
                rY = 1;
            }
            indice.str("");
        }
        pXY[0][0] = 950;
        pXY[0][1] = 0;
        paradas.close();

    }

}



