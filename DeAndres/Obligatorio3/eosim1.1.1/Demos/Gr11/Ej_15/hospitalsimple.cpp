#include "hospitalsimple.hpp"
#include <eosim/core/entity.hpp>
#include <iostream>

using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

HospitalSimple::HospitalSimple(unsigned int cantCamas, double tasaArribos, double tiempoEstadia, bool antitetico):
// se contruyen los eventos B, los eventos C, las distribuciones, los recursos y los histogramas
								tasaArribos(tasaArribos),
								tiempoEstadia(tiempoEstadia),
								pF(*this),
								sP(*this),
								arribos(antitetico ? ANTHITETICMT19937 : MT19937, tasaArribos),
								estadia(antitetico ? ANTHITETICMT19937 : MT19937, tiempoEstadia),
								camas(cantCamas, cantCamas),
								tEspera("Tiempos de Espera"),
								lCola("Largos Medios de Colas", *this) {}

HospitalSimple::~HospitalSimple() {}

void HospitalSimple::init() {
	// registro los eventos B
	registerBEvent(&pF);
	registerBEvent(&sP);

	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);
}

void HospitalSimple::doInitialSchedules() {
	// agendo el primer paciente
	schedule(0.0, new Entity(), pacienteF);
}

