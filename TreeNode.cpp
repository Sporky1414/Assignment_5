/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include <iostream>

using namespace std;

template <class T>

//A helper template class used to store the nodes of the Binary Search Tree Data Type
class TreeNode {
  public:
    //Constructors/Destructor
    TreeNode();
    TreeNode(int argKey, T argData);
    ~TreeNode();

    //Data stored in the node
    int key;
    T data;

    //Pointers to the children of the node
    TreeNode<T>* left;
    TreeNode<T>* right;

    //Overridden equals
    bool operator ==(const TreeNode<T>* otherNode);
};

//Default Constructor: Sets default values for everything.
template <class T>
TreeNode<T>::TreeNode() {
  left = NULL;
  right = NULL;
  key = 0;
  data = new T();
}

//Constructor: Sets pointers to the children to NULL (not assigned yet) and passes the key and the data to the node.
template <class T>
TreeNode<T>::TreeNode(int argKey, T argData) {
  left = NULL;
  right = NULL;
  key = argKey;
  data = argData;
}

//Destructor: Deletes the children of the node
template <class T>
TreeNode<T>::~TreeNode() {
  delete left;
  delete right;
}

//Overrides equals. Determined based on key of the node.
template <class T>
bool TreeNode<T>::operator ==(const TreeNode<T>* otherNode) {
  return key == otherNode->key;
}
