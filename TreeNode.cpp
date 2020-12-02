#include <iostream>

using namespace std;

template <class T>

class TreeNode {
  public:
    TreeNode();
    TreeNode(T data);
    ~TreeNode();

    T key;
    TreeNode<T>* left;
    TreeNode<T>* right;
    bool operator ==(const TreeNode<T>* otherNode);
};

template <class T>
TreeNode<T>::TreeNode() {
  left = NULL;
  right = NULL;
  key = T();
}

template <class T>
TreeNode<T>::TreeNode(T data) {
  left = NULL;
  right = NULL;
  key = data;
}

template <class T>
TreeNode<T>::~TreeNode() {
  delete left;
  delete right;
}

template <class T>
bool TreeNode<T>::operator ==(const TreeNode<T>* otherNode) {
  return key == otherNode->key;
}
