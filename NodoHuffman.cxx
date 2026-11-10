
#include "NodoHuffman.h"
#include <cstddef>

NodoHuffman::NodoHuffman( unsigned char simboloInicial,
                          unsigned long long frecuenciaInicial,
                          int ordenInicial )
{
  simbolo = simboloInicial;
  frecuencia = frecuenciaInicial;
  orden = ordenInicial;
  hijoIzq = NULL;
  hijoDer = NULL;
}

NodoHuffman::NodoHuffman( NodoHuffman* izq, NodoHuffman* der, int ordenInicial )
{
  simbolo = 0;
  frecuencia = 0;
  if( izq != NULL ) frecuencia += izq->ObtenerFrecuencia();
  if( der != NULL ) frecuencia += der->ObtenerFrecuencia();
  orden = ordenInicial;
  hijoIzq = izq;
  hijoDer = der;
}

unsigned char NodoHuffman::ObtenerSimbolo() const { return( simbolo ); }
unsigned long long NodoHuffman::ObtenerFrecuencia() const { return( frecuencia ); }
int NodoHuffman::ObtenerOrden() const { return( orden ); }
NodoHuffman* NodoHuffman::ObtenerHijoIzq() const { return( hijoIzq ); }
NodoHuffman* NodoHuffman::ObtenerHijoDer() const { return( hijoDer ); }

bool NodoHuffman::EsHoja() const
{
  return( hijoIzq == NULL && hijoDer == NULL );
}
