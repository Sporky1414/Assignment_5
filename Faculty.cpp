#include "Faculty.h"

using namespace std;

Faculty::Faculty() {
  id = 0;
  name = "";
  level = "";
  department = "";
  listOfStudentAdviseeIDs = NULL;
}

Faculty::Faculty(int facultyID, string facultyName) {
  id = facultyID;
  name = facultyName;
  setLevel();
  setDepartment();
  listOfStudentAdviseeIDs = new LinkedList<int>();
}

Faculty::Faculty(string dataFromFile) {
  stringstream readingData(dataFromFile);
  string tempString = "";
  getline(readingData, tempString);
  stringstream stringToNum(tempString);
  stringToNum >> id;
  stringToNum.clear();
  getline(readingData, name);
  getline(readingData, level);
  getline(readingData, department);
  tempString = "";
  getline(readingData, tempString);
  stringToNum.str(tempString);
  int tempLength = 0;
  stringToNum >> tempLength;
  stringToNum.clear();
  int tempID = 0;
  listOfStudentAdviseeIDs = new LinkedList<int>();
  for(int i = 0; i < tempLength; ++i) {
    tempString = "";
    getline(readingData, tempString);
    stringToNum.str(tempString);
    stringToNum >> tempID;
    listOfStudentAdviseeIDs->append(tempID);
    stringToNum.clear();
    tempID = 0;
  }
  stringToNum.clear();
  readingData.clear();
}

//Do not run destrucotr unless all advisees have been removed from list.
Faculty::~Faculty() {
  delete listOfStudentAdviseeIDs;
}

int Faculty::getID() {
  return id;
}

string Faculty::getName() {
  return name;
}

string Faculty::getLevel() {
  return level;
}

void Faculty::setLevel() {
  while(true) {
    cout << "Enter the level of the faculty member (Adjunct Instructor, "
      << "Graduate Teaching Assistant, Visitng Professor, Assistant Professor, Associate Professor, "
      << "Full Professor, Endowed Professor, Distinguished Professor, Administrator, Professor Emeritus)." << endl;
    string tempString = "";
    getline(cin, tempString);
    level = "";
    for(int i = 0; i < tempString.length(); ++i) {
      level += toupper(tempString[i]);
    }
    if(level.compare("ADJUNCT INSTRUCTOR") == 0 || level.compare("GRADUATE TEACHING ASSISTANT") == 0
      || level.compare("VISITING PROFESSOR") == 0 || level.compare("ASSISTANT PROFESSOR") == 0
      || level.compare("ASSOCIATE PROFESSOR") == 0 || level.compare("FULL PROFESSOR") == 0
      || level.compare("ENDOWED PROFESSOR") == 0 || level.compare("DISTINGUISHED PROFESSOR") == 0
      || level.compare("ADMINISTRATOR") == 0 || level.compare("PROFESSOR EMERITUS") == 0) {
        break;
    } else {
      cout << "INVALID LEVEL ENTERED. Please try again" << endl;
    }
  }
}

string Faculty::getDepartment() {
  return department;
}

void Faculty::setDepartment() {
  while(true) {
    cout << "Enter the department the faculty member works for." << endl;
    getline(cin, department);
    if(department != "") {
      break;
    } else {
      cout << "Nothing was entered. Please try again." << endl;
    }
  }
}

int Faculty::getLevelNumber(string thisLevel) {
  if(thisLevel.compare("ADJUNCT INSTRUCTOR") == 0) {
    return 0;
  } else if (thisLevel.compare("GRADUATE TEACHING ASSISTANT") == 0) {
    return 1;
  } else if (thisLevel.compare("VISITING PROFESSOR") == 0) {
    return 2;
  } else if (thisLevel.compare("ASSISTANT PROFESSOR") == 0) {
    return 3;
  } else if (thisLevel.compare("ASSOCIATE PROFESSOR") == 0) {
    return 4;
  } else if (thisLevel.compare("FULL PROFESSOR") == 0) {
    return 5;
  } else if (thisLevel.compare("ENDOWED PROFESSOR") == 0) {
    return 6;
  } else if (thisLevel.compare("DISTINGUISHED PROFESSOR") == 0) {
    return 7;
  } else if (thisLevel.compare("ADMINISTRATOR") == 0) {
    return 8;
  }
  return 9;
}

void Faculty::getPrintedListOfStudentAdviseeIDs() {
  listOfStudentAdviseeIDs->print();
}

void Faculty::addStudentAdvisee(Student* student) {
  int tempId = student->getID();
  listOfStudentAdviseeIDs->append(tempId);
}

int Faculty::deleteStudentFromAdviseeList(int studentID) {
  listOfStudentAdviseeIDs->remove(studentID);
}

bool Faculty::operator ==(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return false;
  }
  return id == otherPerson.id;
}

bool Faculty::operator <(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return false;
  }
  return id < otherPerson.id;
}

bool Faculty::operator >(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return true;
  }
  return id > otherPerson.id;
}

bool Faculty::operator <=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return false;
  }
  return id <= otherPerson.id;
}

bool Faculty::operator >=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return true;
  }
  return id >= otherPerson.id;
}

ostream &operator<<(ostream &out, Faculty &faculty) {
  string returnString = to_string(faculty.id) + "\n";
  returnString += faculty.name + "\n";
  returnString += faculty.level + "\n";
  returnString += faculty.department + "\n";
  returnString += to_string(faculty.listOfStudentAdviseeIDs->getLength()) + "\n";
  for(int i = 0; i < faculty.listOfStudentAdviseeIDs->getLength(); ++i) {
    returnString += to_string(faculty.listOfStudentAdviseeIDs->valueAt(i)) + "\n";
  }
  out << returnString;
  return out;
}

string to_string(Faculty &faculty) {
  ostringstream ss;
  ss << faculty;
  return ss.str();
}

string Faculty::printDataForUser() {
  string returnString = "FACULTY ID: " + to_string(id) + "\n";
  returnString += "FACULTY NAME: " + name + "\n";
  returnString += "FACULTY LEVEL: " + level + "\n";
  returnString += "FACULTY DEPARTMENT: " + department + "\n";
  returnString += "STUDENT ID'S OF ALL ADVISEES: \n";
  for(int i = 0; i < listOfStudentAdviseeIDs->getLength(); ++i) {
    returnString += "   " + to_string(listOfStudentAdviseeIDs->valueAt(i)) + "\n";
  }
  return returnString;
}

ListADT<int>* Faculty::getListOfStudentAdviseeIDs() {
  ListADT<int>* newList = new LinkedList<int>();
  for(int i = 0; i < listOfStudentAdviseeIDs->getLength(); ++i) {
    newList->append(listOfStudentAdviseeIDs->valueAt(i));
  }
  return newList;
}
