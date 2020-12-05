#include <iostream>

using namespace std;

template <class T>

class TreeNode {
  public:
    TreeNode();
    TreeNode(int argKey, T argData);
    ~TreeNode();

    int key;
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    bool operator ==(const TreeNode<T>* otherNode);
};

template <class T>
TreeNode<T>::TreeNode() {
  left = NULL;
  right = NULL;
  key = 0;
  data = new T();
}

template <class T>
TreeNode<T>::TreeNode(int argKey, T argData) {
  left = NULL;
  right = NULL;
  key = argKey;
  data = argData;
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
