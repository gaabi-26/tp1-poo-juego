#include "jugadorhumano.h"
#include <stdexcept>

JugadorHumano::JugadorHumano(std::string nombre)
    : Jugador(nombre)
{
}

Carta& JugadorHumano::seleccionarCarta(Carta *cartaOponente)
{
    (void)cartaOponente; // Silencia advertencias del compilador sobre variable no utilizada

    if (CartaActiva == nullptr)
    {
        throw std::runtime_error("El jugador humano no selecciono carta todavia");
    }

    return *CartaActiva;
}

void JugadorHumano::setCartaActiva(Carta *carta)
{
    CartaActiva = carta;
}