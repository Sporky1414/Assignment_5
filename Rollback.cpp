#include "Rollback.h"

using namespace std;

Rollback::Rollback() {
  backupStack = new GenStack<BackupDatabase*>();
}

Rollback::~Rollback() {
  delete backupStack;
}

void Rollback::addNewBackup(BackupDatabase* newBackup) {
  if(backupStack->getSize() == 5) {
    removeOldBackup();
  }
  backupStack->push(newBackup);
}

BackupDatabase* Rollback::restoreBackup() {
  return backupStack->pop();
}

void Rollback::removeOldBackup() {
  GenStack<BackupDatabase*>* tempStack = new GenStack<BackupDatabase*>();
  while(!backupStack->isEmpty()) {
    tempStack->push(backupStack->pop());
  }
  BackupDatabase* oldBackup = tempStack->pop();
  delete oldBackup;
  while(!tempStack->isEmpty()) {
    backupStack->push(tempStack->pop());
  }
  delete tempStack;
}

int Rollback::getNumOfBackupsStored() {
  return backupStack->getSize();
}

bool Rollback::backupsArePresent() {
  return !backupStack->isEmpty();
}
