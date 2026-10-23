#ifndef CONFIGURACIONJUEGO_H
#define CONFIGURACIONJUEGO_H

#include <string>
#include "ConfiguracionDanio.h"

// Parametros de una partida (los que se leen de config.txt). No sabe nada
// de archivos: de eso se encargan los ConfiguracionDao.
class ConfiguracionJuego
{
private:
    int cantidadCartas;
    std::string ia;
    ConfiguracionDanio danio;

public:
    ConfiguracionJuego();

    int getCantidadCartas() const;
    void setCantidadCartas(int cantidad);

    // Nombre de la IA segun FabricaIA::nombres().
    const std::string &getIA() const;
    void setIA(const std::string &ia);

    ConfiguracionDanio &getDanio();
    const ConfiguracionDanio &getDanio() const;
};

#endif // CONFIGURACIONJUEGO_H
