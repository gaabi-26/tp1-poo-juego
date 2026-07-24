#ifndef JUGADORIA_H
#define JUGADORIA_H

#include "jugador.h"
#include "ClaseEstrategiaIA.h"

class JugadorIA : public Jugador
{
private:

    EstrategiaIA* Estrategia;

public:

    JugadorIA(std::string nombre, EstrategiaIA* estrategia);

    Carta& seleccionarCarta(Carta* cartaOponente) override;

    EstrategiaIA* getEstrategia() const;
};

#endif // JUGADORIA_H