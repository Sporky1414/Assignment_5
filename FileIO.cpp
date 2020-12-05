/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "FileIO.h"

//Default constructor: takes in user input itself.
FileIO::FileIO() {
  input.open("student");
  output.open("student");
}

//Constructor: Preliminary input file path and output name given.
FileIO::FileIO(string newInputFilePath) {
  inputFilePath = newInputFilePath;
  input.open(inputFilePath);
  if(input.fail()) {
    cout << "INPUT FILE NOT FOUND. STARTING FROM SCRATCH WITH " << inputFilePath << endl;
    input.close();
  } else if (!checkInputFileValidity()) {
    cout << "INPUT FILE IN WRONG FORMAT. STARTING FROM SCRATCH WITH " << inputFilePath << endl;
    input.close();
  }
}

//Destructor: Closes the input/output streams (should they be in use.)
FileIO::~FileIO() {
  if(input.is_open()) {
    input.close();
  }
  if(output.is_open()) {
    output.close();
  }
}

//Reads the next line of the input file.
string FileIO::readNextLine() {
  if(output.is_open()) {
    cout << "OUTPUT IN USE. NO LONGER CAN READ FILE" << endl;
    return "";
  }
  string tempString = "";
  getline(input, tempString);
  return tempString;
}

//Returns if there is more data in the file to read.
bool FileIO::inputHasDataLeft() {
  return !input.eof();
}

//Writes the argument string to the output file.
void FileIO::closeInputAndWriteData(string data) {
  if(input.is_open()) {
    input.close();
  }
  if(!output.is_open()) {
    output.open(inputFilePath);
  }
  output << data << endl;
}

//Checks if the file connected to the input stream is in the correct format.
bool FileIO::checkInputFileValidity() {
  if(inputFilePath.compare("studentTable.txt") == 0) {
    while(inputHasDataLeft()) {
      //Reads the first line of the file.
      string tempString = "";
      for(int i = 0; i < 6; ++i) {
        tempString = readNextLine();
        if(tempString == "") {
          i--;
          if(inputHasDataLeft()) {
            continue;
          } else {
            break;
          }
        }
        switch(i) {
          case 0:
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            }
            break;
          case 1:
            if(tempString == "") {
              return false;
            }
            break;
          case 2: {
            string level = tempString;
            if(level == "FRESHMAN" || level == "SOPHOMORE" || level == "JUNIOR" || level == "SENIOR" || level == "SUPER SENIOR") {
              break;
            } else {
              return false;
            }
          }
          case 3:
            if(tempString == "") {
              return false;
            }
            break;
          case 4:
            if(!checkIfStringIsDecimalNumber(tempString)) {
              return false;
            }
            break;
          case 5:
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            }
            break;
        }
      }
    }
    input.clear();
    input.seekg(0);
    cout << "POSITION RESET STUDENT" << endl;
  } else {
    while(inputHasDataLeft()) {
      string tempString = "";
      int lengthOfList = 0;
      for(int i = 0; i < 6; ++i) {
        tempString = readNextLine();
        if(tempString == "") {
          i--;
          if(inputHasDataLeft()) {
            continue;
          } else {
            i = 8;
          }
        }
        switch(i) {
          case 0:
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            }
            break;
          case 1:
            if(tempString == "") {
              return false;
            }
            break;
          case 2: {
            string level = tempString;
            if(level.compare("ADJUNCT INSTRUCTOR") == 0 || level.compare("GRADUATE TEACHING ASSISTANT") == 0
              || level.compare("VISITING PROFESSOR") == 0 || level.compare("ASSISTANT PROFESSOR") == 0
              || level.compare("ASSOCIATE PROFESSOR") == 0 || level.compare("FULL PROFESSOR") == 0
              || level.compare("ENDOWED PROFESSOR") == 0 || level.compare("DISTINGUISHED PROFESSOR") == 0
              || level.compare("ADMINISTRATOR") == 0 || level.compare("PROFESSOR EMERITUS") == 0) {
                break;
            } else {
              return false;
            }
          }
          case 3:
            if(tempString == "") {
              return false;
            }
            break;
          case 4: {
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            }
            stringstream ss(tempString);
            ss >> lengthOfList;
            ss.clear();
            break;
          }
          case 5:
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            } else {
              lengthOfList--;
            }
            if(lengthOfList != 0) {
              i--;
            }
        }
      }
    }
    input.clear();
    input.seekg(0);
    cout << "POSITION RESET FACULTY" << endl;
  }
  return true;
}

//Checks if the argument string can be converted to an integer.
bool FileIO::checkIfStringIsNumber(string tempString) {
  //Empty strings automatically return false.
  if(tempString.length() < 1) {
    return false;
  }

  //Checks if each character in a string is a digit. If it is not, false is returned.
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      return false;
    }
  }
  //tempString is a number, true is returned.
  return true;
}

bool FileIO::checkIfStringIsDecimalNumber(string tempString) {
  bool decimalFound = false;
  bool isNum = false;
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      if(!decimalFound && tempString[i] == '.') {
        decimalFound = true;
      } else {
        isNum = false;
        break;
      }
    } else {
      isNum = true;
    }
  }
  return isNum;
}

bool FileIO::hasInput() {
  return input.is_open();
}
