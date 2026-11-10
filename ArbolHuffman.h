
#ifndef ARBOL_HUFFMAN_H
#define ARBOL_HUFFMAN_H

#include <string>
#include "NodoHuffman.h"

using namespace std;

class ArbolHuffman
{
public:
  ArbolHuffman();
  ~ArbolHuffman();

  void Construir( const unsigned long long frecuencias[ 256 ] );

  string ObtenerCodigo( unsigned char simbolo ) const;
  string Codificar( const string& texto ) const;

  bool Decodificar( const string& bits, unsigned long long w, string& texto ) const;

private:
  NodoHuffman* raiz;
  string codigos[ 256 ];

  void GenerarCodigos( NodoHuffman* nodo, const string& prefijo );
  void Liberar( NodoHuffman* nodo );

  ArbolHuffman( const ArbolHuffman& otro );
  ArbolHuffman& operator=( const ArbolHuffman& otro );
};

#endif
