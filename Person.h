/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

//Abstract class for Person, which is the base class for Student and Faculty classes.
class Person {
  public:
    //Constructor/Destructor
    Person();
    ~Person();

    //Getters for person variables, setter for level
    virtual int getID() = 0;
    virtual string getName() = 0;
    virtual string getLevel() = 0;
    virtual void setLevel() = 0;

    //Virtual functions for operators
    virtual bool operator ==(const Person& otherPerson) = 0;
    virtual bool operator <(const Person& otherPerson) = 0;
    virtual bool operator >(const Person& otherPerson) = 0;
    virtual bool operator >=(const Person& otherPerson) = 0;
    virtual bool operator <=(const Person& otherPerson) = 0;

    //Virtual function to complement to_string override in subclasses
    virtual string printDataForUser() = 0;

    //Primitives
    string level;
    int id;
    string name;
  private:
    //Deprecated function for comparing levels in people
    virtual int getLevelNumber(string thisLevel) = 0;
};
