#include "Tablero.h"

Tablero::Tablero()
{
  ConstruirTableroEstandar();
}

void Tablero::AgregarTerritorio( const string& codigo, const string& continente,
                                  const vector<string>& vecinos )
{
  territorios.push_back( Territorio( codigo, continente, vecinos ) );
}

void Tablero::ConstruirTableroEstandar()
{

  AgregarTerritorio( "Alaska", CONTINENTE_AMERICA_NORTE,
    { "TerritorioNoroccidental", "Alberta", "Kamchatka" } );
  AgregarTerritorio( "Alberta", CONTINENTE_AMERICA_NORTE,
    { "Alaska", "TerritorioNoroccidental", "Ontario", "EEUUOeste" } );
  AgregarTerritorio( "TerritorioNoroccidental", CONTINENTE_AMERICA_NORTE,
    { "Alaska", "Alberta", "Ontario", "Groenlandia" } );
  AgregarTerritorio( "Ontario", CONTINENTE_AMERICA_NORTE,
    { "Alberta", "TerritorioNoroccidental", "Groenlandia", "Quebec", "EEUUEste", "EEUUOeste" } );
  AgregarTerritorio( "Quebec", CONTINENTE_AMERICA_NORTE,
    { "Ontario", "EEUUEste", "Groenlandia" } );
  AgregarTerritorio( "Groenlandia", CONTINENTE_AMERICA_NORTE,
    { "TerritorioNoroccidental", "Ontario", "Quebec", "Islandia" } );
  AgregarTerritorio( "EEUUOeste", CONTINENTE_AMERICA_NORTE,
    { "Alberta", "Ontario", "EEUUEste", "AmericaCentral" } );
  AgregarTerritorio( "EEUUEste", CONTINENTE_AMERICA_NORTE,
    { "EEUUOeste", "Ontario", "Quebec", "AmericaCentral" } );
  AgregarTerritorio( "AmericaCentral", CONTINENTE_AMERICA_NORTE,
    { "EEUUOeste", "EEUUEste", "Venezuela" } );


  AgregarTerritorio( "Venezuela", CONTINENTE_AMERICA_SUR,
    { "AmericaCentral", "Brasil", "Peru" } );
  AgregarTerritorio( "Brasil", CONTINENTE_AMERICA_SUR,
    { "Venezuela", "Peru", "Argentina", "AfricaNorte" } );
  AgregarTerritorio( "Peru", CONTINENTE_AMERICA_SUR,
    { "Venezuela", "Brasil", "Argentina" } );
  AgregarTerritorio( "Argentina", CONTINENTE_AMERICA_SUR,
    { "Peru", "Brasil" } );

  AgregarTerritorio( "Islandia", CONTINENTE_EUROPA,
    { "Groenlandia", "GranBretana", "Escandinavia" } );
  AgregarTerritorio( "GranBretana", CONTINENTE_EUROPA,
    { "Islandia", "Escandinavia", "EuropaNorte", "EuropaOccidental" } );
  AgregarTerritorio( "Escandinavia", CONTINENTE_EUROPA,
    { "Islandia", "GranBretana", "EuropaNorte", "Ucrania" } );
  AgregarTerritorio( "EuropaNorte", CONTINENTE_EUROPA,
    { "GranBretana", "Escandinavia", "Ucrania", "EuropaSur", "EuropaOccidental" } );
  AgregarTerritorio( "EuropaOccidental", CONTINENTE_EUROPA,
    { "GranBretana", "EuropaNorte", "EuropaSur", "AfricaNorte" } );
  AgregarTerritorio( "EuropaSur", CONTINENTE_EUROPA,
    { "EuropaOccidental", "EuropaNorte", "Ucrania", "MedioOriente", "Egipto", "AfricaNorte" } );
  AgregarTerritorio( "Ucrania", CONTINENTE_EUROPA,
    { "Escandinavia", "EuropaNorte", "EuropaSur", "Ural", "Afganistan", "MedioOriente" } );


  AgregarTerritorio( "AfricaNorte", CONTINENTE_AFRICA,
    { "Brasil", "EuropaOccidental", "EuropaSur", "Egipto", "AfricaOriental", "Congo" } );
  AgregarTerritorio( "Egipto", CONTINENTE_AFRICA,
    { "EuropaSur", "MedioOriente", "AfricaOriental", "AfricaNorte" } );
  AgregarTerritorio( "AfricaOriental", CONTINENTE_AFRICA,
    { "Egipto", "AfricaNorte", "Congo", "AfricaSur", "Madagascar", "MedioOriente" } );
  AgregarTerritorio( "Congo", CONTINENTE_AFRICA,
    { "AfricaNorte", "AfricaOriental", "AfricaSur" } );
  AgregarTerritorio( "AfricaSur", CONTINENTE_AFRICA,
    { "Congo", "AfricaOriental", "Madagascar" } );
  AgregarTerritorio( "Madagascar", CONTINENTE_AFRICA,
    { "AfricaOriental", "AfricaSur" } );


  AgregarTerritorio( "MedioOriente", CONTINENTE_ASIA,
    { "EuropaSur", "Ucrania", "Afganistan", "India", "AfricaOriental", "Egipto" } );
  AgregarTerritorio( "Afganistan", CONTINENTE_ASIA,
    { "Ucrania", "Ural", "China", "India", "MedioOriente" } );
  AgregarTerritorio( "Ural", CONTINENTE_ASIA,
    { "Ucrania", "Siberia", "China", "Afganistan" } );
  AgregarTerritorio( "Siberia", CONTINENTE_ASIA,
    { "Ural", "Yakutsk", "Irkutsk", "Mongolia", "China" } );
  AgregarTerritorio( "Yakutsk", CONTINENTE_ASIA,
    { "Siberia", "Kamchatka", "Irkutsk" } );
  AgregarTerritorio( "Irkutsk", CONTINENTE_ASIA,
    { "Siberia", "Yakutsk", "Kamchatka", "Mongolia" } );
  AgregarTerritorio( "Kamchatka", CONTINENTE_ASIA,
    { "Yakutsk", "Irkutsk", "Mongolia", "Japon", "Alaska" } );
  AgregarTerritorio( "Mongolia", CONTINENTE_ASIA,
    { "Siberia", "Irkutsk", "Kamchatka", "Japon", "China" } );
  AgregarTerritorio( "Japon", CONTINENTE_ASIA,
    { "Kamchatka", "Mongolia" } );
  AgregarTerritorio( "China", CONTINENTE_ASIA,
    { "Afganistan", "Ural", "Siberia", "Mongolia", "Siam", "India" } );
  AgregarTerritorio( "India", CONTINENTE_ASIA,
    { "MedioOriente", "Afganistan", "China", "Siam" } );
  AgregarTerritorio( "Siam", CONTINENTE_ASIA,
    { "India", "China", "Indonesia" } );


  AgregarTerritorio( "Indonesia", CONTINENTE_OCEANIA,
    { "Siam", "NuevaGuinea", "AustraliaOccidental" } );
  AgregarTerritorio( "NuevaGuinea", CONTINENTE_OCEANIA,
    { "Indonesia", "AustraliaOccidental", "AustraliaOriental" } );
  AgregarTerritorio( "AustraliaOccidental", CONTINENTE_OCEANIA,
    { "Indonesia", "NuevaGuinea", "AustraliaOriental" } );
  AgregarTerritorio( "AustraliaOriental", CONTINENTE_OCEANIA,
    { "NuevaGuinea", "AustraliaOccidental" } );
}

