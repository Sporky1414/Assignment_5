#include "Student.h"

Student::Student() {
 id = 0;
 name = "";
 level = "";
 major = "";
 gpa = 0;
 facultyAdvisor = 0;
}

Student::Student(int studentID, string nameOfStudent, int originalFacultyAdvisor) {
  id = studentID;
  name = nameOfStudent;
  setLevel();
  setMajor();
  setGPA();
  setNewAdvisor(originalFacultyAdvisor);
}

//File Validity Checked in FileIO, so the string being input will be in correct format for this to work.
Student::Student(string dataFromFile) {
  cout << "DATA FROM FILE TO MAKE A STUDENT OUT OF: " << endl;
  cout << dataFromFile << endl;
  stringstream readingData(dataFromFile);
  string tempString = "";
  getline(readingData, tempString);
  stringstream stringToNum(tempString);
  stringToNum >> id;
  stringToNum.clear();
  getline(readingData, name);
  getline(readingData, level);
  getline(readingData, major);
  tempString = "";
  getline(readingData, tempString);
  stringToNum.str(tempString);
  stringToNum >> gpa;
  stringToNum.clear();
  tempString = "";
  getline(readingData, tempString);
  stringToNum.str(tempString);
  stringToNum >> facultyAdvisor;
  stringToNum.clear();
  readingData.clear();
}

Student::~Student() {
  //No pointers to be deleted
}

int Student::getID() {
  return id;
}

string Student::getName() {
  return name;
}

string Student::getLevel() {
  return level;
}

void Student::setLevel() {
  while(true) {
    cout << "Enter the grade of the student (Freshman, Sophomore, Junior, Senior, or Super Senior)." << endl;
    string tempLevel = "";
    getline(cin, tempLevel);
    level = "";
    for(int i = 0; i < tempLevel.length(); ++i) {
      level += toupper(tempLevel[i]);
    }
    if(level == "FRESHMAN" || level == "SOPHOMORE" || level == "JUNIOR" || level == "SENIOR" || level == "SUPER SENIOR") {
      break;
    } else {
      cout << "INVALID GRADE ENTERED. Please try again." << endl;
    }
  }
}

string Student::getMajor() {
  return major;
}

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

double Student::getGPA() {
  return gpa;
}

void Student::setGPA() {
  bool isFinished = false;
  while(!isFinished) {
    cout << "Enter the student's GPA." << endl;
    string tempGPA = "";
    getline(cin, tempGPA);
    bool decimalFound = false;
    bool isNum = false;
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
      stringstream stringToNum(tempGPA);
      double tempGPANum = 0;
      stringToNum >> tempGPANum;
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
      cout << "ERROR: Number not entered. Please try again." << endl;
    }
    if(gpa != 0) {
      isFinished = true;
    }
  }
}

int Student::getFacultyAdvisorID() {
  return facultyAdvisor;
}

void Student::setNewAdvisor(int newFacultyAdvisorID) {
  facultyAdvisor = newFacultyAdvisorID;
}

bool Student::operator ==(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return false;
  }
  return id == otherPerson.id;
}

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

bool Student::operator <(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return true;
  }
  return id < otherPerson.id;
}

bool Student::operator >(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return false;
  }
  return id > otherPerson.id;
}

bool Student::operator <=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return true;
  }
  return id <= otherPerson.id;
}

bool Student::operator >=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return false;
  }
  return id >= otherPerson.id;
}

ostream &operator <<(ostream &out, Student &student) {
  string tempString = to_string(student.id) + "\n" + student.name + "\n" + student.level + "\n" + student.major + "\n" + to_string(student.gpa) + "\n" + to_string(student.facultyAdvisor) + "\n";
  out << tempString;
  return out;
}

string to_string(Student student) {
  ostringstream ss;
  ss << student;
  return ss.str();
}

string Student::printDataForUser() {
  string returnString = "STUDENT ID: " + to_string(id) + "\n";
  returnString += "STUDENT NAME: " + name + "\n";
  returnString += "STUDENT LEVEL: " + level + "\n";
  returnString += "STUDENT MAJOR: " + major + "\n";
  returnString += "STUDENT GPA: "  + to_string(gpa) + "\n";
  returnString += "STUDENT'S FACULTY ADVISOR'S ID: " + to_string(facultyAdvisor) + "\n";
  return returnString;
}
