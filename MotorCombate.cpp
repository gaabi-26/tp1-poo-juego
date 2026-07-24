#include "MotorCombate.h"

MotorCombate::MotorCombate(const ConfiguracionDanio &configuracion)
    : m_configuracion(configuracion)
{
}

void MotorCombate::ejecutarTurno(Carta &carta1, Carta &carta2)
{
    int danioHaciaCarta2 = calcularDanio(carta1, carta2);
    int danioHaciaCarta1 = calcularDanio(carta2, carta1);

    carta1.recibirDanio(danioHaciaCarta1);
    carta2.recibirDanio(danioHaciaCarta2);
}

int MotorCombate::calcularDanio(const Carta &atacante, const Carta &defensor) const
{
    return m_configuracion.obtenerDanio(static_cast<int>(atacante.getTipo()),static_cast<int>(defensor.getTipo()));
}