#ifndef PARTIDADAO_H
#define PARTIDADAO_H

#include <string>
#include <vector>
#include "Partida.h"

// Guarda, lista y recupera partidas sin que Partida, los jugadores ni la
// interfaz sepan donde ni como se almacenan (hoy archivos de texto).
class PartidaDao
{
public:
    virtual ~PartidaDao() {}

    // false si el nombre no es valido o no se pudo escribir.
    virtual bool guardar(Partida &partida, const std::string &nombre) = 0;

    // Devuelve una Partida nueva (y sus jugadores) que pasa a ser del llamador.
    // Lanza std::runtime_error si no existe o esta corrupta.
    virtual Partida *cargar(const std::string &nombre) = 0;

    virtual std::vector<std::string> listar() = 0;
};

#endif // PARTIDADAO_H
