#ifndef LINEA_H
#define LINEA_H

#include <eosim/core/entity.hpp>
#include <eosim/utils/entityqueuefifo.hpp>

#include <eosim/core/model.hpp>


//#include <eosim/dist/negexpdist.hpp>
//#include <eosim/statics/timeweighted.hpp>
//#include <eosim/statics/observation.hpp>

#include <vector>
#include <string>


using namespace std;

class Linea: public eosim::core::Entity
{
    public:
        Linea();
        Linea(int linea, double frecuencia, vector<int> recorrido, int cantFlota);
        eosim::utils::EntityQueueFifo omnibusDisponibles;

        double getFrecuencia();
        vector<int> getRecorrido();
        int getLinea();
        int getCantFlota();

        void setCantFlota(int);
        virtual ~Linea();

    private:
        int linea;
        double frecuencia;
        vector<int> recorrido;
        int cantFlota;
};

const std::string  crearOm = "crearOm";

class CrearOmnibus: public eosim::core::BEvent {

    public:
        // constructores
        CrearOmnibus(eosim::core::Model& model);
        // destructor
        ~CrearOmnibus();
        // rutina del evento fijo
        void eventRoutine(eosim::core::Entity* who);
};

#endif // LINEA_H
