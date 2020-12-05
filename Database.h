#include "Faculty.h"
#include "FileIO.h"

using namespace std;

class Database {
  public:
    Database();
    ~Database();

    void printDatabasesToFile();
    void printDatabaseToConsole(bool studentListOrNot);
    Student* searchForStudent(int studentID);
    Faculty* searchForFaculty(int facultyID);
    void printAdvisorOfStudent(int studentID);
    void printAdviseesOfFaculty(int facultyID);
    void addStudent();
    void addFaculty();
    Student* deleteStudent(int studentID);
    Faculty* deleteFaculty(int facultyID);
    void changeAdvisorForStudent(int studentID);
    void removeAdviseeFromFaculty(int facultyID, int studentID);

  private:
    BST<Student*>* studentRecord;
    BST<Faculty*>* facultyRecord;
    FileIO* studentFileHandler;
    FileIO* facultyFileHandler;

    int determineAdvisor();
};
