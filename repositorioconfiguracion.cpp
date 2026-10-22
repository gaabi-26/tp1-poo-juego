#include "repositorioconfiguracion.h"
#include <fstream>
#include <stdexcept>
#include "fabricaia.h"

namespace {
// Indices: deben coincidir con el orden del enum TipoElemento (Agua=0, Fuego=1, Tierra=2)
const char *const NOMBRES_TIPO[ConfiguracionDanio::CANTIDAD_TIPOS] = {"Agua", "Fuego", "Tierra"};
}

ConfiguracionJuego RepositorioConfiguracion::cargar(const std::string &ruta) const
{
    std::ifstream archivo(ruta);

    if (!archivo)
    {
        return ConfiguracionJuego();
    }

    return desdeClaves(leerClaves(archivo));
}

std::map<std::string, std::string> RepositorioConfiguracion::leerClaves(std::istream &entrada)
{
    std::map<std::string, std::string> claves;
    std::string linea;

    while (std::getline(entrada, linea))
    {
        linea = recortar(linea);

        size_t igual = linea.find('=');

        if (linea.empty() || linea[0] == '#' || igual == std::string::npos)
        {
            continue;
        }

        claves[recortar(linea.substr(0, igual))] = recortar(linea.substr(igual + 1));
    }

    return claves;
}

ConfiguracionJuego RepositorioConfiguracion::desdeClaves(const std::map<std::string, std::string> &claves)
{
    ConfiguracionJuego configuracion;
    int valor;

    std::map<std::string, std::string>::const_iterator cantidad = claves.find("cantidadCartas");

    if (cantidad != claves.end() && aEntero(cantidad->second, 1, 20, valor))
    {
        configuracion.setCantidadCartas(valor);
    }

    std::map<std::string, std::string>::const_iterator ia = claves.find("ia");

    if (ia != claves.end())
    {
        for (const std::string &nombre : FabricaIA::nombres())
        {
            if (nombre == ia->second)
            {
                configuracion.setIA(nombre);
            }
        }
    }

    for (int atacante = 0; atacante < ConfiguracionDanio::CANTIDAD_TIPOS; ++atacante)
    {
        for (int defensor = 0; defensor < ConfiguracionDanio::CANTIDAD_TIPOS; ++defensor)
        {
            std::string clave = std::string("danio.") + NOMBRES_TIPO[atacante] + "." + NOMBRES_TIPO[defensor];
            std::map<std::string, std::string>::const_iterator danio = claves.find(clave);

            if (danio != claves.end() && aEntero(danio->second, 0, 100, valor))
            {
                configuracion.obtenerDanio().configurarDanio(atacante, defensor, valor);
            }
        }
    }

    return configuracion;
}

void RepositorioConfiguracion::escribir(const ConfiguracionJuego &configuracion, std::ostream &salida)
{
    salida << "cantidadCartas=" << configuracion.obtenerCantidadCartas() << "\n";
    salida << "ia=" << configuracion.obtenerIA() << "\n";

    for (int atacante = 0; atacante < ConfiguracionDanio::CANTIDAD_TIPOS; ++atacante)
    {
        for (int defensor = 0; defensor < ConfiguracionDanio::CANTIDAD_TIPOS; ++defensor)
        {
            salida << "danio." << NOMBRES_TIPO[atacante] << "." << NOMBRES_TIPO[defensor] << "="
                   << configuracion.obtenerDanio().obtenerDanio(atacante, defensor) << "\n";
        }
    }
}

std::string RepositorioConfiguracion::nombreTipo(TipoElemento tipo)
{
    return NOMBRES_TIPO[static_cast<int>(tipo)];
}

TipoElemento RepositorioConfiguracion::tipoDesdeNombre(const std::string &nombre)
{
    for (int i = 0; i < ConfiguracionDanio::CANTIDAD_TIPOS; ++i)
    {
        if (nombre == NOMBRES_TIPO[i])
        {
            return static_cast<TipoElemento>(i);
        }
    }

    throw std::invalid_argument("Tipo de elemento desconocido: " + nombre);
}

std::string RepositorioConfiguracion::recortar(const std::string &texto)
{
    const char *espacios = " \t\r\n";

    size_t inicio = texto.find_first_not_of(espacios);

    if (inicio == std::string::npos)
    {
        return "";
    }

    return texto.substr(inicio, texto.find_last_not_of(espacios) - inicio + 1);
}

bool RepositorioConfiguracion::aEntero(const std::string &texto, int minimo, int maximo, int &resultado)
{
    try
    {
        size_t usados = 0;
        int valor = std::stoi(texto, &usados);

        if (usados != texto.size() || valor < minimo || valor > maximo)
        {
            return false;
        }

        resultado = valor;
        return true;
    }
    catch (const std::exception &)
    {
        return false;
    }
}
