#include "Ejecucion.h" // [IA] Corregido: el archivo se llama Ejecucion.h (en Linux importa la mayuscula)
#include "ArchivoComprimido.h"
#include "Grafo.h" // [IA] Entrega 3: Componente 3
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <cstdlib>

const int INICIO_CORRECTO   = 0;
const int INICIO_VACIO      = 1;
const int INICIO_SIN_FORMATO = 2;

static int bono_por_continente( const string& continente )
{
  if( continente == CONTINENTE_AMERICA_SUR )   return( 2 );
  if( continente == CONTINENTE_OCEANIA )       return( 2 );
  if( continente == CONTINENTE_AFRICA )        return( 3 );
  if( continente == CONTINENTE_AMERICA_NORTE ) return( 5 );
  if( continente == CONTINENTE_EUROPA )        return( 5 );
  return( 7 );
}

static bool esta_en( const vector<string>& valores, const string& valor )
{
  for( unsigned int i = 0; i < valores.size(); ++i )
    if( valores[ i ] == valor )
      return( true );
  return( false );
}

static bool termina_en( const string& valor, const string& extension )
{
  if( valor.size() < extension.size() )
    return( false );
  return( valor.compare( valor.size() - extension.size(),
                         extension.size(), extension ) == 0 );
}

static string leer_linea_entrada()
{
  string linea;
  if( !getline( cin, linea ) )
  {
    cout << endl << "Fin de la entrada. Saliendo del sistema." << endl;
    exit( 0 );
  }
  return( linea );
}

static string leer_token()
{
  istringstream iss( leer_linea_entrada() );
  string token;
  iss >> token;
  return( token );
}

static bool convertir_entero( const string& token, int& valor )
{
  istringstream iss( token );
  char sobrante;
  if( !( iss >> valor ) || ( iss >> sobrante ) )
    return( false );
  return( true );
}

static bool leer_entero( int& valor )
{
  return( convertir_entero( leer_token(), valor ) );
}

int interpretar_contenido_inicio( const string& contenido, Partida& partida )
{
  bool solo_blancos = true;
  for( unsigned int i = 0; i < contenido.size() && solo_blancos; ++i )
    if( !isspace( static_cast<unsigned char>( contenido[ i ] ) ) )
      solo_blancos = false;
  if( contenido.empty() || solo_blancos )
    return( INICIO_VACIO );

  istringstream iss( contenido );

  int n;
  if( !( iss >> n ) || n < 3 || n > 6 )
    return( INICIO_SIN_FORMATO );

  vector<string> nombres, colores;
  for( int i = 0; i < n; ++i )
  {
    string nom, col;
    if( !( iss >> nom >> col ) || nom.size() > 8 ||
        esta_en( nombres, nom ) || esta_en( colores, col ) )
      return( INICIO_SIN_FORMATO );
    nombres.push_back( nom );
    colores.push_back( col );
  }

  Tablero nuevoTablero;
  set<string> codigosLeidos;

  for( int i = 0; i < 42; ++i )
  {
    string codigo, colorOcupa;
    int unidades;
    if( !( iss >> codigo >> colorOcupa >> unidades ) )
      return( INICIO_SIN_FORMATO );

    Territorio* territorio = nuevoTablero.ObtenerTerritorio( codigo );
    if( territorio == NULL || codigosLeidos.find( codigo ) != codigosLeidos.end() )
      return( INICIO_SIN_FORMATO );
    codigosLeidos.insert( codigo );

    if( !esta_en( colores, colorOcupa ) || unidades <= 0 )
      return( INICIO_SIN_FORMATO );

    territorio->FijarColorJugador( colorOcupa );
    territorio->FijarNumUnidades( unidades );
  }


  string sobrante;
  if( codigosLeidos.size() != 42 || ( iss >> sobrante ) )
    return( INICIO_SIN_FORMATO );

  ListaJugadores nuevaLista;
  for( int i = 0; i < n; ++i )
    nuevaLista.AgregarJugador( Jugador( nombres[ i ], colores[ i ] ) );

  partida.Inicializar( nuevaLista, nuevoTablero );

  for( int i = 0; i < n; ++i )
    if( nuevoTablero.ContarTerritoriosDe( colores[ i ] ) == 42 )
      partida.FinalizarPartida( colores[ i ] );

  return( INICIO_CORRECTO );
}

