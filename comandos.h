#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <vector>

using namespace std;

const int TP_LIBRE           = 0;
const int TP_NOMBRE_JUGADOR  = 1;
const int TP_ARCHIVO_INICIO  = 2;
const int TP_ARCHIVO_DESTINO = 3;
const int TP_TERRITORIO      = 4;

struct ComandoInfo
{
  string nombre;
  int min_parametros;
  int max_parametros;
  string uso;
  string descripcion;
  vector<int> tipos_parametros;
};
vector<ComandoInfo> obtener_tabla_comandos();

bool buscar_comando( const string& nombre, ComandoInfo& info );

vector<string> separar_en_tokens( const string& linea );

bool validar_formato_parametro( int tipo, const string& valor, string& motivo );

bool validar_parametros( const ComandoInfo& info, const vector<string>& parametros,string& motivo );
#endif
