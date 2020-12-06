/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/


//A class that implements the Binary Search Tree data structure.
#include "TreeNode.cpp"
#include "LinkedList.cpp"

using namespace std;

//Template class to allow for the BST to be used with any class.
template <class T>

class BST {
  public:
    //Constructor/Destructor
    BST();
    ~BST();

    //Methods to manipulate data in the BST
    void insertNode(int key, T data);
    bool searchNode(int key);
    bool deleteNode(int key);

    //Get the data stored in a node from its key.
    T getDataOfNodeFromKey(int key);

    //Checks if the BST is empty
    bool isEmpty();

    //Gets largest/smallest key values
    int getMax();
    int getMin();

    //Gets height of the tree (or a subtree of the tree)
    int getHeightOfTree();
    int getHeightOfSubtree(int keyOfRootForSubtree);

    //Returns the number of nodes in the tree
    int getNumOfKeys();

    //Methods to print the data of all nodes in each of the traversal forms.
    //Methods with Ref are used when T is a reference.
    //Methods with Pointer are used with T is a pointer.
    string printInOrderRef();
    string printInOrderPointer();
    string printPreOrderRef();
    string printPreOrderPointer();
    string printPostOrderRef();
    string printPostOrderPointer();

    //Methods to get a list of all the keys in a tree in 2 of the 3 traversal forms (pre order was not needed)
    LinkedList<int>* getListOfKeysInOrder();
    LinkedList<int>* getListOfKeysPostOrder();



  private:
    //The tree itself is stored under the root TreeNode and its connections.
    TreeNode<T>* root;
    //Holds the number of nodes in the tree.
    int numOfKeys;

    //Returns the node that contains the given key.
    TreeNode<T>* getNodeWithKey(int key);

    //Recursive helper methods for the print methods.
    string printInOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer);
    string printInOrderRec(TreeNode<T>* nodeToStart);
    string printPreOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer);
    string printPreOrderRec(TreeNode<T>* nodeToStart);
    string printPostOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer);
    string printPostOrderRec(TreeNode<T>* nodeToStart);
    void getListOfKeysInOrderRec(LinkedList<int>* keyList, TreeNode<T>* nodeToStart);
    void getListOfKeysPostOrderRec(LinkedList<int>* keyList, TreeNode<T>* nodeToStart);

    //Recursive helper method for the getHeight methods.
    int getHeightOfTreeRec(TreeNode<T>* rootNodeForSubtree);
};

//Constructor: Sets up a new, empty BST.
template <class T>
BST<T>::BST() {
  numOfKeys = 0;
  root = NULL;
}

//Destructor: Deletes root, which will then lead to the deletion of all other nodes.
template <class T>
BST<T>::~BST() {
  delete root;
}

//Returns if root is NULL, which means the tree is empty.
template <class T>
bool BST<T>::isEmpty() {
  return root == NULL;
}

//Returns the biggest key value in the tree.
template <class T>
int BST<T>::getMax() {
  //If the tree is empty
  if(isEmpty()) {
    return -1;
  }
  //Set a pointer to the rightmost node of the tree, which holds the biggest key.
  TreeNode<T>* current = root;
  while(current->right != NULL) {
    current = current->right;
  }
  //Return the key found by the above code, which is the biggest key value.
  return current->key;
}

//Returns the smallest key value in the BST.
template <class T>
int BST<T>::getMin() {
  //Returns -1 if the BST is empty.
  if(isEmpty()) {
    return -1;
  }
  //Set a pointer to the leftmost node of the tree, which holds the smallest key.
  TreeNode<T>* current = root;
  while(current->left != NULL) {
    current = current->left;
  }
  //Return the key found by the above code, which is the smallest key value.
  return current->key;
}

//Getter for the numOfKeys variable.
template <class T>
int BST<T>::getNumOfKeys() {
  return numOfKeys;
}

