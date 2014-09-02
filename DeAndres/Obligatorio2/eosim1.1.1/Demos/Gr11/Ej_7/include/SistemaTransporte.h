#ifndef SISTEMATRANSPORTE_H
#define SISTEMATRANSPORTE_H

#include "Omnibus.h"
#include "Pasajero.h"
#include "Linea.h"

class SistemaTransporte: public eosim::core::Model
{
    public:
        SistemaTransporte();
        virtual ~SistemaTransporte();
        eosim::utils::EntityQueueFifo paradaPasajeros[85];
        Linea* lineas[13];
        Linea* getLinea(int);
        double obtenerCosto(int, int);

        void imprimirFlotaPorLinea();
        void init();
        // lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
        void doInitialSchedules();
    private:
        CrearOmnibus crearOmnibus;
        BajarPasajeros bajarPasajeros;
        SubirPasajeros subirPasajeros;
        CrearPasajero crearPasajero;
        double costos[85][85];

};

#endif // SISTEMATRANSPORTE_H
