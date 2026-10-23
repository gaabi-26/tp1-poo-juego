#include "partidadaofiletxt.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <QDir>
#include <QStringList>
#include "fabricaia.h"
#include "jugadorhumano.h"
#include "jugadoria.h"

PartidaDaoFileTxt::PartidaDaoFileTxt(const std::string &carpeta)
{
    this->carpeta = carpeta;
}

bool PartidaDaoFileTxt::guardar(Partida &partida, const std::string &nombre)
{
    if (!this->nombreValido(nombre)) {
        return false;
    }

    // Si la carpeta no existe se crea
    QDir().mkpath(QString::fromStdString(this->carpeta));

    std::ofstream archivo(this->carpeta + "/" + nombre + ".txt");
    if (!archivo.is_open()) {
        return false;
    }

    ConfiguracionJuego configuracion;
    configuracion.setCantidadCartas(partida.obtenerJugadorHumano()->getCartas().size());
    configuracion.getDanio() = partida.obtenerMotor().obtenerConfiguracion();

    JugadorIA *ia = dynamic_cast<JugadorIA *>(partida.obtenerJugadorIA());
    if (ia != nullptr) {
        configuracion.setIA(ia->getEstrategia()->nombre());
    }

    this->configuracionDao.escribir(configuracion, archivo);

    archivo << "jugador=" << partida.obtenerJugadorHumano()->getNombre() << "\n"
            << "oponente=" << partida.obtenerJugadorIA()->getNombre() << "\n"
            << "turno=" << partida.obtenerTurno() << "\n"
            << "activaHumano=" << partida.indiceCartaActivaHumano() << "\n"
            << "activaIA=" << partida.indiceCartaActivaIA() << "\n"
            << "cartasHumano=" << this->cartasATexto(partida.obtenerJugadorHumano()->getCartas()) << "\n"
            << "cartasIA=" << this->cartasATexto(partida.obtenerJugadorIA()->getCartas()) << "\n";

    bool ok = archivo.good();
    archivo.close();
    return ok;
}

Partida *PartidaDaoFileTxt::cargar(const std::string &nombre)
{
    if (!this->nombreValido(nombre)) {
        throw std::runtime_error("Nombre de partida invalido: " + nombre);
    }

    std::ifstream archivo(this->carpeta + "/" + nombre + ".txt");
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir la partida: " + nombre);
    }

    std::map<std::string, std::string> claves = this->configuracionDao.leerClaves(archivo);
    archivo.close();
    ConfiguracionJuego configuracion = this->configuracionDao.desdeClaves(claves);

    std::vector<Carta> cartasHumano;
    std::vector<Carta> cartasIA;
    int turno;
    int activaHumano;
    int activaIA;

    // Si falta una clave o esta mal formada la partida no se puede usar
    try {
        cartasHumano = this->cartasDesdeTexto(claves.at("cartasHumano"));
        cartasIA = this->cartasDesdeTexto(claves.at("cartasIA"));
        turno = std::stoi(claves.at("turno"));
        activaHumano = std::stoi(claves.at("activaHumano"));
        activaIA = std::stoi(claves.at("activaIA"));
    }
    catch (const std::exception &e) {
        throw std::runtime_error("La partida '" + nombre + "' esta corrupta o incompleta");
    }

    // Las IA guardan una referencia a la tabla de danio: queda en el heap junto con la partida.
    ConfiguracionDanio *danio = new ConfiguracionDanio(configuracion.getDanio());

    JugadorHumano *humano = new JugadorHumano(claves["jugador"]);
    JugadorIA *ia = new JugadorIA(claves["oponente"], FabricaIA::crear(configuracion.getIA(), *danio));

    humano->setCartas(cartasHumano);
    ia->setCartas(cartasIA);

    Partida *partida = new Partida(humano, ia, MotorCombate(*danio));
    partida->restaurar(turno, activaHumano, activaIA);

    return partida;
}

std::vector<std::string> PartidaDaoFileTxt::listar()
{
    std::vector<std::string> nombres;

    QDir directorio(QString::fromStdString(this->carpeta));
    QStringList archivos = directorio.entryList(QStringList() << "*.txt", QDir::Files, QDir::Name);

    for (int i = 0; i < archivos.size(); i++) {
        // Se quita la extension ".txt"
        nombres.push_back(archivos[i].left(archivos[i].size() - 4).toStdString());
    }

    return nombres;
}

bool PartidaDaoFileTxt::nombreValido(const std::string &nombre)
{
    // Solo letras, numeros, espacio, '_' y '-': evita rutas y caracteres que no se leen bien en el archivo
    if (nombre.empty()) {
        return false;
    }

    for (int i = 0; i < nombre.size(); i++) {
        unsigned char c = nombre[i];

        if (!isalnum(c) && c != ' ' && c != '_' && c != '-') {
            return false;
        }
    }

    return true;
}

std::string PartidaDaoFileTxt::cartasATexto(const std::vector<Carta> &cartas)
{
    std::string texto;

    for (int i = 0; i < cartas.size(); i++) {
        if (i > 0) {
            texto += ",";
        }

        texto += this->configuracionDao.nombreTipo(cartas[i].getTipo()) + ":" + std::to_string(cartas[i].getEnergia());
    }

    return texto;
}

std::vector<Carta> PartidaDaoFileTxt::cartasDesdeTexto(const std::string &texto)
{
    std::vector<Carta> cartas;
    std::stringstream ss(texto);
    std::string parte;

    // Leemos las cartas separadas por ','
    while (std::getline(ss, parte, ',')) {
        size_t separador = parte.find(':');

        if (separador == std::string::npos) {
            throw std::invalid_argument("carta sin energia: " + parte);
        }

        int energia = std::stoi(parte.substr(separador + 1));

        if (energia < 0 || energia > 100) {
            throw std::invalid_argument("energia fuera de rango: " + parte);
        }

        cartas.push_back(Carta(this->configuracionDao.tipoDesdeNombre(parte.substr(0, separador)), energia));
    }

    if (cartas.empty()) {
        throw std::invalid_argument("jugador sin cartas");
    }

    return cartas;
}
