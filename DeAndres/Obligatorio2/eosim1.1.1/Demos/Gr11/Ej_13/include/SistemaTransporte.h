#ifndef SISTEMATRANSPORTE_H
#define SISTEMATRANSPORTE_H

#include "Omnibus.h"
#include "Pasajero.h"
#include "Linea.h"
#include <eosim/dist/distribution.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <eosim/statics/observation.hpp>
#include <eosim/dist/normaldist.hpp>
#include <eosim/dist/negexpdist.hpp>
using namespace eosim::dist;

class SistemaTransporte: public eosim::core::Model
{
    public:
        SistemaTransporte();
        virtual ~SistemaTransporte();
        eosim::utils::EntityQueueFifo paradaPasajeros[85];
        Linea* lineas[13];
        NegexpDist* m[85][85];
        NormalDist* d[85][85];
        Linea* getLinea(int);
        void setearSemillasAHuevo(int seed);

        eosim::statics::Observation histTEsperaGlobal;
        double obtenerCosto(int, int);
        double costos[85][85];

        void imprimirFlotaPorLinea(int i);
        void init();
        // lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
        void doInitialSchedules();
    private:
        CrearOmnibus crearOmnibus;
        BajarPasajeros bajarPasajeros;
        SubirPasajeros subirPasajeros;
        CrearPasajero crearPasajero;


};

#endif // SISTEMATRANSPORTE_H
