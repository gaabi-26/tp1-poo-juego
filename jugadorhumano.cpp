#include "jugadorhumano.h"
#include <iostream>
using namespace std;
JugadorHumano::JugadorHumano(std::string nombre)
    : Jugador(nombre)
{
}

Carta& JugadorHumano::seleccionarCarta(Carta *cartaOponente)
{
    (void)cartaOponente;

    cout << "\n" << Nombre << ", elegi tu proxima carta:\n";

    vector<int> indicesVivos;

    for(size_t i = 0; i < Cartas.size(); i++)
    {
        if(Cartas[i].estaViva())
        {
            indicesVivos.push_back(i);

            cout << "  [" << indicesVivos.size() - 1
                 << "] Energia: "
                 << Cartas[i].getEnergia()
                 << "\n";
        }
    }

    if(indicesVivos.empty())
    {
        return Cartas.front();
    }

    int opcion;

    while(true)
    {
        cout << "Opcion: ";

        if(!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida.\n";
            continue;
        }

        if(opcion >= 0 && opcion < (int)indicesVivos.size())
        {
            break;
        }

        cout << "Opcion invalida.\n";
    }

    return Cartas[indicesVivos[opcion]];
}