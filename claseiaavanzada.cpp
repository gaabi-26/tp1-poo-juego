#include "claseiaavanzada.h"

#include<stdexcept>

ClaseIAAvanzada::ClaseIAAvanzada(ConfiguracionDanio& configuracion) :configuracion(configuracion) {}

Carta ClaseIAAvanzada::elegirCarta(vector<Carta> cartasDisponibles, Carta cartaOponente){
    if (cartasDisponibles.empty()){
        throw std::runtime_error(
            "La IA avanzada no tiene cartas disponibles");
    }

    int energiaOponente = cartaOponente.getEnergia();
    ///VERIFICAR. ver si el getIndice va a estar dentro de TipoElemento
    int indiceDefensor=static_cast<int>(cartaOponente.getTipo());

    int posicionCartaEliminadora=-1;
    int menorEnergiaPropia=101;

    ///PRIMERA PARTE: busca una carta que pueda eliminar al oponente

    for(int i=0;i<static_cast<int>(cartasDisponibles.size());i++){

        int indiceAtacante= static_cast<int>(cartasDisponibles[i].getTipo());

        int danioActual=configuracion.obtenerDanio(indiceAtacante,indiceDefensor);
        if(danioActual>=energiaOponente){
            int energiaPropia = cartasDisponibles[i].getEnergia();

            if(energiaPropia<menorEnergiaPropia){
                menorEnergiaPropia = energiaPropia;
                posicionCartaEliminadora= i;
            }
        }
    }


    ///si encontro una carta capaz de eliminar al oponente devuelve esa carta.
    if(posicionCartaEliminadora!=-1){
        return cartasDisponibles[posicionCartaEliminadora];
    }



    ///SEGUNDA PARTE: si ninguna carta puede eliminar al rival, elegir la que cause mayor danio

    int posicionMejorCarta=0;
    int mayorDanio=-1;

    for(int i=0;i<static_cast<int>(cartasDisponibles.size());i++){
        int indiceAtacante= static_cast<int>(cartasDisponibles[i].getTipo());

        int danioActual=configuracion.obtenerDanio(indiceAtacante,indiceDefensor);

        if(danioActual>mayorDanio){
            mayorDanio = danioActual;
            posicionMejorCarta = i;
        }

    }
    return cartasDisponibles[posicionMejorCarta];
}