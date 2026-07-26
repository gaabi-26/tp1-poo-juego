#include "cartawidget.h"
#include "ui_cartawidget.h"

#include <QString>
#include <QMouseEvent>

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

void CartaWidget::setCarta(Carta *carta)
{
    this->carta = carta;

    actualizar();
}

void CartaWidget::actualizar()
{
    QString tipo;

    switch(carta->getTipo())
    {
    case TipoElemento::Agua:
        tipo="Agua";
        break;

    case TipoElemento::Fuego:
        tipo="Fuego";
        break;

    case TipoElemento::Tierra:
        tipo="Tierra";
        break;
    }

    ui->nombreTipo->setText(tipo);

    ui->cantidadEnergia->setText(
        "Energia: " +
        QString::number(carta->getEnergia()));
}

bool CartaWidget::estaMuerta() const
{
    return !carta->estaViva();
}

void CartaWidget::mousePressEvent(QMouseEvent *event) {
    emit cartaSeleccionada(this);

    // Llamamos a la implementación base para mantener el comportamiento estándar
    QWidget::mousePressEvent(event);
}

Carta* CartaWidget::getCarta() const
{
    return carta;
}

void CartaWidget::setSeleccionada(bool seleccionada)
{
    this->seleccionada = seleccionada;

    if(seleccionada)
    {
        ui->frame->setStyleSheet(
            "QFrame{"
            "border:4px solid green;"
            "border-radius:10px;"
            "}"
            );
    }
    else
    {
        ui->frame->setStyleSheet(
            "QFrame{"
            "border:2px solid black;"
            "border-radius:10px;"
            "}"
            "QFrame:hover{"
            "border:3px solid #2E86DE;"
            "}"
            );
    }
}