Territorio* Tablero::ObtenerTerritorio( const string& codigo )
{
  for( unsigned int i = 0; i < territorios.size(); ++i )
    if( territorios[ i ].ObtenerCodigo() == codigo )
      return( &territorios[ i ] );
  return( NULL );
}

const Territorio* Tablero::ObtenerTerritorio( const string& codigo ) const
{
  for( unsigned int i = 0; i < territorios.size(); ++i )
    if( territorios[ i ].ObtenerCodigo() == codigo )
      return( &territorios[ i ] );
  return( NULL );
}

int Tablero::ContarTerritoriosDe( const string& colorJugador ) const
{
  int cantidad = 0;
  for( unsigned int i = 0; i < territorios.size(); ++i )
    if( territorios[ i ].ObtenerColorJugador() == colorJugador )
      ++cantidad;
  return( cantidad );
}

int Tablero::ContarTerritoriosContinente( const string& continente, const string& colorJugador ) const
{
  int cantidad = 0;
  for( unsigned int i = 0; i < territorios.size(); ++i )
    if( territorios[ i ].ObtenerContinente() == continente &&
        territorios[ i ].ObtenerColorJugador() == colorJugador )
      ++cantidad;
  return( cantidad );
}

bool Tablero::OcupaTodoElContinente( const string& continente, const string& colorJugador ) const
{
  for( unsigned int i = 0; i < territorios.size(); ++i )
    if( territorios[ i ].ObtenerContinente() == continente &&
        territorios[ i ].ObtenerColorJugador() != colorJugador )
      return( false );
  return( true );
}

int Tablero::ObtenerCantidadTerritorios() const
{
  return( static_cast<int>( territorios.size() ) );
}

const Territorio& Tablero::ObtenerTerritorioEnPosicion( int indice ) const
{
  return( territorios[ indice ] );
}