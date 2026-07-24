#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Partida;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Partida* partida, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Partida* partida;
};
#endif // MAINWINDOW_H
