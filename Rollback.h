#include "BackupDatabase.h"
#include "Stack.cpp"

using namespace std;

class Rollback {
  public:
    Rollback();
    ~Rollback();

    void addNewBackup(BackupDatabase* newBackup);
    BackupDatabase* restoreBackup();

    int getNumOfBackupsStored();
    bool backupsArePresent();

  private:
    GenStack<BackupDatabase*>* backupStack;

    void removeOldBackup();
};
