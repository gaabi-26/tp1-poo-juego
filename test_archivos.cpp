// Auto-chequeo de la persistencia. Sin Qt: target "test_archivos" (no se compila con "all").
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "fabricaia.h"
#include "jugadorhumano.h"
#include "jugadoria.h"
#include "repositoriopartidas.h"
#include "repositorioconfiguracion.h"

int main()
{
    // Archivo inexistente -> valores por defecto.
    ConfiguracionJuego porDefecto = RepositorioConfiguracion().cargar("no_existe.txt");
    assert(porDefecto.obtenerCantidadCartas() == 5 && porDefecto.obtenerIA() == "Aleatoria");

    // Lineas invalidas se ignoran, las validas se aplican.
    std::istringstream texto("# c\ncantidadCartas=abc\nia=Super\nbasura\ndanio.Agua.Fuego=77\ndanio.Agua.Tierra=x\nia2=Super\n");
    ConfiguracionJuego leida = RepositorioConfiguracion::desdeClaves(RepositorioConfiguracion::leerClaves(texto));
    assert(leida.obtenerCantidadCartas() == 5 && leida.obtenerIA() == "Super");
    assert(leida.obtenerDanio().obtenerDanio(0, 1) == 77);
    assert(leida.obtenerDanio().obtenerDanio(0, 2) == porDefecto.obtenerDanio().obtenerDanio(0, 2));

    // Ida y vuelta: guardar -> listar -> cargar.
    std::filesystem::remove_all("test_partidas");
    RepositorioPartidas repo("test_partidas");

    ConfiguracionDanio *danio = new ConfiguracionDanio();
    danio->configurarDanio(0, 1, 55);
    JugadorHumano *humano = new JugadorHumano("Ana");
    JugadorIA *ia = new JugadorIA("PC", FabricaIA::crear("Super", *danio));
    Partida original(humano, ia, MotorCombate(*danio));
    original.iniciarPartida(4);
    original.seleccionarCartaHumano(&humano->getCartas()[2]);
    original.ejecutarRonda();

    assert(repo.guardar(original, "uno"));
    assert(!repo.guardar(original, "../malo"));
    assert(repo.listar().size() == 1 && repo.listar()[0] == "uno");

    Partida *copia = repo.cargar("uno");
    assert(copia->obtenerTurno() == original.obtenerTurno());
    assert(copia->indiceCartaActivaHumano() == 2);
    assert(copia->indiceCartaActivaIA() == original.indiceCartaActivaIA());
    assert(copia->obtenerMotor().obtenerConfiguracion().obtenerDanio(0, 1) == 55);
    assert(dynamic_cast<JugadorIA *>(copia->obtenerJugadorIA())->getEstrategia()->nombre() == "Super");
    assert(copia->obtenerJugadorHumano()->getNombre() == "Ana");
    for (int jugador = 0; jugador < 2; jugador++)
    {
        std::vector<Carta> &a = (jugador ? original.obtenerJugadorIA() : original.obtenerJugadorHumano())->getCartas();
        std::vector<Carta> &b = (jugador ? copia->obtenerJugadorIA() : copia->obtenerJugadorHumano())->getCartas();
        assert(a.size() == b.size());
        for (size_t i = 0; i < a.size(); i++)
        {
            assert(a[i].getTipo() == b[i].getTipo() && a[i].getEnergia() == b[i].getEnergia());
        }
    }

    // Archivo corrupto / inexistente -> excepcion.
    std::ofstream("test_partidas/roto.txt") << "turno=1\ncartasHumano=Agua:100\n";
    for (const char *nombre : {"roto", "fantasma"})
    {
        bool lanzo = false;

        try
        {
            repo.cargar(nombre);
        }
        catch (const std::runtime_error &)
        {
            lanzo = true;
        }

        assert(lanzo);
    }

    std::filesystem::remove_all("test_partidas");

    // La IA vuelve a elegir carta en cada ronda (sin danio no muere ninguna).
    ConfiguracionDanio *sinDanio = new ConfiguracionDanio();

    for (int atacante = 0; atacante < ConfiguracionDanio::CANTIDAD_TIPOS; atacante++)
    {
        for (int defensor = 0; defensor < ConfiguracionDanio::CANTIDAD_TIPOS; defensor++)
        {
            sinDanio->configurarDanio(atacante, defensor, 0);
        }
    }

    JugadorHumano *humano2 = new JugadorHumano("Ana");
    JugadorIA *ia2 = new JugadorIA("PC", FabricaIA::crear("Aleatoria", *sinDanio));
    Partida sinMuertes(humano2, ia2, MotorCombate(*sinDanio));
    sinMuertes.iniciarPartida(5);
    sinMuertes.seleccionarCartaHumano(&humano2->getCartas()[0]);

    int primera = -1;
    bool cambio = false;

    for (int ronda = 0; ronda < 30; ronda++)
    {
        sinMuertes.ejecutarRonda();

        if (primera == -1)
        {
            primera = sinMuertes.indiceCartaActivaIA();
        }
        else if (sinMuertes.indiceCartaActivaIA() != primera)
        {
            cambio = true;
        }
    }

    assert(cambio);

    std::cout << "test_archivos OK\n";
    return 0;
}