void ejecutar_inicializar( Partida& partida, const string& archivo )
{
  if( partida.EstaInicializada() )
  {
    cout << "(Juego en curso) El juego ya ha sido inicializado." << endl;
    return;
  }

  ifstream fin( archivo.c_str(), ios::binary );
  if( !fin.is_open() )
  {
    cout << "(Archivo erroneo) " << archivo << " no se encuentra o no puede leerse." << endl;
    return;
  }

  stringstream buffer;
  buffer << fin.rdbuf();
  string contenido = buffer.str();
  fin.close();

  if( contenido.empty() )
  {
    cout << "(Archivo vacio) " << archivo << " no contiene informacion." << endl;
    return;
  }

  if( termina_en( archivo, ".bin" ) )
  {
    ArchivoComprimido comprimido;
    string texto;
    if( !comprimido.LeerArchivo( archivo ) || !comprimido.Descomprimir( texto ) )
    {
      cout << "(Archivo sin formato) " << archivo << " no contiene informacion en el formato esperado." << endl;
      return;
    }
    contenido = texto;
  }

  int resultado = interpretar_contenido_inicio( contenido, partida );
  if( resultado == INICIO_VACIO )
    cout << "(Archivo vacio) " << archivo << " no contiene informacion." << endl;
  else if( resultado == INICIO_SIN_FORMATO )
    cout << "(Archivo sin formato) " << archivo << " no contiene informacion en el formato esperado." << endl;
  else
    cout << "(Comando correcto) El juego se ha inicializado correctamente." << endl;
}

void ejecutar_guardar( const Partida& partida, const string& nombreArchivo )
{
  if( !partida.EstaInicializada() )
  {
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
    return;
  }

  string nombre = nombreArchivo;
  if( !termina_en( nombre, ".txt" ) )
    nombre += ".txt";

  ofstream salida( nombre.c_str(), ios::binary );
  if( !salida.is_open() )
  {
    cout << "(Error al guardar) La partida no ha sido guardada correctamente." << endl;
    return;
  }
  salida << partida.SerializarTexto();
  salida.close();
  if( salida.fail() )
  {
    cout << "(Error al guardar) La partida no ha sido guardada correctamente." << endl;
    return;
  }
  cout << "(Comando correcto) La partida ha sido guardada correctamente." << endl;
}

void ejecutar_guardar_comprimido( const Partida& partida, const string& nombreArchivo )
{
  if( !partida.EstaInicializada() )
  {
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
    return;
  }

  string nombre = nombreArchivo;
  if( !termina_en( nombre, ".bin" ) )
    nombre += ".bin";

  ArchivoComprimido comprimido;
  comprimido.Comprimir( partida.SerializarTexto() );
  if( !comprimido.EscribirArchivo( nombre ) )
  {
    cout << "(Error al codificar y/o guardar) La partida no ha sido codificada ni guardada correctamente." << endl;
    return;
  }
  cout << "(Comando correcto) La partida ha sido codificada y guardada correctamente." << endl;
}

