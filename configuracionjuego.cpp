#include "configuracionjuego.h"

ConfiguracionJuego::ConfiguracionJuego()
{
    this->cantidadCartas = 5;
    this->ia = "Aleatoria";
}

int ConfiguracionJuego::getCantidadCartas() const
{
    return this->cantidadCartas;
}

void ConfiguracionJuego::setCantidadCartas(int cantidad)
{
    this->cantidadCartas = cantidad;
}

const std::string &ConfiguracionJuego::getIA() const
{
    return this->ia;
}

void ConfiguracionJuego::setIA(const std::string &ia)
{
    this->ia = ia;
}

ConfiguracionDanio &ConfiguracionJuego::getDanio()
{
    return this->danio;
}

const ConfiguracionDanio &ConfiguracionJuego::getDanio() const
{
    return this->danio;
}
