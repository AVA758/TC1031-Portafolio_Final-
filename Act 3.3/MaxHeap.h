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

template <class T>
MaxHeap<T>::MaxHeap() {
  maxSize = 0;
  currentSize = 0;
  data.resize(maxSize);
}

template <class T>
MaxHeap<T>::MaxHeap(int capacity) {
  maxSize = capacity;
  currentSize = 0;
  data.resize(maxSize);
}

template <class T>
MaxHeap<T>::~MaxHeap() {
  maxSize = 0;
  currentSize = 0;
  data.clear();
}

template <class T>
bool MaxHeap<T>::isEmpty() {
  return (currentSize <= 0);
}

template <class T>
int MaxHeap<T>::getCapacity() {
  return maxSize;
}

template <class T>
void MaxHeap<T>::setCapacity(int _maxSize) {
  maxSize = _maxSize;
  currentSize = 0;
  data.resize(maxSize);
}

template <class T>
int MaxHeap<T>::getCurrentSize() {
  return currentSize;
}

template <class T>
void MaxHeap<T>::print() {
  std::cout << "Contenido del maxheap:" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}
  
template <class T>
int MaxHeap<T>::parent(int k) {
  return (k-1)/2;
}

template <class T>
int MaxHeap<T>::left(int k) {
  return (2*k + 1);
}

template <class T>
int MaxHeap<T>::right(int k) {
  return (2*k + 2);
}

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

template <class T>
T MaxHeap<T>::top() {
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    return {};
  }
  return data[0];
}

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