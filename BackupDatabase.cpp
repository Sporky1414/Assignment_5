#include "BackupDatabase.h"

using namespace std;

BackupDatabase::BackupDatabase() {
  backupStudentRecord = NULL;
  backupFacultyRecord = NULL;
}

BackupDatabase::BackupDatabase(BST<Student*>* studentRecord, BST<Faculty*>* facultyRecord) {
  backupStudentRecord = studentRecord;
  backupFacultyRecord = facultyRecord;
}

BackupDatabase::~BackupDatabase() {
  delete backupStudentRecord;
  delete backupFacultyRecord;
}
