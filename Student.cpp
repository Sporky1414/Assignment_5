/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Student.h"

//Default Constructor: Sets all values to defaults.
Student::Student() {
 id = 0;
 name = "";
 level = "";
 major = "";
 gpa = 0;
 facultyAdvisor = 0;
}

//Main constructor: Sets Student ID, nameOfStudent, and faculty advisor from given data. Level, major, and GPA are achieved through setters.
Student::Student(int studentID, string nameOfStudent, int originalFacultyAdvisor) {
  id = studentID;
  name = nameOfStudent;
  setLevel();
  setMajor();
  setGPA();
  setNewAdvisor(originalFacultyAdvisor);
}

//Constructor: Converts data from a string into the information for the student.
//File Validity Checked in FileIO, so the string being input will be in correct format for this to work.
Student::Student(string dataFromFile) {
  //Read input.
  stringstream readingData(dataFromFile);
  string tempString = "";
  getline(readingData, tempString);
  //Get ID and convert to int.
  stringstream stringToNum(tempString);
  stringToNum >> id;
  stringToNum.clear();
  //Get name, level, and major. Store all 3.
  getline(readingData, name);
  getline(readingData, level);
  getline(readingData, major);
  //Get GPA and convert to Double.
  tempString = "";
  getline(readingData, tempString);
  stringToNum.str(tempString);
  stringToNum >> gpa;
  stringToNum.clear();
  //Get facultyAdvisor and convert to int.
  tempString = "";
  getline(readingData, tempString);
  stringToNum.str(tempString);
  stringToNum >> facultyAdvisor;
  stringToNum.clear();
  readingData.clear();
}

//Destructor: Nothing done here.
Student::~Student() {
  //No pointers to be deleted
}

//Getter for ID
int Student::getID() {
  return id;
}

//Getter for name.
string Student::getName() {
  return name;
}

//Getter for level
string Student::getLevel() {
  return level;
}

//Setter for level. Loops through until the string entered by the user matches one of the 5 possible options.
void Student::setLevel() {
  while(true) {
    cout << "Enter the grade of the student (Freshman, Sophomore, Junior, Senior, or Super Senior)." << endl;
    //Gets response from user.
    string tempLevel = "";
    getline(cin, tempLevel);
    level = "";
    //Capitalizes level.
    for(int i = 0; i < tempLevel.length(); ++i) {
      level += toupper(tempLevel[i]);
    } //Checks if level is valid. If not, user has to try again.
    if(level == "FRESHMAN" || level == "SOPHOMORE" || level == "JUNIOR" || level == "SENIOR" || level == "SUPER SENIOR") {
      break;
    } else {
      cout << "INVALID GRADE ENTERED. Please try again." << endl;
    }
  }
}

//Getter for major.
string Student::getMajor() {
  return major;
}

//Setter for major. Loops until a non-blank string is entered by user.
void Student::setMajor() {
  while(true) {
    cout << "Enter the major for the student." << endl;
    getline(cin, major);
    if(major != "") {
      break;
    } else {
      cout << "Nothing entered. Please try again." << endl;
    }
  }
}

//Getter for gpa
double Student::getGPA() {
  return gpa;
}

