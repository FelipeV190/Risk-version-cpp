#ifndef CARTA_H
#define CARTA_H

#include <string>

using namespace std;

const string SIMBOLO_INFANTERIA = "infanteria";
const string SIMBOLO_CABALLERIA = "caballeria";
const string SIMBOLO_ARTILLERIA = "artilleria";
const string SIMBOLO_COMODIN    = "comodin";

class Carta
{
public:
    Carta();
    Carta( const string& territorioInicial, const string& simboloInicial );

    string ObtenerTerritorio() const;
    string ObtenerSimbolo() const;
    bool EsComodin() const;

private:
    string territorio;
    string simbolo;
};

#endif