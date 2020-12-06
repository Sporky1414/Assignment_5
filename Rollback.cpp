/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Rollback.h"

using namespace std;

//Constructor: Initializes the stack of BackupDatabases
Rollback::Rollback() {
  backupStack = new GenStack<BackupDatabase*>();
}

//Destructor: Deletes the stack
Rollback::~Rollback() {
  delete backupStack;
}


//Pushes a new BackupDatabase to the stack. Calls removeOldBackup should 5 backups already be stored in the stack.
void Rollback::addNewBackup(BackupDatabase* newBackup) {
  if(backupStack->getSize() == 5) {
    removeOldBackup();
  }
  backupStack->push(newBackup);
}

//Pops and returns the top BackupDatabase in the stack
BackupDatabase* Rollback::restoreBackup() {
  return backupStack->pop();
}

//Removes the oldest BackupDatabases from backupStack
void Rollback::removeOldBackup() {
  //Creates a tempStack to hold the reversed BackupDatabases
  GenStack<BackupDatabase*>* tempStack = new GenStack<BackupDatabase*>();
  while(!backupStack->isEmpty()) {
    //Pushes the popped BackupDatabases from backupStack to tempStack
    tempStack->push(backupStack->pop());
  }
  //Pops from tempStack, which returns the oldest backup.
  BackupDatabase* oldBackup = tempStack->pop();
  //Deletes the old BackupDatabase and its data, freeing memory.
  delete oldBackup;
  while(!tempStack->isEmpty()) {
    //Pushes the popped BackupDatabases from tempStack to backupStack
    backupStack->push(tempStack->pop());
  }
  //BackupStack has now been freed of the oldest backup. Delete the tempStack that helped achieved this.
  delete tempStack;
}

//Gets the number of backups currently in the stack.
int Rollback::getNumOfBackupsStored() {
  return backupStack->getSize();
}

bool Rollback::backupsArePresent() {
  return !backupStack->isEmpty();
}
