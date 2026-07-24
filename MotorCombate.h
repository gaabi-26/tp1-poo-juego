#ifndef MOTORCOMBATE_H
#define MOTORCOMBATE_H

#include "carta.h"
#include "ConfiguracionDanio.h"

// Encapsula la mecanica de combate: calculo y aplicacion de daño.
class MotorCombate
{
public:
    explicit MotorCombate(const ConfiguracionDanio &configuracion);

    // Ambos daños se calculan antes de aplicar cualquiera de los dos,
    // simulando un combate simultaneo (el orden de aplicacion no afecta
    // el resultado).
    void ejecutarTurno(Carta &carta1, Carta &carta2);

    int calcularDanio(const Carta &atacante, const Carta &defensor) const;

private:
    ConfiguracionDanio m_configuracion;
};

#endif // MOTORCOMBATE_H