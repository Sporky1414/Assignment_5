#include "Simulation.h"

using namespace std;

Simulation::Simulation() {
  database = new Database();
}

Simulation::~Simulation() {
  delete database;
}

void Simulation::run() {
  cout << "Welcome to the Chapman University Student and Faculty Database Program." << endl;
  cout << "To make a selection of what you wish to do, type in the corresponding number of the command you wish to execute." << endl;
  bool isFinished = false;
  while(!isFinished) {
    cout << "Make your selection now!" << endl;
    cout << "1. Print all students and their information." << endl;
    cout << "2. Print all faculty and their information." << endl;
    cout << "3. Display Student Information from ID." << endl;
    cout << "4. Display Faculty Information from ID." << endl;
    cout << "5. Get a student's faculty advisor information." << endl;
    cout << "6. Get the information of all a faculty member's advisees." << endl;
    cout << "7. Add a new student. (FACULTY MEMBER MUST BE PRESENT)" << endl;
    cout << "8. Delete a student." << endl;
    cout << "9. Add a new faculty." << endl;
    cout << "10. Delete a faculty member. (FACULTY MEMBER CAN NOT BE DELETED IF NO FACULTY MEMBERS WILL REMAIN AFTERWARDS.)" << endl;
    cout << "11. Change a student's faculty advisor." << endl;
    cout << "12. Remove an advisee from a faculty member." << endl;
    cout << "13. Rollback to Last Database Version." << endl;
    cout << "14. Exit program." << endl;
    string response = "";
    int selection = 0;
    getline(cin, response);
    if(checkIfStringIsNumber(response)) {
      stringstream ss(response);
      ss >> selection;
      ss.clear();
      switch(selection) {
        case 1:
          printStudents();
          break;
        case 2:
          printFaculty();
          break;
        case 3:
          displayStudent();
          break;
        case 4:
          displayFaculty();
          break;
        case 5:
          printAdvisorOfStudent();
          break;
        case 6:
          printAdviseesOfFaculty();
          break;
        case 7:
          addStudent();
          break;
        case 8:
          deleteStudent();
          break;
        case 9:
          addFaculty();
          break;
        case 10:
          deleteFaculty();
          break;
        case 11:
          changeAdvisorForStudent();
          break;
        case 12:
          removeAdviseeFromFaculty();
          break;
        case 13:
          rollback();
          break;
        case 14:
          isFinished = true;
          break;
        default:
          cout << "You did not enter a valid selection. Please try again." << endl;
          break;
      }
    } else {
      cout << "You did not enter a number. Please try again." << endl;
    }
  }
  cout << "Saving databases to file" << endl;
  database->printDatabasesToFile();
  cout << "Closing program. Goodbye!" << endl;
}

bool Simulation::checkIfStringIsNumber(string tempString) {
  //Empty strings automatically return false.
  if(tempString.length() < 1) {
    return false;
  }

  //Checks if each character in a string is a digit. If it is not, false is returned.
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      return false;
    }
  }
  //tempString is a number, true is returned.
  return true;
}

void Simulation::printStudents() {
  cout << "Printing all students." << endl;
  database->printDatabaseToConsole(true);
}

void Simulation::printFaculty() {
  cout << "Printing all faculty." << endl;
  database->printDatabaseToConsole(false);
}

void Simulation::displayStudent() {
  if(!database->studentRecordHasData()) {
    cout << "Student record is empty. Add students first!" << endl;
    return;
  }
  int tempID = 0;
  while(true) {
    cout << "Enter the ID number of the student to search for." << endl;
    tempID = getNumResponse();
    if(tempID != -1) {
      break;
    } else {
      cout << "Trying again." << endl;
    }
  }
  Student* tempStudent = database->searchForStudent(tempID);
  if(tempStudent == NULL) {
    cout << "The student with ID number " << tempID << " does not exist. Returning to main menu." << endl;
  } else {
    cout << "Printing info of student: " << endl;
    cout << tempStudent->printDataForUser() << endl;
  }
}

