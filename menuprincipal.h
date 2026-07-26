#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QWidget>

class MainWindow;

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

private:
    Ui::MenuPrincipal *ui;

    MainWindow *ventanaJuego = nullptr;
};

#endif