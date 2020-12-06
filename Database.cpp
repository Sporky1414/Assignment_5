/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Database.h"

using namespace std;

//Constructor for Database. Either instnatiates a blank Student/Faculty BST, or creates them based on the files studentTable.txt and facultyTable.txt.
Database::Database() {
  //Seeds the random generator for ID selection.
  srand(time(NULL));
  //Instantiates the Database pointers.
  studentRecord = new BST<Student*>();
  facultyRecord = new BST<Faculty*>();
  studentFileHandler = new FileIO("studentTable.txt");
  facultyFileHandler = new FileIO("facultyTable.txt");
  //Bool used to ensure blank lines do not lead to a failed read.
  bool isBlank = false;
  //If both file handlers successfully opened their files and found them to be valid, the data stored in both needs to be copied to their respective BST's. Otherwise, the BST's remain empty.
  if(studentFileHandler->hasInput() && facultyFileHandler->hasInput()) {
    while(studentFileHandler->inputHasDataLeft()) {
      //Starting with the studentTable file/studentRecord.
      string tempData = "";
      int tempID = 0;
      //Every six lines constitutes one student's data in the file.
      for(int i = 0; i < 6; ++i) {
        //Read the file.
        string tempString = studentFileHandler->readNextLine();
        //If a blank line is found, ignore it by either getting out of the loop earlier (if it is at the end of the file, which only happens should the first line in the six line grouping is blank)
        //If it is found in the middle of the file, the line is skipped.
        if(tempString == "") {
          if(i == 0) {
            isBlank = true;
            i = 8;
          } else {
            i--;
            continue;
          }
        }
        //Concatenate the data from each line of the file into tempData.
        tempData += tempString;
        if(i == 0) {
          //First line of each grouping is the ID, which needs to be stored seperately as an int in order to insert in the BST.
          //This line will be an int, as the file was checked before hand when studentFileHandler was initialized to ensure it was a number.
          stringstream ss(tempData);
          ss >> tempID;
          ss.clear();
        }
        if(i != 5) {
          //Seperates the data in tempData by new line characters.
          tempData += "\n";
        }
      }
      //If the loop was not broken out of due to a blank line, all data from the file for this student has been found.
      //Create the student from this data and insert it into studentRecord.
      if(!isBlank) {
        studentRecord->insertNode(tempID, new Student(tempData));
      }
      //Reset isBlank for the next grouping of lines.
      isBlank = false;
    }
    //Prints the database found in the file for the user to see.
    cout << "FOLLOWING STUDENT DATABSE LOADED FROM FILE: " << endl;
    printDatabaseToConsole(true);
    //Resets isBlank for the faculty database.
    isBlank = false;
    while(facultyFileHandler->inputHasDataLeft()) {
      //Preps to iterate through facultyTable.txt until all data is accounted for.
      string tempData = "";
      int tempID = 0;
      int numOfAdvisees = 0;
      //First five lines are constant for a faculty, so iterate through the first five lines of the grouping and store accordingly.
      for(int i = 0; i < 5; ++i) {
        if(i == 4) {
          //The fifth line of the grouping contains the number of advisees this faculty member has. Store this as an int (will not cause problems due to file validity check)
          string tempString = facultyFileHandler->readNextLine();
          stringstream ss(tempString);
          ss >> numOfAdvisees;
          //Add the number of advisees to tempData.
          tempData += tempString;
        } else {
          //Store the rest of the data in a similar veing to how the studentTable data was read/stored.
          tempData += facultyFileHandler->readNextLine();
          if(i == 0) {
            //ID is also stored seperately due to it needing to be pulled out for tree insertion. This is done the exact same way as with the studentTable read above.
            //It also accounts for blank lines, since all blank lines possible in faculty printing would occur only in the 0 line of the file.
            if(tempData == "") {
              isBlank = true;
              break;
            }
            stringstream ss(tempData);
            ss >> tempID;
            ss.clear();
          }
        }
        //Split up each piece of data by line.
        tempData += "\n";
      }
      //Exit the loop if a blank line was found, since we have reached the end of the file.
      if(isBlank) {
        break;
      }
      //Iterate through however many lines numOfAdvisees noted contained advisee data and store the id numbers to tempData.
      for(int i = 0; i < numOfAdvisees; ++i) {
        tempData += facultyFileHandler->readNextLine();
        if(i != numOfAdvisees - 1) {
          tempData += "\n";
        }
      }
      //All data has been read and stored in tempData for this faculty member, so add to the tree.
      facultyRecord->insertNode(tempID, new Faculty(tempData));
      //Reset isBlank for the next grouping.
      isBlank = false;
    }
    //Print results of the file read.
    cout << "FOLLOWING FACULTY DATABSE LOADED FROM FILE: " << endl;
    printDatabaseToConsole(false);
  }
}

