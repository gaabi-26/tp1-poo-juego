#ifndef FABRICAIA_H
#define FABRICAIA_H

#include <string>
#include <vector>
#include "ClaseEstrategiaIA.h"
#include "ConfiguracionDanio.h"

// Crea la estrategia de IA a partir de su nombre (config.txt / partidas guardadas).
class FabricaIA
{
public:
    // Mismo orden que los items del combo cmbIA del menu.
    static const std::vector<std::string> &nombres();

    // Un nombre desconocido da la IA Aleatoria. La IA guarda una referencia a
    // "danio": debe vivir mas que la estrategia.
    static EstrategiaIA *crear(const std::string &nombre, ConfiguracionDanio &danio);

private:
    static EstrategiaIA *crearAleatoria(ConfiguracionDanio &danio);
    static EstrategiaIA *crearEstrategica(ConfiguracionDanio &danio);
    static EstrategiaIA *crearSuper(ConfiguracionDanio &danio);
};

#endif // FABRICAIA_H
