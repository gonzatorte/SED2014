#ifndef OMNIBUS_H
#define OMNIBUS_H

#include <eosim/core/entity.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <string>
#include <eosim/core/model.hpp>
#include <eosim/graphic.hpp>
#include <map>
//using namespace std;

class Omnibus: public eosim::core::Entity
{
    public:
        Omnibus(eosim::graphic::Display&,int, int , int, int );

        eosim::core::Renewable lugares;
        eosim::utils::EntityQueueFifo pasajeros[85];
//        eosim::graphic::Display dis;
        eosim::graphic::Sprite imagen;
        eosim::graphic::TextSprite cantPasajeros;

        int getLinea();
        int getParadaActual();
        int getID();
        int cantLugares;
        void setParadaActual(int);

        virtual ~Omnibus();
    private:
        int linea;
        int paradaActual;

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
