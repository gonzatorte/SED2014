#include "hospitalsimple.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>

using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

HospitalSimple::HospitalSimple(unsigned int cantCamas, double tasaArribos, double tiempoEstadia, int indiceMedia):
// se contruyen los eventos B, los eventos C, las distribuciones, los recursos y los histogramas
								tasaArribos(tasaArribos),
								tiempoEstadia(tiempoEstadia),
								pF(*this),
								sP(*this),
								crearEvento(*this),
								arribos(MT19937, tasaArribos),
								estadia(MT19937, tiempoEstadia,20),
								camas(cantCamas, cantCamas),
								tEspera("Tiempos de Espera"),
								lCola("Largos Medios de Colas", *this),
								colaEnTiempo("Largos de la Cola vs Tiempo", *this),
								indiceMedia(indiceMedia),
								notSteadyState(true) {}

HospitalSimple::~HospitalSimple() {}

void HospitalSimple::init() {
	// registro los eventos B
	registerBEvent(&pF);
	registerBEvent(&sP);
	registerBEvent(&crearEvento);

	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);
}

void HospitalSimple::doInitialSchedules() {
	// agendo el primer paciente
	schedule(0.0, new Entity(), pacienteF);
	schedule(0.0, (Entity*) new Entidad() , crearEv);

}
