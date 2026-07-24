#include "jugadoria.h"
#include "ClaseEstrategiaIA.h"

JugadorIA::JugadorIA(std::string nombre, EstrategiaIA* estrategia)
    : Jugador(nombre)
{
    this->Estrategia = estrategia;
}

Carta& JugadorIA::seleccionarCarta(Carta* cartaOponente)
{
    std::vector<Carta> cartasDisponibles = obtenerCartasVivas();

    // cartaOponente puede ser nullptr (por ejemplo, si el rival todavia no
    // eligio su carta activa). En ese caso no hay informacion para decidir
    // una estrategia, asi que se devuelve simplemente la primera carta viva.
    if (cartaOponente == nullptr || Estrategia == nullptr)
    {
        for (Carta& carta : Cartas)
        {
            if (carta.estaViva())
            {
                return carta;
            }
        }
        return Cartas.front();
    }

    Carta elegida = Estrategia->elegirCarta(cartasDisponibles, *cartaOponente);

    // La estrategia trabaja sobre copias (cartasDisponibles), asi que hay
    // que ubicar la carta real dentro de Cartas (mismo tipo y energia) para
    // poder devolver una referencia valida que si modifique el estado real.
    for (Carta& carta : Cartas)
    {
        if (carta.estaViva() &&
            carta.getTipo() == elegida.getTipo() &&
            carta.getEnergia() == elegida.getEnergia())
        {
            return carta;
        }
    }

    // Fallback de seguridad, no deberia llegar aca en condiciones normales.
    for (Carta& carta : Cartas)
    {
        if (carta.estaViva())
        {
            return carta;
        }
    }

    return Cartas.front();
}

EstrategiaIA* JugadorIA::getEstrategia() const
{
    return Estrategia;
}