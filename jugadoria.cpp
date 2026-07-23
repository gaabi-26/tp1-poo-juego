#include "jugadoria.h"
#include "claseestrategiaia.h"

JugadorIA::JugadorIA(std::string nombre, EstrategiaIA* estrategia)
    : Jugador(nombre)
{
    this->Estrategia = estrategia;
}

Carta& JugadorIA::seleccionarCarta()
{

    std::vector<Carta> cartasDisponibles = obtenerCartasVivas();

    // Implementar ...
    // Mientras tanto devolvemos la primera carta viva

    for (Carta& carta : Cartas)
    {
        if (carta.estaViva())
        {
            return carta;
        }
    }

    return Cartas.front();
}

EstrategiaIA* JugadorIA::getEstrategia() const
{
    return Estrategia;
}