#include "Partida.h"
#include <cstdlib>
#include <ctime>

using namespace std;


Partida::Partida(Jugador *jugadorHumano, Jugador *jugadorIA, const MotorCombate &motor)
{
    m_jugadorHumano = jugadorHumano;
    m_jugadorIA = jugadorIA;
    m_motor = motor;

    m_cartaActivaHumano = nullptr;
    m_cartaActivaIA = nullptr;

    srand(time(NULL));

    m_tiposDisponibles.push_back(TipoElemento("Agua", 0));
    m_tiposDisponibles.push_back(TipoElemento("Tierra", 1));
    m_tiposDisponibles.push_back(TipoElemento("Fuego", 2));
}


vector<Carta> Partida::generarCartas(int cantidad)
{
    vector<Carta> cartas;

    for(int i = 0; i < cantidad; i++)
    {
        int tipo = rand() % 3;

        cartas.push_back(Carta(m_tiposDisponibles[tipo]));
    }

    return cartas;
}


void Partida::iniciarPartida(int cantidadCartas)
{
    m_jugadorHumano->setCartas(generarCartas(cantidadCartas));
    m_jugadorIA->setCartas(generarCartas(cantidadCartas));

    m_cartaActivaHumano = nullptr;
    m_cartaActivaIA = nullptr;


    while(!hayGanador())
    {
        ejecutarRonda();
    }
}


void Partida::ejecutarRonda()
{
    if(m_cartaActivaHumano == nullptr || !m_cartaActivaHumano->estaViva())
    {
        m_cartaActivaHumano = &m_jugadorHumano->seleccionarCarta(m_cartaActivaIA);
    }


    if(m_cartaActivaIA == nullptr || !m_cartaActivaIA->estaViva())
    {
        m_cartaActivaIA = &m_jugadorIA->seleccionarCarta(m_cartaActivaHumano);
    }


    m_motor.ejecutarTurno(*m_cartaActivaHumano, *m_cartaActivaIA);
}


bool Partida::hayGanador() const
{
    return !m_jugadorHumano->tieneCartasVivas() ||
           !m_jugadorIA->tieneCartasVivas();
}


Jugador* Partida::obtenerGanador() const
{
    if(m_jugadorHumano->tieneCartasVivas())
    {
        return m_jugadorHumano;
    }

    if(m_jugadorIA->tieneCartasVivas())
    {
        return m_jugadorIA;
    }

    return nullptr;
}