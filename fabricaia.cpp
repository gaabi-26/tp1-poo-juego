#include "fabricaia.h"
#include "claseiabasica.h"
#include "claseiaintermedia.h"
#include "claseiaavanzada.h"

std::vector<std::string> FabricaIA::nombres()
{
    std::vector<std::string> lista;
    lista.push_back("Aleatoria");
    lista.push_back("Estrategica");
    lista.push_back("Super");
    return lista;
}

EstrategiaIA *FabricaIA::crear(const std::string &nombre, ConfiguracionDanio &danio)
{
    if (nombre == "Estrategica") {
        return new ClaseIAIntermedia(danio);
    }

    if (nombre == "Super") {
        return new ClaseIAAvanzada(danio);
    }

    return new claseIAbasica();
}
