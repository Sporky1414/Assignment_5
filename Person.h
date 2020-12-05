#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

class Person {
  public:
    Person();
    ~Person();

    virtual int getID() = 0;
    virtual string getName() = 0;
    virtual string getLevel() = 0;
    virtual void setLevel() = 0;

    virtual bool operator ==(const Person& otherPerson) = 0;
    virtual bool operator <(const Person& otherPerson) = 0;
    virtual bool operator >(const Person& otherPerson) = 0;
    virtual bool operator >=(const Person& otherPerson) = 0;
    virtual bool operator <=(const Person& otherPerson) = 0;

    virtual string printDataForUser() = 0;

    string level;
    int id;
    string name;
  private:
    virtual int getLevelNumber(string thisLevel) = 0;
};
