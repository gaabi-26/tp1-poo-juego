#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>

#include "carta.h"

class Jugador
{
protected:

    // Protected para que las clases hijas puedan acceder directamente a estos atributos
    std::string Nombre;
    std::vector<Carta> Cartas;

public:

    Jugador(std::string nombre);

    virtual ~Jugador() = default;

    virtual Carta& seleccionarCarta() = 0;

    bool tieneCartasVivas() const;

    std::vector<Carta> obtenerCartasVivas() const;

    std::string getNombre() const;

    std::vector<Carta> getCartas() const;

    void setCartas(const std::vector<Carta>& cartas);
};

#endif // JUGADOR_H