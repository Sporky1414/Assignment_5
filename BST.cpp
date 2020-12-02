#include "TreeNode.cpp"

using namespace std;

template <class T>

class BST {
  private:
    TreeNode<T>* root;

  public:
    BST();
    ~BST();

    void insertNode(T data);
    bool searchNode(T data);
    bool deleteNode(T data);

    bool isEmpty();
    T getMax();
    T getMin();
    int getHeightOfTree();
    int getHeightOfSubtree(T dataOfRootForSubtree);
    string printInOrder();
    string printPreOrder();
    string printPostOrder();



  private:
    TreeNode<T>* getNodeWithData(T data);
    string printInOrderRec(TreeNode<T>* nodeToStart);
    string printPreOrderRec(TreeNode<T>* nodeToStart);
    string printPostOrderRec(TreeNode<T>* nodeToStart);
    int getHeightOfTreeRec(TreeNode<T>* rootNodeForSubtree);
};

template <class T>
BST<T>::BST() {
  root = NULL;
}

template <class T>
BST<T>::~BST() {
  delete root;
}

template <class T>
bool BST<T>::isEmpty() {
  return root == NULL;
}

template <class T>
T BST<T>::getMax() {
  //looking for rightmost TreeNode

  if(isEmpty()) {
    return T();
  }

  TreeNode<T>* current = root;

  while(current->right != NULL) {
    current = current->right;
  }

  return current->key;
}

template <class T>
T BST<T>::getMin() {
  if(isEmpty()) {
    return T();
  }

  TreeNode<T>* current = root;

  while(current->left != NULL) {
    current = current->left;
  }

  return current->key;
}

template <class T>
void BST<T>::insertNode(T value) {
  TreeNode<T>* node = new TreeNode<T>(value);

  if(isEmpty()) {
    //empty Tree
    root = node;
  } else {
    //it's not an empty Tree
    TreeNode<T>* parent = NULL;
    TreeNode<T>* current = root;

    while(true) {
      parent = current;

      if(value < current->key) {
        //go left
        current = current->left;
        if(current == NULL) {
          //found Insertion Point
          parent->left = node;
          break;
        }
      } else {
        //go right
        current = current->right;
        if(current == NULL) {
          //found insertion Point
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <class T>
bool BST<T>::searchNode(T value) {
  if(isEmpty()) {
    return false;
  } else {
    //tree is not empty, let's go look for the value.
    TreeNode<T>* current = root;

    while (current->key != value) {
      if(value < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
      if(current == NULL) {
        //we did not find it
        return false;
      }
    }
    return true;
  }
}

template <class T>
bool BST<T>::deleteNode(T value) {
  TreeNode<T>* parent = NULL;
  TreeNode<T>* current = root;
  while(current != NULL) {
    if(current->key == value) {
      if(current->left == NULL && current->right == NULL) {
        if(parent == NULL) {
          root = NULL;
        } else if (parent->left == current) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
      } else if (current->right == NULL) {
        if(parent == NULL) {
          root = current->left;
        } else if (parent->left == current) {
          parent->left = current->left;
        } else {
          parent->right = current->left;
        }
      } else if (current->left == NULL) {
        if(parent == NULL) {
          root = current->right;
        } else if (parent->left == current) {
          parent->left = current->right;
        } else {
          parent->right = current->right;
        }
      } else {
        TreeNode<T>* successor = current->right;
        TreeNode<T>* successorParent = current;
        bool successorIsLeftChild = false;
        while(successor->left != NULL) {
          successorParent = successor;
          successor = successor->left;
          successorIsLeftChild = true;
        }
        T successorData = successor->key;
        if(successorData == current->key) {
          if(successorIsLeftChild) {
            successorParent->left = NULL;
          } else {
            successorParent->right = NULL;
          }
        } else {
          deleteNode(successor->key);
          current->key = successorData;
        }
      }
      return true;
    } else if (current->key < value) {
      parent = current;
      current = current->right;
    } else {
      parent = current;
      current = current->left;
    }
  }
  return false;
}

template <class T>
string BST<T>::printInOrder() {
  return printInOrderRec(root);
}

template <class T>
string BST<T>::printInOrderRec(TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringWithTree = "";
  stringWithTree += printInOrderRec(nodeToStart->left);
  stringWithTree += to_string(nodeToStart->key)+ "\n";
  stringWithTree += printInOrderRec(nodeToStart->right);
  return stringWithTree;
}

template <class T>
int BST<T>::getHeightOfTree() {
  return getHeightOfTreeRec(root);
}

template <class T>
int BST<T>::getHeightOfSubtree(T dataOfRootForSubtree) {
  return getHeightOfTreeRec(getNodeWithData(dataOfRootForSubtree));
}

template <class T>
int BST<T>::getHeightOfTreeRec(TreeNode<T>* rootNodeForSubtree) {
  if (rootNodeForSubtree == NULL) {
    return -1;
  }
  int leftMaxHeight = getHeightOfTreeRec(rootNodeForSubtree->left);
  int rightMaxHeight = getHeightOfTreeRec(rootNodeForSubtree->right);
  return 1 + max(leftMaxHeight, rightMaxHeight);
}

template <class T>
TreeNode<T>* BST<T>::getNodeWithData(T data) {
  if(isEmpty()) {
    return NULL;
  } else {
    //tree is not empty, let's go look for the value.
    TreeNode<T>* current = root;

    while (current->key != data) {
      if(data < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
      if(current == NULL) {
        //we did not find it
        return NULL;
      }
    }
    return current;
  }
}

template <class T>
string BST<T>::printPreOrder() {
  return printPreOrderRec(root);
}

template <class T>
string BST<T>::printPreOrderRec(TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringToReturn = to_string(nodeToStart->key) + "\n";
  stringToReturn += printPreOrderRec(nodeToStart->left);
  stringToReturn += printPreOrderRec(nodeToStart->right);
  return stringToReturn;
}

template <class T>
string BST<T>::printPostOrder() {
  return printPostOrderRec(root);
}

template <class T>
string BST<T>::printPostOrderRec(TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringToReturn = printPostOrderRec(nodeToStart->left);
  stringToReturn += printPostOrderRec(nodeToStart->right);
  stringToReturn += to_string(nodeToStart->key) + "\n";
  return stringToReturn;
}
