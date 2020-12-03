#include "BST.cpp"
#include "Faculty.h"

using namespace std;

int main (int argc, char** argv) {
  Student* studentA = new Student(1, "AJ", 1);
  Student* studentB = new Student(2, "Sam", 2);
  Faculty* facultyA = new Faculty(1, "Jodi");
  facultyA->addStudentAdvisee(studentA);
  Faculty* facultyB = new Faculty(2, "Bob");
  facultyA->addStudentAdvisee(studentB);

  cout << "STUDENT A ID: " << studentA->getID() << endl;
  cout << "STUDENT B NAME: " << studentB->getName() << endl;
  cout << "STUDENT A LEVEL: " << studentA->getLevel() << endl;
  cout << "STUDENT B MAJOR: " << studentB->getMajor() << endl;
  cout << "STUDENT A GPA: " << studentA->getGPA() << endl;
  cout << "STUDENT B ADVISOR: " << studentB->getFacultyAdvisorID() << endl;

  cout << "STUDENT A = STUDENT B:" << to_string(studentA == studentB) << endl;
  cout << "STUDENT A <= STUDENT B:" << to_string(studentA <= studentB) << endl;
  cout << "STUDENT A < STUDENT B:" << to_string(studentA < studentB) << endl;
  cout << "STUDENT A >= STUDENT B:" << to_string(studentA >= studentB) << endl;
  cout << "STUDENT A > STUDENT B:" << to_string(studentA > studentB) << endl;

  cout << "STUDENT A: \n" << to_string(*studentA) << endl;

  cout << "FACULTY A ID: " << facultyA->getID() << endl;
  cout << "FACULTY B NAME: " << facultyB->getName() << endl;
  cout << "FACULTY A LEVEL: " << facultyA->getLevel() << endl;
  cout << "FACULTY B DEPARTMENT: " << facultyB->getDepartment() << endl;
  cout << "FACULTY A ADVISEES: " << endl;
  facultyA->getPrintedListOfStudentAdviseeIDs();
  facultyA->deleteStudentFromAdviseeList(1);
  cout << "FACULTY A ADVISEES: " << endl;
  facultyA->getPrintedListOfStudentAdviseeIDs();

  cout << to_string(*facultyB) << endl;

  cout << "FACULTY A <= FACULTY B:" << to_string(facultyA <= facultyB) << endl;
  delete studentA;
  delete studentB;
  delete facultyA;
  delete facultyB;
}
