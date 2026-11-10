#ifndef ARCHIVO_COMPRIMIDO_H
#define ARCHIVO_COMPRIMIDO_H

#include <string>

using namespace std;

class ArchivoComprimido
{
public:
  ArchivoComprimido();

  // Cuenta frecuencias, construye el arbol y guarda los bits codificados.
  void Comprimir( const string& texto );

  // Reconstruye el arbol con 'frecuencias' y decodifica 'bits'.
  // Retorna false si los datos no alcanzan para w caracteres.
  bool Descomprimir( string& texto ) const;

  // Escribe el archivo binario. Retorna false si no se pudo escribir.
  bool EscribirArchivo( const string& nombre ) const;

  // Lee y valida el archivo binario. Retorna false si no se puede leer
  // o no cumple el formato.
  bool LeerArchivo( const string& nombre );

private:
  unsigned long long frecuencias[ 256 ];
  unsigned long long longitudOriginal;
  string bits;
};

#endif
