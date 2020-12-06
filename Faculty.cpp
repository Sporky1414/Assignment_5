/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Faculty.h"

using namespace std;

//Default Constructor: Gives default values to all members of class.
Faculty::Faculty() {
  id = 0;
  name = "";
  level = "";
  department = "";
  listOfStudentAdviseeIDs = NULL;
}

//Constructor: Assigns id and name from arguments. Uses setLevel() and setDepartment() to determine those members. Creates an empty linked list for the advisees.
Faculty::Faculty(int facultyID, string facultyName) {
  id = facultyID;
  name = facultyName;
  setLevel();
  setDepartment();
  listOfStudentAdviseeIDs = new LinkedList<int>();
}

//Constructor:: Gets data for faculty member from a string from a file. Format needs to be checked already in Database for this to work.
Faculty::Faculty(string dataFromFile) {
  //Gets Id from dataFromFile and stores in ID (after converting it to an int.)
  stringstream readingData(dataFromFile);
  string tempString = "";
  getline(readingData, tempString);
  stringstream stringToNum(tempString);
  stringToNum >> id;
  stringToNum.clear();
  //Gets name, level, and department from  dataFromFile.
  getline(readingData, name);
  getline(readingData, level);
  getline(readingData, department);
  //Gets number of advisees from file and notes it in order to properly get the advisees stored..
  tempString = "";
  getline(readingData, tempString);
  stringToNum.str(tempString);
  int tempLength = 0;
  stringToNum >> tempLength;
  stringToNum.clear();
  int tempID = 0;
  //Initalizes the linked list. Iterates through remainder of dataFromFile to store the advisees in this linked list.
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
  //Clears streams used to read dataFromFile/convert the strings to ints.
  stringToNum.clear();
  readingData.clear();
}

//Destructor: Deletes the linked list. Can not be deleted unless all advisees have been removed and reassigned.
Faculty::~Faculty() {
  delete listOfStudentAdviseeIDs;
}

//Getter for ID
int Faculty::getID() {
  return id;
}

//Getter for name
string Faculty::getName() {
  return name;
}

//Getter for name
string Faculty::getLevel() {
  return level;
}

//Setter for level
void Faculty::setLevel() {
  //Loops until valid response given.
  while(true) {
    cout << "Enter the level of the faculty member (Adjunct Instructor, "
      << "Graduate Teaching Assistant, Visitng Professor, Assistant Professor, Associate Professor, "
      << "Full Professor, Endowed Professor, Distinguished Professor, Administrator, Professor Emeritus)." << endl;
    //Gets response
    string tempString = "";
    getline(cin, tempString);
    level = "";
    //Converts response to all uppercase.
    for(int i = 0; i < tempString.length(); ++i) {
      level += toupper(tempString[i]);
    }
    //If the capitalized response does not match one of the following strings, the loop is repeated. Otherwise, it ends.
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

//Getter for department
string Faculty::getDepartment() {
  return department;
}

//Setter for department.
void Faculty::setDepartment() {
  //Loops until a non-blank string is entered as a response.
  while(true) {
    cout << "Enter the department the faculty member works for." << endl;
    getline(cin, department);
    if(department != "") {
      //Valid string entered, leave loop.
      break;
    } else {
      //Empty string entered. Loop repeats.
      cout << "Nothing was entered. Please try again." << endl;
    }
  }
}

//Gets an int for the corresponding level, as per the Best Schools hierarchy online. Deprecated for this assignment.
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

//Prints listOfStudentAdviseeIDs
void Faculty::getPrintedListOfStudentAdviseeIDs() {
  listOfStudentAdviseeIDs->print();
}

//Appends the id of student to listOfStudentAdviseeIDs
void Faculty::addStudentAdvisee(Student* student) {
  int tempId = student->getID();
  listOfStudentAdviseeIDs->append(tempId);
}

//Removes studentID from listOfStudentAdviseeIDs
int Faculty::deleteStudentFromAdviseeList(int studentID) {
  listOfStudentAdviseeIDs->remove(studentID);
  return studentID;
}

//Overrides ==, compares faculty members based on ID. If compared with a student, automatic false since students are not equal to faculty members.
bool Faculty::operator ==(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return false;
  }
  return id == otherPerson.id;
}

//Overrides <, compares faculty members based on ID. If compared with a student, automatic false since faculty members are not less than students in terms of importance.
bool Faculty::operator <(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return false;
  }
  return id < otherPerson.id;
}

//Overrides >, compares faculty members based on ID. If compared with a student, automatic true since faculty members are greater than students in terms of importance.
bool Faculty::operator >(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return true;
  }
  return id > otherPerson.id;
}

//Overrides <=, compares faculty members based on ID. If compared with a student, automatic false since faculty members are not less than or equal to students in terms of importance.
bool Faculty::operator <=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return false;
  }
  return id <= otherPerson.id;
}

//Overrides >=, compares faculty members based on ID. If compared with a student, automatic true since faculty members are greater than or equal to students in terms of importance.
bool Faculty::operator >=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Faculty") {
    return true;
  }
  return id >= otherPerson.id;
}


//Overrides << to output the data of Faculty in the file format.
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

//Overrides to_string to return string written in output
string to_string(Faculty &faculty) {
  ostringstream ss;
  ss << faculty;
  return ss.str();
}

//Gets the faculty data in a user-friendly format and returns that string.
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

//Creates a copy of the listOfStudentAdviseeIDs
ListADT<int>* Faculty::getListOfStudentAdviseeIDs() {
  ListADT<int>* newList = new LinkedList<int>();
  for(int i = 0; i < listOfStudentAdviseeIDs->getLength(); ++i) {
    newList->append(listOfStudentAdviseeIDs->valueAt(i));
  }
  return newList;
}
