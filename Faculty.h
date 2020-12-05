#include "Student.h"
#include "BST.cpp"

using namespace std;

class Faculty: private Person {
  public:
    Faculty();
    Faculty(int facultyID, string facultyName);
    Faculty(string dataFromFile);
    ~Faculty();

    int getID();
    string getName();
    string getLevel();
    void setLevel();
    string getDepartment();
    void setDepartment();
    void getPrintedListOfStudentAdviseeIDs();
    void addStudentAdvisee(Student* student);
    int deleteStudentFromAdviseeList(int studentID);
    ListADT<int>* getListOfStudentAdviseeIDs();

    bool operator ==(const Person& otherPerson);
    bool operator <(const Person& otherPerson);
    bool operator >(const Person& otherPerson);
    bool operator >=(const Person& otherPerson);
    bool operator <=(const Person& otherPerson);

    friend ostream &operator<<(ostream &out, Faculty &faculty);
    friend string to_string(Faculty &faculty);

    string printDataForUser();

  private:
    string department;
    ListADT<int>* listOfStudentAdviseeIDs;

    int getLevelNumber(string thisLevel);
};
