#include <eosim/core/experiment.hpp>
#include "constantes.hpp"
#include "repair.hpp"
#include <iostream>
#include <string>

using namespace eosim::core;
using namespace std;

const unsigned int repeticiones = 4;

int main() {
    string s;
    //repito el experimento una cierta cantidad de veces
    for (int i = 0; i < repeticiones; i++) {
        Repair m(cantMech, cantEq, cantMach, breakDownTime, removalMean, removalSD, repairMean, repairSD);
		Experiment e;
		cout << "Arranco ...\n";
		m.connectToExp(&e);
		e.setSeed((unsigned long) i + 129);
		e.run(8*60);
        cout << "Termine ...\n\n\n";
        m.histTEsperaToRemove.table(480, "HistogramaTiempoEsperaToRemove.txt");
        m.histTEsperaToRepair.table(480, "HistogramaTiempoEsperaToRepair.txt");
        m.largoColaToRemove.table(20, "LargoColaToRemove.txt");
        m.largoColaToRepair.table(20, "LargoColaToRepair.txt");
        m.histUseOfMechanics.table(5, "UseOfMechanics.txt");
        m.histUseOfEquipment.table(4, "UseOfEquipment.txt");
        m.histDownTime.table(20, "Downtime.txt");
        cin >> s;
	}
	return 0;
}
