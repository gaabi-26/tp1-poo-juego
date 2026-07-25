#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "cartawidget.h"
#include "carta.h"
#include <QDebug>

MainWindow::MainWindow(Partida *partida, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    partida(partida)
{
    ui->setupUi(this);

    cartas.emplace_back(TipoElemento::Agua);
    cartas.emplace_back(TipoElemento::Fuego);
    cartas.emplace_back(TipoElemento::Tierra);
    cartas.emplace_back(TipoElemento::Agua);
    cartas.emplace_back(TipoElemento::Fuego);

    for(Carta &carta : cartas)
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::seleccionarCarta(CartaWidget* widget)
{
    if(cartaSeleccionada != nullptr)
        cartaSeleccionada->setSeleccionada(false);

    cartaSeleccionada = widget;

    cartaSeleccionada->setSeleccionada(true);

    Carta* carta = widget->getCarta();

    QString tipo;

    switch(carta->getTipo())
    {
    case TipoElemento::Agua: tipo = "Agua"; break;
    case TipoElemento::Fuego: tipo = "Fuego"; break;
    case TipoElemento::Tierra: tipo = "Tierra"; break;
    }

    qDebug()
        << "Carta seleccionada"
        << "| Tipo:" << tipo
        << "| Energia:" << carta->getEnergia();
}