#include "claseiaintermedia.h"

#include <stdexcept>

ClaseIAIntermedia::ClaseIAIntermedia(
    ConfiguracionDanio& configuracion):configuracion(configuracion  ){}
///el constructor recibe el objeto con la tabla de daños y guarda una referencia a ese objeto

Carta ClaseIAIntermedia::elegirCarta(vector<Carta> cartasDisponibles, Carta cartaOponente)
{
    if(cartasDisponibles.empty()){
        throw std::runtime_error(
            "la IA intermedia no tiene cartas disponibles");
    }
    int posicionMejorCarta =0; ///guarda donde esta la mejor carta encontrada
    int mayorDanio =-1; /// guarda el mayor danio encontrado, se inicia en -1 porque cualquier daño valido sera mayor o igual a 0

    int indiceDefensor = static_cast<int>(cartaOponente.getTipo()); /// obtiene el indice del tipo de la carta del rival ej agua = 0
    for(int i=0;i<static_cast<int>(cartasDisponibles.size());i++){ ///para recorrer las cartas disponibles de la IA
        int indiceAtacante= static_cast<int>(cartasDisponibles[i].getTipo());

        int danioActual=configuracion.obtenerDanio(indiceAtacante, indiceDefensor);
        if(danioActual > mayorDanio){  /// compara el danio de la carta actual con la carta de mayor danio
            mayorDanio = danioActual;
            posicionMejorCarta=i; /// guarda la posicion de la mejor carga
        }
    }
    return cartasDisponibles[posicionMejorCarta];
}