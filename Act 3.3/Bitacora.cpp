#include "Bitacora.h"


Bitacora::Bitacora() {

}

Bitacora::Bitacora(std::string fileName) {
  std::string month, day, hours, minutes, seconds, ipAdd, port, error;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while (!file.eof()) {
        std::getline(file, month, ' ');
        std::getline(file, day, ' ');
        std::getline(file, hours, ':');
        std::getline(file, minutes, ':');
        std::getline(file, seconds, ' ');
        std::getline(file, ipAdd, ':');
        std::getline(file, port, ' ');
        std::getline(file, error);
        // Crear un objeto de la clase Registro
        Registro tmpRegistro(month, day, hours, minutes, seconds, ipAdd, port, error);
        // Agregar al vector de regisrros
        listaRegistros.push_back(tmpRegistro);
      }
    file.close();
  }
}

Bitacora::~Bitacora() {
  listaRegistros.clear();
}

void Bitacora::print() {
  std::cout << "La bitacora contiene lo siguiente:" << std::endl;
  for (int i=0; i < listaRegistros.size(); i++)
    std::cout << listaRegistros[i].getAll() << std::endl;
}

void Bitacora::printHeapSort() {
  std::ofstream myfile;
  myfile.open("bitacoraOrdenada.txt");
  myfile << "Usando el Heap SORT, ordenando por dirección IP la bitacora contiene lo siguiente:" << std::endl << "\n";
  
  for (int i=0; i < listaRegistros.size(); i++)
    myfile << listaRegistros[i].getAll() << std::endl;
  myfile.close();
}



// Heapify
// Ordena un vector con el algoritmo heap sort al comparar un nodo con su hijo izquierdo y su hijo derecho
// Código obtenido de la implementacion de Heap Sort en Geek for Geeks.
// Referencia: Geek for Geeks. (2022). C++ Program for Heap Sort. Recuperado de: https://www.geeksforgeeks.org/cpp-program-for-heap-sort/
// Complejidad: O(nlogn)
void Bitacora::heapify(int n, int i)
{
    int largest = i; // Initialize largest as root Since we are using 0 based indexing
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && listaRegistros[l] > listaRegistros[largest]) 
      largest = l;
 
    // If right child is larger than largest so far
    if (r < n && listaRegistros[r] > listaRegistros[largest])
      largest = r;
 
    // If largest is not root
    if (largest != i) {
        std::swap(listaRegistros[i], listaRegistros[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(n, largest);
    }
}

// Heap Sort
// Código obtenido de la implementacion de Heap Sort en Geek for Geeks.
// Referencia: Geek for Geeks. (2022). C++ Program for Heap Sort. Recuperado de: https://www.geeksforgeeks.org/cpp-program-for-heap-sort/
// Complejidad: O(nlogn)
void Bitacora::heapSort()
{
    int n = listaRegistros.size()-1;
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);
 
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(listaRegistros[0], listaRegistros[i]);
 
        // call max heapify on the reduced heap
        heapify(i, 0);
    }
}


// Conteo de Repeticiones de IP
// Obtenida de la Asesoria publicada en 31 de enero por el profesor
// Complejidad: O(n)
void Bitacora::contIpRep(){
  std::ofstream myfile;
  myfile.open("ips_con_mayor_acceso.txt");
  
  int cont = 1;
  MayoresIPs.setCapacity(listaRegistros.size());
  for (int i = 0; i < listaRegistros.size(); i++){
    if (listaRegistros[i] == listaRegistros[i+1]) {
      cont++;
    }
    else{
      IP tmp(listaRegistros[i].getIp(), cont);
      MayoresIPs.push(tmp);
      cont = 1;      
    }
  }
    for (int i = 0; i < 5; i++) {
      myfile << MayoresIPs.top() << std::endl; 
      MayoresIPs.pop();
    }

  myfile.close();
}

