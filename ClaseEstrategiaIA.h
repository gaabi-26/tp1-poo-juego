#ifndef CLASEESTRATEGIAIA_H
#define CLASEESTRATEGIAIA_H

#include <vector>
#include "carta.h"

using namespace std;

class EstrategiaIA{
public:
    virtual Carta elegirCarta(vector<Carta> cartasDisponibles, Carta cartaOponente) = 0;
    virtual ~EstrategiaIA() = default;
};

#endif // ESTRATEGIAIA_H