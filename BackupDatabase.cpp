/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "BackupDatabase.h"

using namespace std;

//Constructor: Default constructor that sets the two BST pointers to NULL.
BackupDatabase::BackupDatabase() {
  backupStudentRecord = NULL;
  backupFacultyRecord = NULL;
}

//Constructor: Constructor takes in the BST's from Database to store as backups.
BackupDatabase::BackupDatabase(BST<Student*>* studentRecord, BST<Faculty*>* facultyRecord) {
  backupStudentRecord = studentRecord;
  backupFacultyRecord = facultyRecord;
}

//Deletes the records stored. The pointers are safe to delete here because they
//are copies of the original trees and all their data, meaning nothing valuable is lost when
//these pointers are deleted.
BackupDatabase::~BackupDatabase() {
  delete backupStudentRecord;
  delete backupFacultyRecord;
}