//Method to insert a new datapoint/TreeNode into the tree.
template <class T>
void BST<T>::insertNode(int key, T data) {
  //Creates the new node.
  TreeNode<T>* node = new TreeNode<T>(key, data);
  if(isEmpty()) {
    //If the tree is empty, set the node just created to root.
    root = node;
  } else {
    //The tree is not empty, so set up pointers to help us find the insertion point.
    TreeNode<T>* parent = NULL;
    TreeNode<T>* current = root;

    //Loop through tree until current is pointing at the insertion point.
    while(true) {
      //Sets parent to what current is now, since current is about to point to one its children.
      parent = current;
      if(key < current->key) {
        //If the key we are looking for is less than the key stored at current, we must continue moving left due to BST rules to find the insertion point.
        current = current->left;
        if(current == NULL) {
          //If there is no node in that left position, we can store the node here by storing it as the left child of parent. Insertion is complete.
          parent->left = node;
          break;
        }
      } else {
        //If the key we are looking for is greater than the key stored at current, we must continue moving right due to BST rules to find the insertion point.
        current = current->right;
        if(current == NULL) {
          //If there is no node in that right position, we can store the node here by storing it as the right child of parent. Insertion is complete.
          parent->right = node;
          break;
        }
      }
    }
  }
  //Increase the number of keys in the tree.
  ++numOfKeys;
}

