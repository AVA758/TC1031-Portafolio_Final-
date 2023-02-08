#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"


class Bitacora {

  private:
    std::vector<Registro> listaRegistros;
    // DLinkedList<Registro> listaRegistros;
    
    void merge(int low, int m, int high, unsigned int &compara);

  public:
    Bitacora();
    Bitacora(std::string fileName);
    ~Bitacora();
    
    //Impresión
    void print();
    void printBubbleSort(unsigned int comparaciones, unsigned int swaps);
    void printMergeSort(unsigned int comparaciones2);

    // Ordenamiento
    void bubbleSort(unsigned int &comparaciones, unsigned int &swaps);
    void mergeSort(int low, int high, unsigned int &comparaciones);
    void doMergeSort(unsigned int &comparaciones);

    // Busqueda
    int busquedaBinaria(Registro key);
    void realizarBusqueda (Registro key1, Registro key2);  
};


#endif  // _BITACORA_H_