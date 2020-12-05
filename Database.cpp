#include "Database.h"

using namespace std;

Database::Database() {
  srand(time(NULL));
  studentRecord = new BST<Student*>();
  facultyRecord = new BST<Faculty*>();
  studentFileHandler = new FileIO("studentTable.txt");
  facultyFileHandler = new FileIO("facultyTable.txt");
  bool isBlank = false;
  if(studentFileHandler->hasInput()) {
    while(studentFileHandler->inputHasDataLeft()) {
      string tempData = "";
      int tempID = 0;
      for(int i = 0; i < 6; ++i) {
        string tempString = studentFileHandler->readNextLine();
        if(tempString == "") {
          if(i == 0) {
            isBlank = true;
            i = 8;
          } else {
            i--;
            continue;
          }
        }
        tempData += tempString;
        if(i == 0) {
          stringstream ss(tempData);
          ss >> tempID;
          ss.clear();
        }
        if(i != 5) {
          tempData += "\n";
        }
      }
      cout << "EOFL" << endl;
      if(!isBlank) {
        studentRecord->insertNode(tempID, new Student(tempData));
      }
      isBlank = false;
    }
    cout << "FOLLOWING STUDENT DATABSE LOADED FROM FILE: " << endl;
    printDatabaseToConsole(true);
  }
  isBlank = false;
  if(facultyFileHandler->hasInput()) {
    while(facultyFileHandler->inputHasDataLeft()) {
      string tempData = "";
      int tempID = 0;
      int numOfAdvisees = 0;
      for(int i = 0; i < 5; ++i) {
        if(i == 4) {
          string tempString = facultyFileHandler->readNextLine();
          stringstream ss(tempString);
          ss >> numOfAdvisees;
          tempData += tempString;
        } else {
          tempData += facultyFileHandler->readNextLine();
          if(i == 0) {
            if(tempData == "") {
              isBlank = true;
              break;
            }
            stringstream ss(tempData);
            ss >> tempID;
            ss.clear();
          }
        }
        tempData += "\n";
      }
      if(isBlank) {
        break;
      }
      for(int i = 0; i < numOfAdvisees; ++i) {
        tempData += facultyFileHandler->readNextLine();
        if(i != numOfAdvisees - 1) {
          tempData += "\n";
        }
      }
      facultyRecord->insertNode(tempID, new Faculty(tempData));
      isBlank = false;
    }
    cout << "FOLLOWING FACULTY DATABSE LOADED FROM FILE: " << endl;
    printDatabaseToConsole(false);
  }
}

Database::~Database() {
  delete studentFileHandler;
  delete facultyFileHandler;
  delete studentRecord;
  delete facultyRecord;
}

void Database::printDatabasesToFile() {
  string returnString = "";
  returnString += studentRecord->printPostOrderPointer();
  studentFileHandler->closeInputAndWriteData(returnString);
  returnString = "";
  returnString += facultyRecord->printPostOrderPointer();
  facultyFileHandler->closeInputAndWriteData(returnString);
}

void Database::printDatabaseToConsole(bool studentListOrNot) {
  if(studentListOrNot) {
    for(int i = 0; i <=studentRecord->getMax(); ++i) {
      if(studentRecord->searchNode(i)) {
        cout << studentRecord->getDataOfNodeFromKey(i)->printDataForUser() << endl;
      }
    }
  } else {
    for(int i = 0; i <= facultyRecord->getMax(); ++i) {
      if(facultyRecord->searchNode(i)) {
        cout << facultyRecord->getDataOfNodeFromKey(i)->printDataForUser() << endl;
      }
    }
  }
}

Student* Database::searchForStudent(int studentID) {
  return studentRecord->getDataOfNodeFromKey(studentID);
}

Faculty* Database::searchForFaculty(int facultyID) {
  return facultyRecord->getDataOfNodeFromKey(facultyID);
}

void Database::printAdvisorOfStudent(int studentID) {
  if(studentRecord->searchNode(studentID)) {
    Student* tempStudent = studentRecord->getDataOfNodeFromKey(studentID);
    int facultyID = tempStudent->getFacultyAdvisorID();
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(facultyID);
    cout << tempFaculty->printDataForUser() << endl;
  } else {
    cout << "STUDENT " << studentID << " DOES NOT EXIST." << endl;
  }
}

void Database::printAdviseesOfFaculty(int facultyID) {
  if(facultyRecord->searchNode(facultyID)) {
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(facultyID);
    ListADT<int>* tempAdviseeList = tempFaculty->getListOfStudentAdviseeIDs();
    for(int i = 0; i < tempAdviseeList->getLength(); ++i) {
      Student* tempStudent = studentRecord->getDataOfNodeFromKey(tempAdviseeList->valueAt(i));
      cout << tempStudent->printDataForUser() << endl;
    }
    delete tempAdviseeList;
  } else {
    cout << "FACULTY " << facultyID << " DOES NOT EXIST." << endl;
  }
}

void Database::addStudent() {
  if(facultyRecord->isEmpty()) {
    cout << "ERROR: CAN NOT ADD STUDENT IF THERE IS NO ONE TO TEACH THEM! PLEASE TRY AGAIN." << endl;
    return;
  }
  int tempID = 2;
  while(studentRecord->searchNode(tempID) || facultyRecord->searchNode(tempID)) {
    tempID = 1 + rand()/((RAND_MAX)/100000);
  }
  cout << "Enter the name of the student being added." << endl;
  string tempName = "";
  getline(cin, tempName);
  int tempFacultyID = determineAdvisor();
  studentRecord->insertNode(tempID, new Student(tempID, tempName, tempFacultyID));
  Student* tempStudent = studentRecord->getDataOfNodeFromKey(tempID);
  Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(tempFacultyID);
  tempFaculty->addStudentAdvisee(tempStudent);
}

