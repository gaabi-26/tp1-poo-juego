#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "cartawidget.h"
#include "carta.h"

MainWindow::MainWindow(Partida *partida, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    partida(partida)
{
    ui->setupUi(this);

    std::vector<Carta> cartas;

    cartas.emplace_back(TipoElemento::Agua);
    cartas.emplace_back(TipoElemento::Fuego);
    cartas.emplace_back(TipoElemento::Tierra);
    cartas.emplace_back(TipoElemento::Agua);
    cartas.emplace_back(TipoElemento::Fuego);

    for(const Carta& carta : cartas)
    {
        CartaWidget *widget = new CartaWidget(this);

        widget->setCarta(carta);

        ui->horizontalLayout_2->addWidget(widget);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}