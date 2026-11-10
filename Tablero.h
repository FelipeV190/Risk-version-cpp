
#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include <vector>
#include "Territorio.h"

using namespace std;

const string CONTINENTE_AMERICA_NORTE = "AmericaNorte";
const string CONTINENTE_AMERICA_SUR   = "AmericaSur";
const string CONTINENTE_EUROPA        = "Europa";
const string CONTINENTE_AFRICA        = "Africa";
const string CONTINENTE_ASIA          = "Asia";
const string CONTINENTE_OCEANIA       = "Oceania";

class Tablero
{
public:
    Tablero();

    Territorio* ObtenerTerritorio( const string& codigo );
    const Territorio* ObtenerTerritorio( const string& codigo ) const;

    int ContarTerritoriosDe( const string& colorJugador ) const;
    int ContarTerritoriosContinente( const string& continente, const string& colorJugador ) const;
    bool OcupaTodoElContinente( const string& continente, const string& colorJugador ) const;

    int ObtenerCantidadTerritorios() const;
    const Territorio& ObtenerTerritorioEnPosicion( int indice ) const;

private:
    vector<Territorio> territorios;

    void AgregarTerritorio( const string& codigo, const string& continente,
                             const vector<string>& vecinos );
    void ConstruirTableroEstandar();
};

#endif