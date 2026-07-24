/*
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
*/

#include <iostream>

#include "ConfiguracionDanio.h"
#include "MotorCombate.h"
#include "jugadorhumano.h"
#include "jugadoria.h"
#include "claseiaintermedia.h"
#include "Partida.h"

using namespace std;

int main()
{
    ConfiguracionDanio configuracion;
    MotorCombate motor(configuracion);

    ClaseIAIntermedia estrategiaIA(configuracion);

    JugadorHumano jugadorHumano("Jugador");
    JugadorIA jugadorIA("CPU", &estrategiaIA);

    Partida partida(&jugadorHumano, &jugadorIA, motor);

    partida.iniciarPartida(5);

    if (partida.hayGanador())
    {
        cout << "\nGano: "
             << partida.obtenerGanador()->getNombre()
             << endl;
    }

    return 0;
}