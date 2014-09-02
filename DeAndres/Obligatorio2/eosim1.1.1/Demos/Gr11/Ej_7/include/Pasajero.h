#ifndef PASAJERO_H
#define PASAJERO_H

#include <eosim/core/entity.hpp>
#include <string>

#include <eosim/core/model.hpp>

class Pasajero: public eosim::core::Entity
{
    public:
        Pasajero(int, int, double);
        virtual ~Pasajero();
        int getParadaDestino();
        int getParadaOrigen();
        double getPasajeroFrecuencia();

    private:
        int paradaDestino;
        int paradaOrigen;
        double pasajeroFrecuencia;
};

const std::string  crearPa = "crearPa";

class CrearPasajero: public eosim::core::BEvent {

    public:
        // constructores
        CrearPasajero(eosim::core::Model& model);
        // destructor
        ~CrearPasajero();
        // rutina del evento fijo
        void eventRoutine(eosim::core::Entity* who);
};


#endif // PASAJERO_H
