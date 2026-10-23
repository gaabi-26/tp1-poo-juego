// Auto-chequeo de la persistencia y de las IA. Se compila con cmake -DBUILD_TESTS=ON (target "test_archivos").
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QDir>
#include "claseiaavanzada.h"
#include "claseiaintermedia.h"
#include "configuraciondaofiletxt.h"
#include "fabricaia.h"
#include "jugadorhumano.h"
#include "jugadoria.h"
#include "partidadaofiletxt.h"

using namespace std;

int main()
{
    // Archivo inexistente -> valores por defecto.
    ConfiguracionDaoFileTxt configuracionDao("no_existe.txt");
    ConfiguracionJuego porDefecto = configuracionDao.leer();
    assert(porDefecto.getCantidadCartas() == 5 && porDefecto.getIA() == "Aleatoria");

    // Las lineas invalidas se ignoran y las validas se aplican.
    istringstream texto("# c\ncantidadCartas=abc\nia=Super\nbasura\ndanio.Agua.Fuego=77\ndanio.Agua.Tierra=x\nia2=Super\n");
    ConfiguracionJuego leida = configuracionDao.desdeClaves(configuracionDao.leerClaves(texto));
    assert(leida.getCantidadCartas() == 5 && leida.getIA() == "Super");
    assert(leida.getDanio().obtenerDanio(0, 1) == 77);
    assert(leida.getDanio().obtenerDanio(0, 2) == porDefecto.getDanio().obtenerDanio(0, 2));

    // Ida y vuelta: guardar -> listar -> cargar.
    QDir("test_partidas").removeRecursively();
    PartidaDao *dao = new PartidaDaoFileTxt("test_partidas");

    ConfiguracionDanio *danio = new ConfiguracionDanio();
    danio->configurarDanio(0, 1, 55);
    JugadorHumano *humano = new JugadorHumano("Ana");
    JugadorIA *ia = new JugadorIA("PC", FabricaIA::crear("Super", *danio));
    Partida original(humano, ia, MotorCombate(*danio));
    original.iniciarPartida(4);
    original.seleccionarCartaHumano(&humano->getCartas()[2]);
    original.ejecutarRonda();

    assert(dao->guardar(original, "uno"));
    assert(!dao->guardar(original, "../malo"));
    assert(dao->listar().size() == 1 && dao->listar()[0] == "uno");

    Partida *copia = dao->cargar("uno");
    assert(copia->obtenerTurno() == original.obtenerTurno());
    assert(copia->indiceCartaActivaHumano() == 2);
    assert(copia->indiceCartaActivaIA() == original.indiceCartaActivaIA());
    assert(copia->obtenerMotor().obtenerConfiguracion().obtenerDanio(0, 1) == 55);
    assert(dynamic_cast<JugadorIA *>(copia->obtenerJugadorIA())->getEstrategia()->nombre() == "Super");
    assert(copia->obtenerJugadorHumano()->getNombre() == "Ana");

    for (int i = 0; i < original.obtenerJugadorHumano()->getCartas().size(); i++)
    {
        Carta a = original.obtenerJugadorHumano()->getCartas()[i];
        Carta b = copia->obtenerJugadorHumano()->getCartas()[i];
        assert(a.getTipo() == b.getTipo() && a.getEnergia() == b.getEnergia());

        a = original.obtenerJugadorIA()->getCartas()[i];
        b = copia->obtenerJugadorIA()->getCartas()[i];
        assert(a.getTipo() == b.getTipo() && a.getEnergia() == b.getEnergia());
    }

    // Archivo corrupto o inexistente -> excepcion.
    ofstream roto("test_partidas/roto.txt");
    roto << "turno=1\ncartasHumano=Agua:100\n";
    roto.close();

    string nombres[2] = {"roto", "fantasma"};
    for (int i = 0; i < 2; i++)
    {
        bool lanzo = false;

        try
        {
            dao->cargar(nombres[i]);
        }
        catch (const runtime_error &e)
        {
            lanzo = true;
        }

        assert(lanzo);
    }

    delete dao;
    QDir("test_partidas").removeRecursively();

    // Las estrategias deciden segun la vida de sus cartas (tabla de danio por defecto).
    ConfiguracionDanio tabla;
    ClaseIAIntermedia estrategica(tabla);
    ClaseIAAvanzada experta(tabla);
    vector<Carta> mano;

    // Estrategica: ante el mismo danio usa la carta con mas vida.
    mano.push_back(Carta(TipoElemento::Agua, 40));
    mano.push_back(Carta(TipoElemento::Agua, 100));
    mano.push_back(Carta(TipoElemento::Tierra, 100));
    Carta elegida = estrategica.elegirCarta(mano, Carta(TipoElemento::Fuego));
    assert(elegida.getTipo() == TipoElemento::Agua && elegida.getEnergia() == 100);

    // Experta: elimina a la carta del humano sin morir.
    mano.clear();
    mano.push_back(Carta(TipoElemento::Tierra, 100));
    mano.push_back(Carta(TipoElemento::Agua, 100));
    elegida = experta.elegirCarta(mano, Carta(TipoElemento::Fuego, 30));
    assert(elegida.getTipo() == TipoElemento::Agua);

    // Experta: no manda al frente la carta que moriria.
    mano.clear();
    mano.push_back(Carta(TipoElemento::Agua, 10));
    mano.push_back(Carta(TipoElemento::Fuego, 100));
    elegida = experta.elegirCarta(mano, Carta(TipoElemento::Tierra));
    assert(elegida.getTipo() == TipoElemento::Fuego);

    // Experta: sin poder eliminar usa la mas sana.
    mano.clear();
    mano.push_back(Carta(TipoElemento::Agua, 40));
    mano.push_back(Carta(TipoElemento::Agua, 100));
    elegida = experta.elegirCarta(mano, Carta(TipoElemento::Fuego));
    assert(elegida.getEnergia() == 100);

    // Experta: si elimina gasta la mas debil.
    mano.clear();
    mano.push_back(Carta(TipoElemento::Agua, 100));
    mano.push_back(Carta(TipoElemento::Agua, 60));
    elegida = experta.elegirCarta(mano, Carta(TipoElemento::Fuego, 30));
    assert(elegida.getEnergia() == 60);

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

    cout << "test_archivos OK" << endl;
    return 0;
}
