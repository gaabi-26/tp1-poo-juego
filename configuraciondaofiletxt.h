#ifndef CONFIGURACIONDAOFILETXT_H
#define CONFIGURACIONDAOFILETXT_H

#include <iostream>
#include <map>
#include <string>
#include "configuraciondao.h"
#include "tipoelemento.h"

// CMake define DIRECTORIO_DATOS con la carpeta del proyecto, para que config.txt y
// partidas/ no queden en la carpeta de build.
#ifndef DIRECTORIO_DATOS
#define DIRECTORIO_DATOS "."
#endif

// Archivo de texto con una clave por linea: clave=valor ('#' comenta).
// Tambien lo usa PartidaDaoFileTxt para la parte de configuracion de una partida.
class ConfiguracionDaoFileTxt : public ConfiguracionDao
{
private:
    std::string ruta;

    std::string recortar(const std::string &texto);
    bool aEntero(const std::string &texto, int minimo, int maximo, int &resultado);

public:
    ConfiguracionDaoFileTxt(const std::string &ruta = DIRECTORIO_DATOS "/config.txt");
    virtual ~ConfiguracionDaoFileTxt() {}

    // Archivo inexistente -> valores por defecto.
    ConfiguracionJuego leer() override;

    // Ignora las lineas vacias, los comentarios y las lineas sin '='.
    std::map<std::string, std::string> leerClaves(std::istream &entrada);

    // Ignora las claves desconocidas y los valores invalidos (queda el valor por defecto).
    ConfiguracionJuego desdeClaves(const std::map<std::string, std::string> &claves);

    // Escribe cantidadCartas, ia y danio.<Atacante>.<Defensor>.
    void escribir(const ConfiguracionJuego &configuracion, std::ostream &salida);

    std::string nombreTipo(TipoElemento tipo);

    // Lanza std::invalid_argument si el nombre no es un tipo.
    TipoElemento tipoDesdeNombre(const std::string &nombre);
};

#endif // CONFIGURACIONDAOFILETXT_H
