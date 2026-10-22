#include "fabricaia.h"
#include <map>
#include "claseiabasica.h"
#include "claseiaintermedia.h"
#include "claseiaavanzada.h"

const std::vector<std::string> &FabricaIA::nombres()
{
    static const std::vector<std::string> lista = {"Aleatoria", "Estrategica", "Super"};

    return lista;
}

EstrategiaIA *FabricaIA::crear(const std::string &nombre, ConfiguracionDanio &danio)
{
    typedef EstrategiaIA *(*Creador)(ConfiguracionDanio &);

    // Se busca por nombre en vez de encadenar if/else.
    static const std::map<std::string, Creador> creadores = {
        {"Aleatoria",   &FabricaIA::crearAleatoria},
        {"Estrategica", &FabricaIA::crearEstrategica},
        {"Super",       &FabricaIA::crearSuper}
    };

    std::map<std::string, Creador>::const_iterator creador = creadores.find(nombre);

    if (creador == creadores.end())
    {
        return crearAleatoria(danio);
    }

    return creador->second(danio);
}

EstrategiaIA *FabricaIA::crearAleatoria(ConfiguracionDanio &)
{
    return new claseIAbasica();
}

EstrategiaIA *FabricaIA::crearEstrategica(ConfiguracionDanio &danio)
{
    return new ClaseIAIntermedia(danio);
}

EstrategiaIA *FabricaIA::crearSuper(ConfiguracionDanio &danio)
{
    return new ClaseIAAvanzada(danio);
}
