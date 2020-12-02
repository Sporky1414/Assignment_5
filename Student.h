#include "Person.h"

using namespace std;

class Student: private Person {
  public:
    Student();
    Student(int studentID, string nameOfStudent, int originalFacultyAdvisor);
    Student(string dataFromFile);
    ~Student();

    int getID();
    string getName();
    string getLevel();
    void setLevel();
    string getMajor();
    void setMajor();
    double getGPA();
    void setGPA();
    int getFacultyAdvisorID();
    void setNewAdvisor(int newFacultyAdvisorID);

    bool operator ==(const Person& otherPerson) = 0;
    bool operator <(const Person& otherPerson) = 0;
    bool operator >(const Person& otherPerson) = 0;
    bool operator >=(const Person& otherPerson) = 0;
    bool operator <=(const Person& otherPerson) = 0;

    friend ostream &operator<<(ostream &out, Student &student);
    friend string to_string(Student &student);

    string getDataForFile();

  private:
    string major;
    double gpa;
    int facultyAdvisor;

    int getLevelNumber(string thisLevel);
};
