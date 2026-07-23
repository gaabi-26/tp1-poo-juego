#ifndef CARTA_H
#define CARTA_H

#include "tipoelemento.h"

class Carta
{
private:
    int Energia;
    TipoElemento Tipo;

public:
    Carta(TipoElemento tipo);

    void recibirDanio(int danio);

    bool estaViva() const;

    int getEnergia() const;

    TipoElemento getTipo() const;
};

#endif // CARTA_H