#include "menuprincipal.h"
#include "ui_menuprincipal.h"

#include "mainwindow.h"

#include "ConfiguracionDanio.h"
#include "MotorCombate.h"

#include "jugadorhumano.h"
#include "jugadoria.h"

#include "fabricaia.h"
#include "repositorioconfiguracion.h"
#include "repositoriopartidas.h"

#include <QInputDialog>
#include <QMessageBox>

#include "Partida.h"

MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);

    // Valores iniciales desde config.txt (si no existe, quedan los por defecto).
    ConfiguracionJuego config = RepositorioConfiguracion().cargar("config.txt");

    cantidadCartas = config.obtenerCantidadCartas();

    const std::vector<std::string> &nombresIA = FabricaIA::nombres();

    for (size_t i = 0; i < nombresIA.size(); i++)
    {
        if (nombresIA[i] == config.obtenerIA())
        {
            ui->cmbIA->setCurrentIndex(static_cast<int>(i));
        }
    }

    ui->spAguaAgua->setValue(config.obtenerDanio().obtenerDanio(0,0));
    ui->spAguaFuego->setValue(config.obtenerDanio().obtenerDanio(0,1));
    ui->spAguaTierra->setValue(config.obtenerDanio().obtenerDanio(0,2));

    ui->spFuegoAgua->setValue(config.obtenerDanio().obtenerDanio(1,0));
    ui->spFuegoFuego->setValue(config.obtenerDanio().obtenerDanio(1,1));
    ui->spFuegoTierra->setValue(config.obtenerDanio().obtenerDanio(1,2));

    ui->spTierraAgua->setValue(config.obtenerDanio().obtenerDanio(2,0));
    ui->spTierraFuego->setValue(config.obtenerDanio().obtenerDanio(2,1));
    ui->spTierraTierra->setValue(config.obtenerDanio().obtenerDanio(2,2));
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

void MenuPrincipal::on_btnIniciar_clicked()
{
    //----------------------------------------------------
    // CONFIGURACION DE DAÑO
    //----------------------------------------------------

    ConfiguracionDanio configuracion;

    configuracion.configurarDanio(0,0,ui->spAguaAgua->value());
    configuracion.configurarDanio(0,1,ui->spAguaFuego->value());
    configuracion.configurarDanio(0,2,ui->spAguaTierra->value());

    configuracion.configurarDanio(1,0,ui->spFuegoAgua->value());
    configuracion.configurarDanio(1,1,ui->spFuegoFuego->value());
    configuracion.configurarDanio(1,2,ui->spFuegoTierra->value());

    configuracion.configurarDanio(2,0,ui->spTierraAgua->value());
    configuracion.configurarDanio(2,1,ui->spTierraFuego->value());
    configuracion.configurarDanio(2,2,ui->spTierraTierra->value());

    //----------------------------------------------------
    // MOTOR
    //----------------------------------------------------

    MotorCombate motor(configuracion);

    //----------------------------------------------------
    // IA
    //----------------------------------------------------

    // La IA guarda una referencia a la tabla de danio, por eso va en el heap.
    ConfiguracionDanio *danioIA = new ConfiguracionDanio(configuracion);

    EstrategiaIA *estrategia = FabricaIA::crear(
        FabricaIA::nombres()[ui->cmbIA->currentIndex()], *danioIA);

    //----------------------------------------------------
    // JUGADORES
    //----------------------------------------------------

    JugadorHumano *humano =
        new JugadorHumano("Jugador");

    JugadorIA *ia =
        new JugadorIA("Computadora",
                      estrategia);

    //----------------------------------------------------
    // PARTIDA
    //----------------------------------------------------

    Partida *partida =
        new Partida(humano,
                    ia,
                    motor);

    partida->iniciarPartida(cantidadCartas);

    abrirJuego(partida);
}

void MenuPrincipal::on_btnCargar_clicked()
{
    RepositorioPartidas repositorio;

    QStringList nombres;
    for (const std::string &nombre : repositorio.listar())
    {
        nombres << QString::fromStdString(nombre);
    }

    if (nombres.isEmpty())
    {
        QMessageBox::information(this, "Cargar partida", "No hay partidas guardadas.");
        return;
    }

    bool aceptado = false;
    QString elegida = QInputDialog::getItem(this, "Cargar partida", "Partida:", nombres, 0, false, &aceptado);

    if (!aceptado)
    {
        return;
    }

    try
    {
        abrirJuego(repositorio.cargar(elegida.toStdString()));
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Error al cargar", e.what());
    }
}

void MenuPrincipal::abrirJuego(Partida *partida)
{
    ventanaJuego = new MainWindow(partida);

    ventanaJuego->show();

    this->hide();
}