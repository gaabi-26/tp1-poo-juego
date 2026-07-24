#include "ConfiguracionDanio.h"

namespace {
// Indices: deben coincidir con el orden del enum TipoElemento (Agua=0, Fuego=1, Tierra=2)
const int AGUA = 0;
const int FUEGO = 1;
const int TIERRA = 2;
}

ConfiguracionDanio::ConfiguracionDanio()
{
    // Se inicializa toda la matriz en 0 y luego se cargan los valores
    // nombres de tipos: todo se resuelve por posicion en la matriz.
    for (int i = 0; i < CANTIDAD_TIPOS; ++i) {
        for (int j = 0; j < CANTIDAD_TIPOS; ++j) {
            m_tablaDanio[i][j] = 0;
        }
    }

    // Valores de ejemplo para poder iniciar.
    m_tablaDanio[AGUA][FUEGO]   = 40;
    m_tablaDanio[TIERRA][FUEGO] = 20;
    m_tablaDanio[FUEGO][TIERRA] = 40;
    m_tablaDanio[AGUA][TIERRA]  = 20;
    m_tablaDanio[FUEGO][AGUA]   = 20;
    m_tablaDanio[TIERRA][AGUA]  = 40;
    m_tablaDanio[TIERRA][TIERRA]  = 10;
    m_tablaDanio[FUEGO][FUEGO]  = 10;
    m_tablaDanio[AGUA][AGUA]  = 10;

}

void ConfiguracionDanio::configurarDanio(int atacante, int defensor, int porcentaje)
{
    if (atacante < 0 || atacante >= CANTIDAD_TIPOS) return;
    if (defensor < 0 || defensor >= CANTIDAD_TIPOS) return;
    if (porcentaje < 0) porcentaje = 0;
    if (porcentaje > 100) porcentaje = 100;

    m_tablaDanio[atacante][defensor] = porcentaje;
}

int ConfiguracionDanio::obtenerDanio(int atacante, int defensor) const
{
    if (atacante < 0 || atacante >= CANTIDAD_TIPOS) return 0;
    if (defensor < 0 || defensor >= CANTIDAD_TIPOS) return 0;

    return m_tablaDanio[atacante][defensor];
}