//Destructor: Delete all pointers in object (starting with the file handlers to allow them to close their streams)
Database::~Database() {
  delete studentFileHandler;
  delete facultyFileHandler;
  delete studentRecord;
  delete facultyRecord;
}

//Print both databases to their respective files.
void Database::printDatabasesToFile() {
  //Gets the data from the studentRecord BST and sends it to the fileHandler to put in it's file. This will be in the same format that the file was read in.
  //Post order is used because a post order traversal reading will lead to the same tree being created when the file is read.
  string returnString = "";
  returnString += studentRecord->printPostOrderPointer();
  studentFileHandler->closeInputAndWriteData(returnString);
  //Same thing is done for the facultyRecord BST.
  returnString = "";
  returnString += facultyRecord->printPostOrderPointer();
  facultyFileHandler->closeInputAndWriteData(returnString);
}

//Prints one of the two databases (selected by the given boolean) in a user-friendly format, unlike printDatabasesToFile(). Done with inOrder traversal method.
void Database::printDatabaseToConsole(bool studentListOrNot) {
  if(studentListOrNot) {
    //Printing student list. Gets list of all the keys in the tree with the inorder traversal printing version.
    LinkedList<int>* listOfStudentKeys = studentRecord->getListOfKeysInOrder();
    while(!listOfStudentKeys->isEmpty()) {
      //While there are keys left to check, keep removing each key at the front of the list and storing it in tempID.
      int tempID = listOfStudentKeys->remove(listOfStudentKeys->valueAt(0));
      //With this ID, print out the data associated with it (should the node with the key be present, which it should.)
      if(studentRecord->searchNode(tempID)) {
        //Prints out the data found to the user.
        cout << studentRecord->getDataOfNodeFromKey(tempID)->printDataForUser() << endl;
      }
    }
    //List is now empty, can be deleted without issue.
    delete listOfStudentKeys;
  } else {
    //Printing student list. Implementation of this is the exact same as the above student implementation, replacing studentRecord with facultyRecord.
    LinkedList<int>* listOfFacultyKeys = facultyRecord->getListOfKeysInOrder();
    while(!listOfFacultyKeys->isEmpty()) {
      int tempID = listOfFacultyKeys->remove(listOfFacultyKeys->valueAt(0));
      if(facultyRecord->searchNode(tempID)) {
        cout << facultyRecord->getDataOfNodeFromKey(tempID)->printDataForUser() << endl;
      }
    }
    delete listOfFacultyKeys;
  }
}

//Returns the Student pointer stored in the BST at the given studentID/key.
Student* Database::searchForStudent(int studentID) {
  return studentRecord->getDataOfNodeFromKey(studentID);
}

//Returns the Faculty pointer stored in the BST at the given facultyID/key.
Faculty* Database::searchForFaculty(int facultyID) {
  return facultyRecord->getDataOfNodeFromKey(facultyID);
}

