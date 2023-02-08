 #ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "DLLNode.h"
  
template <class T>
class DLinkedList {
  private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;

  public:
    DLinkedList();
    ~DLinkedList();
    int getNumElements();
    void printList();
    void addFirst(T value);
    void addLast(T value);
    T getData(int position);
    int findData(T value);


    // Ordenamiento Quick Sort
    void sort(unsigned int &comparaciones, unsigned int &swaps);
    void quickSort(DLLNode<T> *l, DLLNode<T> *h, unsigned int &comparaciones, unsigned int &swaps);
    DLLNode<T> *partition(DLLNode<T> *left, DLLNode<T> *right, unsigned int &comparaciones, unsigned int &swaps);

    // Ordenamiento Merge Sort
    void doMerge(unsigned int &comparaciones2);
    DLLNode<T> * merge(DLLNode<T> *first, DLLNode<T> *second, unsigned int &comparaciones2);
    DLLNode<T> * mergeSort(DLLNode<T> *head,unsigned int &comparaciones2);
    DLLNode<T> * split(DLLNode<T> *head);

    // Búsqueda Binaria
    DLLNode <T> * middle(DLLNode<T>* start, DLLNode<T>* last);
    DLLNode <T> * binarySearch(DLLNode<T>* head, T value);
    int doBinary(T value);


};

// Constructor de la clase DLinkedList
// Complejidad: O(1)
template <class T>
DLinkedList<T>::DLinkedList() {
  std::cout << "---> Creando una lista ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Destructor de la clase DLinkedList
// Complejidad: O(n)
template<class T>
DLinkedList<T>::~DLinkedList() {
  std::cout << "---> Liberando memoria de la lista ligada: " << this << std::endl;
  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Get Num Elements
// Obtener el numero de elementos de la lista doblemente ligada.
// Complejidad: O(1)
template <class T> 
int DLinkedList<T>::getNumElements() {
  return numElements;
}

// Print List
// Imprimir la lista.
// Complejidad: O(n)
template<class T>
void DLinkedList<T>::printList() {
  DLLNode<T> *ptr = head;
  while (ptr != nullptr) {
      std::cout << ptr->data << std::endl;
      ptr = ptr->next;
  }
  std::cout << std::endl;
}

// Add First
// Agregar un nuevo valor al inicio de la lista.
// Complejidad: O(1)
template <class T> 
void DLinkedList<T>::addFirst(T value) {
  // crea un nuevoNodo
  DLLNode<T> *newNode = new DLLNode<T>(value);
  // Si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    head = newNode;
    tail = newNode;
  }
  else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  numElements++;
}

// Add Last
// Agregar un nuevo valor al final de la lista.
// Complejidad: O(1)
template <class T> 
void DLinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    addFirst(value);
  }
  else {
    // 1. crea un nuevoNodo
    DLLNode<T> *newNode = new DLLNode<T>(value);
    // 2. apunto tail->next a el nuevoNodo
    tail->next = newNode;
    newNode->prev = tail;
    // 3. Actualizo tail para que apunte al nuevoNodo
    tail = newNode;
    numElements++;
  }
}


// Get Data
// Regresa el valor almacenado en un nodo de una determinada posicion.
// Complejidad: O(n)
template <class T> 
T DLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else {
    if (position == 0) { // si es el primero de la lista
      return head->data;
    }
    // debemos buscar el elemento
    DLLNode<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (p != nullptr) {
      if (index == position)
        return p->data;
      p = p->next;
      index++;
    }
    return {};
  }
}


// findData
// Busca un elemento en la lista.
// Complejidad: O(n)
template <class T> 
int DLinkedList<T>::findData(T value){
  int pos = 0;
    DLLNode<T> *ite = head;
    while (ite != nullptr) {
        if (ite -> data == value) {
            return pos;
        }
        pos++;
        ite = ite -> next;
    }
    return -1;
}


//Quick Sort
// Ordena los datos de la lista usando el algoritmo quicksort.
// Referencia: Esta función se implementó con apoyo de la página de GeeksforGeeks.
// Sin autor. (2023). QuickSort on Doubly Linked List. GeeksforGeeks. Recuperado de https://www.geeksforgeeks.org/quicksort-for-linked-list/ 
//
// Complejidad: O(1) en quickSort y O(n) en partition
// Complejidad total: O(n^2) peor caso y O(nLogn) promedio
template <class T>
void DLinkedList<T>::sort(unsigned int &comparaciones, unsigned int &swaps){
  quickSort(head,tail, comparaciones, swaps);
}

template <class T>
void DLinkedList<T>::quickSort(DLLNode<T> *head, DLLNode<T> *tail, unsigned int &comparaciones, unsigned int &swaps){
  if (tail != nullptr && head != tail && head != tail->next) {
    DLLNode<T> *p = partition(head, tail, comparaciones, swaps);
    quickSort(head, p->prev, comparaciones, swaps);
    quickSort(p->next, tail, comparaciones, swaps);
  }
}

