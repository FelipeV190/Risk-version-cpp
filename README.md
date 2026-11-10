# Risk version C++

Implementación en C++ del juego **Risk** por consola.

## Características
- Gestión de jugadores, territorios, cartas y tablero.
- Comandos de juego: `inicializar`, `atacar`, `fortificar`, `estado_juego`, `salir`, `ayuda`.
- Guardado de partidas en texto (`guardar`) y comprimido con **codificación Huffman** (`guardar_comprimido`).
- Análisis sobre el **grafo** de territorios: `costo_conquista` y `conquista_mas_barata`.

## Compilación
```bash
g++ -std=c++11 -o risk *.cxx
```

## Ejecución
```bash
./risk
```
Escribe `ayuda` dentro del programa para ver todos los comandos disponibles.
