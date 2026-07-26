#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menuprincipal.h"
#include "cartawidget.h"
#include "carta.h"
#include "Partida.h"
#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>

MainWindow::MainWindow(Partida *partida, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    partida(partida)
{
    ui->setupUi(this);

    ///esto se agrega por un incoveniente con qtdesigner
    // Creamos un layout horizontal dentro del widget reservado
    // para mostrar las cartas de la IA.
    QHBoxLayout *layoutCartasIA =
        new QHBoxLayout(ui->widgetCartasIA);

    // Quitamos los márgenes internos del layout para aprovechar
    // mejor el espacio disponible dentro del widget.
    layoutCartasIA->setContentsMargins(0, 0, 0, 0);

    // Dejamos una separación de 10 píxeles entre las cartas.
    layoutCartasIA->setSpacing(10);

    // Antes: se creaban 5 cartas hardcodeadas que no eran las de la partida.
    // Ahora: se usan las cartas reales del jugador humano, para que el
    // daño aplicado por MotorCombate se refleje en pantalla.
    for (Carta &carta : partida->obtenerJugadorHumano()->getCartas())
    {
        CartaWidget *widget = new CartaWidget(this);
        widget->setCarta(&carta);
        widgetsCartas.push_back(widget);

        connect(widget,
                &CartaWidget::cartaSeleccionada,
                this,
                &MainWindow::seleccionarCarta);

        ui->horizontalLayout_2->addWidget(widget);
    }

    for (Carta &carta : partida->obtenerJugadorIA()->getCartas())
    {
        CartaWidget *widget = new CartaWidget(this);

        widget->setCarta(&carta);

        widgetsCartasIA.push_back(widget);

       layoutCartasIA->addWidget(widget);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::seleccionarCarta(CartaWidget* widget)
{
    Carta* carta = widget->getCarta();

    if (!carta->estaViva())
    {
        qDebug() << "No se puede seleccionar una carta muerta";
        return;
    }

    if (cartaSeleccionada != nullptr)
        cartaSeleccionada->setSeleccionada(false);

    cartaSeleccionada = widget;
    cartaSeleccionada->setSeleccionada(true);

    // Esto reemplaza al setCartaActiva llamado "desde ningun lado" que tenias antes.
    partida->seleccionarCartaHumano(carta);

    qDebug() << "Carta seleccionada | Energia:" << carta->getEnergia();
}

void MainWindow::on_btnRonda_clicked()
{
    if (cartaSeleccionada == nullptr)
    {
        QMessageBox::warning(this, "Falta seleccion", "Elegi una carta antes de jugar la ronda.");
        return;
    }

    partida->ejecutarRonda();

    // Actualizar cartas del jugador
    for (int i = 0; i < widgetsCartas.size(); )
    {
        CartaWidget *w = widgetsCartas[i];

        w->actualizar();

        if (w->estaMuerta())
        {
            ui->horizontalLayout_2->removeWidget(w);

            widgetsCartas.erase(widgetsCartas.begin() + i);

            w->deleteLater();
        }
        else
        {
            i++;
        }
    }

    // Actualizar cartas de la IA
    for (int i = 0; i < widgetsCartasIA.size(); )
    {
        CartaWidget *w = widgetsCartasIA[i];

        w->actualizar();

        if (w->estaMuerta())
        {
            ui->widgetCartasIA->layout()->removeWidget(w);

            widgetsCartasIA.erase(widgetsCartasIA.begin() + i);

            w->deleteLater();
        }
        else
        {
            i++;
        }
    }

    if (partida->hayGanador())
    {
        Jugador* ganador = partida->obtenerGanador();
        QString nombre = ganador ? QString::fromStdString(ganador->getNombre()) : "Nadie";
        QMessageBox::information(this, "Partida finalizada", "Gano: " + nombre);
    }
}

void MainWindow::on_btnVolverMenu_clicked()
{
    menu = new MenuPrincipal();
    menu->show();
    this->close();
}