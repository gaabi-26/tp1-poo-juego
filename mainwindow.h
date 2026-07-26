#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"carta.h"
#include"cartawidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Partida;
class MenuPrincipal;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Partida* partida, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Declaración exacta que muestra la imagen
    void seleccionarCarta(CartaWidget* widget);

    void on_btnRonda_clicked();

    void on_btnVolverMenu_clicked();

private:
    Ui::MainWindow *ui;
    Partida* partida;
    std::vector<Carta> cartas;
    std::vector<CartaWidget*> widgetsCartas;
    std::vector<CartaWidget*> widgetsCartasIA;
    CartaWidget* cartaSeleccionada = nullptr;
    MenuPrincipal *menu = nullptr;
};
#endif // MAINWINDOW_H
