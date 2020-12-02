/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/
#include "LinkedListNode.cpp"
#include "ListADT.h"

using namespace std;

template <class T>

//A template class implementing the Linked List data structure, with it being subclass of the ListADT.
class LinkedList: public ListADT<T> {
  private:
    //Pointer nodes to the front and back nodes of the linked list.
    LinkedListNode<T>* front;
    LinkedListNode<T>* back;
    //Integer value of how many nodes are present in the list.
    unsigned int length;

    //Removes the front and back nodes from the Linked List.
    T removeFront();
    T removeBack();

  public:
    //Constructor/Destructor for the LinkedList.
    LinkedList();
    ~LinkedList();

    //Adds the given data to the front of the list.
    void prepend(T data);
    //Adds the given data to the back of the list.
    void append(T data);
    //Adds the new data after the given datapoint.
    void insertAfter(T newData, T datapointItemBeingAddedAfter);
    //Removes the given data from the linked list.
    T remove(T data);

    //Returns the position currently storing the given data.
    int searchFor(T value);
    //Returns the data stored at the given position of the linked list.
    T valueAt(int pos);

    //Prints the linked list data.
    void print();
    //Prints the linked list data, but in reverse.
    void printReverse();

    //Returns if the linked list is empty (or length == 0)
    bool isEmpty();
    //Returns the value of length.
    unsigned int getLength();

    //Sorts the data of the linked list.
    void sortSelf();
};

//Constructor: Since no data is present, front/back pointers are set to NULL while the length is set to 0.
template <class T>
LinkedList<T>::LinkedList() {
  front = NULL;
  back = NULL;
  length = 0;
}

//Destructor: Deletes each list node from the back to the front. Once all nodes in the list are deleted, the front and back nodes are deleted to ensure
//all nodes are gone.
template <class T>
LinkedList<T>::~LinkedList() {
  for(int i = length; i >= 0; i--) {
    removeBack();
  }
  delete back;
  delete front;
}

//Adds the given data to the front of the list.
template <class T>
void LinkedList<T>::prepend(T d) {
  //Creates a pointer to a new LinkedListNode to hold the new data.
  LinkedListNode<T> *node = new LinkedListNode<T>(d);
  //IF the list is empty, set the front and back pointers to the new node.
  if(getLength() == 0) {
    front = node;
    back = node;
  //Otherwise, set the new node to the front of the list and push the old front node to the new node's next pointer.
  } else {
    front->prev = node;
    node->next = front;
  }
  //Changes the list's front pointer to the new node, now that the node is properly inserted before the first node.
  front = node;
  //Increase the length of the list, since a node was added.
  ++length;
}

//Adds the given data to the back of the list.
template <class T>
void LinkedList<T>::append(T d) {
  //Creates a pointer to a new LinkedListNode to hold the new data.
  LinkedListNode<T> *node = new LinkedListNode<T>(d);
  //IF the list is empty, set the front and back pointers to the new node.
  if(getLength() == 0) {
    front = node;
    back = node;
  //Otherwise, set the new node to the back of the list and push the old back node to the new node's prev pointer.
  } else {
    back->next = node;
    node->prev = back;
  }
  //Changes the list's back pointer to the new node, now that the node is properly inserted after the last node.
  back = node;
  //Increase the length of the list, since a node was added.
  ++length;
}

template <class T>
void LinkedList<T>::insertAfter(T d, T datapointItemBeingAddedAfter) {
  //Find the position of the datapoint the new data is being added after.
  int pos = this->searchFor(datapointItemBeingAddedAfter);
  if(pos == 0) {
    //Prepend the data if the datapoint the new data is being added after is in front.
    prepend(d);
    return;
  } else if (pos >= length - 1) {
    //Prepend the data if the datapoint the new data is being added after is in the back.
    append(d);
    return;
  } else if (pos == -1) {
    //If the datapoint is not in the list, tell the user and insert the data at the back.
    cout <<"INVALID POSITION ENTERED. INSERTING DATA AT BACK" << endl;
    append(d);
    return;
  }
  //Position found is not the front/back and is indeed a position on the list, so move on.

  //Creates a pointer to a new LinkedListNode to hold the new data.
  LinkedListNode<T>* newNode = new LinkedListNode<T>(d);
  //Creates a counter to store what position we are currently pointing to.
  int p = 0;

  //Creates the current pointer and successor pointers to show where we are currently searching in the list.
  LinkedListNode<T>* curr = front;
  LinkedListNode<T>* succ = front->next;

  //Sets curr pointer to the correct node found earlier with this loop.
  while(p != pos) {
    curr = curr->next;
    ++p;
  }
  //Sets the succ pointer to the curr pointer's next.
  succ = curr->next;

  //Changes the next/prev nodes of the new node, curr node, and succ node so that the new node is inbetween curr and succ in the list.
  newNode->next = succ;
  newNode->prev = curr;
  curr->next = newNode;
  succ->prev = newNode;

  //Increase the length of the list, since a node was added.
  ++length;
}