//Prints the advisor of the student with studentID.
void Database::printAdvisorOfStudent(int studentID) {
  //Checks if the student with studentID exists first.
  if(studentRecord->searchNode(studentID)) {
    //Gets the student stored in studentRecord with studentID.
    Student* tempStudent = studentRecord->getDataOfNodeFromKey(studentID);
    //Gets the faculty advisor from tempStudent.
    int facultyID = tempStudent->getFacultyAdvisorID();
    //Gets the faculty stored in facultyRecord with the advisor ID just found.
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(facultyID);
    //Prints out the advisor data.
    cout << tempFaculty->printDataForUser() << endl;
  } else {
    //User is alerted they tried to find the advisor of a student who does not exist.
    cout << "STUDENT " << studentID << " DOES NOT EXIST." << endl;
  }
}

//Prints a list of all the students being advised by the faculty member with the given facultyID.
void Database::printAdviseesOfFaculty(int facultyID) {
  if(facultyRecord->searchNode(facultyID)) {
    //After confirming that a faculty member with this ID number exists, that faculty member is stored in tempFaculty.
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(facultyID);
    //Gets a copy of the LinkedList of Advisees stored in tempFaculy.
    ListADT<int>* tempAdviseeList = tempFaculty->getListOfStudentAdviseeIDs();
    for(int i = 0; i < tempAdviseeList->getLength(); ++i) {
      //Iterates through tempAdviseeList, getting the student with the given ID and printing them for the user.
      Student* tempStudent = studentRecord->getDataOfNodeFromKey(tempAdviseeList->valueAt(i));
      cout << tempStudent->printDataForUser() << endl;
    }
    //The copied linked list, which holds no valuable data, is deleted.
    delete tempAdviseeList;
  } else {
    //Invalid faculty ID tried, so the user is alerted and nothing else happens.
    cout << "FACULTY " << facultyID << " DOES NOT EXIST." << endl;
  }
}

//Adds a student to the database. Returns a pointer to the student just added.
Student* Database::addStudent() {
  //Can not add students if there are no faculty (you need faculty to teach at a university), so the method terminates if no faculty are present and the user is alerted as such.
  //Since there is no student being added, null is returend.
  if(facultyRecord->isEmpty()) {
    cout << "ERROR: CAN NOT ADD STUDENT IF THERE IS NO ONE TO TEACH THEM! PLEASE TRY AGAIN." << endl;
    return NULL;
  }
  //Determine the student ID using this random number generator. It allows for more efficient BST storing with random ID's. Supports up to 100000 ID's split between facultyRecord and studentRecord.
  int tempID = 1 + rand()/((RAND_MAX)/100000);
  while(studentRecord->searchNode(tempID) || facultyRecord->searchNode(tempID)) {
    //A new ID is generated should the one found above already be in use. The loop continues until a free ID is found.
    tempID = 1 + rand()/((RAND_MAX)/100000);
  }
  //Gets the name of the student from the user.
  cout << "Enter the name of the student being added." << endl;
  string tempName = "";
  getline(cin, tempName);
  //Uses the determineAdvisor() method to determine the advisor with the fewest advisees, and assigns it to the student. This can be changed manually later.
  int tempFacultyID = determineAdvisor();
  //Creates the new student using the above data.
  studentRecord->insertNode(tempID, new Student(tempID, tempName, tempFacultyID));
  //Gets the student just created and stored in the tree.
  Student* tempStudent = studentRecord->getDataOfNodeFromKey(tempID);
  //Gets the faculty with the ID used as the student's faculty advisor ID.
  Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(tempFacultyID);
  //Adds the new student to the given faculty member's advisee list.
  tempFaculty->addStudentAdvisee(tempStudent);
  //returns the newly created student.
  return tempStudent;
}

