#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "hospitalsimple.hpp"
#include "constantes.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const unsigned int repeticiones = 15;

double calcularVarianza(vector<double> v, double m) {
    double varianza = 0.0;
    for (std::vector<double>::iterator it = v.begin() ; it != v.end(); ++it)
    {
        varianza = varianza + pow((*it - m), 2);
    }
    return (varianza/v.size());
}

double calcularMedia ( vector<double> m) {
    double media = 0.0;
    for (std::vector<double>::iterator it = m.begin() ; it != m.end(); ++it)
    {
        media = media + *it;
    }
    return media/m.size();
}

double calcularCovarianza(double mm, vector<double> vm, double ma, vector<double> va) {
    double covarianza = 0.0;
    for (int i = 0; i < vm.size(); i++)
    {
        covarianza += (vm[i]-mm)*(va[i]-ma);
    }
    return (covarianza/(vm.size()-1));
}

int main () {
	std::string s;
    using namespace eosim::core;
    //repito el experimento una cierta cantidad de veces
    std::vector<double> promedioLargoColaAntitetico;
    std::vector<double> promedioTiempoEsperaAntitetico;
    std::vector<double> promedioLargoCola;
    std::vector<double> promedioTiempoEspera;
    std::vector<double> promedioLargoCola2;
    std::vector<double> promedioTiempoEspera2;
    for (int i = 0; i < (2*repeticiones); i++) {
        HospitalSimple m(cantCamas, tasaArribos, tiempoEstadia, false);
        Experiment e;
        std::cout << "Arranco normal ...\n";
        m.connectToExp(&e);
        e.setSeed((unsigned long) i + 129);
        e.run(720.0);
        std::cout << "Termine normal ...\n\n\n";
		promedioLargoCola.push_back(m.lCola.getMean());
        promedioTiempoEspera.push_back(m.tEspera.getMean());
    }
    for (int i = 0; i < repeticiones; i++) {
        HospitalSimple m2(cantCamas, tasaArribos, tiempoEstadia, false);
        HospitalSimple mAntitetico(cantCamas, tasaArribos, tiempoEstadia, true);
        Experiment e2;
        Experiment eAntitetico;
        std::cout << "Arranco normal ...\n";
        m2.connectToExp(&e2);
        e2.setSeed((unsigned long) i + 129);
        e2.run(720.0);
        std::cout << "Termine normal ...\n\n\n";
//        std::cin >> s;
        std::cout << "Arranco Antitetico ...\n";
        mAntitetico.connectToExp(&eAntitetico);
        eAntitetico.setSeed((unsigned long) i + 129);
        eAntitetico.run(720.0);
        std::cout << "Termine Antitetico...\n\n\n";
		m2.lCola.print(10);
		std::cout << '\n';
		m2.tEspera.print(52);
		promedioLargoColaAntitetico.push_back(mAntitetico.lCola.getMean());
        promedioTiempoEsperaAntitetico.push_back(mAntitetico.tEspera.getMean());
		promedioLargoCola2.push_back(m2.lCola.getMean());
        promedioTiempoEspera2.push_back(m2.tEspera.getMean());
    }

    //Normal
    double mediaLargoCola = calcularMedia(promedioLargoCola);
    double VarianzaLargoCola = calcularVarianza(promedioLargoCola,mediaLargoCola);

    double mediaTiempoEspera = calcularMedia(promedioTiempoEspera);
    double VarianzaTiempoEspera = calcularVarianza(promedioTiempoEspera,mediaTiempoEspera);

    // Método de Reduccion de Varianza
    // #######################################################################
    // Largo Cola
    double mediaLargoCola2 = calcularMedia(promedioLargoCola2);
    double VarianzaLargoCola2 = calcularVarianza(promedioLargoCola2,mediaLargoCola2);

    // Largo Cola Antitetico
    double mediaLargoColaAntitetico = calcularMedia(promedioLargoColaAntitetico);
    double VarianzaColaAntitetico = calcularVarianza(promedioLargoColaAntitetico,mediaLargoColaAntitetico);

    // Tiempo Espera
    double mediaTiempoEspera2 = calcularMedia(promedioTiempoEspera2);
    double VarianzaTiempoEspera2 = calcularVarianza(promedioTiempoEspera2,mediaTiempoEspera2);

    // Tiempo Espera Antitetico
    double mediaTiempoEsperaAntitetico = calcularMedia(promedioTiempoEsperaAntitetico);
    double VarianzaTiempoEsperaAntitetico = calcularVarianza(promedioTiempoEsperaAntitetico,mediaTiempoEsperaAntitetico);

    //Covarianza Largo Cola
    double CovarianzaLCola = calcularCovarianza(mediaLargoCola2,promedioLargoCola2,mediaLargoColaAntitetico,promedioLargoColaAntitetico);

    //Covarianza Tiempo Espera
    double CovarianzaTEspera = calcularCovarianza(mediaTiempoEspera2,promedioTiempoEspera2,mediaTiempoEsperaAntitetico,promedioTiempoEsperaAntitetico);

    //Reducción de varianza Largo Cola
    double reduccionVarianzaLCola = (VarianzaLargoCola + VarianzaColaAntitetico + 2*CovarianzaLCola)/(4*promedioLargoCola2.size());

    //Reducción de varianza Tiempo Espera
    double reduccionVarianzaTEspera = (VarianzaTiempoEspera + VarianzaTiempoEsperaAntitetico + 2*CovarianzaTEspera)/(4*promedioTiempoEspera2.size());

    //Media total antitética
    for (std::vector<double>::iterator it = promedioLargoColaAntitetico.begin() ; it != promedioLargoColaAntitetico.end(); ++it)
    {
        promedioLargoCola2.push_back(*it);
    }

    double mediaLargoColaTotalAntitetica = calcularMedia(promedioLargoCola2);

    for (std::vector<double>::iterator it2 = promedioTiempoEspera2.begin() ; it2 != promedioTiempoEspera2.end(); ++it2)
    {
        promedioTiempoEsperaAntitetico.push_back(*it2);
    }

    double medioTiempoEsperaTotalAntitetica = calcularMedia(promedioTiempoEsperaAntitetico);

    std::cout << "Normal 30 Iteraciones" << endl;
    std::cout << "Media Largo Cola: " << mediaLargoCola << endl;
    std::cout << "VarianzaLargoCola: " << VarianzaLargoCola << endl;
    std::cout << "MediaTiempoEspera: " << mediaTiempoEspera << endl;
    std::cout << "VarianzaTiempoEspera: " << VarianzaTiempoEspera << endl;
    std::cout << endl;
    std::cout << "Metodo de Reduccion de Varianza 15 Iteraciones" << endl;
    std::cout << "Media Largo Cola: " << mediaLargoColaTotalAntitetica << endl;
    std::cout << "VarianzaLargoCola: " << VarianzaLargoCola2 << endl;
    std::cout << "VarianzaLargoColaAntitetico: " << VarianzaColaAntitetico << endl;
    std::cout << "CovarianzaLargoCola: " << CovarianzaLCola << endl;
    std::cout << "Calculo de Reduccion de Varianza: " << reduccionVarianzaLCola << endl;
    std::cout << "MediaTiempoEspera: " << medioTiempoEsperaTotalAntitetica << endl;
    std::cout << "VarianzaTiempoEspera: " << VarianzaTiempoEspera2 << endl;
    std::cout << "VarianzaTiempoEsperaAntitetico: " << VarianzaTiempoEsperaAntitetico << endl;
    std::cout << "CovarianzaTiempoEspera: " << CovarianzaTEspera << endl;
    std::cout << "Calculo de Reduccion de Varianza: " << reduccionVarianzaTEspera << endl;
}

