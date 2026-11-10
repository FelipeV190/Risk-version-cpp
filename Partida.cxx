#include "Partida.h"
#include <sstream>

Partida::Partida()
{
    inicializada = false;
    terminada = false;
    colorGanador = "";
    grupoCartasIntercambiados = 0;
}

bool Partida::EstaInicializada() const { return( inicializada ); }
bool Partida::EstaTerminada() const { return( terminada ); }

ListaJugadores& Partida::ObtenerJugadores() { return( jugadores ); }
const ListaJugadores& Partida::ObtenerJugadores() const { return( jugadores ); }
Tablero& Partida::ObtenerTablero() { return( tablero ); }
const Tablero& Partida::ObtenerTablero() const { return( tablero ); }

void Partida::Inicializar( const ListaJugadores& listaJugadoresLeida, const Tablero& tableroLeido )
{
    jugadores = listaJugadoresLeida;
    tablero = tableroLeido;
    inicializada = true;
}

void Partida::FinalizarPartida( const string& colorJugadorGanador )
{
    terminada = true;
    colorGanador = colorJugadorGanador;
}

string Partida::ObtenerColorGanador() const { return( colorGanador ); }

int Partida::CalcularBonoPorIntercambio()
{
    static const int bonos_iniciales[ 6 ] = { 4, 6, 8, 10, 12, 15 };
    int bono;
    if( grupoCartasIntercambiados < 6 )
        bono = bonos_iniciales[ grupoCartasIntercambiados ];
    else
        bono = 15 + 5 * ( grupoCartasIntercambiados - 5 );
    ++grupoCartasIntercambiados;
    return( bono );
}

// Formato: N, luego "nombre color" de cada jugador en el orden de la cola
// (el de turno vigente primero) y luego "codigo color unidades" de los 42
// territorios en el orden del tablero. Cada linea termina en '\n'.
string Partida::SerializarTexto() const
{
    ostringstream salida;
    salida << jugadores.ObtenerCantidad() << '\n';
    for( int i = 0; i < jugadores.ObtenerCantidad(); ++i )
    {
        const Jugador& j = jugadores.ObtenerJugadorEnPosicion( i );
        salida << j.ObtenerNombre() << ' ' << j.ObtenerColor() << '\n';
    }
    for( int i = 0; i < tablero.ObtenerCantidadTerritorios(); ++i )
    {
        const Territorio& t = tablero.ObtenerTerritorioEnPosicion( i );
        salida << t.ObtenerCodigo() << ' ' << t.ObtenerColorJugador() << ' '
               << t.ObtenerNumUnidades() << '\n';
    }
    return( salida.str() );
}