void ejecutar_obtener_unidades( Partida& partida, const string& nombreJugador )
{
  if( !partida.EstaInicializada() )
  {
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
    return;
  }
  if( partida.EstaTerminada() )
  {
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
    return;
  }
  Jugador* jugador = partida.ObtenerJugadores().BuscarJugador( nombreJugador );
  if( jugador == NULL )
  {
    cout << "(Jugador no valido) El jugador " << nombreJugador << " no forma parte de esta partida." << endl;
    return;
  }
  if( !partida.ObtenerJugadores().EsTurnoDe( nombreJugador ) )
  {
    cout << "(Jugador fuera de turno) No es el turno del jugador " << nombreJugador << "." << endl;
    return;
  }

  if( jugador->ObtenerFase() != FASE_INICIO )
  {
    cout << "(Unidades ya obtenidas) El jugador " << nombreJugador
         << " ya ejecuto el comando obtener_unidades en este turno." << endl;
    return;
  }

  Tablero& tablero = partida.ObtenerTablero();
  string color = jugador->ObtenerColor();

  int unidades = tablero.ContarTerritoriosDe( color ) / 3;


  static const string continentes[ 6 ] = {
    CONTINENTE_AMERICA_NORTE, CONTINENTE_AMERICA_SUR, CONTINENTE_EUROPA,
    CONTINENTE_AFRICA, CONTINENTE_ASIA, CONTINENTE_OCEANIA
  };
  for( int i = 0; i < 6; ++i )
    if( tablero.OcupaTodoElContinente( continentes[ i ], color ) )
      unidades += bono_por_continente( continentes[ i ] );


  if( jugador->TieneCombinacionValida() )
  {
    cout << "Tiene una combinacion valida de cartas. Desea intercambiarla "
         << "por unidades adicionales? (s/n): ";
    string resp = leer_token();
    if( resp == "s" || resp == "S" )
    {
      cout << "Cartas actuales:" << endl;
      for( int i = 0; i < jugador->ObtenerNumCartas(); ++i )
      {
        const Carta& c = jugador->ObtenerCarta( i );
        cout << "  [" << i << "] " << c.ObtenerSimbolo();
        if( !c.EsComodin() )
          cout << " (" << c.ObtenerTerritorio() << ")";
        cout << endl;
      }
      cout << "Ingrese los 3 indices de las cartas a intercambiar: ";
      int i1 = -1, i2 = -1, i3 = -1;

      istringstream lineaIndices( leer_linea_entrada() );
      string t1, t2, t3;
      lineaIndices >> t1 >> t2 >> t3;
      if( !convertir_entero( t1, i1 ) ) i1 = -1;
      if( !convertir_entero( t2, i2 ) ) i2 = -1;
      if( !convertir_entero( t3, i3 ) ) i3 = -1;
      int numCartas = jugador->ObtenerNumCartas();
      bool indicesValidos = i1 >= 0 && i1 < numCartas && i2 >= 0 && i2 < numCartas &&
                             i3 >= 0 && i3 < numCartas && i1 != i2 && i2 != i3 && i1 != i3;
      if( indicesValidos )
      {
        string s1 = jugador->ObtenerCarta( i1 ).ObtenerSimbolo();
        string s2 = jugador->ObtenerCarta( i2 ).ObtenerSimbolo();
        string s3 = jugador->ObtenerCarta( i3 ).ObtenerSimbolo();
        bool comboValido = ( s1 == SIMBOLO_COMODIN || s2 == SIMBOLO_COMODIN || s3 == SIMBOLO_COMODIN ) ||
                            ( s1 == s2 && s2 == s3 ) ||
                            ( s1 != s2 && s2 != s3 && s1 != s3 );
        if( comboValido )
        {
          int bono = partida.CalcularBonoPorIntercambio();
          unidades += bono;
          cout << "Intercambio realizado: +" << bono << " unidades." << endl;

          int indicesCartas[ 3 ] = { i1, i2, i3 };
          for( int k = 0; k < 3; ++k )
          {
            const Carta& carta = jugador->ObtenerCarta( indicesCartas[ k ] );
            if( carta.EsComodin() )
              continue;
            Territorio* propio = tablero.ObtenerTerritorio( carta.ObtenerTerritorio() );
            if( propio != NULL && propio->ObtenerColorJugador() == color )
            {
              propio->AgregarUnidades( 2 );
              cout << "  +2 unidades extra en " << carta.ObtenerTerritorio()
                   << " (territorio propio de la carta)." << endl;
            }
          }

          vector<int> indices;
          indices.push_back( i1 );
          indices.push_back( i2 );
          indices.push_back( i3 );
          jugador->QuitarCartas( indices );
        }
        else
          cout << "Las cartas seleccionadas no forman una combinacion valida; no se realiza el intercambio." << endl;
      }
      else
        cout << "Indices invalidos; no se realiza el intercambio." << endl;
    }
  }


  cout << "El jugador " << nombreJugador << " puede reclamar " << unidades
       << " unidades adicionales." << endl;
  int restantes = unidades;
  while( restantes > 0 )
  {
    cout << "Unidades restantes por ubicar: " << restantes << endl;
    cout << "Territorio propio donde ubicarlas: ";
    string codigo = leer_token();
    Territorio* territorio = tablero.ObtenerTerritorio( codigo );
    if( territorio == NULL || territorio->ObtenerColorJugador() != color )
    {
      cout << "Territorio invalido o no pertenece al jugador. Intente de nuevo." << endl;
      continue;
    }
    cout << "Cantidad a ubicar (maximo " << restantes << "): ";
    int cantidad;
    if( !leer_entero( cantidad ) || cantidad <= 0 || cantidad > restantes )
    {
      cout << "Cantidad invalida. Intente de nuevo." << endl;
      continue;
    }
    territorio->AgregarUnidades( cantidad );
    restantes -= cantidad;
  }

  jugador->FijarFase( FASE_UNIDADES_OBTENIDAS );
  cout << "(Comando correcto) El jugador " << nombreJugador
       << " ha terminado de reclamar y ubicar sus unidades." << endl;
}

