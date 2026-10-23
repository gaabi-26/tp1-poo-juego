#include "claseiaavanzada.h"

#include<stdexcept>

ClaseIAAvanzada::ClaseIAAvanzada(ConfiguracionDanio& configuracion) :configuracion(configuracion) {}

Carta ClaseIAAvanzada::elegirCarta(vector<Carta> cartasDisponibles, Carta cartaOponente){
if (cartasDisponibles.empty()){
    throw std::runtime_error(
        "La IA avanzada no tiene cartas disponibles");
}

int energiaOponente = cartaOponente.getEnergia();

int indiceDefensor=static_cast<int>(cartaOponente.getTipo());

///La IA ya conoce la carta que va a jugar el humano: simula el choque de esta ronda con cada una de sus cartas

int posicionMejorCarta=0;
int mejorPuntaje=-1000; ///se inicia muy bajo porque el puntaje puede ser negativo
int energiaMejorCarta=0;

for(int i=0;i<static_cast<int>(cartasDisponibles.size());i++){

    int indiceAtacante= static_cast<int>(cartasDisponibles[i].getTipo());
    int energiaPropia = cartasDisponibles[i].getEnergia();

    int danioHecho=configuracion.obtenerDanio(indiceAtacante,indiceDefensor);
    int danioRecibido=configuracion.obtenerDanio(indiceDefensor,indiceAtacante);

    bool eliminaAlOponente = danioHecho>=energiaOponente;
    bool muerePropia = danioRecibido>=energiaPropia;

    ///ventaja de danio sobre el rival, con premio por eliminarlo y castigo por perder la carta
    int puntaje=danioHecho-danioRecibido;
    if(eliminaAlOponente){
        puntaje+=200;
    }
    if(muerePropia){
        puntaje-=150;
    }

    ///a igual puntaje decide la vida propia: si elimina gasta la carta mas debil, si no usa la mas sana
    bool desempata = energiaPropia>energiaMejorCarta;
    if(eliminaAlOponente){
        desempata = energiaPropia<energiaMejorCarta;
    }

    if(puntaje>mejorPuntaje || (puntaje==mejorPuntaje && desempata)){
        mejorPuntaje = puntaje;
        energiaMejorCarta = energiaPropia;
        posicionMejorCarta = i;
    }
}
return cartasDisponibles[posicionMejorCarta];
}

string ClaseIAAvanzada::nombre() const
{
    return "Super";
}
