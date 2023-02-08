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
#include <iostream>
#include <fstream>
#include "Bitacora.h"


//Main
int main () {

  // Llamar mi Bitacora para pasar los datos de el archivo de texto de string a valores numericos unix timestamp y guardarlos en un vector
  Bitacora miBitacora("bitacora.txt");
  
  unsigned int comparaciones, swaps = 0;
  
  // Utilizacion de algoritmos de ordenamiento para ordenar el vector
  miBitacora.bubbleSort(comparaciones, swaps);
  miBitacora.printBubbleSort(comparaciones, swaps);

  Bitacora miBitacora2("bitacora.txt");
  
  unsigned int comparaciones2 = 0;
  miBitacora.doMergeSort(comparaciones2);
  miBitacora.printMergeSort(comparaciones2);
  

  // Pedir valores para la Busqueda
  std::string mes, dia, hora, minutos, segundos;

  std::cout << "Ingrese la primera fecha de búsqueda en formato Mes Día Hora Minuto Segundos " << std::endl;
  std::cin >> mes >> dia >> hora >> minutos >> segundos;
  Registro key1(mes, dia, hora, minutos, segundos, "", "", "");

  std::cout << "Ingrese la segunda fecha de búsqueda en formato Mes Día Hora Minuto Segundos " << std::endl;
  std::cin >> mes >> dia >> hora >> minutos >> segundos;
  Registro key2(mes, dia, hora, minutos, segundos, "", "", "");



  // Algoritmo de Busqueda 


  miBitacora.realizarBusqueda(key1, key2);
  
// imprimir posicion de la busqueda 1 hasta la busqueda 2 directo del archivo de texto

}