void ejecutar_atacar( Partida& partida, const string& nombreJugador )
{
  if( !partida.EstaInicializada() )
  {
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
    return;
  }
  if( partida.EstaTerminada() )
  {
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
    return;
  }
  Jugador* jugador = partida.ObtenerJugadores().BuscarJugador( nombreJugador );
  if( jugador == NULL )
  {
    cout << "(Jugador no valido) El jugador " << nombreJugador << " no forma parte de esta partida." << endl;
    return;
  }
  if( !partida.ObtenerJugadores().EsTurnoDe( nombreJugador ) )
  {
    cout << "(Jugador fuera de turno) No es el turno del jugador " << nombreJugador << "." << endl;
    return;
  }
  if( jugador->ObtenerFase() < FASE_UNIDADES_OBTENIDAS )
  {
    cout << "(Jugador no ha ubicado unidades) El jugador " << nombreJugador
         << " no ha ejecutado el comando obtener_unidades." << endl;
    return;
  }

  Tablero& tablero = partida.ObtenerTablero();
  string colorAtacante = jugador->ObtenerColor();
  bool conquistoAlguno = false;

  while( true )
  {
    cout << "Territorio origen (o 'fin' para terminar de atacar): ";
    string origen = leer_token();
    if( origen == "fin" )
      break;
    cout << "Territorio destino: ";
    string destino = leer_token();

    Territorio* to = tablero.ObtenerTerritorio( origen );
    if( to == NULL || to->ObtenerColorJugador() != colorAtacante )
    {
      cout << "El territorio origen no es valido o no pertenece al jugador." << endl;
      continue;
    }
    if( to->ObtenerNumUnidades() <= 1 )
    {
      cout << "El territorio origen debe tener mas de 1 unidad para poder atacar." << endl;
      continue;
    }
    Territorio* td = tablero.ObtenerTerritorio( destino );
    if( td == NULL || !to->EsVecinoDe( destino ) )
    {
      cout << "El territorio destino no es valido o no es vecino del origen." << endl;
      continue;
    }
    if( td->ObtenerColorJugador() == colorAtacante )
    {
      cout << "El territorio destino ya pertenece al jugador atacante." << endl;
      continue;
    }

    int dadosAtacante = min( 3, to->ObtenerNumUnidades() - 1 );
    int dadosDefensor = min( 2, td->ObtenerNumUnidades() );
    if( dadosDefensor < 1 )
      dadosDefensor = 1;

    vector<int> dA, dD;
    for( int i = 0; i < dadosAtacante; ++i )
      dA.push_back( rand() % 6 + 1 );
    for( int i = 0; i < dadosDefensor; ++i )
      dD.push_back( rand() % 6 + 1 );
    sort( dA.rbegin(), dA.rend() );
    sort( dD.rbegin(), dD.rend() );

    cout << "Dados atacante:";
    for( unsigned int i = 0; i < dA.size(); ++i ) cout << " " << dA[ i ];
    cout << endl << "Dados defensor:";
    for( unsigned int i = 0; i < dD.size(); ++i ) cout << " " << dD[ i ];
    cout << endl;

    int comparaciones = static_cast<int>( min( dA.size(), dD.size() ) );
    int perdidasAtacante = 0, perdidasDefensor = 0;
    for( int i = 0; i < comparaciones; ++i )
    {
      if( dA[ i ] > dD[ i ] )
        ++perdidasDefensor;
      else
        ++perdidasAtacante;
    }
    to->QuitarUnidades( perdidasAtacante );
    td->QuitarUnidades( perdidasDefensor );
    cout << "El atacante pierde " << perdidasAtacante << " unidad(es); "
         << "el defensor pierde " << perdidasDefensor << " unidad(es)." << endl;

    if( td->ObtenerNumUnidades() == 0 )
    {
      cout << "Territorio " << destino << " conquistado!" << endl;
      int minimo = dadosAtacante;
      int maximo = to->ObtenerNumUnidades() - 1;
      int mover;
      while( true )
      {
        cout << "Cuantas unidades desea mover desde " << origen
             << " (entre " << minimo << " y " << maximo << ")? ";
        if( leer_entero( mover ) && mover >= minimo && mover <= maximo )
          break;
        cout << "Cantidad invalida. Intente de nuevo." << endl;
      }
      string colorDefensor = td->ObtenerColorJugador();
      to->QuitarUnidades( mover );
      td->FijarColorJugador( colorAtacante );
      td->FijarNumUnidades( mover );

      if( tablero.ContarTerritoriosDe( colorDefensor ) == 0 )
      {
        ListaJugadores& lista = partida.ObtenerJugadores();
        Jugador* eliminado = lista.BuscarJugadorPorColor( colorDefensor );
        if( eliminado != NULL )
        {
          string nombreEliminado = eliminado->ObtenerNombre();
          lista.EliminarJugador( nombreEliminado );
          jugador = lista.BuscarJugador( nombreJugador );
          cout << "El jugador " << nombreEliminado
               << " se quedo sin territorios y sale de la partida." << endl;
        }
      }

      if( !conquistoAlguno )
      {
        static const string simbolos[ 3 ] = { SIMBOLO_INFANTERIA, SIMBOLO_CABALLERIA, SIMBOLO_ARTILLERIA };
        string simboloCarta = simbolos[ rand() % 3 ];
        jugador->AgregarCarta( Carta( destino, simboloCarta ) );
        cout << "El jugador recibe una carta de territorio (" << simboloCarta << ")." << endl;
        conquistoAlguno = true;
      }

      if( tablero.ContarTerritoriosDe( colorAtacante ) == 42 )
      {
        partida.FinalizarPartida( colorAtacante );
        jugador->FijarFase( FASE_ATAQUE_TERMINADO );
        cout << "(Juego terminado) El jugador " << nombreJugador
             << " ha conquistado los 42 territorios y gana la partida." << endl;
        return;
      }
    }

    cout << "Desea continuar atacando? (s/n): ";
    string resp = leer_token();
    if( resp != "s" && resp != "S" )
      break;
  }

  jugador->FijarFase( FASE_ATAQUE_TERMINADO );
  cout << "(Comando correcto) El jugador " << nombreJugador << " ha terminado de atacar." << endl;
}

