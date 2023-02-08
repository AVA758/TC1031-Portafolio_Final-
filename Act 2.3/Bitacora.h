#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"
#include "DLinkedList.h"

class Bitacora {
  private:
    DLinkedList<Registro> listaRegistros;
    // DLinkedList<Registro> listaRegistros;    

  public:
    Bitacora();
    Bitacora(std::string fileName);
    ~Bitacora();
    
    //Impresión
    void print();
    void printQuickSort(unsigned int comparaciones, unsigned int swaps);
    void printMergeSort(unsigned int comparaciones2);

    // Ordenamiento
    void quickSort(unsigned int &comparaciones, unsigned int &swaps);
    void mergeSort(unsigned int &comparaciones2);

    void invertir();

    // Busqueda
    int busquedaBinaria(Registro key);
    void realizarBusqueda (Registro key1, Registro key2);  

};

#endif  // _BITACORA_H_