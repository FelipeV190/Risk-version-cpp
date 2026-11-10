#ifndef LISTA_JUGADORES_H
#define LISTA_JUGADORES_H

#include <deque>
#include <string>
#include "Jugador.h"

using namespace std;

class ListaJugadores
{
public:
    ListaJugadores();

    void AgregarJugador( const Jugador& jugador );

    int ObtenerCantidad() const;
    Jugador& ObtenerJugadorActual();
    const Jugador& ObtenerJugadorActual() const;

    Jugador* BuscarJugador( const string& nombre );

    Jugador* BuscarJugadorPorColor( const string& color );
    void EliminarJugador( const string& nombre );

    bool EsTurnoDe( const string& nombre ) const;
    void AvanzarTurno();

    const Jugador& ObtenerJugadorEnPosicion( int indice ) const;

private:
    deque<Jugador> jugadores;
};

#endif