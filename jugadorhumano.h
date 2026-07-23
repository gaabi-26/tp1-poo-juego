#ifndef JUGADORHUMANO_H
#define JUGADORHUMANO_H

#include "jugador.h"

class JugadorHumano : public Jugador
{
public:

    JugadorHumano(std::string nombre);

    // Devolver una referencia a la carta elegida
    Carta& seleccionarCarta() override;
};

#endif // JUGADORHUMANO_H