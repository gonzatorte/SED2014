#ifndef OMNIBUS_H
#define OMNIBUS_H

#include <eosim/core/entity.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <string>
#include <eosim/core/model.hpp>
//using namespace std;

class Omnibus: public eosim::core::Entity
{
    public:
        Omnibus(int, int , int, int );

        eosim::core::Renewable lugares;
        eosim::utils::EntityQueueFifo pasajeros[85];

        int getLinea();
        int getParadaActual();
        int getID();

        void setParadaActual(int);

        virtual ~Omnibus();
    private:
        int linea;
        int paradaActual;
        int cantLugares;
        int ID;
};

const std::string  bajarPa = "bajarPa";

class BajarPasajeros: public eosim::core::BEvent {

    public:
        // constructores
        BajarPasajeros(eosim::core::Model& model);
        // destructor
        ~BajarPasajeros();
        // rutina del evento fijo
        void eventRoutine(eosim::core::Entity* who);
};

const std::string  subirPa = "subirPa";

class SubirPasajeros: public eosim::core::BEvent {

    public:
        // constructores
        SubirPasajeros(eosim::core::Model& model);
        // destructor
        ~SubirPasajeros();
        // rutina del evento fijo
        void eventRoutine(eosim::core::Entity* who);
};

#endif // OMNIBUS_H
