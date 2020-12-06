/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Database.h"

using namespace std;

//A class that holds copies of the BST's stored in the Database class. This is used in conjunction with Rollback to perform the rollback feature.
class BackupDatabase {
  public:
    //Constructors/Destructor
    BackupDatabase();
    BackupDatabase(BST<Student*>* studentRecord, BST<Faculty*>* facultyRecord);
    ~BackupDatabase();

    //Pointers to the backup trees. Public to allow easy access from Rollback and Database classes.
    BST<Student*>* backupStudentRecord;
    BST<Faculty*>* backupFacultyRecord;
};
