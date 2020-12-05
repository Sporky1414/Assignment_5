#include "Database.h"

using namespace std;

int main (int argc, char** argv) {
  Database* database = new Database();
  database->printDatabaseToConsole(true);
  cout << endl;
  database->printDatabaseToConsole(false);
  cout << "Enter the ID number of a student to delete." << endl;
  string tempResponse = "";
  getline(cin, tempResponse);
  stringstream ss(tempResponse);
  int id;
  ss >> id;
  ss.clear();
  tempResponse = "";
  cout << "STUDENT BEING DELETED: " << database->deleteStudent(id) << endl;
  database->printDatabaseToConsole(true);
  cout << endl;
  database->printDatabaseToConsole(false);
  cout << "Enter the ID number of a faculty to delete." << endl;
  getline(cin, tempResponse);
  ss.str(tempResponse);
  ss >> id;
  ss.clear();
  cout << "FACULTY BEING DELETED: " << database->deleteFaculty(id) << endl;
  database->printDatabaseToConsole(true);
  cout << endl;
  database->printDatabaseToConsole(false);
  cout << "Searching for Student 2" << endl;
  if(database->searchForStudent(2) == NULL) {
    cout << "NOT PRESENT" << endl;
  } else {
    cout << "DISPLAYING ADVISOR: " << endl;
    database->printAdvisorOfStudent(2);
  }
  cout << "Searching for Faculty 5" << endl;
  if(database->searchForFaculty(1) == NULL) {
    cout << "NOT PRESENT" << endl;
  } else {
    cout << "DISPLAYING ADVISEES: " << endl;
    database->printAdviseesOfFaculty(1);
  }
  database->printDatabasesToFile();
  delete database;
}
