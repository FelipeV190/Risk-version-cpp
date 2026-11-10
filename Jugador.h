#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "Carta.h"

using namespace std;

const int FASE_INICIO             = 0;
const int FASE_UNIDADES_OBTENIDAS = 1;
const int FASE_ATAQUE_TERMINADO   = 2;

class Jugador
{
public:
    Jugador();
    Jugador( const string& nombreInicial, const string& colorInicial );

    string ObtenerNombre() const;
    string ObtenerColor() const;
    int ObtenerFase() const;
    void FijarFase( int nuevaFase );

    void AgregarCarta( const Carta& carta );
    void QuitarCartas( const vector<int>& indices );
    int ObtenerNumCartas() const;
    const Carta& ObtenerCarta( int indice ) const;
    bool TieneCombinacionValida() const;

private:
    string nombre;
    string color;
    int fase;
    vector<Carta> cartas;
};

#endif