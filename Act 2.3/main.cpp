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
#include "DLinkedList.h"
#include "Registro.h"
#include "DLLNode.h"


//Main
int main () {

  // Llamar mi Bitacora para pasar los datos de el archivo de texto de string a valores numericos unix timestamp y guardarlos en un vector
  
  Bitacora miBitacora("bitacora.txt");
  
  unsigned int comparaciones, swaps = 0;
  
  // Utilizacion de algoritmos de ordenamiento para ordenar el vector. Método Quick Sort
  miBitacora.quickSort(comparaciones, swaps);
  miBitacora.printQuickSort(comparaciones, swaps);

  // Creación de 2da bitácora para aplicar el Merge Sort
  Bitacora miBitacora2("bitacora.txt");

  // Método Merge Sort
  unsigned int comparaciones2 = 0;
  miBitacora2.mergeSort(comparaciones2);
  miBitacora2.printMergeSort(comparaciones2);
  

  // Pedir valores para la Busqueda
  std::string mes, dia, hora, minutos, segundos;

  std::cout << "Ingrese la primera fecha de búsqueda en formato:" << std::endl;
  std::cout << "Mes Día Hora Minuto Segundos " << std::endl; 
  std::cout << "Ejemplo." << std::endl;
  std::cout << "Jun 27 03 10 10" << std::endl;
  std::cout << std::endl;
  std::cout << "Ingresa fecha: " << std::endl;
  std::cin >> mes >> dia >> hora >> minutos >> segundos;
  Registro key1(mes, dia, hora, minutos, segundos, "", "", "");

  std::cout << std::endl;
  std::cout << "Ingrese la segunda fecha de búsqueda en formato:" <<  std::endl;
  std::cout << "Mes Día Hora Minuto Segundos " << std::endl; 
  std::cout << "Ejemplo." << std::endl;
  std::cout << "Jun 29 04 11 03" << std::endl;
  std::cout << std::endl;
  std::cout << "Ingresa fecha: " << std::endl;
  std::cin >> mes >> dia >> hora >> minutos >> segundos;
  Registro key2(mes, dia, hora, minutos, segundos, "", "", "");


  // Algoritmo de Busqueda 
  miBitacora.realizarBusqueda(key1, key2);
  
}