void ejecutar_fortificar( Partida& partida, const string& nombreJugador )
{
  if( !partida.EstaInicializada() )
  {
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
    return;
  }
  if( partida.EstaTerminada() )
  {
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
    return;
  }
  Jugador* jugador = partida.ObtenerJugadores().BuscarJugador( nombreJugador );
  if( jugador == NULL )
  {
    cout << "(Jugador no valido) El jugador " << nombreJugador << " no forma parte de esta partida." << endl;
    return;
  }
  if( !partida.ObtenerJugadores().EsTurnoDe( nombreJugador ) )
  {
    cout << "(Jugador fuera de turno) No es el turno del jugador " << nombreJugador << "." << endl;
    return;
  }
  if( jugador->ObtenerFase() < FASE_ATAQUE_TERMINADO )
  {
    cout << "(Jugador no ha atacado) El jugador " << nombreJugador
         << " no ha ejecutado el comando atacar." << endl;
    return;
  }

  Tablero& tablero = partida.ObtenerTablero();
  string color = jugador->ObtenerColor();

  while( true )
  {

    cout << "Territorio origen (o 'fin' para no fortificar): ";
    string origen = leer_token();
    if( origen == "fin" )
    {
      cout << "No se fortifica ninguna posicion en este turno." << endl;
      break;
    }
    cout << "Territorio destino: ";
    string destino = leer_token();
    cout << "Cantidad de unidades a mover: ";
    int cantidad;
    if( !leer_entero( cantidad ) )
    {
      cout << "La cantidad debe ser un numero entero. Intente de nuevo." << endl;
      continue;
    }

    Territorio* to = tablero.ObtenerTerritorio( origen );
    Territorio* td = tablero.ObtenerTerritorio( destino );

    if( to == NULL || to->ObtenerColorJugador() != color ||
        td == NULL || td->ObtenerColorJugador() != color )
    {
      cout << "Ambos territorios deben ser propios del jugador. Intente de nuevo." << endl;
      continue;
    }
    if( !to->EsVecinoDe( destino ) )
    {
      cout << "Los territorios deben ser vecinos entre si. Intente de nuevo." << endl;
      continue;
    }
    if( cantidad <= 0 || cantidad > to->ObtenerNumUnidades() - 1 )
    {
      cout << "Cantidad invalida (debe quedar minimo 1 unidad en el origen). Intente de nuevo." << endl;
      continue;
    }

    to->QuitarUnidades( cantidad );
    td->AgregarUnidades( cantidad );
    break;
  }

  partida.ObtenerJugadores().AvanzarTurno();
  cout << "(Comando correcto) El jugador " << nombreJugador
       << " ha terminado de fortificar su posicion." << endl;
}

