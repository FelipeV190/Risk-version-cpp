
#ifndef NODO_HUFFMAN_H
#define NODO_HUFFMAN_H

using namespace std;

class NodoHuffman
{
public:

  NodoHuffman( unsigned char simboloInicial, unsigned long long frecuenciaInicial,
               int ordenInicial );

  NodoHuffman( NodoHuffman* izq, NodoHuffman* der, int ordenInicial );

  unsigned char ObtenerSimbolo() const;
  unsigned long long ObtenerFrecuencia() const;
  int ObtenerOrden() const;
  NodoHuffman* ObtenerHijoIzq() const;
  NodoHuffman* ObtenerHijoDer() const;
  bool EsHoja() const;

private:
  unsigned char simbolo;
  unsigned long long frecuencia;
  int orden;
  NodoHuffman* hijoIzq;
  NodoHuffman* hijoDer;
};

struct ComparadorNodos
{
  bool operator()( const NodoHuffman* a, const NodoHuffman* b ) const
  {
    if( a->ObtenerFrecuencia() != b->ObtenerFrecuencia() )
      return( a->ObtenerFrecuencia() > b->ObtenerFrecuencia() );
    return( a->ObtenerOrden() > b->ObtenerOrden() );
  }
};

#endif
