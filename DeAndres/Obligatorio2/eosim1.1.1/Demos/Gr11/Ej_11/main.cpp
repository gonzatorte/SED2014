#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "hospitalsimple.hpp"
#include "constantes.hpp"
#include <vector>
#include <windows.h>
#include <cmath>

#include <iostream>
#include <fstream>

const unsigned int repeticiones = 100;
using namespace eosim::core;
using namespace std;

double calcularMedia ( vector<double> m) {
    double media = 0.0;
    for (std::vector<double>::iterator it = m.begin() ; it != m.end(); ++it)
    {
        media = media + *it;
    }
    return media/m.size();
}

double calcularDesviacion(vector<double> v, double m) {
    double varianza = 0.0;
    for (std::vector<double>::iterator it = v.begin() ; it != v.end(); ++it)
    {
        varianza = varianza + pow((*it - m), 2);
    }
    return sqrt(varianza/(v.size()-1));
}

vector<double> calcularIntervaloConfianza(double m, double sd, int n) {
    vector<double> result;
    result.push_back( m - ( 1.96*( sd / sqrt(n) ) ) );
    result.push_back( m + ( 1.96*( sd / sqrt(n) ) ) );
    return result;
}

int main () {
	std::string s;
    std::vector<double> promedioLargoCola;
    std::vector<double> promedioTiempoEspera;

    int valorMedia;
    cout << "Elija un Valor de Media para el Tiempo de estadia" << endl;
    cout << "0 - 48 hrs" << endl;
    cout << "1 - 84 hrs" << endl;
    cout << "2 - 120 hrs" << endl;
    cin >> valorMedia;
    if ((valorMedia == 0) || (valorMedia == 1) || (valorMedia == 2)) {
        //repito el experimento una cierta cantidad de veces
        for (int i = 0; i < repeticiones; i++) {
            HospitalSimple m(cantCamas, tasaArribos, tiempoEstadia[valorMedia], valorMedia);
            Experiment e;
            std::cout << "Arranco ...\n";
            m.connectToExp(&e);
            e.setSeed((unsigned long) i + 129);
            e.run(50000.0);
            std::cout << "Termine ...\n\n\n";
            if (i == 0) {
                char buffer[50];
                sprintf(buffer, "HistogramaLCola%d.txt" , tiempoEstadia[valorMedia]);
                m.lCola.table(5000, buffer );
                sprintf(buffer, "HistogramaTEspera%d.txt" , tiempoEstadia[valorMedia]);
                m.tEspera.table(5000, buffer );
                sprintf(buffer, "HistogramaColaEnTiempo%d.txt" , tiempoEstadia[valorMedia]);
                m.colaEnTiempo.table(5000, buffer );
            }
            promedioLargoCola.push_back(m.lCola.getMean());
            promedioTiempoEspera.push_back(m.tEspera.getMean());

            // Reseteo Colas
            m.lCola.reset();
            m.tEspera.reset();
            m.colaEnTiempo.reset();

            //system("PAUSE");
        }


        // Largo Cola
        double mediaLargoCola = calcularMedia(promedioLargoCola);
        double sdLargoCola = calcularDesviacion(promedioLargoCola,mediaLargoCola);
        std::vector<double> intervaloConfianzaLargoCola = calcularIntervaloConfianza(mediaLargoCola,sdLargoCola,promedioLargoCola.size());

        // Tiempo Espera
        double mediaTiempoEspera = calcularMedia(promedioTiempoEspera);
        double sdTiempoEspera = calcularDesviacion(promedioTiempoEspera,mediaTiempoEspera);
        std::vector<double> intervaloConfianzaTiempoEspera = calcularIntervaloConfianza(mediaTiempoEspera,sdTiempoEspera,promedioTiempoEspera.size());

        cout << "Intervalo de Confianza para Largo de la Cola: [" << intervaloConfianzaLargoCola.front() << "," << intervaloConfianzaLargoCola.back() << "]" << endl;
        cout << "Intervalo de Confianza para Tiempo de la Espera: [" << intervaloConfianzaTiempoEspera.front() << "," << intervaloConfianzaTiempoEspera.back() << "]" << endl;
    }
    else{
        cout << "El valor ingresado no es correcto" << endl;
        system("pause");
    }
}
