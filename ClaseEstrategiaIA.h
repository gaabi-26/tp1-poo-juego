#ifndef CLASEESTRATEGIAIA_H
#define CLASEESTRATEGIAIA_H

#include <string>
#include <vector>
#include "carta.h"

using namespace std;

class EstrategiaIA{
public:
    virtual Carta elegirCarta(vector<Carta> cartasDisponibles, Carta cartaOponente) = 0;
    // Nombre usado en la persistencia y en config.txt (ver FabricaIA).
    virtual string nombre() const = 0;
    virtual ~EstrategiaIA() = default;
};

#endif // ESTRATEGIAIA_H