Faculty* Database::addFaculty() {
  //Determine the student ID using this random number generator. It allows for more efficient BST storing with random ID's. Supports up to 100000 ID's split between facultyRecord and studentRecord.
  int tempID = 1 + rand()/((RAND_MAX)/100000);
  while(studentRecord->searchNode(tempID) || facultyRecord->searchNode(tempID)) {
    //A new ID is generated should the one found above already be in use. The loop continues until a free ID is found.
    tempID = 1 + rand()/((RAND_MAX)/100000);
  }
  //Gets the name of the new faculty member.
  cout << "Enter the name of the faculty being added." << endl;
  string tempName = "";
  getline(cin, tempName);
  //Creates a new Faculty member from the ID/Name and stores it in the tree.
  facultyRecord->insertNode(tempID, new Faculty(tempID, tempName));
  //Returns a pointer to the newly created Faculty.
  return facultyRecord->getDataOfNodeFromKey(tempID);
}

//Determines a student's advisor based on how many advisees each faculty member has. It also prevents the previous advisor (signified by oldAdvisor) to be reassigned to this student.
int Database::determineAdvisor(int oldAdvisor) {
  //Gets a list of faculty advisor ID's.
  LinkedList<int>* keysInOrder = facultyRecord->getListOfKeysInOrder();
  //Preps idOfMin and minAdvisees, which store the minimum number of advisees and who has that number (currently set as the first ID and however many advisees they have).
  int idOfMin = keysInOrder->valueAt(0);
  int minAdvisees = studentRecord->getNumOfKeys();
  //Temp variable used to store what ID is being looked at.
  int tempID = 0;
  while(!keysInOrder->isEmpty()) {
    //Checks each datapoint in keysInOrder. As each datapoint is checked, it is removed from keysInOrder.
    tempID = keysInOrder->remove(keysInOrder->valueAt(0));
    //Faculty from tempID is pointed to by tempFaculty.
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(tempID);
    //Gets the list of advisees present.
    ListADT<int>* tempListOfAdvisees = tempFaculty->getListOfStudentAdviseeIDs();
    //Adjusts idOfMin and minAdvisees should the current faculty member have fewer advisees than the faculty stored in idOfMin (whose advisee number is stored in minAdvisees). This loop is skipped for the advisor being looked at be the one noted as oldAdvisor.
    if(minAdvisees > tempListOfAdvisees->getLength() && tempID != oldAdvisor) {
      idOfMin = tempID;
      minAdvisees = tempListOfAdvisees->getLength();
    }
    //Deletes the list of advisees, since it is a non-valuable copy.
    delete tempListOfAdvisees;
  }
  //All faculty has been checked, so return the winner and delete the now depeleted keysInOrder.
  delete keysInOrder;
  return idOfMin;
}

//Determines a student's advisor based on how many advisees each faculty member has. Same implementation as above except there is no limitation from an oldAdvisor on wwhat idOfMin will end up being.
int Database::determineAdvisor() {
  LinkedList<int>* keysInOrder = facultyRecord->getListOfKeysInOrder();
  int idOfMin = keysInOrder->valueAt(0);
  int minAdvisees = studentRecord->getNumOfKeys();
  int tempID = 0;
  while(!keysInOrder->isEmpty()) {
    tempID = keysInOrder->remove(keysInOrder->valueAt(0));
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(tempID);
    ListADT<int>* tempListOfAdvisees = tempFaculty->getListOfStudentAdviseeIDs();
    if(minAdvisees > tempListOfAdvisees->getLength()) {
      idOfMin = tempID;
      minAdvisees = tempListOfAdvisees->getLength();
    }
    delete tempListOfAdvisees;
  }
  delete keysInOrder;
  return idOfMin;
}

