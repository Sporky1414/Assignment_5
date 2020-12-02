/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/

#include <iostream>

using namespace std;

//A template class that stores the nodes of a Linked List data type.
template <class T>
class LinkedListNode {
  public:
    //Constructors/Destructor
    LinkedListNode();
    LinkedListNode(T newData);
    ~LinkedListNode();

    //Pointers for the next and previous nodes in the Linked List
    LinkedListNode<T>* next;
    LinkedListNode<T>* prev;

    //The data stored in the node.
    T data;
};

//Constructor: Default constructor where all pointers and data are set to null.
template <class T>
LinkedListNode<T>::LinkedListNode() {
  next = NULL;
  prev = NULL;
  data = NULL;
}

//Constructor: Constructor where pointers are set to null and the data passed through is added to the node.
template <class T>
LinkedListNode<T>::LinkedListNode(T newData) {
  next = NULL;
  prev = NULL;
  data = newData;
}

//Destructor: Sets the next/prev pointers to NULL, then deletes the pointers.
template <class T>
LinkedListNode<T>::~LinkedListNode() {
  next = NULL;
  prev = NULL;
  delete next;
  delete prev;
}
