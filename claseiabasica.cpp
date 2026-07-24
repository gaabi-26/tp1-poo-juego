#include "claseiabasica.h" //incluye la delcaracion de cada clase

#include <cstdlib> // perimite usar el rand
#include <stdexcept> // para obtener numero aleatorio


Carta claseIAbasica::elegirCarta(
    vector<Carta> cartasDisponibles, Carta cartaOponente) {
    if(cartasDisponibles.empty()){ /// comprueba que haya cartas disponibles
        throw std::runtime_error(
            "la IA basica no tiene cartas disponibles");
    }
    int posicionAleatoria= std::rand() % cartasDisponibles.size(); //seleccion aleatoria de cartas, poner en main srand(time(nullptr))
    return cartasDisponibles[posicionAleatoria]; /// devuelve la carta ubicada en la posicion generada al azar



}