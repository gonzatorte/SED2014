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
#include <eosim/dist/uniformdist.hpp>
#include <eosim/graphic.hpp>
#include <map>

using namespace eosim::dist;

class SistemaTransporte: public eosim::core::Model
{
    public:
        SistemaTransporte( double*** frecuencias, double** costos, bool muestraDisplay);
        virtual ~SistemaTransporte();
        eosim::utils::EntityQueueFifo paradaPasajeros[85];
        Linea* lineas[13];
        map<int,eosim::dist::NegexpDist*> m;
        map<int,eosim::dist::NormalDist*> d;
        map<int,eosim::dist::UniformDist*> u;
        Linea* getLinea(int);
        eosim::graphic::Display display;
        eosim::graphic::RefreshGraphic refreshDisplay;
        eosim::graphic::TextSprite paradas[85];
        eosim::graphic::TextSprite referenciaParadas[85];
        eosim::graphic::TextSprite referenciaLineasTexto[14];
        eosim::graphic::Sprite referenciaLineasSprite[14];
        void setearSemillasAHuevo(int seed);
        double funcionThinning(double,int,int);
        double fun(double, double, double, double);

        eosim::statics::Observation histTEsperaGlobal;
        double obtenerCosto(int, int);
        double** costos;
        double*** frecuencias;
        double pXY[85][2];
        bool muestraDisplay;


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
