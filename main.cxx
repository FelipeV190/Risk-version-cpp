
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "comandos.h"
#include "Ejecucion.h" // [IA] Corregido: el archivo se llama Ejecucion.h (en Linux importa la mayuscula)

using namespace std;

void mostrar_ayuda_general()
{
  vector<ComandoInfo> tabla = obtener_tabla_comandos();
  cout << "Comandos disponibles:" << endl;
  for( unsigned int i = 0; i < tabla.size(); ++i )
    cout << "  " << tabla[ i ].nombre << " - " << tabla[ i ].descripcion << endl;
  cout << "Use 'ayuda nombre_comando' para ver el detalle de uso "
       << "de un comando especifico." << endl;
}

void mostrar_ayuda_comando( const string& nombre_comando )
{
  ComandoInfo info;
  if( !buscar_comando( nombre_comando, info ) )
  {
    cout << "(Comando no valido) '" << nombre_comando
         << "' no es un comando reconocido por el sistema." << endl;
    return;
  }
  cout << "Uso: " << info.uso << endl;
  cout << "Descripcion: " << info.descripcion << endl;
}

bool procesar_linea( const string& linea, Partida& partida )
{
  vector<string> tokens = separar_en_tokens( linea );

  if( tokens.empty() )
    return( true );

  string nombre_comando = tokens[ 0 ];
  vector<string> parametros( tokens.begin() + 1, tokens.end() );

  ComandoInfo info;
  if( !buscar_comando( nombre_comando, info ) )
  {
    cout << "(Comando no valido) '" << nombre_comando
         << "' no es un comando reconocido. Use 'ayuda' para ver "
         << "la lista de comandos disponibles." << endl;
    return( true );
  }
  string motivo_error;
  if( !validar_parametros( info, parametros, motivo_error ) )
  {
    cout << "(Parametros invalidos) " << motivo_error << ". "
         << "Uso correcto: " << info.uso << endl;
    return( true );
  }
  if( nombre_comando == "salir" )
  {
    cout << "Saliendo del sistema. Hasta pronto." << endl;
    return( false );
  }
  if( nombre_comando == "ayuda" )
  {
    if( parametros.empty() )
      mostrar_ayuda_general();
    else
      mostrar_ayuda_comando( parametros[ 0 ] );
    return( true );
  }
  if( nombre_comando == "inicializar" )
  {
    ejecutar_inicializar( partida, parametros[ 0 ] );
    return( true );
  }
  if( nombre_comando == "obtener_unidades" )
  {
    ejecutar_obtener_unidades( partida, parametros[ 0 ] );
    return( true );
  }
  if( nombre_comando == "atacar" )
  {
    ejecutar_atacar( partida, parametros[ 0 ] );
    return( true );
  }
  if( nombre_comando == "fortificar" )
  {
    ejecutar_fortificar( partida, parametros[ 0 ] );
    return( true );
  }
  if( nombre_comando == "estado_juego" )
  {
    ejecutar_estado_juego( partida );
    return( true );
  }

  if( nombre_comando == "guardar" )
  {
    ejecutar_guardar( partida, parametros[ 0 ] );
    return( true );
  }
  if( nombre_comando == "guardar_comprimido" )
  {
    ejecutar_guardar_comprimido( partida, parametros[ 0 ] );
    return( true );
  }
  if( nombre_comando == "costo_conquista" )
  {
    ejecutar_costo_conquista( partida, parametros[ 0 ], parametros[ 1 ] );
    return( true );
  }
  if( nombre_comando == "conquista_mas_barata" )
  {
    ejecutar_conquista_mas_barata( partida, parametros[ 0 ] );
    return( true );
  }

  return( true );
}

int main()
{

  srand( static_cast<unsigned int>( time( NULL ) ) );
  //srand( 42 );

  cout << "Sistema de apoyo para el juego Risk" << endl;
  cout << "Escriba 'ayuda' para ver los comandos disponibles." << endl;

  Partida partida;

  bool continuar = true;
  string linea;

  while( continuar )
  {
    cout << "$ ";
    if( !getline( cin, linea ) )
      break;

    continuar = procesar_linea( linea, partida );
  }

  return( 0 );
}