//Deletes a student from studentRecord and returns it.
Student* Database::deleteStudent(int studentID) {
  //Iterates through each faculty member. If a faculty member has the student being deleted as an advisee, that advisee is removed from their list.
  LinkedList<int>* keysInOrder = facultyRecord->getListOfKeysInOrder();
  int tempID = 0;
  while(!keysInOrder->isEmpty()) {
    tempID = keysInOrder->remove(keysInOrder->valueAt(0));
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(tempID);
    ListADT<int>* tempList = tempFaculty->getListOfStudentAdviseeIDs();
    if(tempList->searchFor(studentID) > -1) {
      tempFaculty->deleteStudentFromAdviseeList(studentID);
    }
    delete tempList;
  }
  delete keysInOrder;

  //Finds the node containing the student with studentID, should one exist. Deletes that node from studentRecord and returns the data stored from it.
  if(studentRecord->searchNode(studentID)) {
    Student* tempStudent = studentRecord->getDataOfNodeFromKey(studentID);
    studentRecord->deleteNode(studentID);
    return tempStudent;
  } else {
    //Student ID did not match a student in studentRecord, so no deleting took place. NULL is returned as a result, since nothing was deleted.
    return NULL;
  }
}

//Deletes a faculty member from facultyRecord.
Faculty* Database::deleteFaculty(int facultyID) {
  if(facultyRecord->searchNode(facultyID)) {
    //After checking to make sure the faculty member exists, the faculty member is stored in tempFaculty.
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(facultyID);
    //A copy of tempFaculty (used to return the faculty member) is created (tempFaculty member currently points to the data in the tree).
    Faculty* copyOfFaculty = new Faculty(to_string(*tempFaculty));
    //Gets list of all students.
    LinkedList<int>* keysInOrder = studentRecord->getListOfKeysInOrder();
    int tempID = 0;
    //Iterates through all students. If a student has the faculty member being deleted as their advisor, changeAdvisorForStudent is run to replace that advisor.
    while(!keysInOrder->isEmpty()) {
      tempID = keysInOrder->remove(keysInOrder->valueAt(0));
      Student* tempStudent = studentRecord->getDataOfNodeFromKey(tempID);
      if(tempStudent->getFacultyAdvisorID() == facultyID) {
        cout << "Student Advisee " << tempStudent->getName() << " found." << endl;
        changeAdvisorForStudent(tempID);
      }
    }
    //The faculty member is deleted from the tree.
    facultyRecord->deleteNode(facultyID);
    //The copy of the faculty record is returned, after deleting the now depleted linked list of student ids.
    tempFaculty = copyOfFaculty;
    delete keysInOrder;
    return tempFaculty;
  } else {
    //The faculty to be deleted does not exist, so NULL is returned and nothing happens.
    return NULL;
  }
}

