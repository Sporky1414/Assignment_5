/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 3
*/

//A class that implements the Stack abstract data type with an array-based
//implementation.
#include <iostream>

using namespace std;

//Template class used in order to allow for use of any data type with the stack.
template <class T>

//Header portion (Header/Implementation are in same file due to template class rules)
class GenStack {
  public:
    //Constructor/Destructor
    GenStack();
    ~GenStack();

    //Methods to manipulate stack data
    void push(T data);
    T pop();
    T peek();

    //Methods to get information about the stack
    bool isEmpty();
    int getSize();

  private:
    //Methods to determine if the array holding the stack is full and to resize
    //the array if it is indeed full. Private because implementer has no need
    //for either method.
    bool isFull();
    void resize();

    //Pointer to array holding the stack, the pointer for the top of the stack,
    //and the current size of the underlying array
    T *stackArray;
    int top; //top element of stack
    int currArraySize;
};



//Implementation portion (Header/Implementation are in same file due to template class rules)

//Default Constructor: Initalizes array to have 10 spots originally, denotes stack as Empty
//by setting "top" value to -1.
template <class T>
GenStack<T>::GenStack() {
  stackArray = new T[10];
  currArraySize = 10;
  top = -1;
}

//Destructor: Deletes the stack array.
template <class T>
GenStack<T>::~GenStack() {
  delete stackArray;
}


//Enters data onto the stack.
template <class T>
void GenStack<T>::push(T data) {
  //Adds data to stack array at the corresponding index. Overwrites old data
  //if data is already stored in that index.
  stackArray[++top] = data;
  //If array is full after the data is added, the resize method is called to fix that.
  if(isFull()) {
    resize();
  }
}

//Removes top data from the stack and returns it to the user.
template <class T>
T GenStack<T>::pop() {
  //Exception thrown if stack is empty, so try/catch block is used for exception handling.
  try {
    //Checks if empty. If so, throws an arbitrary exception.
    if(isEmpty()) {
      throw 20;
    } else {
      //Stack has data, so set the "top" index back by one to "remove" the data,
      //but not before returning the value stored at the index "top" used to be.
      return stackArray[top--];
    }
  } catch (int e) {
    //Aborts program if the stack empty exception is thrown.
    cout << "EXCEPTION: Stack is Empty. Please input data before pop!" << endl;
    abort();
  }
}

//Reveals data at the top of the stack.
template <class T>
T GenStack<T>::peek() {
  //Exception thrown if stack is empty, so try/catch block is used for exception handling.
  try {
    if(isEmpty()) {
      //Checks if empty. If so, throws an arbitrary exception.
      throw 20;
    } else {
      //Stack has data, so return the data at the index "top" in the array.
      return stackArray[top];
    }
  } catch(int e) {
    //Aborts program if the stack empty exception is thrown.
    cout << "EXCEPTION: Stack is Empty. Please input data before peek!" << endl;
    abort();
  }
}

//Checks if the stack itself is empty.
template <class T>
bool GenStack<T>::isEmpty() {
  //Returns whether or not the top value is equal to -1. If it is, there is no
  //data in use stored in the array, so it is empty. If it is not -1, data being
  //currently used by the stack is present, so return true.
  return (top == -1);
}

//Returns the size of the stack.
template <class T>
int GenStack<T>::getSize() {
  //Since top measures the index in the array where the newest data piece is,
  //adding one to "top" gets the number of data pieces in the array. So this
  //is returned as the "height"
  return (top + 1);
}

//Checks if the underlying stack array is full
template <class T>
bool GenStack<T>::isFull() {
  //If top is equal to the current array length - 1 (to account for the array indexes starting at 0),
  //then the stack is full and true is returned. Otherwise, false is returned.
  return (top == currArraySize - 1);
}

//Replaces the old underlying array with a new array twice the size of the previous one,
//copying over the data to the new array in the process.
template <class T>
void GenStack<T>::resize() {
  //Determines the new size of the array and creates the new array.
  int tempSize = currArraySize * 2;
  T *tempArray = new T[tempSize];
  //Copies all the data from the old array to the new array.
  for(int i = 0; i < currArraySize; ++i) {
    tempArray[i] = stackArray[i];
  }
  //Sets the stackArray pointer to the new array.
  stackArray = tempArray;
  //Sets currArraySize to the new array size
  currArraySize = tempSize;
}
