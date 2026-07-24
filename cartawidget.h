#ifndef CARTAWIDGET_H
#define CARTAWIDGET_H

#include <QWidget>

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

    void setCarta(const Carta& carta);

private:
    Ui::CartaWidget *ui;
};

#endif // CARTAWIDGET_H