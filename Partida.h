
#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include "ListaJugadores.h"
#include "Tablero.h"

using namespace std;

class Partida
{
public:
    Partida();

    bool EstaInicializada() const;
    bool EstaTerminada() const;

    ListaJugadores& ObtenerJugadores();
    const ListaJugadores& ObtenerJugadores() const;
    Tablero& ObtenerTablero();
    const Tablero& ObtenerTablero() const;

    void Inicializar( const ListaJugadores& listaJugadoresLeida, const Tablero& tableroLeido );

    void FinalizarPartida( const string& colorJugadorGanador );
    string ObtenerColorGanador() const;

    int CalcularBonoPorIntercambio();

    string SerializarTexto() const;

private:
    ListaJugadores jugadores;
    Tablero tablero;
    bool inicializada;
    bool terminada;
    string colorGanador;
    int grupoCartasIntercambiados;
};

#endif