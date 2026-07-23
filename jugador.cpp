#include "jugador.h"

Jugador::Jugador(std::string nombre)
{
    Nombre = nombre;
}

bool Jugador::tieneCartasVivas() const
{
    for (const Carta& carta : Cartas)
    {
        if (carta.estaViva())
        {
            return true;
        }
    }

    return false;
}

std::vector<Carta> Jugador::obtenerCartasVivas() const
{
    std::vector<Carta> cartasVivas;

    for (const Carta& carta : Cartas)
    {
        if (carta.estaViva())
        {
            cartasVivas.push_back(carta);
        }
    }

    return cartasVivas;
}

std::string Jugador::getNombre() const
{
    return Nombre;
}

std::vector<Carta> Jugador::getCartas() const
{
    return Cartas;
}

void Jugador::setCartas(const std::vector<Carta>& cartas)
{
    Cartas = cartas;
}