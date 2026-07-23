#include "carta.h"

Carta::Carta(TipoElemento tipo)
{
    Energia = 100;
    Tipo = tipo;
}

void Carta::recibirDanio(int danio)
{
    Energia -= danio;

    // Evitar que la energía sea negativa
    if (Energia < 0)
    {
        Energia = 0;
    }
}

bool Carta::estaViva() const
{
    return Energia > 0;
}

int Carta::getEnergia() const
{
    return Energia;
}

TipoElemento Carta::getTipo() const
{
    return Tipo;
}