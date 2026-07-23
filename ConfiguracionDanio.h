#ifndef CONFIGURACIONDANIO_H
#define CONFIGURACIONDANIO_H

// Indices: 0 = Agua, 1 = Tierra, 2 = Fuego.
// TablaDanio[atacante][defensor] = porcentaje de daño infligido.
class ConfiguracionDanio
{
public:
    static const int CANTIDAD_TIPOS = 3;

    ConfiguracionDanio();

    void configurarDanio(int atacante, int defensor, int porcentaje);

    int obtenerDanio(int atacante, int defensor) const;

private:
    int m_tablaDanio[CANTIDAD_TIPOS][CANTIDAD_TIPOS];
};

#endif // CONFIGURACIONDANIO_H
