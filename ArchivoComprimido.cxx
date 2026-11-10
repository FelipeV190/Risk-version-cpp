// ---------------------------------------------------------------------------
// [IA] Archivo generado con apoyo de IA generativa (Claude).
// Prompt: "Implementa en C++11 el TAD ArchivoComprimido del documento de
// diseno de la Entrega 2: Comprimir, Descomprimir, EscribirArchivo y
// LeerArchivo con el formato n c1 f1 ... cn fn w binary_code del enunciado"
// ---------------------------------------------------------------------------
#include "ArchivoComprimido.h"
#include "ArbolHuffman.h"
#include <fstream>

// Formato del archivo .bin (todos los enteros en el orden de bytes de la
// maquina; en un PC x86 es little-endian):
//   n            unsigned short      (2 bytes)  caracteres distintos
//   c_i, f_i     unsigned char (1 byte) + unsigned long long (8 bytes), n veces
//   w            unsigned long long  (8 bytes)  longitud del texto original
//   binary_code  los bits codificados, de 8 en 8; el primer bit va en el
//                bit mas significativo; el ultimo byte se rellena con ceros.

ArchivoComprimido::ArchivoComprimido()
{
  for( int s = 0; s < 256; ++s )
    frecuencias[ s ] = 0;
  longitudOriginal = 0;
  bits = "";
}

void ArchivoComprimido::Comprimir( const string& texto )
{
  for( int s = 0; s < 256; ++s )
    frecuencias[ s ] = 0;
  for( unsigned int i = 0; i < texto.size(); ++i )
    frecuencias[ static_cast<unsigned char>( texto[ i ] ) ]++;
  longitudOriginal = texto.size();

  ArbolHuffman arbol;
  arbol.Construir( frecuencias );
  bits = arbol.Codificar( texto );
}

bool ArchivoComprimido::Descomprimir( string& texto ) const
{
  ArbolHuffman arbol;
  arbol.Construir( frecuencias );
  return( arbol.Decodificar( bits, longitudOriginal, texto ) );
}

bool ArchivoComprimido::EscribirArchivo( const string& nombre ) const
{
  ofstream salida( nombre.c_str(), ios::binary );
  if( !salida.is_open() )
    return( false );

  // n: cantidad de caracteres distintos
  unsigned short n = 0;
  for( int s = 0; s < 256; ++s )
    if( frecuencias[ s ] > 0 )
      ++n;
  salida.write( reinterpret_cast<const char*>( &n ), sizeof( n ) );

  // pares (c_i, f_i) en orden ASCII ascendente
  for( int s = 0; s < 256; ++s )
  {
    if( frecuencias[ s ] == 0 )
      continue;
    unsigned char c = static_cast<unsigned char>( s );
    unsigned long long f = frecuencias[ s ];
    salida.write( reinterpret_cast<const char*>( &c ), sizeof( c ) );
    salida.write( reinterpret_cast<const char*>( &f ), sizeof( f ) );
  }

  // w: longitud del texto original
  unsigned long long w = longitudOriginal;
  salida.write( reinterpret_cast<const char*>( &w ), sizeof( w ) );

  // binary_code: se agrupan los bits de 8 en 8
  unsigned char byte = 0;
  int bitsEnByte = 0;
  for( unsigned int i = 0; i < bits.size(); ++i )
  {
    byte = static_cast<unsigned char>( byte << 1 );
    if( bits[ i ] == '1' )
      byte = static_cast<unsigned char>( byte | 1 );
    ++bitsEnByte;
    if( bitsEnByte == 8 )
    {
      salida.write( reinterpret_cast<const char*>( &byte ), 1 );
      byte = 0;
      bitsEnByte = 0;
    }
  }
  if( bitsEnByte > 0 )
  {
    // relleno con ceros a la derecha hasta completar el byte
    byte = static_cast<unsigned char>( byte << ( 8 - bitsEnByte ) );
    salida.write( reinterpret_cast<const char*>( &byte ), 1 );
  }

  salida.close();
  return( !salida.fail() );
}

bool ArchivoComprimido::LeerArchivo( const string& nombre )
{
  ifstream entrada( nombre.c_str(), ios::binary );
  if( !entrada.is_open() )
    return( false );

  for( int s = 0; s < 256; ++s )
    frecuencias[ s ] = 0;
  longitudOriginal = 0;
  bits = "";

  // n
  unsigned short n = 0;
  if( !entrada.read( reinterpret_cast<char*>( &n ), sizeof( n ) ) )
    return( false );
  if( n == 0 || n > 256 )
    return( false );

  // pares (c_i, f_i)
  unsigned long long suma = 0;
  for( int i = 0; i < n; ++i )
  {
    unsigned char c = 0;
    unsigned long long f = 0;
    if( !entrada.read( reinterpret_cast<char*>( &c ), sizeof( c ) ) )
      return( false );
    if( !entrada.read( reinterpret_cast<char*>( &f ), sizeof( f ) ) )
      return( false );
    if( f == 0 || frecuencias[ c ] != 0 )   // frecuencia nula o repetido
      return( false );
    frecuencias[ c ] = f;
    suma += f;
  }

  // w
  unsigned long long w = 0;
  if( !entrada.read( reinterpret_cast<char*>( &w ), sizeof( w ) ) )
    return( false );
  if( w != suma )
    return( false );
  longitudOriginal = w;

  // binary_code: cada byte se expande a 8 caracteres '0'/'1'
  char leido;
  while( entrada.get( leido ) )
  {
    unsigned char b = static_cast<unsigned char>( leido );
    for( int k = 7; k >= 0; --k )
      bits += ( ( b >> k ) & 1 ) ? '1' : '0';
  }
  return( true );
}
