/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/


#include "Student.h"
#include "BST.cpp"

using namespace std;

//A class that stores faculty members, the data stored within, their getters/setters, modifiers, and overrides. Implements the Person abstract class.
class Faculty: private Person {
  public:
    //Constructors/Destructor
    Faculty();
    Faculty(int facultyID, string facultyName);
    Faculty(string dataFromFile);
    ~Faculty();

    //Getters/Setters for primitives and strings
    int getID();
    string getName();
    string getLevel();
    void setLevel();
    string getDepartment();
    void setDepartment();

    //Modifiers/Getters for listOfStudentAdviseeIDs
    void getPrintedListOfStudentAdviseeIDs();
    void addStudentAdvisee(Student* student);
    int deleteStudentFromAdviseeList(int studentID);
    ListADT<int>* getListOfStudentAdviseeIDs();

    //Overrides for comparison operators
    bool operator ==(const Person& otherPerson);
    bool operator <(const Person& otherPerson);
    bool operator >(const Person& otherPerson);
    bool operator >=(const Person& otherPerson);
    bool operator <=(const Person& otherPerson);

    //Overrides for string functions
    friend ostream &operator<<(ostream &out, Faculty &faculty);
    friend string to_string(Faculty &faculty);

    //Print data for user method
    string printDataForUser();

  private:
    //Non-Person related variables
    string department;
    ListADT<int>* listOfStudentAdviseeIDs;

    //Deprecated
    int getLevelNumber(string thisLevel);
};