//Removes the datapoint at the front of the list and returns it.
template <class T>
T LinkedList<T>::removeFront() {
  //Creates a pointer to store the node being deleted, which is the front node in this case.
  LinkedListNode<T> *node = front;

  //Returns a null version of T() should the list be empty.
  if(node == NULL) {
    return T();
  }

  if(front->next == NULL) {
    //If the list has only one node, set the back pointer to node.
    back = NULL;
  } else {
    //more than one node in the list, so set the front node's successor's previous pointer to NULL (remove reference to current front node)
    front->next->prev = NULL;
  }
  //Change the front node to it's successor
  front = front->next;
  //Remove pointer to node at the next pointer in node (the old front)
  node->next = NULL;

  //Create a copy of the data stored in node, decrement the length, delete the old node, and return the copy of the data.
  T temp = node->data;
  length--;
  delete node;
  return temp;
}

//Removes the datapoint at the back of the list and returns it.
template <class T>
T LinkedList<T>::removeBack() {
  //Creates a pointer to store the node being deleted, which is the back node in this case.
  LinkedListNode<T> *node = back;

  //Returns a null version of T() should the list be empty.
  if(node == NULL) {
    return T();
  }

  if(back->prev == NULL) {
    //If the list has only one node, set the front pointer to node.
    front = NULL;
  } else {
    //more than one node in the list, so set the back node's predecessor's next pointer to NULL (remove reference to current back node)
    back->prev->next = NULL;
  }
  //Change the back node to it's predecessor
  back = back->prev;
  //Remove pointer to node at the prev pointer in node (the old back)
  node->prev = NULL;

  //Create a copy of the data stored in node, decrement the length, delete the old node, and return the copy of the data.
  T temp = node->data;
  length--;
  delete node;
  return temp;
}

//Remove the specified data point ffrom the list.
template <class T>
T LinkedList<T>::remove(T data) {
  //Find the position of the data point to remove. Return the default of T should the position not exist.
  int pos = searchFor(data);
  if(pos == -1) {
    return T();
  }

  //Set the current pointer to the front of the list, then iterate through the list until curr matches the node with the datapoint being removed.
  LinkedListNode<T>* curr = front;
  for(int i = 0; i < pos; ++i) {
    curr = curr->next;
  }
  //Sets the sucNode and predNode to the curr's next and prev pointers, respectively.
  LinkedListNode<T>* sucNode = curr->next;
  LinkedListNode<T>* predNode = curr->prev;
  //Sets the prev of successor to predNode should sucNode not be NULL.
  if(sucNode != NULL) {
    sucNode->prev = predNode;
  }
  //Sets the next of predecessor to sucNode should predNode not be NULL.
  if(predNode != NULL) {
    predNode->next = sucNode;
  }
  //Should the front be being removed, front is set to the successor node.
  if(curr == front) {
    front = sucNode;
  }
  //Should the back be being removed, back is set to the predecessor node.
  if(curr == back) {
    back = predNode;
  }
  //Decreases the length of the list, copies the data from the old node, deletes the old node, and returns the data copy.
  length--;
  T temp = curr->data;
  delete curr;
  return temp;
}

