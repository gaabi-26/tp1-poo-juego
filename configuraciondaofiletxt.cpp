#include "configuraciondaofiletxt.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "fabricaia.h"

namespace {
// Indices: deben coincidir con el orden del enum TipoElemento (Agua=0, Fuego=1, Tierra=2)
const char *const NOMBRES_TIPO[ConfiguracionDanio::CANTIDAD_TIPOS] = {"Agua", "Fuego", "Tierra"};
}

ConfiguracionDaoFileTxt::ConfiguracionDaoFileTxt(const std::string &ruta)
{
    this->ruta = ruta;
}

ConfiguracionJuego ConfiguracionDaoFileTxt::leer()
{
    std::ifstream archivo(this->ruta);

    if (!archivo.is_open()) {
        return ConfiguracionJuego();
    }

    ConfiguracionJuego configuracion = this->desdeClaves(this->leerClaves(archivo));
    archivo.close();
    return configuracion;
}

std::map<std::string, std::string> ConfiguracionDaoFileTxt::leerClaves(std::istream &entrada)
{
    std::map<std::string, std::string> claves;
    std::string linea;

    while (std::getline(entrada, linea)) {
        linea = this->recortar(linea);

        if (linea.empty() || linea[0] == '#') {
            continue;
        }

        std::stringstream ss(linea);
        std::string clave, valor;

        // Leemos los campos separados por '='
        std::getline(ss, clave, '=');
        if (!std::getline(ss, valor)) {
            continue;
        }

        claves[this->recortar(clave)] = this->recortar(valor);
    }

    return claves;
}

ConfiguracionJuego ConfiguracionDaoFileTxt::desdeClaves(const std::map<std::string, std::string> &claves)
{
    ConfiguracionJuego configuracion;
    int valor;

    if (claves.count("cantidadCartas") > 0 && this->aEntero(claves.at("cantidadCartas"), 1, 20, valor)) {
        configuracion.setCantidadCartas(valor);
    }

    if (claves.count("ia") > 0) {
        std::vector<std::string> nombres = FabricaIA::nombres();

        for (int i = 0; i < nombres.size(); i++) {
            if (nombres[i] == claves.at("ia")) {
                configuracion.setIA(nombres[i]);
            }
        }
    }

    for (int atacante = 0; atacante < ConfiguracionDanio::CANTIDAD_TIPOS; atacante++) {
        for (int defensor = 0; defensor < ConfiguracionDanio::CANTIDAD_TIPOS; defensor++) {
            std::string clave = std::string("danio.") + NOMBRES_TIPO[atacante] + "." + NOMBRES_TIPO[defensor];

            if (claves.count(clave) > 0 && this->aEntero(claves.at(clave), 0, 100, valor)) {
                configuracion.getDanio().configurarDanio(atacante, defensor, valor);
            }
        }
    }

    return configuracion;
}

void ConfiguracionDaoFileTxt::escribir(const ConfiguracionJuego &configuracion, std::ostream &salida)
{
    salida << "cantidadCartas=" << configuracion.getCantidadCartas() << "\n";
    salida << "ia=" << configuracion.getIA() << "\n";

    for (int atacante = 0; atacante < ConfiguracionDanio::CANTIDAD_TIPOS; atacante++) {
        for (int defensor = 0; defensor < ConfiguracionDanio::CANTIDAD_TIPOS; defensor++) {
            salida << "danio." << NOMBRES_TIPO[atacante] << "." << NOMBRES_TIPO[defensor] << "="
                   << configuracion.getDanio().obtenerDanio(atacante, defensor) << "\n";
        }
    }
}

std::string ConfiguracionDaoFileTxt::nombreTipo(TipoElemento tipo)
{
    return NOMBRES_TIPO[static_cast<int>(tipo)];
}

TipoElemento ConfiguracionDaoFileTxt::tipoDesdeNombre(const std::string &nombre)
{
    for (int i = 0; i < ConfiguracionDanio::CANTIDAD_TIPOS; i++) {
        if (nombre == NOMBRES_TIPO[i]) {
            return static_cast<TipoElemento>(i);
        }
    }

    throw std::invalid_argument("Tipo de elemento desconocido: " + nombre);
}

std::string ConfiguracionDaoFileTxt::recortar(const std::string &texto)
{
    // Tambien quita el '\r' que dejan los archivos con saltos de linea de Windows
    const char *espacios = " \t\r\n";
    size_t inicio = texto.find_first_not_of(espacios);

    if (inicio == std::string::npos) {
        return "";
    }

    return texto.substr(inicio, texto.find_last_not_of(espacios) - inicio + 1);
}

bool ConfiguracionDaoFileTxt::aEntero(const std::string &texto, int minimo, int maximo, int &resultado)
{
    try {
        size_t usados = 0;
        int valor = std::stoi(texto, &usados);

        if (usados != texto.size() || valor < minimo || valor > maximo) {
            return false;
        }

        resultado = valor;
        return true;
    }
    catch (const std::exception &e) {
        return false;
    }
}
