#ifndef CONFIGURACIONDAO_H
#define CONFIGURACIONDAO_H

#include "configuracionjuego.h"

// Lee la configuracion del juego sin que el resto del programa sepa
// de donde viene (hoy un archivo de texto).
class ConfiguracionDao
{
public:
    virtual ~ConfiguracionDao() {}
    virtual ConfiguracionJuego leer() = 0;
};

#endif // CONFIGURACIONDAO_H
