
#include "ArbolHuffman.h"
#include <queue>
#include <vector>
#include <cstddef>

ArbolHuffman::ArbolHuffman()
{
  raiz = NULL;
}

ArbolHuffman::~ArbolHuffman()
{
  Liberar( raiz );
}

void ArbolHuffman::Construir( const unsigned long long frecuencias[ 256 ] )
{
  Liberar( raiz );
  raiz = NULL;
  for( int s = 0; s < 256; ++s )
    codigos[ s ] = "";

  priority_queue< NodoHuffman*, vector<NodoHuffman*>, ComparadorNodos > cola;
  int orden = 0;

  for( int s = 0; s < 256; ++s )
    if( frecuencias[ s ] > 0 )
      cola.push( new NodoHuffman( static_cast<unsigned char>( s ),
                                  frecuencias[ s ], orden++ ) );

  if( cola.empty() )
    return;

  if( cola.size() == 1 )
  {
    NodoHuffman* unica = cola.top();
    cola.pop();
    raiz = new NodoHuffman( unica, NULL, orden++ );
    GenerarCodigos( raiz, "" );
    return;
  }

  while( cola.size() > 1 )
  {
    NodoHuffman* izq = cola.top(); cola.pop();
    NodoHuffman* der = cola.top(); cola.pop();
    cola.push( new NodoHuffman( izq, der, orden++ ) );
  }
  raiz = cola.top();
  GenerarCodigos( raiz, "" );
}

void ArbolHuffman::GenerarCodigos( NodoHuffman* nodo, const string& prefijo )
{
  if( nodo == NULL )
    return;
  if( nodo->EsHoja() )
  {
    codigos[ nodo->ObtenerSimbolo() ] = prefijo;
    return;
  }
  GenerarCodigos( nodo->ObtenerHijoIzq(), prefijo + "0" );
  GenerarCodigos( nodo->ObtenerHijoDer(), prefijo + "1" );
}

string ArbolHuffman::ObtenerCodigo( unsigned char simbolo ) const
{
  return( codigos[ simbolo ] );
}

string ArbolHuffman::Codificar( const string& texto ) const
{
  string bits;
  for( unsigned int i = 0; i < texto.size(); ++i )
    bits += codigos[ static_cast<unsigned char>( texto[ i ] ) ];
  return( bits );
}

bool ArbolHuffman::Decodificar( const string& bits, unsigned long long w,
                                string& texto ) const
{
  texto = "";
  if( raiz == NULL )
    return( w == 0 );

  NodoHuffman* actual = raiz;
  for( unsigned int i = 0; i < bits.size() && texto.size() < w; ++i )
  {
    if( bits[ i ] == '0' )
      actual = actual->ObtenerHijoIzq();
    else
      actual = actual->ObtenerHijoDer();

    if( actual == NULL )
      return( false );

    if( actual->EsHoja() )
    {
      texto += static_cast<char>( actual->ObtenerSimbolo() );
      actual = raiz;
    }
  }
  return( texto.size() == w );
}

void ArbolHuffman::Liberar( NodoHuffman* nodo )
{
  if( nodo == NULL )
    return;
  Liberar( nodo->ObtenerHijoIzq() );
  Liberar( nodo->ObtenerHijoDer() );
  delete nodo;
}
