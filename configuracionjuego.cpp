#include "configuracionjuego.h"

ConfiguracionJuego::ConfiguracionJuego()
{
    m_cantidadCartas = 5;
    m_ia = "Aleatoria";
}

int ConfiguracionJuego::obtenerCantidadCartas() const
{
    return m_cantidadCartas;
}

void ConfiguracionJuego::setCantidadCartas(int cantidad)
{
    m_cantidadCartas = cantidad;
}

std::string ConfiguracionJuego::obtenerIA() const
{
    return m_ia;
}

void ConfiguracionJuego::setIA(const std::string &ia)
{
    m_ia = ia;
}

ConfiguracionDanio &ConfiguracionJuego::obtenerDanio()
{
    return m_danio;
}

const ConfiguracionDanio &ConfiguracionJuego::obtenerDanio() const
{
    return m_danio;
}
