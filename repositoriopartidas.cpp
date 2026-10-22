#include "repositoriopartidas.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "fabricaia.h"
#include "jugadorhumano.h"
#include "jugadoria.h"
#include "repositorioconfiguracion.h"

namespace fs = std::filesystem;

RepositorioPartidas::RepositorioPartidas(const std::string &carpeta)
{
    m_carpeta = carpeta;
}

bool RepositorioPartidas::guardar(Partida &partida, const std::string &nombre) const
{
    if (!nombreValido(nombre))
    {
        return false;
    }

    std::error_code error;
    fs::create_directories(m_carpeta, error);

    std::ofstream archivo(fs::path(m_carpeta) / (nombre + ".txt"));

    if (!archivo)
    {
        return false;
    }

    ConfiguracionJuego configuracion;
    configuracion.setCantidadCartas(static_cast<int>(partida.obtenerJugadorHumano()->getCartas().size()));
    configuracion.obtenerDanio() = partida.obtenerMotor().obtenerConfiguracion();

    JugadorIA *ia = dynamic_cast<JugadorIA *>(partida.obtenerJugadorIA());

    if (ia != nullptr)
    {
        configuracion.setIA(ia->getEstrategia()->nombre());
    }

    RepositorioConfiguracion::escribir(configuracion, archivo);

    archivo << "jugador=" << partida.obtenerJugadorHumano()->getNombre() << "\n"
            << "oponente=" << partida.obtenerJugadorIA()->getNombre() << "\n"
            << "turno=" << partida.obtenerTurno() << "\n"
            << "activaHumano=" << partida.indiceCartaActivaHumano() << "\n"
            << "activaIA=" << partida.indiceCartaActivaIA() << "\n"
            << "cartasHumano=" << cartasATexto(partida.obtenerJugadorHumano()->getCartas()) << "\n"
            << "cartasIA=" << cartasATexto(partida.obtenerJugadorIA()->getCartas()) << "\n";

    return archivo.good();
}

Partida *RepositorioPartidas::cargar(const std::string &nombre) const
{
    if (!nombreValido(nombre))
    {
        throw std::runtime_error("Nombre de partida invalido: " + nombre);
    }

    std::ifstream archivo(fs::path(m_carpeta) / (nombre + ".txt"));

    if (!archivo)
    {
        throw std::runtime_error("No se pudo abrir la partida: " + nombre);
    }

    std::map<std::string, std::string> claves = RepositorioConfiguracion::leerClaves(archivo);
    ConfiguracionJuego configuracion = RepositorioConfiguracion::desdeClaves(claves);

    std::vector<Carta> cartasHumano;
    std::vector<Carta> cartasIA;
    int turno;
    int activaHumano;
    int activaIA;

    // Cualquier clave faltante o mal formada vuelve la partida inutilizable.
    try
    {
        cartasHumano = cartasDesdeTexto(claves.at("cartasHumano"));
        cartasIA = cartasDesdeTexto(claves.at("cartasIA"));
        turno = std::stoi(claves.at("turno"));
        activaHumano = std::stoi(claves.at("activaHumano"));
        activaIA = std::stoi(claves.at("activaIA"));
    }
    catch (const std::exception &)
    {
        throw std::runtime_error("La partida '" + nombre + "' esta corrupta o incompleta");
    }

    // Las IA guardan una referencia a la tabla de danio: queda en el heap junto con la partida.
    ConfiguracionDanio *danio = new ConfiguracionDanio(configuracion.obtenerDanio());

    JugadorHumano *humano = new JugadorHumano(claves["jugador"]);
    JugadorIA *ia = new JugadorIA(claves["oponente"], FabricaIA::crear(configuracion.obtenerIA(), *danio));

    humano->setCartas(cartasHumano);
    ia->setCartas(cartasIA);

    Partida *partida = new Partida(humano, ia, MotorCombate(*danio));
    partida->restaurar(turno, activaHumano, activaIA);

    return partida;
}

std::vector<std::string> RepositorioPartidas::listar() const
{
    std::vector<std::string> nombres;
    std::error_code error;

    for (fs::directory_iterator it(m_carpeta, error), fin; !error && it != fin; it.increment(error))
    {
        if (it->path().extension() == ".txt")
        {
            nombres.push_back(it->path().stem().string());
        }
    }

    std::sort(nombres.begin(), nombres.end());

    return nombres;
}

bool RepositorioPartidas::nombreValido(const std::string &nombre)
{
    // Sin separadores de ruta para que no pueda salir de la carpeta.
    return !nombre.empty() && nombre.find_first_of("/\\:") == std::string::npos;
}

std::string RepositorioPartidas::cartasATexto(const std::vector<Carta> &cartas)
{
    std::string texto;

    for (const Carta &carta : cartas)
    {
        if (!texto.empty())
        {
            texto += ",";
        }

        texto += RepositorioConfiguracion::nombreTipo(carta.getTipo()) + ":" + std::to_string(carta.getEnergia());
    }

    return texto;
}

std::vector<Carta> RepositorioPartidas::cartasDesdeTexto(const std::string &texto)
{
    std::vector<Carta> cartas;
    std::stringstream partes(texto);
    std::string parte;

    while (std::getline(partes, parte, ','))
    {
        size_t separador = parte.find(':');

        if (separador == std::string::npos)
        {
            throw std::invalid_argument("carta sin energia: " + parte);
        }

        int energia = std::stoi(parte.substr(separador + 1));

        if (energia < 0 || energia > 100)
        {
            throw std::invalid_argument("energia fuera de rango: " + parte);
        }

        cartas.push_back(Carta(RepositorioConfiguracion::tipoDesdeNombre(parte.substr(0, separador)), energia));
    }

    if (cartas.empty())
    {
        throw std::invalid_argument("jugador sin cartas");
    }

    return cartas;
}
