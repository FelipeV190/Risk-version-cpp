#ifndef EJECUCION_H
#define EJECUCION_H

#include <string>
#include "Partida.h"

using namespace std;

void ejecutar_inicializar( Partida& partida, const string& archivo );
void ejecutar_obtener_unidades( Partida& partida, const string& nombreJugador );
void ejecutar_atacar( Partida& partida, const string& nombreJugador );
void ejecutar_fortificar( Partida& partida, const string& nombreJugador );
void ejecutar_estado_juego( const Partida& partida );

int interpretar_contenido_inicio( const string& contenido, Partida& partida );
void ejecutar_guardar( const Partida& partida, const string& nombreArchivo );
void ejecutar_guardar_comprimido( const Partida& partida, const string& nombreArchivo );

void ejecutar_costo_conquista( Partida& partida, const string& nombreJugador,
                               const string& territorio );
void ejecutar_conquista_mas_barata( Partida& partida, const string& nombreJugador );

#endif