void ejecutar_estado_juego( const Partida& partida )
{
  if( !partida.EstaInicializada() )
  {
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
    return;
  }
  if( partida.EstaTerminada() )
  {
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
    return;
  }

  const ListaJugadores& jugadores = partida.ObtenerJugadores();
  cout << "Cantidad de jugadores: " << jugadores.ObtenerCantidad() << endl;
  for( int i = 0; i < jugadores.ObtenerCantidad(); ++i )
  {
    const Jugador& j = jugadores.ObtenerJugadorEnPosicion( i );
    cout << "  " << j.ObtenerNombre() << " (" << j.ObtenerColor() << ")";
    if( i == 0 )
      cout << "  <- turno vigente";
    cout << endl;
  }

  const Tablero& tablero = partida.ObtenerTablero();
  cout << "Territorios:" << endl;
  for( int i = 0; i < tablero.ObtenerCantidadTerritorios(); ++i )
  {
    const Territorio& t = tablero.ObtenerTerritorioEnPosicion( i );
    cout << "  " << t.ObtenerCodigo() << ": " << t.ObtenerColorJugador()
         << " (" << t.ObtenerNumUnidades() << " unidades)" << endl;
  }
}

struct RutaConquista
{
  int costo;
  int saltos;
  vector<int> camino;
};

