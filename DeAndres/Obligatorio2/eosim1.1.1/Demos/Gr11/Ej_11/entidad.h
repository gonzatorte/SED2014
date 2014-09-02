#ifndef ENTIDAD_H
#define ENTIDAD_H


#include <eosim/core/entity.hpp>
#include <string>

#include <eosim/core/model.hpp>

class Entidad: public eosim::core::Entity
{
    public:
        Entidad();
        virtual ~Entidad();

    private:

};

const std::string  crearEv = "crearEv";

class CrearEvento: public eosim::core::BEvent {

    public:
        // constructores
        CrearEvento(eosim::core::Model& model);
        // destructor
        ~CrearEvento();
        // rutina del evento fijo
        void eventRoutine(eosim::core::Entity* who);
};



#endif // ENTIDAD_H
