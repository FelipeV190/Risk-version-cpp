#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>
#include <list>
#include <utility>

using namespace std;

const int COSTO_INFINITO = 2147483647;

struct NodoDijkstra
{
  int vertice;
  int padre;
  int costo;
};

class Grafo
{
public:
  Grafo();

  int CantidadVertices() const;

  bool InsertarVertice( const string& territorio );

  bool InsertarArista( const string& origen, const string& destino, int unidades );

  int BuscarVertice( const string& territorio ) const;
  string ObtenerVertice( int indice ) const;

  bool Dijkstra( const string& origen, vector<int>& dist, vector<int>& pred ) const;

  vector<int> ReconstruirRuta( const vector<int>& pred, int destino ) const;

private:
  vector<string> vertices;
  vector< list< pair<int, int> > > aristas;
};

#endif
