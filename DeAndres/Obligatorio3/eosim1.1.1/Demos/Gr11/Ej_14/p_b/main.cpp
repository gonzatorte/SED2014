#include <eosim/core/experiment.hpp>
#include "constantes.hpp"
#include "repair.hpp"
#include <iostream>
#include <string>

using namespace eosim::core;

const unsigned int repeticiones = 4;

int main() {
    std::string s;
    //repito el experimento una cierta cantidad de veces
    for (int i = 0; i < repeticiones; i++) {
        Repair m(cantMechExperienced, cantMechInexperienced, cantMechAverage, cantEq, cantMach, breakDownTime, removalMean, removalSD, repairMeanInexperienced, repairMeanAverage, repairMeanExperienced, repairSD);
		Experiment e;
		std::cout << "Arranco ...\n";
		m.connectToExp(&e);
		e.setSeed((unsigned long) i + 129);
		e.run(8*60);
        std::cout << "Termine ...\n\n\n";
        m.histTEsperaToRemove.table(480, "HistogramaTiempoEsperaToRemove.txt");
        m.histTEsperaToRepair.table(480, "HistogramaTiempoEsperaToRepair.txt");
        m.largoColaToRemove.table(20, "LargoColaToRemove.txt");
        m.largoColaToRepair.table(20, "LargoColaToRepair.txt");
        m.histUseOfMechanics.table(5, "UseOfMechanics.txt");
        m.histUseOfEquipment.table(4, "UseOfEquipment.txt");
        m.histDownTime.table(20, "Downtime.txt");
        std::cin >> s;
	}
	return 0;
}