static void construir_grafo_conquista( const Tablero& tablero, const string& color,
                                       Grafo& grafo )
{
  int n = tablero.ObtenerCantidadTerritorios();
  for( int i = 0; i < n; ++i )
    grafo.InsertarVertice( tablero.ObtenerTerritorioEnPosicion( i ).ObtenerCodigo() );

  for( int u = 0; u < n; ++u )
  {
    const Territorio& tu = tablero.ObtenerTerritorioEnPosicion( u );
    const vector<string>& vecinos = tu.ObtenerVecinos();
    for( unsigned int k = 0; k < vecinos.size(); ++k )
    {
      const Territorio* tv = tablero.ObtenerTerritorio( vecinos[ k ] );
      if( tv != NULL && tv->ObtenerColorJugador() != color )
        grafo.InsertarArista( tu.ObtenerCodigo(), tv->ObtenerCodigo(),
                              tv->ObtenerNumUnidades() );
    }
  }
}

static void calcular_rutas_conquista( const Tablero& tablero, const string& color,
                                      vector<RutaConquista>& mejores )
{
  Grafo grafo;
  construir_grafo_conquista( tablero, color, grafo );

  int n = grafo.CantidadVertices();
  RutaConquista vacia;
  vacia.costo = COSTO_INFINITO;
  vacia.saltos = 0;
  mejores.assign( n, vacia );

  for( int f = 0; f < n; ++f )
  {
    if( tablero.ObtenerTerritorioEnPosicion( f ).ObtenerColorJugador() != color )
      continue;

    vector<int> dist, pred;
    grafo.Dijkstra( grafo.ObtenerVertice( f ), dist, pred );

    for( int v = 0; v < n; ++v )
    {
      if( tablero.ObtenerTerritorioEnPosicion( v ).ObtenerColorJugador() == color )
        continue;
      if( dist[ v ] == COSTO_INFINITO )
        continue;
      vector<int> ruta = grafo.ReconstruirRuta( pred, v );
      int saltos = static_cast<int>( ruta.size() ) - 1;
      if( dist[ v ] < mejores[ v ].costo ||
          ( dist[ v ] == mejores[ v ].costo && saltos < mejores[ v ].saltos ) )
      {
        mejores[ v ].costo = dist[ v ];
        mejores[ v ].saltos = saltos;
        mejores[ v ].camino = ruta;
      }
    }
  }
}

static Jugador* validar_comando_estrategia( Partida& partida, const string& nombreJugador )
{
  if( !partida.EstaInicializada() )
  {
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
    return( NULL );
  }
  if( partida.EstaTerminada() )
  {
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
    return( NULL );
  }
  Jugador* jugador = partida.ObtenerJugadores().BuscarJugador( nombreJugador );
  if( jugador == NULL )
  {
    cout << "(Jugador no valido) El jugador " << nombreJugador
         << " no forma parte de esta partida." << endl;
    return( NULL );
  }
  return( jugador );
}

static string mostrar_ruta( const Tablero& tablero, const vector<int>& camino )
{
  cout << "Ruta de conquista:" << endl;
  int acumulado = 0;
  for( unsigned int i = 0; i < camino.size(); ++i )
  {
    const Territorio& t = tablero.ObtenerTerritorioEnPosicion( camino[ i ] );
    cout << "  " << ( i + 1 ) << ". " << t.ObtenerCodigo();
    if( i == 0 )
      cout << " (propio, origen del ataque)" << endl;
    else
    {
      acumulado += t.ObtenerNumUnidades();
      cout << " [" << t.ObtenerColorJugador() << ", "
           << t.ObtenerNumUnidades() << " unidad(es), acumulado "
           << acumulado << "]" << endl;
    }
  }

  string intermedios;
  for( unsigned int i = 1; i + 1 < camino.size(); ++i )
  {
    if( !intermedios.empty() )
      intermedios += ", ";
    intermedios += tablero.ObtenerTerritorioEnPosicion( camino[ i ] ).ObtenerCodigo();
  }
  if( intermedios.empty() )
    return( " (ataque directo, sin pasar por otros territorios)" );
  return( ", pasando por los territorios " + intermedios );
}

