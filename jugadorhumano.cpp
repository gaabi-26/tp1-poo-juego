#include "jugadorhumano.h"

JugadorHumano::JugadorHumano(std::string nombre)
    : Jugador(nombre)
{

}

Carta& JugadorHumano::seleccionarCarta()
{
    // Por ahora devolvemos la primera carta viva
    // Implementar ...
    for (Carta& carta : Cartas)
    {
        if (carta.estaViva())
        {
            return carta;
        }
    }

    return Cartas.front(); // No tendria que llegar hasta aca. Ya que dicho metodo solo se llama si hay cartas vivas
}