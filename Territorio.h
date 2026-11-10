#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <string>
#include <vector>

using namespace std;

class Territorio
{
public:
    Territorio();
    Territorio( const string& codigoInicial, const string& continenteInicial,
                const vector<string>& vecinosIniciales );

    string ObtenerCodigo() const;
    string ObtenerContinente() const;
    string ObtenerColorJugador() const;
    int ObtenerNumUnidades() const;
    const vector<string>& ObtenerVecinos() const;

    void FijarColorJugador( const string& nuevoColor );
    void FijarNumUnidades( int nuevoNum );
    void AgregarUnidades( int cantidad );
    void QuitarUnidades( int cantidad );

    bool EsVecinoDe( const string& codigoOtroTerritorio ) const;

private:
    string codigo;
    string continente;
    string colorJugador;
    int numUnidades;
    vector<string> vecinos;
};

#endif