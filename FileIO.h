/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//File Handler that reads studentTable/facultyTable at the beginning and replaces them at the end of the program.
class FileIO {
  public:
    //Constructor/Destructor
    FileIO();
    FileIO(string newInputFilePath);
    ~FileIO();

    //Methods to read/write data.
    string readNextLine();
    void closeInputAndWriteData(string data);

    //Method to check on status of the input file.
    bool inputHasDataLeft();

    //Methods to determine if the string passed through is an integer or double
    bool checkIfStringIsNumber(string tempString);
    bool checkIfStringIsDecimalNumber(string tempString);

    //Checks if the input stream is in use.
    bool hasInput();

    //Checks if the file attached to input has the correct format for this program.
    bool checkInputFileValidity();
  private:
    //Determines if the input file passed in by the user is valid.
    bool checkInputFileValidityStudent();

    //Strings containing the file path of the input and name of the output file.
    string inputFilePath;

    //Objects to take in data from a file and write to a file.
    ifstream input;
    ofstream output;
};