//Returns the position of the given datapoint. -1 is returned if the datapoint is not present in the list.
template <class T>
int LinkedList<T>::searchFor(T value) {
  //Sets the default position to -1. Puts a curr pointer at front.
  int pos = -1;
  LinkedListNode<T> *curr = front;

  //Iterates through the list to find the node with the data being looked for. If it exists, that position is saved in pos. Otherwise, curr is set to NULL.
  while (curr != NULL) {
    ++pos;
    if(curr->data == value) {
      break;
    }
    curr = curr->next;
  }
  //If curr is null, the datapoint is not in the list, so set the position back to -1.
  if(curr == NULL)
    pos = -1;
  //Return the position of the datapoint (or -1 should the datapoint not be present).
  return pos;
}

//Returns the data of the given position in the linked list.
template <class T>
T LinkedList<T>::valueAt(int pos) {
  //if pos is less than 0, return a default T().
  if(pos < 0) {
    return T();
  }
  //Current pointer used to iterate through the list.
  LinkedListNode<T> *curr = front;

  //Iterate through the list until pos is found or until curr becomes NULL (end of list)
  for(int i = 0; i < pos; ++i) {
    curr = curr->next;
    if(curr == NULL) {
      break;
    }
  }

  //Return an empty T() should pos not be in the loop
  if(curr == NULL) {
    return T();
  }
  //Return the data of curr should pos be in the loop.
  return curr->data;
}

//Prints the queue
template <class T>
void LinkedList<T>::print() {
  //String to hold what is being printed.
  string returnString = "";
  //Curr pointer to iterate through linked list.
  LinkedListNode<T> *curr = front;

  //Loop to iterate through list.
  while(curr != NULL) {
    //Add each piece of data from the list to returnString
    returnString += "\"" + to_string(curr->data) + "\"";
    //Set curr to the next pointer. If curr is now null, add a period to signify the end of the list.
    //Otherwise, add a comma to signify that more is coming.
    curr = curr->next;
    if(curr != NULL) {
      returnString += ", ";
    } else {
      returnString +=". ";
    }
  }
  //Curr is null, so delete the pointer
  delete curr;
  //Print returnString
  cout << returnString << endl;
}

//Print the list in reverse order.
template <class T>
void LinkedList<T>::printReverse() {
  //String to hold what is being printed.
  string returnString = "";
  //Curr pointer to iterate through linked list from the back to the front.
  LinkedListNode<T> *curr = back;

  //Loop to iterate through list.
  while(curr != NULL) {
    //Add each piece of data from the list to returnString
    returnString += "\"" + to_string(curr->data) + "\"";
    //Set curr to the previous pointer. If curr is now null, add a period to signify the end of the list.
    //Otherwise, add a comma to signify that more is coming.
    curr = curr->prev;
    if(curr != NULL) {
      returnString += ", ";
    } else {
      returnString +=". ";
    }
  }
  //Curr is null, so delete the pointer
  delete curr;
  //Print returnString
  cout << returnString << endl;
}

//Sort the elements of LinkedList into the correct order.
template <class T>
void LinkedList<T>::sortSelf() {
  //Copy of the data of front to value min, which will hold each minimum value found.
  T min = front->data;
  //Create a temporary LinkedList to hold the sorted list
  LinkedList<T> *newList = new LinkedList<T>();
  //Create a curr pointer to iterate through the list.
  LinkedListNode<T> *curr = front;

  //Iterate through list until all list elements have been sorted.
  while(front != NULL) {
    //Find node with smallest data. Set the data to min.
    while(curr != NULL) {
      if(min > curr->data) {
        min = curr->data;
      }
      curr = curr->next;
    }
    //Once min is found, remove min from the current linked list (data is stored in min)
    remove(min);
    //Set the min to the back of the list (min will progressively get bigger, so adding to end will ensure list is in order as loop continues)
    newList->append(min);

    //If there is still more in the original list, reset min and curr for another loop.
    if(front != NULL) {
      min = front->data;
      curr = front;
    }
  }
  //Set the curr pointer to the front of the temp list.
  curr = newList->front;
  //Iterate through temp list and copy all the data from the temp list to the recently-emptied main list.
  while(curr != NULL) {
    append(curr->data);
    curr = curr->next;
  }
  //Delete curr (which is pointing to null) and the temp list, whose data has been copied back into the main list.
  delete curr;
  delete newList;
}

//Return if the length of the linked list is 0.
template <class T>
bool LinkedList<T>::isEmpty() {
  return length <= 0;
}

//Return the length of the linked list.
template <class T>
unsigned int LinkedList<T>::getLength() {
  return length;
}
