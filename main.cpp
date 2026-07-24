#include "mainwindow.h"

#include <QApplication>

#include "ConfiguracionDanio.h"
#include "MotorCombate.h"
#include "jugadorhumano.h"
#include "jugadoria.h"
#include "claseiaintermedia.h"
#include "Partida.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w(nullptr);
    w.show();

    return a.exec();
}