static int posicion_en_tablero( const Tablero& tablero, const string& codigo )
{
  for( int i = 0; i < tablero.ObtenerCantidadTerritorios(); ++i )
    if( tablero.ObtenerTerritorioEnPosicion( i ).ObtenerCodigo() == codigo )
      return( i );
  return( -1 );
}

void ejecutar_costo_conquista( Partida& partida, const string& nombreJugador,
                               const string& territorio )
{
  Jugador* jugador = validar_comando_estrategia( partida, nombreJugador );
  if( jugador == NULL )
    return;

  const Tablero& tablero = partida.ObtenerTablero();
  int destino = posicion_en_tablero( tablero, territorio );
  if( destino == -1 )
  {
    cout << "(Territorio no valido) El territorio " << territorio
         << " no existe en el tablero." << endl;
    return;
  }
  string color = jugador->ObtenerColor();
  if( tablero.ObtenerTerritorioEnPosicion( destino ).ObtenerColorJugador() == color )
  {
    cout << "(Territorio propio) El territorio " << territorio
         << " ya pertenece al jugador " << nombreJugador << "." << endl;
    return;
  }

  vector<RutaConquista> mejores;
  calcular_rutas_conquista( tablero, color, mejores );

  if( mejores[ destino ].camino.empty() )
  {
    cout << "(Sin ruta) El jugador " << nombreJugador
         << " no tiene territorios desde donde llegar a " << territorio << "." << endl;
    return;
  }

  const vector<int>& camino = mejores[ destino ].camino;
  string pasando = mostrar_ruta( tablero, camino );
  cout << "(Comando correcto) Para conquistar el territorio " << territorio
       << ", " << nombreJugador << " debe atacar desde "
       << tablero.ObtenerTerritorioEnPosicion( camino[ 0 ] ).ObtenerCodigo() << pasando
       << ". Debe conquistar " << mejores[ destino ].costo
       << " unidades de ejercito." << endl;
}

void ejecutar_conquista_mas_barata( Partida& partida, const string& nombreJugador )
{
  Jugador* jugador = validar_comando_estrategia( partida, nombreJugador );
  if( jugador == NULL )
    return;

  const Tablero& tablero = partida.ObtenerTablero();
  vector<RutaConquista> mejores;
  calcular_rutas_conquista( tablero, jugador->ObtenerColor(), mejores );

  int mejor = -1;
  for( unsigned int v = 0; v < mejores.size(); ++v )
  {
    if( mejores[ v ].camino.empty() )
      continue;
    if( mejor == -1 || mejores[ v ].costo < mejores[ mejor ].costo ||
        ( mejores[ v ].costo == mejores[ mejor ].costo &&
          mejores[ v ].saltos < mejores[ mejor ].saltos ) )
      mejor = static_cast<int>( v );
  }

  if( mejor == -1 )
  {
    cout << "(Sin ruta) El jugador " << nombreJugador
         << " no tiene territorios enemigos alcanzables." << endl;
    return;
  }

  const vector<int>& camino = mejores[ mejor ].camino;
  string objetivo = tablero.ObtenerTerritorioEnPosicion( mejor ).ObtenerCodigo();
  string origen = tablero.ObtenerTerritorioEnPosicion( camino[ 0 ] ).ObtenerCodigo();
  string pasando = mostrar_ruta( tablero, camino );
  cout << "(Comando correcto) La conquista mas barata es avanzar sobre el territorio "
       << objetivo << " desde el territorio " << origen
       << ". Para conquistar el territorio " << objetivo
       << ", debe atacar desde " << origen << pasando
       << ". Debe conquistar " << mejores[ mejor ].costo
       << " unidades de ejercito." << endl;
}
