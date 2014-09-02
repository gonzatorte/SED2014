#include <eosim/dist/numbergenerator.hpp>
#include <eosim/dist/distribution.hpp>
#include <eosim/dist/mt19937.hpp>
#include <iostream>
#include <windows.h>
#include "algoritmoDeMuestreo.h"

using namespace eosim::dist;
using namespace eosim::core;
using namespace std;

int main () {

    double indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
    double probabilidades[] = {0, 0.05, 0.45, 0.17, 0.15, 0.08 , 0.04 , 0.03, 0.03};
    double F[9];
    F[0] = 0;
    for (int i = 1; i < 9; i++ ) {
        F[i] = F[i-1] + probabilidades[i];
    }
    for (int j = 0; j < 5; j++)
    {
        cout << "Va a comenzar un nuevo muestreo" << endl;
        system("PAUSE");

        int cantUnos = 0;
        int cantDos = 0;
        int cantTres = 0;
        int cantCuatro = 0;
        int cantCinco = 0;
        int cantSeis = 0;
        int cantSiete = 0;
        int cantOcho = 0;

        algoritmoDeMuestreo discreta(MT19937,indices,F,true);
        discreta.setSeed(j+129);
        cout << "Muestreo discreto" << endl;
        for(int i = 0; i < 100; i++) {
            int x = discreta.sample();

            switch (x)
            {
            case 1: cantUnos++;
            break;
            case 2: cantDos++;
            break;
            case 3: cantTres++;
            break;
            case 4: cantCuatro++;
            break;
            case 5: cantCinco++;
            break;
            case 6: cantSeis++;
            break;
            case 7: cantSiete++;
            break;
            case 8: cantOcho++;
            break;
            }
            cout << x << endl;

        }
        cout << "Cant1: " << cantUnos << endl;
        cout << "Cant2: " << cantDos << endl;
        cout << "Cant3: " << cantTres << endl;
        cout << "Cant4: " << cantCuatro << endl;
        cout << "Cant5: " << cantCinco << endl;
        cout << "Cant6: " << cantSeis << endl;
        cout << "Cant7: " << cantSiete << endl;
        cout << "Cant8: " << cantOcho << endl;

        cout << "----------------------------------------" << endl;

        algoritmoDeMuestreo continua(MT19937,indices,F,false);
        continua.setSeed(j+129);
        cout << "Muestreo continuo" << endl;
        for(int i = 0; i < 100; i++) {
            cout << continua.sample() << endl;
        }
    }


	return 0;
}

