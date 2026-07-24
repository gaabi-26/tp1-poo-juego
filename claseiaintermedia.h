#ifndef CLASEIAINTERMEDIA_H
#define CLASEIAINTERMEDIA_H

#include "ClaseEstrategiaIA.h"
#include "ConfiguracionDanio.h"

class ClaseIAIntermedia : public EstrategiaIA
{
private:
    ConfiguracionDanio& configuracion;
public:

    ClaseIAIntermedia(ConfiguracionDanio& configuracion);

    virtual Carta elegirCarta(vector<Carta> cartasDisponibles,Carta cartaOponente)override;
};

#endif // CLASEIAINTERMEDIA_H