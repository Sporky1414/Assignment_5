/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Rollback.h"

using namespace std;

//Class to run the database program.
class Simulation {
  public:
    //Constructor/Destructor
    Simulation();
    ~Simulation();

    //Runs the program.
    void run();

  private:
    //Methods that correspond to each selection in the program.
    void printStudents();
    void printFaculty();
    void displayStudent();
    void displayFaculty();
    void printAdvisorOfStudent();
    void printAdviseesOfFaculty();
    void addStudent();
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeAdvisorForStudent();
    void removeAdviseeFromFaculty();
    void rollback();

    //Checks if a string is a positive number.
    bool checkIfStringIsNumber(string tempString);

    //Takes in a response from the user and spits back out either the corresponding number or -1 should the response not be a string.
    int getNumResponse();

    //Rollback functions.
    void prepBackup();
    void restoreBackup();

    //Database to store main data and the Rollback to store the backups.
    Database* database;
    Rollback* backups;
};
