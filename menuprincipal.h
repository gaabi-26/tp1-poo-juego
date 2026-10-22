#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QWidget>

class MainWindow;
class Partida;

namespace Ui {
class MenuPrincipal;
}

class MenuPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = nullptr);
    ~MenuPrincipal();

private slots:
    void on_btnIniciar_clicked();

    void on_btnCargar_clicked();

private:
    void abrirJuego(Partida *partida);

    Ui::MenuPrincipal *ui;

    int cantidadCartas = 5;

    MainWindow *ventanaJuego = nullptr;
};

#endif