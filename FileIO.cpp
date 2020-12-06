/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "FileIO.h"

//Default constructor: default names. Not used.
FileIO::FileIO() {
  input.open("student");
  output.open("student");
}

//Constructor: Preliminary input file path given. Input with given file path is either opened or a file is created with inputFilePath to do so.
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

//Reads the next line of the input file. Will return a blank string should the output side of the handler be in use.
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

//Writes the argument string to the output file. However, it will close the input stream first to prevent any problems.
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
    //If the file is studentTable.txt, check for the student file format.
    while(inputHasDataLeft()) {
      string tempString = "";
      //Each student is grouped in lines of six, which each line being a specific datapoint of student.
      for(int i = 0; i < 6; ++i) {
        //Read line
        tempString = readNextLine();
        //If two blanks are present, the end of the file has been reached, so break out of the for loop early.
        if (tempString == "" && inputHasDataLeft()) {
          tempString = readNextLine();
          if(tempString == "") {
            break;
          }
        }
        //switch based on what line number of the grouping it is.
        switch(i) {
          case 0:
          //Line 0 should be a number. Return false if this is not the case.
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            }
            break;
          case 1:
          //Line 1 should be a string. Return false if this is blank.
            if(tempString == "") {
              return false;
            }
            break;
          case 2: {
            //If level does not match one of these options, return false.
            string level = tempString;
            if(level == "FRESHMAN" || level == "SOPHOMORE" || level == "JUNIOR" || level == "SENIOR" || level == "SUPER SENIOR") {
              break;
            } else {
              return false;
            }
          }
          case 3:
          //Same as case 1
            if(tempString == "") {
              return false;
            }
            break;
          case 4:
          //Line 4 should be a double. If that is not the case, return false.
            if(!checkIfStringIsDecimalNumber(tempString)) {
              return false;
            }
            break;
          case 5:
          //Line 5 should be an int. Return false if not.
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            }
            break;
        }
      }
    }
    //Reset input for reading afterwards.
    input.clear();
    input.seekg(0);
  } else {
    while(inputHasDataLeft()) {
      //Iterate until file is out.
      string tempString = "";
      int lengthOfList = 0;
      //Faculty are grouped in 6 lines plus however many advisees that faculty has.
      for(int i = 0; i < 6; ++i) {
        if(i == 5 && lengthOfList == 0) {
          //break out of grouping early should no advisees be present.
          break;
        }
        //Get line from file. If two blanks are present, its the end of the file, so exit.
        tempString = readNextLine();
        if (tempString == "" && inputHasDataLeft()) {
          tempString = readNextLine();
          if(tempString == "") {
            break;
          }
        }
        switch(i) {
          case 0:
            //Line 0 is a number. If not, return false.
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            }
            break;
          case 1:
            //Line 1 is a string. Return false if this is blank.
            if(tempString == "") {
              return false;
            }
            break;
          case 2: {
            //Return false if the string at line 2 does not match one of the following.
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
          //Same as case 1
            if(tempString == "") {
              return false;
            }
            break;
          case 4: {
            //Line 4 should be an integer. Return false if not. Should line 4 pass, store as length of list, since this is how many extra lines need to be read.
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            }
            stringstream ss(tempString);
            ss >> lengthOfList;
            ss.clear();
            break;
          }
          case 5:
            //Now on extra lines, which are all ints. If not an int, return false. Otherwise, if lengthOfList (which is decremented after each read) is not 0, decrement i to go through this step again.
            if(!checkIfStringIsNumber(tempString)) {
              return false;
            } else {
              lengthOfList--;
            }
            if(lengthOfList != 0) {
              i--;
            }
            break;
        }
      }
    }
    //File has passed so reset.
    input.clear();
    input.seekg(0);
  }
  //File has passed at this point, so return true.
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

//Checks if the argument string can be converted to a decimal.
bool FileIO::checkIfStringIsDecimalNumber(string tempString) {
  //Bools for if a decimal point has been found or if the string is a num. Both set to false to start.
  bool decimalFound = false;
  bool isNum = false;
  //Iterates through each character of the string.
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      //Character is not a digit.
      if(!decimalFound && tempString[i] == '.') {
        //But it is a decimal point, and we still can have one of those. Set decimalFound to true. If a decimal point is found again, this if statement will be skipped for the else.
        decimalFound = true;
      } else {
        //Not a number so set isNum to false.
        isNum = false;
        break;
      }
    } else {
      //Digit found, so benefit of the doubt can be given that this will be a number. Set isNum to true (this can be reverse if later characters are not digits).
      isNum = true;
    }
  }
  return isNum;
}

//Returns if the input file is open.
bool FileIO::hasInput() {
  return input.is_open();
}
