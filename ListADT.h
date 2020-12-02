/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/

using namespace std;

template <class T>

//A template, pure virtual base class that implements the List abstract data type from Zybooks
class ListADT {
  public:
    //No constructor/destructor needed for a pue virtual base class.

    //Adds the data to the back of the list.
    virtual void append(T data) = 0;
    //Adds the data to the front of the list.
    virtual void prepend(T data) = 0;
    //Inserts the data into the linked list after the given datapoint.
    virtual void insertAfter(T newData, T datapointItemBeingAddedAfter) = 0;
    //Removes the given data point from the list and returns it.
    virtual T remove(T data) = 0;

    //Returns the position in the list of the data.
    virtual int searchFor(T data) = 0;
    //Returns a copy of the data stored at the given position.
    virtual T valueAt(int pos) = 0;

    //Prints out the list.
    virtual void print() = 0;
    //Prints out the list in reverse order.
    virtual void printReverse() = 0;

    //Sorts the data inside the list.
    virtual void sortSelf() = 0;

    //Returns if the list is empty.
    virtual bool isEmpty() = 0;
    //Returns the length of the list.
    virtual unsigned int getLength() = 0;
};
