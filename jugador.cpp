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

std::vector<Carta>& Jugador::getCartas()
{
    return Cartas;
}

void Jugador::setCartas(const std::vector<Carta>& cartas)
{
    Cartas = cartas;
}

int Jugador::indiceCarta(const Carta *carta) const
{
    for (size_t i = 0; i < Cartas.size(); i++)
    {
        if (&Cartas[i] == carta)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}