void Database::addFaculty() {
  int tempID = 1;
  while(studentRecord->searchNode(tempID) || facultyRecord->searchNode(tempID)) {
    tempID = 1 + rand()/((RAND_MAX)/100000);
  }
  cout << "Enter the name of the faculty being added." << endl;
  string tempName = "";
  getline(cin, tempName);
  facultyRecord->insertNode(tempID, new Faculty(tempID, tempName));
}

int Database::determineAdvisor() {
  LinkedList<int>* keysInOrder = facultyRecord->getListOfKeysInOrder();
  int idOfMin = keysInOrder->valueAt(0);
  int minAdvisees = studentRecord->getNumOfKeys();
  int tempID = 0;
  while(!keysInOrder->isEmpty()) {
    tempID = keysInOrder->remove(keysInOrder->valueAt(0));
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(tempID);
    ListADT<int>* tempListOfAdvisees = tempFaculty->getListOfStudentAdviseeIDs();
    if(minAdvisees > tempListOfAdvisees->getLength()) {
      idOfMin = tempID;
      minAdvisees = tempListOfAdvisees->getLength();
    }
    delete tempListOfAdvisees;
  }
  delete keysInOrder;
  return idOfMin;
}

Student* Database::deleteStudent(int studentID) {
  LinkedList<int>* keysInOrder = facultyRecord->getListOfKeysInOrder();
  int tempID = 0;
  while(!keysInOrder->isEmpty()) {
    tempID = keysInOrder->remove(keysInOrder->valueAt(0));
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(tempID);
    ListADT<int>* tempList = tempFaculty->getListOfStudentAdviseeIDs();
    if(tempList->searchFor(studentID) > -1) {
      tempFaculty->deleteStudentFromAdviseeList(studentID);
    }
    delete tempList;
  }
  delete keysInOrder;
  if(studentRecord->searchNode(studentID)) {
    Student* tempStudent = studentRecord->getDataOfNodeFromKey(studentID);
    studentRecord->deleteNode(studentID);
    return tempStudent;
  } else {
    cout << "Student does not exist. Returning NULL." << endl;
    return NULL;
  }
}

Faculty* Database::deleteFaculty(int facultyID) {
  if(facultyRecord->searchNode(facultyID)) {
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(facultyID);
    facultyRecord->deleteNode(facultyID);
    LinkedList<int>* keysInOrder = studentRecord->getListOfKeysInOrder();
    int tempID = 0;
    while(!keysInOrder->isEmpty()) {
      tempID = keysInOrder->remove(keysInOrder->valueAt(0));
      Student* tempStudent = studentRecord->getDataOfNodeFromKey(tempID);
      if(tempStudent->getFacultyAdvisorID() == facultyID) {
        cout << "Student Advisee " << tempStudent->getName() << " found." << endl;
        changeAdvisorForStudent(tempID);
      }
    }
    delete keysInOrder;
    return tempFaculty;
  } else {
    cout << "Faculty does not exist. Returning NULL." << endl;
    return NULL;
  }
}

void Database::changeAdvisorForStudent(int studentID) {
  if(studentRecord->searchNode(studentID)) {
    Student* tempStudent = studentRecord->getDataOfNodeFromKey(studentID);
    while(true) {
      cout << "Do you wish to assign this student's new advisor manually or automatically? Type '1' for manually or '2' for automatically." << endl;
      string tempResponse = "";
      getline(cin, tempResponse);
      if(studentFileHandler->checkIfStringIsNumber(tempResponse)) {
        int tempInt = 0;
        stringstream ss(tempResponse);
        ss >> tempInt;
        ss.clear();
        int facultyAdvisorID = 0;
        if(tempInt == 1) {
          while (true) {
            cout << "Enter the ID number of the new faculty advisor." << endl;
            getline(cin, tempResponse);
            if(studentFileHandler->checkIfStringIsNumber(tempResponse)) {
              ss.str(tempResponse);
              ss >> facultyAdvisorID;
              ss.clear();
              if(facultyRecord->searchNode(facultyAdvisorID)) {
                tempStudent->setNewAdvisor(facultyAdvisorID);
                break;
              } else {
                cout << "Number input does not correspond with a faculty member. Please try again." << endl;
              }
            } else {
              cout << "Input was not a number. Please try again." << endl;
            }
          }
          break;
        } else if (tempInt == 2) {
          tempStudent->setNewAdvisor(determineAdvisor());
          break;
        } else {
          cout << "Invalid Number given. Please try again." << endl;
        }
      } else {
        cout << "Number not entered. Please try again." << endl;
      }
    }
  } else {
    cout << "STUDENT " << studentID << " DOES NOT EXIST." << endl;
  }
}

void Database::removeAdviseeFromFaculty(int facultyID, int studentID) {
  if(facultyRecord->searchNode(facultyID) && studentRecord->searchNode(studentID)) {
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(facultyID);
    ListADT<int>* tempList = tempFaculty->getListOfStudentAdviseeIDs();
    if(tempList->searchFor(studentID) > -1) {
      tempFaculty->deleteStudentFromAdviseeList(studentID);
    }
    delete tempList;
    cout << "Student removed from Faculty Advisee List. You now must reassign the student." << endl;
    changeAdvisorForStudent(studentID);
  } else {
    cout << "ERROR: FACULTY ID OR STUDENT ID DO NOT POINT TO A VALID STUDENT. PLEASE TRY AGAIN." << endl;
  }
}