// Funcion implementada en el metodo quick sort para seleccionar el pivote y partir los elementos. 
template <class T>
DLLNode<T> * DLinkedList<T>::partition(DLLNode<T> *head, DLLNode<T> *tail, unsigned int &comparaciones, unsigned int &swaps) {  
  T x = tail->data;
  DLLNode<T> *i = head->prev;
  
  for(DLLNode<T> *j = head; j != tail; j=j->next){
    if(j->data <= x){
      i = (i == nullptr)? head : i->next;
      std::swap((i->data), (j->data));
      swaps++;
    }
    comparaciones++;
  }
  
  i = (i == nullptr)? head : i->next; 
  std::swap(i->data, tail->data);
  swaps++;
  return i;
}



// Merge Sort
// Ordena la doubly linked list en orden ascendiente al dividir la lista en listas pequeñas y ordenar al juntarlas.
// Referencia: Esta función se implementó con apoyo de la página de GeeksforGeeks.
// Sin autor. (2023). Merge Sort for Doubly Linked List. GeeksforGeeks. Recuperado de https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
// Complejidad: O(nLogn)
template <class T>
void DLinkedList<T>::doMerge(unsigned int &comparaciones2){
  mergeSort(head, comparaciones2);
}

// Implementacion recursiva del algoritmo merge sort con la funcion de merge a continuacion.
// Complejidad: O(nLogn)
template <class T>
DLLNode<T> * DLinkedList<T>::mergeSort(DLLNode<T> *head, unsigned int &comparaciones2){
  if (!head || !head->next) return head; 

  DLLNode<T> *second = split(head); 

  head = mergeSort(head, comparaciones2); 
  second = mergeSort(second, comparaciones2); 

  return merge(head,second, comparaciones2); 
}

//  La función compara los elementos en la lista y los combina en una sola lista ordenada para ordenar.
// Complejidad: O(nLogn)
template <class T>
DLLNode<T> * DLinkedList<T>::merge(DLLNode<T> *first, DLLNode<T> *second, unsigned int &comparaciones2){
  if (!first) return second; 

  if (!second) return first; 

  if (first->data < second->data) { 
    comparaciones2++;
    first->next = merge(first->next,second, comparaciones2); 
    first->next->prev = first; 
    first->prev = nullptr; 
    return first; 
  } 
  else{ 
      comparaciones2++;
      second->next = merge(first,second->next, comparaciones2); 
      second->next->prev = second; 
      second->prev = nullptr; 
      return second; 
  } 
}

// Dividir la lista en dos
// Complejidad: O(n)
template <class T>
DLLNode <T> * DLinkedList<T>::split(DLLNode<T> *head){
  DLLNode<T> *fast = head,*slow = head; 
  
  while (fast->next && fast->next->next) { 
      fast = fast->next->next; 
      slow = slow->next; 
  } 
  
  DLLNode<T> *temp = slow->next; 
  slow->next = nullptr; 
  return temp;
}


// Busqueda Binaria.
// Referencia: Esta función se implementó con apoyo de la página de GeeksforGeeks que proporciono la busqueda binaria para una singly linked list, se transformó para ser usada en una doubly.
// Sin autor. (2023). Binary search on singly linked list. GeeksforGeeks. https://www.geeksforgeeks.org/binary-search-on-singly-linked-list/
// Complejidad: O(logn)
template <class T>
DLLNode<T>* DLinkedList<T>::middle(DLLNode<T>* start, DLLNode<T>* last) {
    if (start == nullptr)
        return nullptr;
  
    DLLNode<T>* slow = start;
    DLLNode<T>* fast = start->next;
  
    while (fast != last) {
        fast = fast->next;
        if (fast != last) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}

// Binary Search
// Realizar una busqueda binarai en una lista doblemente ligada, llamando la funcion middle para encotrar el nodo medio.
// Complejidad: O(log n)
template <class T>
DLLNode<T>* DLinkedList<T>::binarySearch(DLLNode<T>* head, T value) {
    DLLNode<T>* start = head;
    DLLNode<T>* last = nullptr;
  
    while (start != last) {
        DLLNode<T>* mid = middle(start, last);
        if (mid == nullptr)
            return nullptr;
        if (mid->data == value)
            return mid;
        else if (mid->data < value)
            start = mid->next;
        else
            last = mid;
    }
  
    return nullptr;
}

// Llamada para implementar la busqueda binaria.
template <class T>
int DLinkedList<T>::doBinary(T value){
    DLLNode<T>* result = binarySearch(head, value);
  
    if(result != nullptr) 
      return findData(result->data);
    
    else
      return -1;
}

#endif // _DLINKEDLIST_H_
