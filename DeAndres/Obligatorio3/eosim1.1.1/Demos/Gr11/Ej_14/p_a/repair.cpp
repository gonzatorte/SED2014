#include "repair.hpp"
#include <eosim/dist/numbergenerator.hpp>

using namespace eosim::core;
using namespace eosim::dist;

Repair::Repair(int cantMech, int cantEq, int cantMach, double breakDownTime,
			   double removalMean, double removalSD, double repairMean, double repairSD):
	eW(*this),
	eRv(*this),
	eRp(*this),
	sRv(*this),
	sRp(*this),
	tCafe(*this),
	numMachinesBroken(0),
	mechanics(cantMech, cantMech),
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
	repair(MT19937, repairMean, repairSD) {

	for (int i = 0; i < cantMach; i++) {
		machine.push_back(new Machine(i));
	}

}

Repair::~Repair() {}

void Repair::init() {

	registerBEvent(&eW);
	registerBEvent(&eRv);
	registerBEvent(&eRp);
	registerBEvent(&tCafe);

	registerCEvent(&sRv);
	registerCEvent(&sRp);

	registerDist(&breakDown);
	registerDist(&removal);
	registerDist(&repair);
}

void Repair::doInitialSchedules() {
	for (unsigned int i = 0; i < machine.size(); i++)
		schedule(breakDown.sample(), machine[i], endW);
}
