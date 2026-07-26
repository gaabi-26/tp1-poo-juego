#include "menuprincipal.h"
#include "ui_menuprincipal.h"

#include "mainwindow.h"

#include "ConfiguracionDanio.h"
#include "MotorCombate.h"

#include "jugadorhumano.h"
#include "jugadoria.h"

#include "claseiabasica.h"

#include "Partida.h"

MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);
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

    EstrategiaIA *estrategia = new claseIAbasica();

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

    partida->iniciarPartida();

    //----------------------------------------------------
    // ABRIR EL JUEGO
    //----------------------------------------------------

    ventanaJuego = new MainWindow(partida);

    ventanaJuego->show();

    this->hide();
}