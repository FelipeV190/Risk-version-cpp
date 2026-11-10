#include "Jugador.h"
#include <algorithm>

Jugador::Jugador()
{
  nombre = "";
  color = "";
  fase = FASE_INICIO;
}

Jugador::Jugador( const string& nombreInicial, const string& colorInicial )
{
  nombre = nombreInicial;
  color = colorInicial;
  fase = FASE_INICIO;
}

string Jugador::ObtenerNombre() const { return( nombre ); }
string Jugador::ObtenerColor() const { return( color ); }
int Jugador::ObtenerFase() const { return( fase ); }
void Jugador::FijarFase( int nuevaFase ) { fase = nuevaFase; }

void Jugador::AgregarCarta( const Carta& carta )
{
  cartas.push_back( carta );
}

void Jugador::QuitarCartas( const vector<int>& indices )
{
  vector<int> ordenados = indices;
  sort( ordenados.begin(), ordenados.end() );
  for( int i = static_cast<int>( ordenados.size() ) - 1; i >= 0; --i )
  {
    int pos = ordenados[ i ];
    if( pos >= 0 && pos < static_cast<int>( cartas.size() ) )
      cartas.erase( cartas.begin() + pos );
  }
}

int Jugador::ObtenerNumCartas() const
{
  return( static_cast<int>( cartas.size() ) );
}

const Carta& Jugador::ObtenerCarta( int indice ) const
{
  return( cartas[ indice ] );
}

static bool combinacion_valida( const string& s1, const string& s2, const string& s3 )
{
  if( s1 == SIMBOLO_COMODIN || s2 == SIMBOLO_COMODIN || s3 == SIMBOLO_COMODIN )
    return( true );
  if( s1 == s2 && s2 == s3 )
    return( true );
  if( s1 != s2 && s2 != s3 && s1 != s3 )
    return( true );
  return( false );
}

bool Jugador::TieneCombinacionValida() const
{
  int n = static_cast<int>( cartas.size() );
  for( int i = 0; i < n; ++i )
    for( int j = i + 1; j < n; ++j )
      for( int k = j + 1; k < n; ++k )
      {
        if( combinacion_valida( cartas[ i ].ObtenerSimbolo(),
                                 cartas[ j ].ObtenerSimbolo(),
                                 cartas[ k ].ObtenerSimbolo() ) )
          return( true );
      }
  return( false );
}