#ifndef CLASEIABASICA_H
#define CLASEIABASICA_H

#include "ClaseEstrategiaIA.h"

class claseIAbasica : public EstrategiaIA
{
public:
    virtual Carta elegirCarta(vector<Carta> cartasDisponibles,Carta cartaOponente) override;
    string nombre() const override;
};

#endif // CLASEIABASICA_H