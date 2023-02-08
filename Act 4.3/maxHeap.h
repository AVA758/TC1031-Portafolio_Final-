#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <vector>
#include <iostream>
#include <stdexcept>

template <class T>
class MaxHeap {
  private:
    // contiene los elementos del heap
    std::vector<T> data;
    // capacidad maxima del heap
    int maxSize;
    // tamano actual del heap
    int currentSize;
    int parent(int k);
    int left(int k);
    int right(int k);

  public:
    MaxHeap();
    MaxHeap(int capacity);
    ~MaxHeap();
    bool isEmpty();
    int getCapacity();
    void setCapacity(int _maxSize);
    int getCurrentSize();
    void print();
    void push(T key);
    T top();

    int size();
    // TO-DO
    void pop();

};

// Complejidad: O(1)
template <class T>
MaxHeap<T>::MaxHeap() {
  maxSize = 0;
  currentSize = 0;
  data.resize(maxSize);
}

// Complejidad: O(n)
template <class T>
MaxHeap<T>::MaxHeap(int capacity) {
  maxSize = capacity;
  currentSize = 0;
  data.resize(maxSize);
}

// Complejidad: O(1)
template <class T>
MaxHeap<T>::~MaxHeap() {
  maxSize = 0;
  currentSize = 0;
  data.clear();
}


// isEmpty
// Dice si el maxHeap está vacío o no
// Complejidad: O(1)
template <class T>
bool MaxHeap<T>::isEmpty() {
  return (currentSize <= 0);
}


// getcapacity
// Despliega la capacidad del maxHeap
// Complejidad: O(1)
template <class T>
int MaxHeap<T>::getCapacity() {
  return maxSize;
}


// setCapacity 
// Setter, a comando, reestablece el tamaño del heap.
// Funcion recuperada de la asesoria dada por el profesor el 
// 31 de enero
// Complejidad: O(n)
template <class T>
void MaxHeap<T>::setCapacity(int _maxSize) {
  maxSize = _maxSize;
  currentSize = 0;
  data.resize(maxSize);
}

// getCurrentSize
// Depliega el tamaño actual del maxHeap
// Complejidad: O(1)
template <class T>
int MaxHeap<T>::getCurrentSize() {
  return currentSize;
}

// print
// Imprime el heap
// Complejidad: O(n)
template <class T>
void MaxHeap<T>::print() {
  std::cout << "Contenido del maxheap:" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}


// parent
// Obtiene el nodo padre de un nodo.
// Complejidad: O(1)
template <class T>
int MaxHeap<T>::parent(int k) {
  return (k-1)/2;
}


// left
// Obtiene el hijo de la izquierda de un nodo.
// Complejidad: O(1)
template <class T>
int MaxHeap<T>::left(int k) {
  return (2*k + 1);
}


// right
// Obtiene el hijo de la derecha de un nodo.
// Complejidad: O(1)
template <class T>
int MaxHeap<T>::right(int k) {
  return (2*k + 2);
}


// push
// Mete valores del tipo T al heap para luego acomodarlos 
// de mayor a menor.
// Complejidad: O(log n)
template <class T>
void MaxHeap<T>::push(T key) {
  if (currentSize == maxSize) {
    throw std::out_of_range("Overflow: no se puede insertar la llave");
  }
  // Insertamos la nueva llave al final del vecor
  int k = currentSize;
  data[k] = key;
  currentSize++;
  // Reparar las propiedades del maxheap si son violadas
  while (k != 0 && data[parent(k)] < data[k]) {
    std::swap(data[k], data[parent(k)]);
    k = parent(k);
  }
}


// Top
// Desplega el primer elemento del heap.
// Complejidad: O(1)
template <class T>
T MaxHeap<T>::top() {
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    return {};
  }
  return data[0];
}


// Pop
// Elimina el maximo elemento del max heap
// Proceso de filtrado hacia abajo basado en la funcion heapify utilizada en Bitacora.cpp recuperada de Geek for Geeks C++ program for heap sort
// Complejidad: O(log n)
template <class T>
void MaxHeap<T>::pop() {
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    return;
  }

  data[0] = data[currentSize - 1];
  currentSize--;

  int k = 0;
  while (left(k) < currentSize) {
    int j = left(k);
    if (j + 1 < currentSize && data[j + 1] > data[j]) {
      j = right(k);
    }
    if (data[k] >= data[j]) {
      break;
    }
    std::swap(data[k], data[j]);
    k = j;
  }
}

#endif // _MAXHEAP_H_