//Setter for GPA
void Student::setGPA() {
  bool isFinished = false;
  gpa = -1;
  while(!isFinished) {
    //Loops until valid GPA is given.
    cout << "Enter the student's GPA." << endl;
    string tempGPA = "";
    getline(cin, tempGPA);
    bool decimalFound = false;
    bool isNum = false;
    //Takes in response and checks if it is a double. Same methodology used as for the format checker in FileIO.
    for(int i = 0; i < tempGPA.length(); ++i) {
      if(!isdigit(tempGPA[i])) {
        if(!decimalFound && tempGPA[i] == '.') {
          decimalFound = true;
        } else {
          isNum = false;
          break;
        }
      } else {
        isNum = true;
      }
    }
    if(isNum) {
      //GPA passed test and is a number. Stored as such.
      stringstream stringToNum(tempGPA);
      double tempGPANum = 0;
      stringToNum >> tempGPANum;
      //If the GPA is 0 <= gpa <= 4, it will be stored and the method will end. Otherwise, the user has to try again.
      if(tempGPANum < 0.0) {
        cout << "ERROR: The GPA you entered is less than 0. Please try again." << endl;
        stringToNum.clear();
      } else if (tempGPANum > 4.0) {
        cout << "ERROR: The GPA you entered is greater than 4. Please try again." << endl;
        stringToNum.clear();
      } else {
        gpa = tempGPANum;
        stringToNum.clear();
      }
    } else {
      //User did not enter a number, so they have to try again.
      cout << "ERROR: Number not entered. Please try again." << endl;
    }
    if(gpa != -1) {
      //If a gpa is stored that is not -1 (default), loop boolean will become true to end loop.
      isFinished = true;
    }
  }
}

//Getter for facultyAdvisor
int Student::getFacultyAdvisorID() {
  return facultyAdvisor;
}

//Setter for facultyAdvisor
void Student::setNewAdvisor(int newFacultyAdvisorID) {
  facultyAdvisor = newFacultyAdvisorID;
}

//Overrides ==, compares students based on ID. If compared with a faculty, automatic false since students are not equal to faculty members.
bool Student::operator ==(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return false;
  }
  return id == otherPerson.id;
}

//Deprecated, but returns corresponding number to grade based on seniority.
int Student::getLevelNumber(string thisLevel) {
  int firstLevel = 0;
  if(thisLevel.compare("FRESHMAN") == 0) {
    firstLevel = 0;
  } else if (thisLevel.compare("SOPHOMORE") == 0) {
    firstLevel = 1;
  } else if (thisLevel.compare("JUNIOR") == 0) {
    firstLevel = 2;
  } else if (thisLevel.compare("SENIOR") == 0) {
    firstLevel = 3;
  } else {
    firstLevel = 4;
  }
  return firstLevel;
}

//Overrides <, compares students based on ID. If compared with a faculty, automatic true since students are less than faculty members.
bool Student::operator <(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return true;
  }
  return id < otherPerson.id;
}

//Overrides >, compares students based on ID. If compared with a faculty, automatic false since students are not greater than faculty members.
bool Student::operator >(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return false;
  }
  return id > otherPerson.id;
}

//Overrides <=, compares students based on ID. If compared with a faculty, automatic true since students are less than or equal to faculty members.
bool Student::operator <=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return true;
  }
  return id <= otherPerson.id;
}

//Overrides >=, compares students based on ID. If compared with a faculty, automatic false since students are not greater than or equal to faculty members.
bool Student::operator >=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return false;
  }
  return id >= otherPerson.id;
}

//Overrides << to output the data of Student in the file format.
ostream &operator <<(ostream &out, Student &student) {
  string tempString = to_string(student.id) + "\n" + student.name + "\n" + student.level + "\n" + student.major + "\n" + to_string(student.gpa) + "\n" + to_string(student.facultyAdvisor) + "\n";
  out << tempString;
  return out;
}

//Overrides to_string to return string written in output
string to_string(Student student) {
  ostringstream ss;
  ss << student;
  return ss.str();
}

//Gets the student data in a user-friendly format and returns that string.
string Student::printDataForUser() {
  string returnString = "STUDENT ID: " + to_string(id) + "\n";
  returnString += "STUDENT NAME: " + name + "\n";
  returnString += "STUDENT LEVEL: " + level + "\n";
  returnString += "STUDENT MAJOR: " + major + "\n";
  returnString += "STUDENT GPA: "  + to_string(gpa) + "\n";
  returnString += "STUDENT'S FACULTY ADVISOR'S ID: " + to_string(facultyAdvisor) + "\n";
  return returnString;
}
