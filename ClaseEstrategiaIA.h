#ifndef CLASEESTRATEGIAIA_H
#define CLASEESTRATEGIAIA_H

#include <vector>
#include "Carta.h"

using namespace std;

class EstrategiaIA{
public:
    virtual Carta& elegirCarta(vector<Carta>cartasDisponibles,Carta cartaOponente)=0;
};

#endif // ESTRATEGIAIA_H