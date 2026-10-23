#ifndef REPOSITORIOCONFIGURACION_H
#define REPOSITORIOCONFIGURACION_H

#include <iosfwd>
#include <map>
#include <string>
#include "configuracionjuego.h"
#include "tipoelemento.h"

// CMake define DIRECTORIO_DATOS con la carpeta del proyecto, para que config.txt y
// partidas/ no queden en la carpeta de build.
#ifndef DIRECTORIO_DATOS
#define DIRECTORIO_DATOS "."
#endif

// Lee y escribe el formato de texto "clave=valor" (una por linea, '#' comenta)
// que usan config.txt y las partidas guardadas. Es el unico lugar que parsea.
class RepositorioConfiguracion
{
public:
    // Archivo inexistente -> valores por defecto.
    ConfiguracionJuego cargar(const std::string &ruta) const;

    // Ignora lineas sin '=' y comentarios.
    static std::map<std::string, std::string> leerClaves(std::istream &entrada);

    // Ignora claves desconocidas y valores invalidos (queda el valor por defecto).
    static ConfiguracionJuego desdeClaves(const std::map<std::string, std::string> &claves);

    // Escribe cantidadCartas, ia y danio.<Atacante>.<Defensor>.
    static void escribir(const ConfiguracionJuego &configuracion, std::ostream &salida);

    static std::string nombreTipo(TipoElemento tipo);

    // Lanza std::invalid_argument si el nombre no es un tipo.
    static TipoElemento tipoDesdeNombre(const std::string &nombre);

private:
    static std::string recortar(const std::string &texto);

    // false si el texto no es un entero completo dentro de [minimo, maximo].
    static bool aEntero(const std::string &texto, int minimo, int maximo, int &resultado);
};

#endif // REPOSITORIOCONFIGURACION_H
