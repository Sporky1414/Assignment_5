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
  stringstream readingData(dataFromFile);
  string tempString = "";
  getline(readingData, tempString);
  stringstream stringToNum(tempString);
  stringToNum >> id;
  stringToNum.clear();
  getline(readingData, name);
  getline(readingData, level);
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
    cin >> tempLevel;
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
  cout << "Enter the major for the student." << endl;
  cin >> major;
}

double Student::getGPA() {
  return gpa;
}

void Student::setGPA() {
  while(true) {
    cout << "Enter the student's GPA." << endl;
    string tempGPA = "";
    cin >> tempGPA;
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
      stringToNum >> gpa;
      break;
    } else {
      cout << "ERROR: Number not entered. Please try again." << endl;
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
  return getLevelNumber(level) < getLevelNumber(otherPerson.level);
}

bool Student::operator >(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return false;
  }
  return getLevelNumber(level) > getLevelNumber(otherPerson.level);
}

bool Student::operator <=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return true;
  }
  return getLevelNumber(level) <= getLevelNumber(otherPerson.level);
}

bool Student::operator >=(const Person& otherPerson) {
  if(typeid(otherPerson).name() != "Student") {
    return false;
  }
  return getLevelNumber(level) >= getLevelNumber(otherPerson.level);
}

ostream& operator<<(ostream &out, Student &student) {
  out << "STUDENT ID: " << to_string(student.getID()) << "\n";
  out << "STUDENT NAME: " << student.getName() << "\n";
  out << "STUDENT LEVEL: " << student.getLevel() << "\n";
  out << "STUDENT MAJOR: " << student.getMajor() << "\n";
  out << "STUDENT GPA: " << setprecision(4) << student.getGPA() << "\n";
  out << "STUDENT'S FACULTY ADVISOR'S ID: " << to_string(student.getFacultyAdvisorID()) << endl;
  return out;
}

string to_string(Student &student) {
  ostringstream ss;
  ss << student;
  return ss.str();
}

string Student::getDataForFile() {
  string returnString = to_string(id) + "\n" + name + "\n" + level + "\n" + major + "\n" + to_string(gpa) + "\n" + to_string(facultyAdvisor) + "\n";
  return returnString;
}
