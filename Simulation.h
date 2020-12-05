#include "Database.h"

using namespace std;

class Simulation {
  public:
    Simulation();
    ~Simulation();

    void run();

  private:
    void printStudents();
    void printFaculty();
    void displayStudent();
    void displayFaculty();
    void printAdvisorOfStudent();
    void printAdviseesOfFaculty();
    void addStudent();
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeAdvisorForStudent();
    void removeAdviseeFromFaculty();
    void rollback();

    bool checkIfStringIsNumber(string tempString);

    int getNumResponse();

    Database* database;
};
