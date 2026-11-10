#include "Territorio.h"

Territorio::Territorio()
{
    codigo = "";
    continente = "";
    colorJugador = "";
    numUnidades = 0;
}

Territorio::Territorio( const string& codigoInicial, const string& continenteInicial,
                         const vector<string>& vecinosIniciales )
{
    codigo = codigoInicial;
    continente = continenteInicial;
    vecinos = vecinosIniciales;
    colorJugador = "";
    numUnidades = 0;
}

string Territorio::ObtenerCodigo() const { return( codigo ); }
string Territorio::ObtenerContinente() const { return( continente ); }
string Territorio::ObtenerColorJugador() const { return( colorJugador ); }
int Territorio::ObtenerNumUnidades() const { return( numUnidades ); }
const vector<string>& Territorio::ObtenerVecinos() const { return( vecinos ); }

void Territorio::FijarColorJugador( const string& nuevoColor ) { colorJugador = nuevoColor; }
void Territorio::FijarNumUnidades( int nuevoNum ) { numUnidades = nuevoNum; }
void Territorio::AgregarUnidades( int cantidad ) { numUnidades += cantidad; }

void Territorio::QuitarUnidades( int cantidad )
{
    numUnidades -= cantidad;
    if( numUnidades < 0 )
        numUnidades = 0;
}

bool Territorio::EsVecinoDe( const string& codigoOtroTerritorio ) const
{
    for( unsigned int i = 0; i < vecinos.size(); ++i )
        if( vecinos[ i ] == codigoOtroTerritorio )
            return( true );
    return( false );
}