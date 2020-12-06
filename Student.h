/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Person.h"

using namespace std;

//A class that stores students, the data stored within, their getters/setters, modifiers, and overrides. Implements the Person abstract class.
class Student: private Person {
  public:
    //Constructors/Destructors
    Student();
    Student(int studentID, string nameOfStudent, int originalFacultyAdvisor);
    Student(string dataFromFile);
    ~Student();

    //Getters/Setters
    int getID();
    string getName();
    string getLevel();
    void setLevel();
    string getMajor();
    void setMajor();
    double getGPA();
    void setGPA();
    int getFacultyAdvisorID();
    void setNewAdvisor(int newFacultyAdvisorID);

    //Overriden comparison operators
    bool operator ==(const Person& otherPerson);
    bool operator <(const Person& otherPerson);
    bool operator >(const Person& otherPerson);
    bool operator >=(const Person& otherPerson);
    bool operator <=(const Person& otherPerson);

    //Overridden printing functions
    friend ostream &operator<<(ostream &out, Student &student);
    friend string to_string(Student student);

    //Print in user-friendly format.
    string printDataForUser();

  private:
    //Non-person related primitives
    string major;
    double gpa;
    int facultyAdvisor;

    //Deprecated
    int getLevelNumber(string thisLevel);
};
