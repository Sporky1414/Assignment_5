#include "TreeNode.cpp"
#include "LinkedList.cpp"

using namespace std;

template <class T>

class BST {
  public:
    BST();
    ~BST();

    void insertNode(int key, T data);
    bool searchNode(int key);
    bool deleteNode(int key);

    T getDataOfNodeFromKey(int key);

    bool isEmpty();
    int getMax();
    int getMin();
    int getHeightOfTree();
    int getHeightOfSubtree(int keyOfRootForSubtree);
    int getNumOfKeys();
    string printInOrderRef();
    string printInOrderPointer();
    string printPreOrderRef();
    string printPreOrderPointer();
    string printPostOrderRef();
    string printPostOrderPointer();
    LinkedList<int>* getListOfKeysInOrder();



  private:
    TreeNode<T>* root;
    int numOfKeys;

    TreeNode<T>* getNodeWithKey(int key);
    string printInOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer);
    string printInOrderRec(TreeNode<T>* nodeToStart);
    string printPreOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer);
    string printPreOrderRec(TreeNode<T>* nodeToStart);
    string printPostOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer);
    string printPostOrderRec(TreeNode<T>* nodeToStart);
    void getListOfKeysInOrderRec(LinkedList<int>* keyList, TreeNode<T>* nodeToStart);
    int getHeightOfTreeRec(TreeNode<T>* rootNodeForSubtree);
};

template <class T>
BST<T>::BST() {
  numOfKeys = 0;
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
int BST<T>::getMax() {
  //looking for rightmost TreeNode

  if(isEmpty()) {
    return -1;
  }

  TreeNode<T>* current = root;

  while(current->right != NULL) {
    current = current->right;
  }

  return current->key;
}

template <class T>
int BST<T>::getMin() {
  if(isEmpty()) {
    return -1;
  }

  TreeNode<T>* current = root;

  while(current->left != NULL) {
    current = current->left;
  }

  return current->key;
}

template <class T>
int BST<T>::getNumOfKeys() {
  return numOfKeys;
}

template <class T>
void BST<T>::insertNode(int key, T data) {
  TreeNode<T>* node = new TreeNode<T>(key, data);

  if(isEmpty()) {
    //empty Tree
    root = node;
  } else {
    //it's not an empty Tree
    TreeNode<T>* parent = NULL;
    TreeNode<T>* current = root;

    while(true) {
      parent = current;

      if(key < current->key) {
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
  ++numOfKeys;
}

template <class T>
bool BST<T>::searchNode(int key) {
  if(isEmpty()) {
    return false;
  } else {
    //tree is not empty, let's go look for the value.
    TreeNode<T>* current = root;

    while (current->key != key) {
      if(key < current->key) {
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
T BST<T>::getDataOfNodeFromKey(int key) {
  if(isEmpty()) {
    return T();
  } else {
    TreeNode<T>* current = root;

    while(current->key != key) {
      if(key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
      if(current == NULL) {
        return T();
      }
    }
    return current->data;
  }
}

template <class T>
bool BST<T>::deleteNode(int key) {
  TreeNode<T>* parent = NULL;
  TreeNode<T>* current = root;
  while(current != NULL) {
    if(current->key == key) {
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
        T successorData = successor->data;
        int successorKey = successor->key;
        if(successorKey == current->key) {
          if(successorIsLeftChild) {
            successorParent->left = NULL;
          } else {
            successorParent->right = NULL;
          }
        } else {
          deleteNode(successor->key);
          current->key = successorKey;
          current->data = successorData;
        }
      }
      numOfKeys--;
      return true;
    } else if (current->key < key) {
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
string BST<T>::printInOrderPointer() {
  return printInOrderRec(root, is_pointer<T>::value);
}

template <class T>
string BST<T>::printInOrderRef() {
  return printInOrderRec(root);
}

template <class T>
string BST<T>::printInOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringWithTree = "";
  stringWithTree += printInOrderRec(nodeToStart->left, tIsPointer);
  T tempData = nodeToStart->data;
  stringWithTree += to_string(*tempData);
  stringWithTree += printInOrderRec(nodeToStart->right, tIsPointer);
  return stringWithTree;
}

template <class T>
string BST<T>::printInOrderRec(TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringWithTree = "";
  stringWithTree += printInOrderRec(nodeToStart->left);
  stringWithTree += to_string(nodeToStart->data);
  stringWithTree += printInOrderRec(nodeToStart->right);
  return stringWithTree;
}

template <class T>
LinkedList<int>* BST<T>::getListOfKeysInOrder() {
  LinkedList<int>* tempList = new LinkedList<int>();
  getListOfKeysInOrderRec(tempList, root);
  return tempList;
}

template <class T>
void BST<T>::getListOfKeysInOrderRec(LinkedList<int>* keysList, TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return;
  }
  getListOfKeysInOrderRec(keysList, nodeToStart->left);
  keysList->append(nodeToStart->key);
  getListOfKeysInOrderRec(keysList, nodeToStart->right);
}

template <class T>
int BST<T>::getHeightOfTree() {
  return getHeightOfTreeRec(root);
}

template <class T>
int BST<T>::getHeightOfSubtree(int key) {
  return getHeightOfTreeRec(getNodeWithKey(key));
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
TreeNode<T>* BST<T>::getNodeWithKey(int key) {
  if(isEmpty()) {
    return NULL;
  } else {
    //tree is not empty, let's go look for the value.
    TreeNode<T>* current = root;

    while (current->key != key) {
      if(key < current->key) {
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
string BST<T>::printPreOrderPointer() {
  return printPreOrderRec(root, is_pointer<T>::value);
}

template <class T>
string BST<T>::printPreOrderRef() {
  return printPreOrderRec(root);
}

template <class T>
string BST<T>::printPreOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringToReturn = "";
  if(!tIsPointer) {
    stringToReturn += to_string(nodeToStart->data);
  } else {
    T tempData = nodeToStart->data;
    stringToReturn += to_string(*tempData);
  }
  stringToReturn += printPreOrderRec(nodeToStart->left, tIsPointer);
  stringToReturn += printPreOrderRec(nodeToStart->right, tIsPointer);
  return stringToReturn;
}

template <class T>
string BST<T>::printPreOrderRec(TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringToReturn = "";
  stringToReturn += to_string(nodeToStart->data);
  stringToReturn += printPreOrderRec(nodeToStart->left);
  stringToReturn += printPreOrderRec(nodeToStart->right);
  return stringToReturn;
}

template <class T>
string BST<T>::printPostOrderRef() {
  return printPostOrderRec(root);
}

template <class T>
string BST<T>::printPostOrderPointer() {
  return printPostOrderRec(root, is_pointer<T>::value);
}

template <class T>
string BST<T>::printPostOrderRec(TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringToReturn = printPostOrderRec(nodeToStart->left);
  stringToReturn += printPostOrderRec(nodeToStart->right);
  stringToReturn += to_string(nodeToStart->data);
  return stringToReturn;
}

template <class T>
string BST<T>::printPostOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer) {
  if(nodeToStart == NULL) {
    return "";
  }
  string stringToReturn = printPostOrderRec(nodeToStart->left, tIsPointer);
  stringToReturn += printPostOrderRec(nodeToStart->right, tIsPointer);
  T tempData = nodeToStart->data;
  stringToReturn += to_string(*tempData);
  return stringToReturn;
}
