#include "jugadorhumano.h"

JugadorHumano::JugadorHumano(std::string nombre)
    : Jugador(nombre)
{
}

Carta& JugadorHumano::seleccionarCarta(Carta *cartaOponente)
{
    (void)cartaOponente;

    return *CartaActiva;
}

void JugadorHumano::setCartaActiva(Carta *carta)
{
    CartaActiva = carta;
}