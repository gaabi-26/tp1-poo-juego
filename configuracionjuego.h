#ifndef CONFIGURACIONJUEGO_H
#define CONFIGURACIONJUEGO_H

#include <string>
#include "ConfiguracionDanio.h"

// Parametros de una partida (los que se leen de config.txt). No sabe nada
// de archivos: de eso se encarga RepositorioConfiguracion.
class ConfiguracionJuego
{
public:
    ConfiguracionJuego();

    int obtenerCantidadCartas() const;
    void setCantidadCartas(int cantidad);

    // Nombre de la IA segun FabricaIA::nombres().
    std::string obtenerIA() const;
    void setIA(const std::string &ia);

    ConfiguracionDanio &obtenerDanio();
    const ConfiguracionDanio &obtenerDanio() const;

private:
    int m_cantidadCartas;
    std::string m_ia;
    ConfiguracionDanio m_danio;
};

#endif // CONFIGURACIONJUEGO_H
