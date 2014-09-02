#include "repair.hpp"
#include <eosim/dist/numbergenerator.hpp>

using namespace eosim::core;
using namespace eosim::dist;

Repair::Repair(int cantMechExperienced, int cantMechInexperienced, int cantMechAverage, int cantEq, int cantMach, double breakDownTime,
			   double removalMean, double removalSD, double repairMeanInexperienced,
			   double repairMeanAverage, double repairMeanExperienced, double repairSD):
	eW(*this),
	eRv(*this),
	eRp(*this),
	sRv(*this),
	sRp(*this),
	tCafeE(*this),
	tCafeA(*this),
	tCafeI(*this),
	numMachinesBroken(0),
	experiencedMechanic(cantMechExperienced, cantMechExperienced),
	inexperiencedMechanic(cantMechInexperienced, cantMechInexperienced),
	averageMechanics(cantMechAverage, cantMechAverage),
	histUseOfMechanics("Uso de Mecánicos", *this),
	equipment(cantEq, cantEq),
	histUseOfEquipment("Uso de Equipo", *this),
    histTEsperaToRemove("Tiempo espera To Remove"),
    histTEsperaToRepair("Tiempo espera To Repair"),
    histDownTime("Tiempo de baja"),
    largoColaToRemove("Largo cola To Remove", *this),
    largoColaToRepair("Largo cola To Repair", *this),
	breakDown(MT19937, breakDownTime),
	removal(MT19937, removalMean, removalSD),
	repairInexperienced(MT19937, repairMeanInexperienced, repairSD),
	repairAverage(MT19937, repairMeanAverage, repairSD),
	repairExperienced(MT19937, repairMeanExperienced, repairSD) {

	for (int i = 0; i < cantMach; i++) {
		machine.push_back(new Machine(i));
	}

}

Repair::~Repair() {}

void Repair::init() {

	registerBEvent(&eW);
	registerBEvent(&eRv);
	registerBEvent(&eRp);
	registerBEvent(&tCafeE);
	registerBEvent(&tCafeA);
	registerBEvent(&tCafeI);

	registerCEvent(&sRv);
	registerCEvent(&sRp);

	registerDist(&breakDown);
	registerDist(&removal);
	registerDist(&repairInexperienced);
	registerDist(&repairAverage);
	registerDist(&repairExperienced);
}

void Repair::doInitialSchedules() {
	for (unsigned int i = 0; i < machine.size(); i++)
		schedule(breakDown.sample(), machine[i], endW);
}
