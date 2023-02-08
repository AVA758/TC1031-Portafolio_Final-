/** 
* Nombres de los integrantes:
* Alain Vicencio Arizabalo A01620758
* Julian Andres Gonzalez Arguello A00831514
*  
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/

#include "Registro.h"
#include "MaxHeap.h"
#include "IP.h"
#include <iostream>
#include <fstream>
#include "Bitacora.h"
#include <sstream>
#include <string.h>


int main() {

  // Llamar mi Bitacora para pasar los datos de el archivo de texto de string a valores numericos unix timestamp y guardarlos en un vector
  Bitacora miBitacora("bitacoraHeap.txt");

  miBitacora.heapSort();
  miBitacora.printHeapSort();

  miBitacora.contIpRep();

  
 
}