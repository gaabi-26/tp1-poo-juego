#ifndef JUGADORIA_H
#define JUGADORIA_H

#include "jugador.h"
#include "claseestrategiaia.h"

class JugadorIA : public Jugador
{
private:

    EstrategiaIA* Estrategia;

public:

    JugadorIA(std::string nombre, EstrategiaIA* estrategia);

    Carta& seleccionarCarta() override;

    EstrategiaIA* getEstrategia() const;
};

#endif // JUGADORIA_H