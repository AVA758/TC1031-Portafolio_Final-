/** 
* Codigo base recuperado como fork de la Asesoria de la - 
* Actividad 4.3 (integral de grafos)
*
* Nombres de los integrantes:
* Alain Vicencio Arizabalo A01620758
* Julian Andres Gonzalez Arguello A00831514
*
* Compilacion para debug:  
*    g++ -std=c++17 -Wall -g -o main *.cpp 
*
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main 
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -Wall -O3 -o main *.cpp 
* Ejecucion:
*    ./main 
**/

#include <iostream>
#include "Graph.h"

int main() {
  Graph graph;

  graph.loadGraph("bitacoraGrafos.txt");

  graph.gradosIPs();
  
  graph.cincoMayores();

  return 0;
}