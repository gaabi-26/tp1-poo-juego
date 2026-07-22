#ifndef CLASEIAAVANZADA_H
#define CLASEIAAVANZADA_H

#include "EstrategiaIA.h"
#include "ConfiguracionDanio.h"

class ClaseIAAvanzada : public EstrategiaIA
{
private:
    configuracionDanio& configuracion;
public:
    ClaseIAAvanzada(ConfiguracionDanio& configuracion);

    virtual Carta elegirCarta(vector<Carta> cartasDisponibles, Carta cartaOponente)override;
};

#endif // CLASEIAAVANZADA_H
