#ifndef _DLLNODE_H_
#define _DLLNODE_H_

template <class T>
class DLLNode {
  public:
    T data;
    DLLNode<T> *next;
    DLLNode<T> *prev;
    DLLNode();
    DLLNode(T value);
};

// Constructor
template <class T>
DLLNode<T>::DLLNode() : data{}, next{nullptr}, prev{nullptr} {}

// Constructor
template <class T>
DLLNode<T>::DLLNode(T value) : data{value}, next{nullptr}, prev{nullptr} {}


#endif // _DLLNODE_H_