void Simulation::displayFaculty() {
  if(!database->facultyRecordHasData()) {
    cout << "Faculty record is empty. Add faculty first!" << endl;
    return;
  }
  int tempID = 0;
  while(true) {
    cout << "Enter the ID number of the faculty to search for." << endl;
    tempID = getNumResponse();
    if(tempID != -1) {
      break;
    } else {
      cout << "Trying again." << endl;
    }
  }
  Faculty* tempFaculty = database->searchForFaculty(tempID);
  if(tempFaculty == NULL) {
    cout << "The faculty with ID number " << tempID << " does not exist. Returning to main menu." << endl;
  } else {
    cout << tempFaculty->printDataForUser() << endl;
  }
}

void Simulation::printAdvisorOfStudent() {
  if(!database->studentRecordHasData()) {
    cout << "Student record is empty. Add students first!" << endl;
    return;
  }
  int tempID = 0;
  while(true) {
    cout << "Enter the ID number of the student to get the advisor of." << endl;
    tempID = getNumResponse();
    if(tempID != -1) {
      break;
    } else {
      cout << "Trying again." << endl;
    }
  }
  Student* tempStudent = database->searchForStudent(tempID);
  if(tempStudent == NULL) {
    cout << "The student with ID number " << tempID << " does not exist. Returning to main menu." << endl;
  } else {
    Faculty* tempFaculty = database->searchForFaculty(tempStudent->getFacultyAdvisorID());
    cout << "Advisor of " << tempStudent->getName() << " has the following information: " << endl;
    cout << tempFaculty->printDataForUser() << endl;
  }
}

void Simulation::printAdviseesOfFaculty() {
  if(!database->facultyRecordHasData()) {
    cout << "Faculty record is empty. Add faculty first!" << endl;
    return;
  }
  int tempID = 0;
  while(true) {
    cout << "Enter the ID number of the faculty to get the advisees of." << endl;
    tempID = getNumResponse();
    if(tempID != -1) {
      break;
    } else {
      cout << "Trying again." << endl;
    }
  }
  Faculty* tempFaculty = database->searchForFaculty(tempID);
  if(tempFaculty == NULL) {
    cout << "The faculty with ID number " << tempID << " does not exist. Returning to main menu." << endl;
  } else {
    cout << "Advisees of " << tempFaculty->getName() << " are the following: " << endl;
    ListADT<int>* tempList = tempFaculty->getListOfStudentAdviseeIDs();
    Student* tempStudent = NULL;
    int tempStudentID = 0;
    while(!tempList->isEmpty()) {
      tempStudentID = tempList->remove(tempList->valueAt(0));
      tempStudent = database->searchForStudent(tempStudentID);
      cout << tempStudent->printDataForUser() << "\n" << endl;
    }
  }
}

void Simulation::addStudent() {
  cout << "Preparing to add student. ID Number is randomly generated. Faculty Advisor is also randomly assigned. You can reassign the faculty advisor from the main menu." << endl;
  Student* tempStudent = database->addStudent();
  if(tempStudent != NULL) {
    cout << "Student added with following data: \n" << tempStudent->printDataForUser() << endl;
  }
}

void Simulation::addFaculty() {
  cout << "Preparing to add faculty." << endl;
  Faculty* tempFaculty = database->addFaculty();
  cout << "Faculty added with following data: \n" << tempFaculty->printDataForUser() << endl;
}

void Simulation::deleteStudent() {
  if(!database->studentRecordHasData()) {
    cout << "Student record is empty. No deleting possible." << endl;
    return;
  }
  int selection = 0;
  while(true) {
    cout << "Are you sure you wish to continue deleting a student? Type the number of your choice." << endl;
    cout << "1. Yes, I want to delete a student." << endl;
    cout << "2. No, I do not want to delete a student." << endl;
    selection = getNumResponse();
    if(selection == -1) {
      cout << "You did not enter a number. Please try again." << endl;
      continue;
    }
    switch(selection) {
      case 1: {
        int tempID = 0;
        while(true) {
          cout << "Enter the ID number of the student to delete." << endl;
          tempID = getNumResponse();
          if(tempID == -1) {
            cout << "You did not enter a number. Please try again." << endl;
          } else {
            Student* tempStudent = database->deleteStudent(tempID);
            if(tempStudent == NULL) {
              cout << "Student with ID number " << tempID << " does not exist. Returning to main menu." << endl;
              return;
            } else {
              cout << "The student with the following information has been deleted: " << endl;
              cout << tempStudent->printDataForUser() << endl;
              return;
            }
          }
        }
        break;
      }
      case 2:
        cout << "Not deleting student. Exiting to main menu." << endl;
        return;
        break;
      default:
        cout << "Invalid response. Please try again." << endl;
        break;
    }
  }
}