//Changes the advisor of the given student.
void Database::changeAdvisorForStudent(int studentID) {
  //Does not exit loop until an advisor is changed.
  while(true) {
    if(studentRecord->searchNode(studentID)) {
      //Looks for the given student and stores a pointer to it in tempStudent.
      Student* tempStudent = studentRecord->getDataOfNodeFromKey(studentID);
      while(true) {
        //Loop used to check if the user wishes to manually reassign the student advisor or use determineAdvisor to randomly select one.
        cout << "Do you wish to assign this student's new advisor manually or randomly? Type '1' for manually or '2' for randomly." << endl;
        string tempResponse = "";
        getline(cin, tempResponse);
        if(studentFileHandler->checkIfStringIsNumber(tempResponse)) {
          int tempInt = 0;
          stringstream ss(tempResponse);
          ss >> tempInt;
          ss.clear();
          int facultyAdvisorID = 0;
          if(tempInt == 1) {
            while (true) {
              //If we get here, the user wishes to change the advisor manually.
              cout << "Enter the ID number of the new faculty advisor." << endl;
              getline(cin, tempResponse);
              if(studentFileHandler->checkIfStringIsNumber(tempResponse)) {
                ss.str(tempResponse);
                ss >> facultyAdvisorID;
                ss.clear();
                if(facultyRecord->searchNode(facultyAdvisorID)) {
                  //User has given a valid faculty member.
                  //The old faculty member has the student removed from their advisee list
                  Faculty* tempFaculty = searchForFaculty(tempStudent->getFacultyAdvisorID());
                  tempFaculty->deleteStudentFromAdviseeList(tempStudent->getID());
                  //The student has their advisor replaced.
                  tempStudent->setNewAdvisor(facultyAdvisorID);
                  //The new faculty member has the student added to their advisee list.
                  tempFaculty = searchForFaculty(facultyAdvisorID);
                  tempFaculty->addStudentAdvisee(tempStudent);
                  break;
                } else {
                  //User did not give a valid faculty number and has to try again.
                  cout << "Number input does not correspond with a faculty member. Please try again." << endl;
                }
              } else {
                //User did not input a number for the faculty advisor ID instruction and has to try again.
                cout << "Input was not a number. Please try again." << endl;
              }
            }
            //If we get here, we can get out of the loop, since the change was made successfully and does not have to be done again.
            break;
          } else if (tempInt == 2) {
            //User wishes to replace the advisor with determineAdvisor
            //The faculty member has the student dropped from their advisee list.
            Faculty* tempFaculty = searchForFaculty(tempStudent->getFacultyAdvisorID());
            tempFaculty->deleteStudentFromAdviseeList(tempStudent->getID());
            //The new advisor is determined by determineAdvisor(int oldAdvisor) and stored. This form of determineAdvisor prevents the student from a repeat advisor.
            int facultyAdvisorID = determineAdvisor(tempFaculty->getID());
            tempStudent->setNewAdvisor(facultyAdvisorID);
            //The new advisor adds the student to their list.
            tempFaculty = searchForFaculty(facultyAdvisorID);
            tempFaculty->addStudentAdvisee(tempStudent);
            break;
          } else {
            //User did not give a valid selection, but they did input a number, when asked if they wanted to manually change the advisor or not. They are asked to try again.
            cout << "Invalid Number given. Please try again." << endl;
          }
        } else {
          //User did not enter a number when asked if they wanted to manually change the advisor or not. They are asked to try again.
          cout << "Number not entered. Please try again." << endl;
        }
      }
      break;
    } else {
      //The student passed as an argument to changeAdvisorForStudent is invalid. User tries again.
      cout << "STUDENT " << studentID << " DOES NOT EXIST. Please try a different ID." << endl;
      string response = "";
      while(true) {
        //Exits loop if a number is put in.
        cout << "Enter ID of student to change the advisor of." << endl;
        getline(cin, response);
        if(studentFileHandler->checkIfStringIsNumber(response)) {
          stringstream ss(response);
          ss >> studentID;
          ss.clear();
          break;
        } else {
          //A number was not entered for the new student ID, so they have to try again.
          cout << "You did not enter a number. Please try again." << endl;
        }
      }
    }
  }
}

//Removes an advisee from a faculty's advisee list and replaces the student's advisor.
void Database::removeAdviseeFromFaculty(int facultyID, int studentID) {
  //Loops until the command was executed.
  while(true) {
    if(facultyRecord->searchNode(facultyID) && studentRecord->searchNode(studentID)) {
      //Both ID's passed through are valid. Faculty and their list of advisees are pointed to by below pointers.
      Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(facultyID);
      ListADT<int>* tempList = tempFaculty->getListOfStudentAdviseeIDs();
      //If the faculty member has the student, the student is removed from their advisee list. Otherwise, no change is made to the faculty advisee list at this time.
      //User is alerted of result of deletion attempt, but will change the student's advisor regardless.
      if(tempList->searchFor(studentID) > -1) {
        tempFaculty->deleteStudentFromAdviseeList(studentID);
        cout << "Student removed from " << tempFaculty->getName() << "'s Faculty Advisee List. You now must reassign the student." << endl;
      } else {
        cout << "Given student was not in the faculty member's advisee list. You will still be prompted to change their advisor as a backup plan." << endl;
      }
      delete tempList;
      //Calls changeAdvisorForStudent to change the student's advisor.
      changeAdvisorForStudent(studentID);
      break;
    } else {
      //Either argument does not point to a valid faculty or student. Following while loops take in new numbers for the faculty and student. Main while loop then goes again with the new numbers, checking then if they are valid.
      //Getting the number is implemented in the same way as in the same situation with changeAdvisorForStudent.
      cout << "ERROR: FACULTY ID DOES NOT POINT TO AN EXISTING FACULTY OR STUDENT ID DO NOT POINT TO A VALID STUDENT. Please Try Again." << endl;
      string response;
      while(true) {
        cout << "Enter the ID of the faculty member to remove the advisee from." << endl;
        getline(cin, response);
        if(studentFileHandler->checkIfStringIsNumber(response)) {
          stringstream ss(response);
          ss >> facultyID;
          ss.clear();
        } else {
          cout << "You did not enter a number. Please try again." << endl;
        }
      }
      response = "";
      while(true) {
        cout << "Enter ID of student to remove from this advisor." << endl;
        getline(cin, response);
        if(studentFileHandler->checkIfStringIsNumber(response)) {
          stringstream ss(response);
          ss >> studentID;
          ss.clear();
        } else {
          cout << "You did not enter a number. Please try again." << endl;
        }
      }
    }
  }
}

