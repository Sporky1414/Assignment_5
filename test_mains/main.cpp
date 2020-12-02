#include "BST.cpp"

using namespace std;

int main (int argc, char** argv) {
  BST<int>* tree = new BST<int>();
  srand(time(NULL));
  for(int i = 0; i < 15; ++i) {
    int numToAdd = 1 + rand()/((RAND_MAX)/100);
    tree->insertNode(numToAdd);
    cout << "NUM TO ADD: " << numToAdd << endl;
  }
  cout << "TREE IN ORDER:" << endl;
  cout << tree->printInOrder() << endl;
  int nodeToSearch = 44;
  tree->insertNode(44);
  cout << "44 PRESENT: " << tree->searchNode(44) << endl;
  cout << "102 PRESENT: " << tree->searchNode(102) << endl;
  cout << "TREE POST ORDER WITH 44" << endl;
  cout << tree->printPostOrder() << endl;
  for(int i = 50; i != 49; ++i) {
    cout << "I: " << i << endl;
    if(tree->searchNode(i)) {
      cout << "TREE PREORDER PRIOR TO DELETE OF " << i << ":" << endl;
      cout << tree->printPreOrder() << endl;
      cout << "DELETING " << i << ": " << tree->deleteNode(i) << endl;
      cout << "NEW TREE PREORDER: " << endl;
      cout << "TRYING AGAIN: " << tree->deleteNode(i) << endl;
      cout << tree->printPreOrder() << endl;
      break;
    }
    if(i > 100) {
      i = -1;
    }
  }
  cout << "TREE MAX: " << tree->getMax() << endl;
  cout << "TREE MIN: " << tree->getMin() << endl;
  cout << "GET HEIGHT: " << tree->getHeightOfTree() << endl;
  cout << "DELETING TREE" << endl;
  while(!tree->isEmpty()) {
    tree->deleteNode(tree->getMax());
    cout << "NEW TREE: " << endl;
    cout << tree->printInOrder() << endl;
  }
}
