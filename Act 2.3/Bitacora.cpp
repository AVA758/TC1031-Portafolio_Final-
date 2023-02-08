#include "Bitacora.h"
#include "DLinkedList.h"

// Constructor
Bitacora::Bitacora() { }

// Constructor
// Plantea el formato que tendrá la información de
// la bitácora
// Complejidad: O(n)
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
        listaRegistros.addLast(tmpRegistro);
      }
    file.close();
  }
}

// Destructor
Bitacora::~Bitacora() {
  listaRegistros.~DLinkedList();
}

// printQuickSort
// Función crea/abre archivo de texto e imprime la 
// lista de los registros en orden directo basado en
// el ordenamiento Quick Sort previamente hecho.
// Complejidad: O(n)
void Bitacora::printQuickSort(unsigned int comparaciones, unsigned int swaps) {
  std::ofstream myfile;
  myfile.open("bitacora_ordenada_quickSort.txt");
  myfile << "Usando el QUICK SORT, la bitacora contiene lo siguiente:" << std::endl << "\n";
  myfile << "Comparaciones: " << comparaciones << std::endl;
  myfile << "Swaps: " << swaps << std::endl << "\n";
  for (int i=0; i < listaRegistros.getNumElements(); i++)
    myfile << listaRegistros.getData(i).getAll() << std::endl;
  myfile.close();

  //En pantalla
  std::cout << std::endl;
  std::cout << "Ordenamiento Quick." << std::endl;
  std::cout <<  "Usando el Quick SORT, la bitacora contiene lo siguiente:" << std::endl << "\n";
  std::cout << "Comparaciones: " << comparaciones << std::endl;
  std::cout << "Swaps: " << swaps << std::endl << "\n";
}

// printMergeSort
// Función crea/abre archivo de texto e imprime la 
// lista de los registros en orden directo basado en
// el ordenamiento Merge Sort previamente hecho.
void Bitacora::printMergeSort(unsigned int comparaciones2) {
  std::ofstream myfile;
  myfile.open("bitacora_ordenada_mergeSort.txt");
  myfile << "Usando el MERGE SORT, la bitacora contiene lo siguiente:" << std::endl << "\n";
  myfile << "Comparaciones: " << comparaciones2 << std::endl << "\n";
  for (int i=0; i < listaRegistros.getNumElements(); i++)
    myfile << listaRegistros.getData(i).getAll() << std::endl;
  myfile.close();

  //En pantalla
  std::cout << std::endl;
  std::cout << "Ordenamiento Merge." << std::endl;
  std::cout << "Usando el MERGE SORT, la bitacora contiene lo siguiente:" << std::endl << "\n";
  std::cout << "Comparaciones: " << comparaciones2 << std::endl << "\n";
}



// Ordena Merge
// Ordena arreglo en forma ascendente recursivamente dividiendo el problema en subproblemas de menor tamano.
// Complejidad: O(n log n) (peor caso)
void Bitacora::mergeSort(unsigned int &comparaciones2){
  listaRegistros.doMerge(comparaciones2);
}



// Ordena Quick
// Ordena arreglo en forma ascendente haciendo 
// comparaciones 
void Bitacora::quickSort(unsigned int &comparaciones, unsigned int &swaps){
  listaRegistros.sort(comparaciones, swaps);
}


// Busqueda Binaria
// Algoritmo de buscamiento que funciona teniendo una llave y comparandola con las dos mitades del arreglo.
// Complejidad: O(log n) (peor caso)

int Bitacora::busquedaBinaria(Registro key) {
  return listaRegistros.doBinary(key);
}


void Bitacora::realizarBusqueda(Registro key1, Registro key2){
   // pedir al usiario las dos fechas
  //key1 = registro1
  //key2 = registro2
  int pos1 = busquedaBinaria(key1);
  int pos2 = busquedaBinaria(key2);
  std::ofstream myfile;
  myfile.open("resultado_busqueda.txt");
  if (pos1 != -1 && pos2 != -1) {
    myfile << "fecha 1: " << key1.getAll() << std::endl;
   myfile << "fecha 2: " << key2.getAll() << std::endl << "\n";

    myfile << "Resultado: " << (pos2-pos1)+1 << " Registros" << std::endl;
    for (int i = pos1; i <= pos2; i++)
      myfile << listaRegistros.getData(i).getAll() << std::endl;
  }
  else{
    myfile << "No se pudo encontrar el registro que ingresó" << std::endl;
    
  }
  myfile.close();
}

