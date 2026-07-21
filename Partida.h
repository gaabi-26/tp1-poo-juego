#ifndef PARTIDA_H
#define PARTIDA_H

#include <vector>
#include "Jugador.h"
#include "MotorCombate.h"
#include "TipoElemento.h"

// Coordinador central del juego: inicializa jugadores y cartas, ejecuta
// el ciclo de rondas y determina al ganador. No implementa logica de
// combate ni de decision: orquesta los objetos que si lo hacen.
class Partida
{
public:
    Partida(Jugador *jugadorHumano, Jugador *jugadorIA, const MotorCombate &motor);

    void iniciarPartida(int cantidadCartas = 5);
    void ejecutarRonda();
    bool hayGanador() const;
    Jugador *obtenerGanador() const;

    // Utilizado tambien por Partida para reponer mazos; expuesto para
    // poder testear la generacion de cartas de forma aislada.
    std::vector<Carta> generarCartas(int cantidad);

private:
    Jugador *m_jugadorHumano;
    Jugador *m_jugadorIA;
    MotorCombate m_motor;

    std::vector<TipoElemento> m_tiposDisponibles;

    // Carta actualmente en combate de cada jugador. Se mantiene hasta que
    // muere; en ese momento el jugador debe elegir una nueva (ver
    // ejecutarRonda()). Este comportamiento reproduce el ejemplo de
    // partida descripto en el enunciado.
    Carta *m_cartaActivaHumano;
    Carta *m_cartaActivaIA;
};

#endif // PARTIDA_H
