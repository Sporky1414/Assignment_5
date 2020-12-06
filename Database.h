/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Faculty.h"
#include "FileIO.h"

using namespace std;

//A class that holds the database of students and faculty members, File handlers for their respective files, and methods to manipulate all four objects.
class Database {
  public:
    //Constructor/Destructor
    Database();
    ~Database();

    //Methods to print the databases.
    void printDatabasesToFile();
    void printDatabaseToConsole(bool studentListOrNot);

    //Methods to search the database for the given Student/Faculty
    Student* searchForStudent(int studentID);
    Faculty* searchForFaculty(int facultyID);

    //Methods to print advisor/advisee data.
    void printAdvisorOfStudent(int studentID);
    void printAdviseesOfFaculty(int facultyID);

    //Adds/deletes students and faculty to the databases.
    Student* addStudent();
    Faculty* addFaculty();
    Student* deleteStudent(int studentID);
    Faculty* deleteFaculty(int facultyID);

    //Changes the advisor/advisees for the students and faculty.
    void changeAdvisorForStudent(int studentID);
    void removeAdviseeFromFaculty(int facultyID, int studentID);

    //Methods to check the status of the how much data is in studentRecord and facultyRecord
    bool studentRecordHasData();
    bool facultyRecordHasData();
    bool facultyRecordHasMoreThanOneFaculty();

    //Methods used for backing up the databases.
    BST<Student*>* copyStudentRecord();
    BST<Faculty*>* copyFacultyRecord();
    BST<Student*>* restoreStudentRecord(BST<Student*>* backup);
    BST<Faculty*>* restoreFacultyRecord(BST<Faculty*>* backup);

  private:
    //Pointers to the BST's holding the studetnts and faculty.
    BST<Student*>* studentRecord;
    BST<Faculty*>* facultyRecord;

    //File handlers for the databases' files.
    FileIO* studentFileHandler;
    FileIO* facultyFileHandler;

    //Randomly determines an advisor for a student based on the data already stored in facultyRecord.
    int determineAdvisor(int oldAdvisor);
    int determineAdvisor();
};
