#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"
#include "MaxHeap.h"
#include "IP.h"


class Bitacora {
  private:
    std::vector<Registro> listaRegistros;

    void heapify(int N, int i);

    MaxHeap<IP> MayoresIPs;
    

  public:
    Bitacora();
    Bitacora(std::string fileName);
    ~Bitacora();
    
    //Impresión
    void print();
    void printHeapSort();

    // Ordenamiento 
    void heapSort();

    // Conteo de IP repetidas
    void contIpRep();


};


#endif  // _BITACORA_H_