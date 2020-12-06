#include "Database.h"

using namespace std;

class BackupDatabase {
  public:
    BackupDatabase();
    BackupDatabase(BST<Student*>* studentRecord, BST<Faculty*>* facultyRecord);
    ~BackupDatabase();

    BST<Student*>* backupStudentRecord;
    BST<Faculty*>* backupFacultyRecord;
};