//Returns if there is data present in studentRecord.
bool Database::studentRecordHasData() {
  return !studentRecord->isEmpty();
}

//Returns if there is data present in facultyRecord.
bool Database::facultyRecordHasData() {
  return !facultyRecord->isEmpty();
}

//Returns if facultyRecord has more than 1 faculty member stored in it.
bool Database::facultyRecordHasMoreThanOneFaculty() {
  int keysOfTree = facultyRecord->getNumOfKeys();
  return keysOfTree > 1;
}

//Creates and returns a deep BST copy of studentRecord.
BST<Student*>* Database::copyStudentRecord() {
  //Creates the copy BST and the list of student keys.
  BST<Student*>* copy = new BST<Student*>();
  LinkedList<int>* listOfKeys = studentRecord->getListOfKeysPostOrder();
  int tempID = 0;
  while(!listOfKeys->isEmpty()) {
    //Adds a deep copy of each student stored in studentRecord to copy. listOfKeys is used to find all the students.
    tempID = listOfKeys->remove(listOfKeys->valueAt(0));
    Student* tempStudent = studentRecord->getDataOfNodeFromKey(tempID);
    string dataToCopy = to_string(*tempStudent);
    tempStudent = new Student(dataToCopy);
    copy->insertNode(tempStudent->getID(), tempStudent);
  }
  //The deep copy BST is returned.
  return copy;
}

//Creates and returns a deep BST copy of facultyRecord. Same implementation as copyStudentRecord()
BST<Faculty*>* Database::copyFacultyRecord() {
  BST<Faculty*>* copy = new BST<Faculty*>();
  LinkedList<int>* listOfKeys = facultyRecord->getListOfKeysPostOrder();
  int tempID = 0;
  while(!listOfKeys->isEmpty()) {
    tempID = listOfKeys->remove(listOfKeys->valueAt(0));
    Faculty* tempFaculty = facultyRecord->getDataOfNodeFromKey(tempID);
    string dataToCopy = to_string(*tempFaculty);
    tempFaculty = new Faculty(dataToCopy);
    copy->insertNode(tempFaculty->getID(), tempFaculty);
  }
  return copy;
}

//Replaces studentRecord with the passed through argument, which is seen as a backup.
BST<Student*>* Database::restoreStudentRecord(BST<Student*>* backup) {
  BST<Student*>* temp = studentRecord;
  studentRecord = backup;
  backup = temp;
  return backup;
}

//Replaces facultyRecord with the passed through argument, which is seen as a backup.
BST<Faculty*>* Database::restoreFacultyRecord(BST<Faculty*>* backup) {
  BST<Faculty*>* temp = facultyRecord;
  facultyRecord = backup;
  backup = temp;
  return backup;
}
