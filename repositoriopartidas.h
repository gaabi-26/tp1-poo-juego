#ifndef REPOSITORIOPARTIDAS_H
#define REPOSITORIOPARTIDAS_H

#include <string>
#include <vector>
#include "Partida.h"

// Guarda, lista y recupera partidas como archivos de texto "<carpeta>/<nombre>.txt".
// Usa el mismo formato que config.txt (ver RepositorioConfiguracion) mas el estado.
class RepositorioPartidas
{
public:
    explicit RepositorioPartidas(const std::string &carpeta = "partidas");

    // false si el nombre no es valido o no se pudo escribir el archivo.
    bool guardar(Partida &partida, const std::string &nombre) const;

    // Devuelve una Partida nueva (y sus jugadores) que pasa a ser del llamador.
    // Lanza std::runtime_error si no existe o esta corrupta.
    Partida *cargar(const std::string &nombre) const;

    std::vector<std::string> listar() const;

private:
    std::string m_carpeta;

    static bool nombreValido(const std::string &nombre);

    // Formato "Agua:100,Fuego:0". cartasDesdeTexto lanza si esta mal formado.
    static std::string cartasATexto(const std::vector<Carta> &cartas);
    static std::vector<Carta> cartasDesdeTexto(const std::string &texto);
};

#endif // REPOSITORIOPARTIDAS_H
