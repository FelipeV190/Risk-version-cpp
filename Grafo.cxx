
#include "Grafo.h"
#include <queue>
#include <algorithm>

Grafo::Grafo()
{
}

int Grafo::CantidadVertices() const
{

  return( static_cast<int>( vertices.size() ) );
}

bool Grafo::InsertarVertice( const string& territorio )
{
  if( BuscarVertice( territorio ) != -1 )
    return( false );
  vertices.push_back( territorio );
  aristas.push_back( list< pair<int, int> >() );
  return( true );
}

bool Grafo::InsertarArista( const string& origen, const string& destino, int unidades )
{
  int io = BuscarVertice( origen );
  int id = BuscarVertice( destino );
  if( io == -1 || id == -1 )
    return( false );
  list< pair<int, int> >::const_iterator it;
  for( it = aristas[ io ].begin(); it != aristas[ io ].end(); ++it )
    if( it->first == id )
      return( false );
  aristas[ io ].push_back( make_pair( id, unidades ) );
  return( true );
}

int Grafo::BuscarVertice( const string& territorio ) const
{
  for( unsigned int i = 0; i < vertices.size(); ++i )
    if( vertices[ i ] == territorio )
      return( static_cast<int>( i ) );
  return( -1 );
}

string Grafo::ObtenerVertice( int indice ) const
{
  return( vertices[ indice ] );
}

struct ComparadorNodoDijkstra
{
  bool operator()( const NodoDijkstra& a, const NodoDijkstra& b ) const
  {
    if( a.costo != b.costo )
      return( a.costo > b.costo );
    return( a.vertice > b.vertice );
  }
};

bool Grafo::Dijkstra( const string& origen, vector<int>& dist, vector<int>& pred ) const
{
  int s = BuscarVertice( origen );
  if( s == -1 )
    return( false );

  int n = CantidadVertices();
  dist.assign( n, COSTO_INFINITO );
  dist[ s ] = 0;
  pred.assign( n, -1 );
  vector<bool> enS( n, false );

  priority_queue< NodoDijkstra, vector<NodoDijkstra>, ComparadorNodoDijkstra > Q;
  NodoDijkstra inicial = { s, -1, 0 };
  Q.push( inicial );

  while( !Q.empty() )
  {

    NodoDijkstra actual = Q.top();
    Q.pop();
    int u = actual.vertice;
    if( enS[ u ] )
      continue;
    enS[ u ] = true;
    pred[ u ] = actual.padre;

    list< pair<int, int> >::const_iterator it;
    for( it = aristas[ u ].begin(); it != aristas[ u ].end(); ++it )
    {
      int v = it->first;
      if( enS[ v ] )
        continue;
      int nuevo = dist[ u ] + it->second;
      if( dist[ v ] > nuevo )
      {
        dist[ v ] = nuevo;
        NodoDijkstra nodo = { v, u, nuevo };
        Q.push( nodo );
      }
    }
  }
  return( true );
}

vector<int> Grafo::ReconstruirRuta( const vector<int>& pred, int destino ) const
{
  vector<int> ruta;
  for( int v = destino; v != -1; v = pred[ v ] )
    ruta.push_back( v );
  reverse( ruta.begin(), ruta.end() );
  return( ruta );
}
