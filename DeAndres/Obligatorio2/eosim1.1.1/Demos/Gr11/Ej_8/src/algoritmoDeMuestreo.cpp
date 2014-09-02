#include "algoritmoDeMuestreo.h"

algoritmoDeMuestreo::algoritmoDeMuestreo(GenType generator, double* a_indices, double* a_F, bool a_esDiscreta): Distribution(generator), indices(a_indices), F(a_F), esDiscreta(a_esDiscreta) {}

double algoritmoDeMuestreo::sample() {
   double u = generator->nextDouble();
   int x = 1;

   while (u > F[x] ) {
        x = x + 1;
   }

   if (esDiscreta) {
    return indices[x];
   }
   else {
    return indices[x-1] + (((u - F[x-1])/(F[x] - F[x-1]))*(indices[x] - indices[x-1]));
   }

}
algoritmoDeMuestreo::~algoritmoDeMuestreo()
{
    //dtor
}
