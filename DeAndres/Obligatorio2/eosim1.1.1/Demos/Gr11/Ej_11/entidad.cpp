#include "entidad.h"
#include "hospitalsimple.hpp"
#include <fstream>
#include <iostream>
#include "constantes.hpp"
using namespace std;
using namespace eosim::core;

Entidad::Entidad() : Entity()
{

}

Entidad::~Entidad()
{

}

CrearEvento::CrearEvento(Model& model) : BEvent(crearEv, model) {}

CrearEvento::~CrearEvento() {}

void CrearEvento::eventRoutine(Entity* who) {

    HospitalSimple& h = dynamic_cast<HospitalSimple&>(owner);
	// se guarda en el histograma el largo de la cola
	if (h.notSteadyState) {

        h.colaEnTiempo.log(h.lCola.getMean());

        if (h.getSimTime() > runIn[h.indiceMedia] ) {
            cout << "Llego al SteadyState" << endl;
            cout << "Se resetean Histogramas para calculo de Intervalo de Confianza" << endl;
            h.notSteadyState = false;
            h.lCola.reset();
            h.tEspera.reset();
        }
        else {
            Entidad* e = dynamic_cast<Entidad*>(who);
            // se castea owner a un HospitalSimple

            h.schedule(1, (Entity*) e, crearEv);
        }

    }
}
