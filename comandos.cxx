#include "comandos.h"
#include <sstream>
#include <cctype>

vector<ComandoInfo> obtener_tabla_comandos()
{
  vector<ComandoInfo> tabla;

  tabla.push_back( { "inicializar", 1, 1,
    "inicializar archivo_inicio (.txt o .bin)",
    "Inicializa el juego a partir de un archivo de configuracion.",
    { TP_ARCHIVO_INICIO } } );

  tabla.push_back( { "obtener_unidades", 1, 1,
    "obtener_unidades nombre_jugador",
    "Permite al jugador reclamar y ubicar nuevas unidades de ejercito.",
    { TP_NOMBRE_JUGADOR } } );

  tabla.push_back( { "atacar", 1, 1,
    "atacar nombre_jugador",
    "Permite al jugador atacar territorios vecinos.",
    { TP_NOMBRE_JUGADOR } } );

  tabla.push_back( { "fortificar", 1, 1,
    "fortificar nombre_jugador",
    "Permite al jugador mover unidades entre territorios vecinos.",
    { TP_NOMBRE_JUGADOR } } );

  tabla.push_back( { "estado_juego", 0, 0,
    "estado_juego",
    "Muestra un resumen del estado actual de la partida.",
    { } } );

  tabla.push_back( { "guardar", 1, 1,
    "guardar nombre_archivo",
    "Guarda el estado actual del juego en un archivo de texto plano.",
    { TP_ARCHIVO_DESTINO } } );

  tabla.push_back( { "guardar_comprimido", 1, 1,
    "guardar_comprimido nombre_archivo",
    "Guarda el estado actual del juego comprimido (codificacion Huffman).",
    { TP_ARCHIVO_DESTINO } } );

  tabla.push_back( { "costo_conquista", 2, 2,
    "costo_conquista nombre_jugador territorio",
    "Calcula el costo y la ruta para conquistar un territorio.",
    { TP_NOMBRE_JUGADOR, TP_TERRITORIO } } );

  tabla.push_back( { "conquista_mas_barata", 1, 1,
    "conquista_mas_barata nombre_jugador",
    "Calcula la conquista que implica perder menos unidades.",
    { TP_NOMBRE_JUGADOR } } );

  tabla.push_back( { "ayuda", 0, 1,
    "ayuda [comando]",
    "Lista los comandos disponibles, o el uso de uno en particular.",
    { TP_LIBRE } } );

  tabla.push_back( { "salir", 0, 0,
    "salir",
    "Termina la ejecucion de la aplicacion.",
    { } } );

  return( tabla );
}

bool buscar_comando( const string& nombre, ComandoInfo& info )
{
  vector<ComandoInfo> tabla = obtener_tabla_comandos();
  for( unsigned int i = 0; i < tabla.size(); ++i )
  {
    if( tabla[ i ].nombre == nombre )
    {
      info = tabla[ i ];
      return( true );
    }
  }
  return( false );
}

vector<string> separar_en_tokens( const string& linea )
{
  vector<string> tokens;
  istringstream flujo( linea );
  string palabra;
  while( flujo >> palabra )
    tokens.push_back( palabra );
  return( tokens );
}

static bool tiene_extension( const string& valor,
                              const string& extension )
{
  if( valor.size() < extension.size() )
    return( false );
  return( valor.compare( valor.size() - extension.size(),
                          extension.size(), extension ) == 0 );
}


static bool contiene_separador_de_ruta( const string& valor )
{
  return( valor.find( '/' ) != string::npos ||
          valor.find( '\\' ) != string::npos );
}

bool validar_formato_parametro( int tipo, const string& valor,
                                 string& motivo )
{
  if( tipo == TP_LIBRE )
  {
    return( true );
  }
  else if( tipo == TP_NOMBRE_JUGADOR )
  {
    if( valor.empty() || valor.size() > 8 )
    {
      motivo = "nombre_jugador debe ser una palabra de 1 a 8 caracteres";
      return( false );
    }
    for( unsigned int i = 0; i < valor.size(); ++i )
    {
      if( !isalnum( static_cast<unsigned char>( valor[ i ] ) ) )
      {
        motivo = "nombre_jugador solo puede tener letras y digitos "
                  "(sin espacios ni simbolos)";
        return( false );
      }
    }
    return( true );
  }
  else if( tipo == TP_ARCHIVO_INICIO )
  {
    if( valor.empty() || contiene_separador_de_ruta( valor ) )
    {
      motivo = "archivo_inicio debe ser un nombre de archivo valido";
      return( false );
    }
    if( !tiene_extension( valor, ".txt" ) && !tiene_extension( valor, ".bin" ) )
    {
      motivo = "archivo_inicio debe terminar en .txt (texto plano) o "
                ".bin (partida comprimida)";
      return( false );
    }
    return( true );
  }
  else if( tipo == TP_ARCHIVO_DESTINO )
  {
    if( valor.empty() || contiene_separador_de_ruta( valor ) )
    {
      motivo = "nombre_archivo debe ser un nombre de archivo valido, "
                "sin '/' ni '\\'";
      return( false );
    }
    return( true );
  }
  else if( tipo == TP_TERRITORIO )
  {

    if( valor.empty() || valor.size() > 30 )
    {
      motivo = "territorio debe ser un nombre no vacio de hasta 30 "
                "caracteres";
      return( false );
    }
    return( true );
  }


  motivo = "tipo de parametro no reconocido internamente";
  return( false );
}

bool validar_parametros( const ComandoInfo& info,
                          const vector<string>& parametros,
                          string& motivo )
{

  int cantidad = static_cast<int>( parametros.size() );
  if( cantidad < info.min_parametros || cantidad > info.max_parametros )
  {
    motivo = "cantidad de parametros invalida";
    return( false );
  }

  for( unsigned int i = 0; i < parametros.size(); ++i )
  {
    int tipo = ( i < info.tipos_parametros.size() )
               ? info.tipos_parametros[ i ]
               : TP_LIBRE;
    if( !validar_formato_parametro( tipo, parametros[ i ], motivo ) )
      return( false );
  }

  return( true );
}
