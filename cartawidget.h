#ifndef CARTAWIDGET_H
#define CARTAWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "carta.h"

namespace Ui {
class CartaWidget;
}

class CartaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CartaWidget(QWidget *parent =nullptr);
    ~CartaWidget();

    void setCarta(Carta* carta);

    void actualizar();

    Carta* getCarta() const;

    void setSeleccionada(bool seleccionada);

signals:
    // Señal para emitir la carta cuando se haga clic
    void cartaSeleccionada(CartaWidget* widget);

protected:
    // Función para detectar el clic del mouse
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::CartaWidget *ui;
    Carta* carta;
    bool seleccionada = false;
};

#endif // CARTAWIDGET_H