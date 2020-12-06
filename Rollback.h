/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "BackupDatabase.h"
#include "Stack.cpp"

using namespace std;

//Class to store 5 backups of the Database class's BST's. Achieved with a stack of BackupDatabases, which holds the two BST's.
class Rollback {
  public:
    //Constructor/Destructor
    Rollback();
    ~Rollback();

    //Push/pop backups in stack.
    void addNewBackup(BackupDatabase* newBackup);
    BackupDatabase* restoreBackup();

    //Get the number of backups in the stack or if there are any at all.
    int getNumOfBackupsStored();
    bool backupsArePresent();

  private:
    //Stack to hold the BackupDatabases
    GenStack<BackupDatabase*>* backupStack;

    //Remove oldest backup should there already be 5 in the stack.
    void removeOldBackup();
};