//Method to determine if a TreeNode is present with the given key.
template <class T>
bool BST<T>::searchNode(int key) {
  if(isEmpty()) {
    //Automatically return false if the tree is empty, since an empty tree can't have a treenode with the given key.
    return false;
  } else {
    //Set a pointer to root, which we will use to traverse the tree.
    TreeNode<T>* current = root;
    //Keep moving down the tree either left or right, depending on if the given key value is greater than/less than the key at the node current is pointing at.
    while (current->key != key) {
      if(key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
      if(current == NULL) {
        //If current exhausts all possible nodes and lands at a NULL pointer before finding the data point, a node with the given tree is not present and false is returned.
        return false;
      }
    }
    //The node with the given key has been found. Return true.
    return true;
  }
}

//Return the data stored in a node with the given key.
template <class T>
T BST<T>::getDataOfNodeFromKey(int key) {
  if(isEmpty()) {
    //Return a default version of T if the tree is empty, since the node with the given key is not present.
    return T();
  } else {
    //Set a pointer to the root. This pointer will be used to traverse the tree.
    TreeNode<T>* current = root;
    //Keep moving down the tree either left or right, depending on if the given key value is greater than/less than the key at the node current is pointing at.
    while(current->key != key) {
      if(key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
      if(current == NULL) {
        //If current exhausts all possible nodes and lands at a NULL pointer before finding the data point, a node with the given tree is not present. A default T() is returned.
        return T();
      }
    }
    //Node is found, returning data stored in node.
    return current->data;
  }
}

//Delete a node from the tree with the given key.
template <class T>
bool BST<T>::deleteNode(int key) {
  //Set pointers to traverse the tree with
  TreeNode<T>* parent = NULL;
  TreeNode<T>* current = root;
  //Loop through the tree to find the needed node.
  while(current != NULL) {
    if(current->key == key) {
      //Node has been found
      if(current->left == NULL && current->right == NULL) {
        //Node has no children, so simply delete the node and adjust pointers to reflect it being deleted.
        if(parent == NULL) {
          root = NULL;
        } else if (parent->left == current) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
      } else if (current->right == NULL) {
        //Node has one child on the left. Set that left child to be the child of the parent of current (or the root if one is not present).
        if(parent == NULL) {
          root = current->left;
        } else if (parent->left == current) {
          parent->left = current->left;
        } else {
          parent->right = current->left;
        }
      } else if (current->left == NULL) {
        //Node has one child on the right. Set that right child to be the child of the parent of current (or the root if one is not present).
        if(parent == NULL) {
          root = current->right;
        } else if (parent->left == current) {
          parent->left = current->right;
        } else {
          parent->right = current->right;
        }
      } else {
        //Node has two children.

        //Set up pointers to find the successor to swap with current.
        TreeNode<T>* successor = current->right;
        TreeNode<T>* successorParent = current;
        //Stores if the successor is determined to be a left child of some sort.
        bool successorIsLeftChild = false;
        while(successor->left != NULL) {
          //If current's right child has children on the left, keep moving through them until the successor pointer's left child is null. The actual successor has been found.
          successorParent = successor;
          successor = successor->left;
          successorIsLeftChild = true;
        }
        //Copy the data of the sucessor to temp variables.
        T successorData = successor->data;
        int successorKey = successor->key;

        if(successorKey == current->key) {
          //If the successor holds a duplicate key of the one to be deleted, simply delete the successor itself (achieves the same goal).
          if(successorIsLeftChild) {
            successorParent->left = NULL;
          } else {
            successorParent->right = NULL;
          }
        } else {
          //Successor is not a duplicate of current. Delete the successor node, then replace the data of current with that from successor.
          deleteNode(successor->key);
          current->key = successorKey;
          current->data = successorData;
        }
      }
      //Take a key away from the number of keys.
      numOfKeys--;
      //The node was successfully deleted, so true is return to signify that.
      return true;
    } else if (current->key < key) {
      //Node has not been found yet. Traverse to the right since the argument key is bigger than the key of the node being pointed at.
      parent = current;
      current = current->right;
    } else {
      //Node has not been found yet. Traverse to the left since the argument key is less than the key of the node being pointed at.
      parent = current;
      current = current->left;
    }
  }
  //Unable to find node, so false is returned since the node could not be deleted.
  return false;
}

//Returns an inorder traversal printing of the tree data. This version is for if T is a pointer.
template <class T>
string BST<T>::printInOrderPointer() {
  return printInOrderRec(root, is_pointer<T>::value);
}

//Returns an inorder traversal printing of the tree data. This version is for if T is a reference.
template <class T>
string BST<T>::printInOrderRef() {
  return printInOrderRec(root);
}

//Recursive helper function used to perform the inorder traversal in the printInOrder methods.
template <class T>
string BST<T>::printInOrderRec(TreeNode<T>* nodeToStart, bool tIsPointer) {
  //Returns a blank string if the node passed as an argument is NULL.
  if(nodeToStart == NULL) {
    return "";
  }
  //String to hold the data from the recursive calling of printInOrderRec
  string stringWithTree = "";
  //Calls printToOrderRec on the left child of nodeToStart. Stores result in stringWithTree.
  stringWithTree += printInOrderRec(nodeToStart->left, tIsPointer);
  //Dereferences pointer and stores data from nodeToStart in stringWithTree.
  T tempData = nodeToStart->data;
  stringWithTree += to_string(*tempData);
  //Calls printToOrderRec on the right child of nodeToStart. Stores in stringWithTree.
  stringWithTree += printInOrderRec(nodeToStart->right, tIsPointer);
  //Returns stringWithTree.
  return stringWithTree;
}

//Recursive helper function used to perform the inorder traversal in the printInOrder methods.
template <class T>
string BST<T>::printInOrderRec(TreeNode<T>* nodeToStart) {
  //Returns a blank string if the node passed as an argument is NULL.
  if(nodeToStart == NULL) {
    return "";
  }
  //String to hold the data from the recursive calling of printInOrderRec
  string stringWithTree = "";
  //Calls printToOrderRec on the left child of nodeToStart. Stores result in stringWithTree.
  stringWithTree += printInOrderRec(nodeToStart->left);
  //Stores data from nodeToStart in stringWithTree.
  stringWithTree += to_string(nodeToStart->data);
  //Calls printToOrderRec on the right child of nodeToStart. Stores in stringWithTree.
  stringWithTree += printInOrderRec(nodeToStart->right);
  //Returns stringWithTree.
  return stringWithTree;
}

//Creates a linkedlist containing all the keys of the tree and returns this list Keys are printed with the inorder traversal method.
template <class T>
LinkedList<int>* BST<T>::getListOfKeysInOrder() {
  LinkedList<int>* tempList = new LinkedList<int>();
  getListOfKeysInOrderRec(tempList, root);
  return tempList;
}

//Helper method for getListOfKeysInOrder(). Functionally works the exact same way as printInOrderRec(TreeNode<T>* nodeToStart).
//Only difference is that the keys are stored directly in keysList (which is a pointer to tempList in the main traversal method)
//As opposed to a string.
template <class T>
void BST<T>::getListOfKeysInOrderRec(LinkedList<int>* keysList, TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return;
  }
  getListOfKeysInOrderRec(keysList, nodeToStart->left);
  keysList->append(nodeToStart->key);
  getListOfKeysInOrderRec(keysList, nodeToStart->right);
}

//Returns the height of the tree.
template <class T>
int BST<T>::getHeightOfTree() {
  return getHeightOfTreeRec(root);
}

//Returns the height of the subtree whose root is the node that contains key.
template <class T>
int BST<T>::getHeightOfSubtree(int key) {
  return getHeightOfTreeRec(getNodeWithKey(key));
}

//Helper recursive method for the getHeight() methods of BST.
template <class T>
int BST<T>::getHeightOfTreeRec(TreeNode<T>* rootNodeForSubtree) {
  //If rootNodeForSubtree is NULL, then return -1 (smallest tree level is 0)
  if (rootNodeForSubtree == NULL) {
    return -1;
  }
  //Recursive call getHeightOfTreeRec on the left and right children of rootNodeForSubtree to get the max heights of each side of the tree.
  int leftMaxHeight = getHeightOfTreeRec(rootNodeForSubtree->left);
  int rightMaxHeight = getHeightOfTreeRec(rootNodeForSubtree->right);
  //Return 1 (rootNodeForSubtree) + the max height of either side, which gives the height of the given subtree.
  return 1 + max(leftMaxHeight, rightMaxHeight);
}

//Returns the treenode that holds the given key.
template <class T>
TreeNode<T>* BST<T>::getNodeWithKey(int key) {
  if(isEmpty()) {
    //Tree is empty, so NULL is returned as no treenode exists in this tree that holds the given key.
    return NULL;
  } else {
    //Tree is not empty. Search through the tree in a similar manner to searchNode() to find the correct node.
    TreeNode<T>* current = root;

    while (current->key != key) {
      if(key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
      if(current == NULL) {
        //We did not find the correct tree node, so NULL is returned.
        return NULL;
      }
    }
    //Node was found, so return it.
    return current;
  }
}

//Prints the data of the tree in the pre order traversal method. Done by recursive call on printPreOrderRec(). This method is for if T is a pointer.
template <class T>
string BST<T>::printPreOrderPointer() {
  return printPreOrderRec(root, is_pointer<T>::value);
}

//Prints the data of the tree in the pre order traversal method. Done by recursive call on printPreOrderRec(). This method is for if T is a reference.
template <class T>
string BST<T>::printPreOrderRef() {
  return printPreOrderRec(root);
}

//Helper recursive method for printPreOrderPointer(). Functions the exact same way as printInOrderPointer's helper method, except the order changes of what data is printed to the string first.
//For the preorder traversal below, the data of nodeToStart is printed, followed by the results of the recursive calls on the left and right children of nodeToStart, respectively.
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

//Helper recursive method for printPreOrderPointer(). Functions the exact same way as printInOrderRef's helper method, except the order changes of what data is printed to the string first.
//For the preorder traversal below, the data of nodeToStart is printed, followed by the results of the recursive calls on the left and right children of nodeToStart, respectively.
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

//Prints the data of the tree in the post order traversal method. Done by recursive call on printPostOrderRec(). This method is for if T is a pointer.
template <class T>
string BST<T>::printPostOrderRef() {
  return printPostOrderRec(root);
}

//Prints the data of the tree in the post order traversal method. Done by recursive call on printPostOrderRec(). This method is for if T is a reference.
template <class T>
string BST<T>::printPostOrderPointer() {
  return printPostOrderRec(root, is_pointer<T>::value);
}

//Helper recursive method for printPostOrderRef(). Functions the exact same way as printInOrderRef's helper method, except the order changes of what data is printed to the string first.
//For the postorder traversal below, the data of nodeToStart's left child and right child, respectively, are printed first. This is followed by printing the data stored in nodeToStart itself.
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

//Helper recursive method for printPostOrderPointer(). Functions the exact same way as printInOrderPointer's helper method, except the order changes of what data is printed to the string first.
//For the postorder traversal below, the data of nodeToStart's left child and right child, respectively, are printed first. This is followed by printing the data stored in nodeToStart itself.
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

//Creates a linkedlist containing all the keys of the tree and returns this list. Keys are printed in the post order traversal method.
template <class T>
LinkedList<int>* BST<T>::getListOfKeysPostOrder() {
  LinkedList<int>* tempList = new LinkedList<int>();
  getListOfKeysPostOrderRec(tempList, root);
  return tempList;
}

//Helper method for getListOfKeysPostOrder(). Functionally works the exact same way as printPostOrderRec(TreeNode<T>* nodeToStart).
//Only difference is that the keys are stored directly in keysList (which is a pointer to tempList in the main traversal method)
//As opposed to a string.
template <class T>
void BST<T>::getListOfKeysPostOrderRec(LinkedList<int>* keysList, TreeNode<T>* nodeToStart) {
  if(nodeToStart == NULL) {
    return;
  }
  getListOfKeysPostOrderRec(keysList, nodeToStart->left);
  getListOfKeysPostOrderRec(keysList, nodeToStart->right);
  keysList->append(nodeToStart->key);
}
