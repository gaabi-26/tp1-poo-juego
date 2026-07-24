#ifndef JUGADORHUMANO_H
#define JUGADORHUMANO_H

#include "jugador.h"

// Implementacion minima de Jugador para el jugador humano: pide por
// consola cual carta viva usar. Se agrega solo para poder instanciar
// Partida (Jugador es abstracta); no formaba parte de los archivos
// originales.
class JugadorHumano : public Jugador
{
protected:
    Carta* CartaActiva = nullptr;
public:
    explicit JugadorHumano(std::string nombre);

    Carta& seleccionarCarta(Carta *cartaOponente) override;
    void setCartaActiva(Carta* carta);
};

#endif // JUGADORHUMANO_H