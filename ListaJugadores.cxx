#include "ListaJugadores.h"
#include <cstddef>

ListaJugadores::ListaJugadores() {}

void ListaJugadores::AgregarJugador( const Jugador& jugador )
{
    jugadores.push_back( jugador );
}

int ListaJugadores::ObtenerCantidad() const
{
    return( static_cast<int>( jugadores.size() ) );
}

Jugador& ListaJugadores::ObtenerJugadorActual()
{
    return( jugadores.front() );
}

const Jugador& ListaJugadores::ObtenerJugadorActual() const
{
    return( jugadores.front() );
}

Jugador* ListaJugadores::BuscarJugador( const string& nombre )
{
    for( unsigned int i = 0; i < jugadores.size(); ++i )
        if( jugadores[ i ].ObtenerNombre() == nombre )
            return( &jugadores[ i ] );
    return( NULL );
}

Jugador* ListaJugadores::BuscarJugadorPorColor( const string& color )
{
    for( unsigned int i = 0; i < jugadores.size(); ++i )
        if( jugadores[ i ].ObtenerColor() == color )
            return( &jugadores[ i ] );
    return( NULL );
}

void ListaJugadores::EliminarJugador( const string& nombre )
{
    for( deque<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); ++it )
    {
        if( it->ObtenerNombre() == nombre )
        {
            jugadores.erase( it );
            return;
        }
    }
}

bool ListaJugadores::EsTurnoDe( const string& nombre ) const
{
    if( jugadores.empty() )
        return( false );
    return( jugadores.front().ObtenerNombre() == nombre );
}

void ListaJugadores::AvanzarTurno()
{
    if( jugadores.empty() )
        return;
    Jugador jugadorActual = jugadores.front();
    jugadores.pop_front();
    jugadorActual.FijarFase( FASE_INICIO );
    jugadores.push_back( jugadorActual );
}

const Jugador& ListaJugadores::ObtenerJugadorEnPosicion( int indice ) const
{
    return( jugadores[ indice ] );
}