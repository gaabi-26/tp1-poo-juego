#ifndef PARTIDADAOFILETXT_H
#define PARTIDADAOFILETXT_H

#include <string>
#include <vector>
#include "partidadao.h"
#include "configuraciondaofiletxt.h"

// Una partida por archivo de texto: <carpeta>/<nombre>.txt, con el mismo formato
// clave=valor que config.txt (ver ConfiguracionDaoFileTxt) mas el estado de la partida.
class PartidaDaoFileTxt : public PartidaDao
{
private:
    std::string carpeta;
    ConfiguracionDaoFileTxt configuracionDao;

    bool nombreValido(const std::string &nombre);

    // Formato "Agua:100,Fuego:0". cartasDesdeTexto lanza una excepcion si esta mal formado.
    std::string cartasATexto(const std::vector<Carta> &cartas);
    std::vector<Carta> cartasDesdeTexto(const std::string &texto);

public:
    PartidaDaoFileTxt(const std::string &carpeta = DIRECTORIO_DATOS "/partidas");
    virtual ~PartidaDaoFileTxt() {}

    bool guardar(Partida &partida, const std::string &nombre) override;
    Partida *cargar(const std::string &nombre) override;
    std::vector<std::string> listar() override;
};

#endif // PARTIDADAOFILETXT_H
