#include "Carta.h"

Carta::Carta()
{
    territorio = "";
    simbolo = "";
}

Carta::Carta( const string& territorioInicial, const string& simboloInicial )
{
    territorio = territorioInicial;
    simbolo = simboloInicial;
}

string Carta::ObtenerTerritorio() const { return( territorio ); }
string Carta::ObtenerSimbolo() const { return( simbolo ); }
bool Carta::EsComodin() const { return( simbolo == SIMBOLO_COMODIN ); }