void Simulation::deleteFaculty() {
  if(!database->facultyRecordHasData()) {
    cout << "Faculty record is empty. No deleting possible." << endl;
    return;
  }
  if(!database->facultyRecordHasMoreThanOneFaculty()) {
    cout << "Can not delete faculty member since there is only one left. Add more faculty members to perform a delete operation." << endl;
    return;
  }
  int selection = 0;
  while(true) {
    cout << "Are you sure you wish to continue deleting a faculty member? Type the number of your choice." << endl;
    cout << "1. Yes, I want to delete a faculty member." << endl;
    cout << "2. No, I do not want to delete a faculty member." << endl;
    selection = getNumResponse();
    if(selection == -1) {
      cout << "You did not enter a number. Please try again." << endl;
      continue;
    }
    switch(selection) {
      case 1: {
        int tempID = 0;
        while(true) {
          cout << "Enter the ID number of the faculty member to delete." << endl;
          tempID = getNumResponse();
          if(tempID == -1) {
            cout << "You did not enter a number. Please try again." << endl;
          } else {
            Faculty* tempFaculty = database->deleteFaculty(tempID);
            if(tempFaculty == NULL) {
              cout << "Faculty member with ID number " << tempID << " does not exist. Returning to main menu." << endl;
              return;
            } else {
              cout << "The faculty member with the following information has been deleted: " << endl;
              cout << tempFaculty->printDataForUser() << endl;
              return;
            }
          }
        }
        break;
      }
      case 2:
        cout << "Not deleting faculty member. Exiting to main menu." << endl;
        return;
        break;
      default:
        cout << "Invalid response. Please try again." << endl;
        break;
    }
  }
}

void Simulation::changeAdvisorForStudent() {
  if(!database->studentRecordHasData() || !database->facultyRecordHasData()) {
    cout << "You do not have any students and/or faculty present. Please add data before trying this." << endl;
    return;
  }
  while(true) {
    cout << "Enter ID of student to change the advisor of." << endl;
    int tempID = getNumResponse();
    if(tempID == -1) {
      cout << "You did not enter a number. Please try again." << endl;
    } else {
      database->changeAdvisorForStudent(tempID);
      return;
    }
  }
}

void Simulation::removeAdviseeFromFaculty() {
  if(!database->studentRecordHasData() || !database->facultyRecordHasData()) {
    cout << "You do not have any students and/or faculty present. Please add data before trying this." << endl;
    return;
  }
  while(true) {
    cout << "Enter the ID number of the faculty member who is losing an advisee." << endl;
    int tempFacultyID = getNumResponse();
    if(tempFacultyID == -1) {
      cout << "You did not enter a number. Please try again." << endl;
    } else {
      while(true) {
        cout << "Enter the ID number of the student to remove from the list of this faculty member's advisee's" << endl;
        int tempStudentID = getNumResponse();
        if(tempStudentID == -1) {
          cout << "You did not enter a number. Please try again." << endl;
        } else {
          database->removeAdviseeFromFaculty(tempFacultyID, tempStudentID);
          return;
        }
      }
    }
  }
}

void Simulation::rollback() {
  cout << "COMING SOON" << endl;
}

int Simulation::getNumResponse() {
  string response = "";
  getline(cin, response);
  if(checkIfStringIsNumber(response)) {
    stringstream ss(response);
    int tempNum = 0;
    ss >> tempNum;
    ss.clear();
    return tempNum;
  } else {
    return -1;
  }
}
