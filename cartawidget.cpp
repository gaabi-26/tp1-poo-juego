#include "cartawidget.h"
#include "ui_cartawidget.h"

#include <QString>

CartaWidget::CartaWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CartaWidget)
{
    ui->setupUi(this);
}

CartaWidget::~CartaWidget()
{
    delete ui;
}

void CartaWidget::setCarta(const Carta &carta)
{
    QString tipo;

    switch(carta.getTipo())
    {
    case TipoElemento::Agua:
        tipo = "Agua";
        break;

    case TipoElemento::Fuego:
        tipo = "Fuego";
        break;

    case TipoElemento::Tierra:
        tipo = "Tierra";
        break;
    }

    ui->nombreTipo->setText(tipo);

    ui->cantidadEnergia->setText(
        "Energia: " + QString::number(carta.getEnergia())
        );
}