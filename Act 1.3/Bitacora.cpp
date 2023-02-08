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

void Bitacora::printBubbleSort(unsigned int comparaciones, unsigned int swaps) {
  std::ofstream myfile;
  myfile.open("bitacoraOrdenadaBubble.txt");
  myfile << "Usando el BUBBLE SORT, la bitacora contiene lo siguiente:" << std::endl << "\n";
  myfile << "Comparaciones: " << comparaciones << std::endl;
  myfile << "Swaps: " << swaps << std::endl << "\n";
  for (int i=0; i < listaRegistros.size(); i++)
    myfile << listaRegistros[i].getAll() << std::endl;
  myfile.close();
}

void Bitacora::printMergeSort(unsigned int comparaciones2) {
  std::ofstream myfile;
  myfile.open("bitacoraOrdenadaMerge.txt");
  myfile << "Usando el MERGE SORT, la bitacora contiene lo siguiente:" << std::endl << "\n";
  myfile << "Comparaciones: " << comparaciones2 << std::endl << "\n";
  for (int i=0; i < listaRegistros.size(); i++)
    myfile << listaRegistros[i].getAll() << std::endl;
  myfile.close();
}


// // Ordena Burbuja
// Ordenar vector en forma ascendente comparando elementos adyacentes y cambiandolos de lugar, como burbujas. 
// Complejidad: O(n^2) (peor caso)
void Bitacora::bubbleSort(unsigned int &comparaciones, unsigned int &swaps) {
  int i, j;
  int n = listaRegistros.size();
  comparaciones = swaps = 0;
  for (i = 0; i < n-1; i++) {
    for (j = 0; j < n-i-1; j++) {
      comparaciones++;
      if (listaRegistros[j] > listaRegistros[j+1]){
        std::swap(listaRegistros[j], listaRegistros[j+1]);
        swaps++;
      }
    }
  }
}

// Ordena Merge
// Ordena arreglo en forma ascendente recursivamente dividiendo el problema en subproblemas de menor tamano.
// Complejidad: O(n log n) (peor caso)
void Bitacora::mergeSort(int low, int high, unsigned int &comparaciones){
   if (low < high) {
    // encontrar el punto medio
    int m = low + (high - low) / 2;
    // Ordenar dos mitades
    mergeSort(low, m, comparaciones);
    mergeSort(m+1, high, comparaciones);
    // Fusionar ambas mitades
    merge(low, m, high, comparaciones);
  }
}

// Merge
// Parte llamada recursivamente del metodo Merge Sort
// Complejidad: O(n)

void Bitacora::merge(int low, int m, int high, unsigned int &comparaciones){
  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m;
  // crear los vectores auxiliares L y R
  std::vector<Registro> L(n1);
  std::vector<Registro> R(n2);
  for (i = 0; i < n1; i++) L[i] = listaRegistros[low + i];
  for (j = 0; j < n2; j++) R[j] = listaRegistros[m + 1 + j];
  // Fusionar los vectores auxiliares Ly R ordenados
  i = j = 0;
  k = low;
  while (i<n1 && j<n2) {
    comparaciones++;
    if (L[i] <= R[j]){
      listaRegistros[k]=L[i];
      i++;
    }
    else{
      listaRegistros[k] = R[j];
      j++;
    }
    k++;
  }
  // Copia los elementos restantes
  while (i < n1){
    listaRegistros[k] = L[i];
    i++;
    k++;
  }
  while (j < n2){
    listaRegistros[k] = R[j];
    j++;
    k++;
  }
}

void Bitacora::doMergeSort(unsigned int &comparaciones) {
  mergeSort(0, listaRegistros.size()-1, comparaciones);
}

// Busqueda Binaria
// Algoritmo de buscamiento que funciona teniendo una llave y comparandola con las dos mitades del arreglo.
// Complejidad: O(log n) (peor caso)

int Bitacora::busquedaBinaria(Registro key) {
  int low = 0;
  int high = (int)listaRegistros.size()-1;
  int mid = 0;
  while(low <= high) {
    mid = (low + high)/2;
    if (key == listaRegistros[mid]) {
      return mid;
    } else if (key < listaRegistros[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}


void Bitacora::realizarBusqueda(Registro key1, Registro key2){
   // pedir al usiario las dos fechas
  //key1 = registro1
  //key2 = registro2
  int pos1 = busquedaBinaria(key1);
  int pos2 = busquedaBinaria(key2);
  if (pos1 != -1 && pos2 != -1) {
    std::cout << "\n" << "fecha 1: " << key1.getAll() << std::endl;
    std::cout << "fecha 2: " << key2.getAll() << std::endl << "\n";

    std::cout << "Resultado: " << (pos2-pos1)+1 << " Registros" << std::endl;
    for (int i = pos1; i <= pos2; i++)
      std::cout << listaRegistros[i].getAll() << std::endl;
  }
  else{
    std::cout << "No se pudo encontrar el registro que ingresó" << std::endl;
  }
}
