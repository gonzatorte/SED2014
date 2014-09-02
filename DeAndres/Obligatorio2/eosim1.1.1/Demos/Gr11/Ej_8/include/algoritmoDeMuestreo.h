#ifndef ALGORITMODEMUESTREO_H
#define ALGORITMODEMUESTREO_H
#include <eosim/dist/distribution.hpp>
using namespace eosim::dist;

class algoritmoDeMuestreo: public eosim::dist::Distribution
{
    public:
        double sample();
        algoritmoDeMuestreo(GenType, double*, double*,bool);
        virtual ~algoritmoDeMuestreo();

    private:
        double* F;
        double* indices;
        bool esDiscreta;
};

#endif // ALGORITMODEMUESTREO_H
