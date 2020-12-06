/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Simulation.h"

using namespace std;

//Constructor: Creates the database and backup objects.
Simulation::Simulation() {
  database = new Database();
  backups = new Rollback();
}

//Destructor: Deletes the database and the backups.
Simulation::~Simulation() {
  delete database;
  delete backups;
}

//Runs the simulation.
void Simulation::run() {
  //Welcomes user to the program.
  cout << "Welcome to the Chapman University Student and Faculty Database Program." << endl;
  cout << "To make a selection of what you wish to do, type in the corresponding number of the command you wish to execute." << endl;
  //Loops until user asks to exit.
  bool isFinished = false;
  while(!isFinished) {
    //Outputs options for user to choose from.
    cout << "\n\nMake your selection now!" << endl;
    cout << "1. Print all students and their information." << endl;
    cout << "2. Print all faculty and their information." << endl;
    cout << "3. Display Student Information from ID." << endl;
    cout << "4. Display Faculty Information from ID." << endl;
    cout << "5. Get a student's faculty advisor information." << endl;
    cout << "6. Get the information of all a faculty member's advisees." << endl;
    cout << "7. Add a new student. (FACULTY MEMBER MUST BE PRESENT)" << endl;
    cout << "8. Delete a student." << endl;
    cout << "9. Add a new faculty." << endl;
    cout << "10. Delete a faculty member. (FACULTY MEMBER CAN NOT BE DELETED IF NO FACULTY MEMBERS WILL REMAIN AFTERWARDS.)" << endl;
    cout << "11. Change a student's faculty advisor." << endl;
    cout << "12. Remove an advisee from a faculty member." << endl;
    cout << "13. Rollback to Last Database Version." << endl;
    cout << "14. Exit program." << endl;

    //Take in response and convert to an int, if it can be done.
    string response = "";
    int selection = 0;
    getline(cin, response);
    if(checkIfStringIsNumber(response)) {
      //If the response is a number, convert it to an int and put it through the switch case.
      stringstream ss(response);
      ss >> selection;
      ss.clear();
      //For 1-10, the option directly calls the needed method in the Simulation class.
      switch(selection) {
        case 1:
          printStudents();
          break;
        case 2:
          printFaculty();
          break;
        case 3:
          displayStudent();
          break;
        case 4:
          displayFaculty();
          break;
        case 5:
          printAdvisorOfStudent();
          break;
        case 6:
          printAdviseesOfFaculty();
          break;
        case 7:
          addStudent();
          break;
        case 8:
          deleteStudent();
          break;
        case 9:
          addFaculty();
          break;
        case 10:
          deleteFaculty();
          break;
        case 11:
          //Checks to make sure the databases have students (or more than one for Faculty) before allowing changeAdvisorForStudent to run. If neither pass, the user is alerted and nothing happens.
          if(!database->studentRecordHasData() || !database->facultyRecordHasData()) {
            cout << "You do not have any students and/or faculty present. Please add data before trying this." << endl;
          } else if(!database->facultyRecordHasMoreThanOneFaculty()) {
            cout << "Advisors can not be adjusted until there is more than one faculty advisor present." << endl;
          } else {
            changeAdvisorForStudent();
          }
          break;
        case 12:
          //Same thing as case 12, but for removeAdviseeFromFaculty().
          if(!database->studentRecordHasData() || !database->facultyRecordHasData()) {
            cout << "You do not have any students and/or faculty present. Please add data before trying this." << endl;
          } else if(!database->facultyRecordHasMoreThanOneFaculty()) {
            cout << "Advisors can not be adjusted until there is more than one faculty advisor present." << endl;
          } else {
            removeAdviseeFromFaculty();
          }
          break;
        case 13:
          //Calls the rollback method should this option be called.
          rollback();
          break;
        case 14:
          //Sets isFinished to true to allow for the simulation to exit.
          isFinished = true;
          break;
        default:
          //Number given does not correspond with a function, so user has to try again.
          cout << "You did not enter a valid selection. Please try again." << endl;
          break;
      }
    } else {
      //A number was not entered, so the user has to try again.
      cout << "You did not enter a number. Please try again." << endl;
    }
  }
  //Exit has been called, so loop exits.
  //User is alerted that everything is being saved to the file and that the program is ending.
  cout << "Saving databases to file" << endl;
  database->printDatabasesToFile();
  cout << "Closing program. Goodbye!" << endl;
}

//Checks if the given string contains an integer.
bool Simulation::checkIfStringIsNumber(string tempString) {
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

//From Option 1: Alerts user it is printing students, then calls on the database to print the student data in a user-friendly format.
void Simulation::printStudents() {
  cout << "Printing all students." << endl;
  database->printDatabaseToConsole(true);
}

//From Option 2: Alerts user it is printing faculty, then calls on the database to print the faculty data in a user-friendly format.
void Simulation::printFaculty() {
  cout << "Printing all faculty." << endl;
  database->printDatabaseToConsole(false);
}

//From Option 3: Display student.
void Simulation::displayStudent() {
  //If no students are present, alert user and terminate method.
  if(!database->studentRecordHasData()) {
    cout << "Student record is empty. Add students first!" << endl;
    return;
  }
  int tempID = 0;
  while(true) {
    //Get ID for student. Keep looping until a number is given.
    cout << "Enter the ID number of the student to search for." << endl;
    tempID = getNumResponse();
    if(tempID != -1) {
      break;
    } else {
      cout << "Trying again." << endl;
    }
  }
  //Attempts to get the student in the database with the corresponding ID.
  Student* tempStudent = database->searchForStudent(tempID);
  if(tempStudent == NULL) {
    //If the student was not found, the user is alerted that the ID is invalid and the method ends.
    cout << "The student with ID number " << tempID << " does not exist. Returning to main menu." << endl;
  } else {
    //Student was found, so print student data.
    cout << "Printing info of student: " << endl;
    cout << tempStudent->printDataForUser() << endl;
  }
}

//From option 4: Display Faculty
void Simulation::displayFaculty() {
  //If no faculty are present, alert user and terminate method.
  if(!database->facultyRecordHasData()) {
    cout << "Faculty record is empty. Add faculty first!" << endl;
    return;
  }
  int tempID = 0;
  while(true) {
    //Get ID for faculty. Keep looping until a number is given.
    cout << "Enter the ID number of the faculty to search for." << endl;
    tempID = getNumResponse();
    if(tempID != -1) {
      break;
    } else {
      cout << "Trying again." << endl;
    }
  }
  //Attempts to geth the faculty in the database with the corresponding ID.
  Faculty* tempFaculty = database->searchForFaculty(tempID);
  if(tempFaculty == NULL) {
    //If the faculty member was not found, the user is alerted that the ID is invalid and the method ends.
    cout << "The faculty with ID number " << tempID << " does not exist. Returning to main menu." << endl;
  } else {
    //Faculty was found, so print faculty data.
    cout << "Printing infor of faculty member: " << endl;
    cout << tempFaculty->printDataForUser() << endl;
  }
}

//From Option 5: Print Advisor of Student
void Simulation::printAdvisorOfStudent() {
  //Method does not continue if students are not present.
  if(!database->studentRecordHasData()) {
    cout << "Student record is empty. Add students first!" << endl;
    return;
  }
  int tempID = 0;
  //Loop continues until user gives an ID number for the student.
  while(true) {
    cout << "Enter the ID number of the student to get the advisor of." << endl;
    tempID = getNumResponse();
    if(tempID != -1) {
      break;
    } else {
      cout << "Trying again." << endl;
    }
  }
  //Attempts to find student.
  Student* tempStudent = database->searchForStudent(tempID);
  if(tempStudent == NULL) {
    //Student was not found. Alert user and end method.
    cout << "The student with ID number " << tempID << " does not exist. Returning to main menu." << endl;
  } else {
    //Student was found. Get corresponding faculty member from the student's faculty advisor variable and print the faculty member's data.
    Faculty* tempFaculty = database->searchForFaculty(tempStudent->getFacultyAdvisorID());
    cout << "Advisor of " << tempStudent->getName() << " has the following information: " << endl;
    cout << tempFaculty->printDataForUser() << endl;
  }
}

//From Option 6: Print Advisees of Faculty
void Simulation::printAdviseesOfFaculty() {
  //Method does not continue if faculty is not present.
  if(!database->facultyRecordHasData()) {
    cout << "Faculty record is empty. Add faculty first!" << endl;
    return;
  }
  int tempID = 0;
  //Loop continues until user gives an ID number for the faculty member.
  while(true) {
    cout << "Enter the ID number of the faculty to get the advisees of." << endl;
    tempID = getNumResponse();
    if(tempID != -1) {
      break;
    } else {
      cout << "Trying again." << endl;
    }
  }
  //Attempts to find faculty.
  Faculty* tempFaculty = database->searchForFaculty(tempID);
  if(tempFaculty == NULL) {
    //Faculty was not found. Alert user and end method.
    cout << "The faculty with ID number " << tempID << " does not exist. Returning to main menu." << endl;
  } else {
    //Faculty was found. Get the list of advisees from the faculty member. Then, using each integer stored in the list, print the corresponding student infor.
    cout << "Advisees of " << tempFaculty->getName() << " are the following: " << endl;
    ListADT<int>* tempList = tempFaculty->getListOfStudentAdviseeIDs();
    Student* tempStudent = NULL;
    int tempStudentID = 0;
    while(!tempList->isEmpty()) {
      tempStudentID = tempList->remove(tempList->valueAt(0));
      tempStudent = database->searchForStudent(tempStudentID);
      cout << tempStudent->printDataForUser() << "\n" << endl;
    }
  }
}

//From Option 7: Add Student
void Simulation::addStudent() {
  //No faculty means no students, so end method here if no faculty is present.
  if(!database->facultyRecordHasData()) {
    cout << "Can not add students if there is no faculty present. Please add faculty then try again." << endl;
    return;
  }
  //Add a backup of the database with prepBackup()
  prepBackup();
  //Alert user they are about to add a student.
  cout << "Preparing to add student. ID Number is randomly generated. Faculty Advisor is also randomly assigned. You can reassign the faculty advisor from the main menu." << endl;
  //Prints result of the add. tempStudent will never be NULL due to the above if statement, but it's there just in case something goes wrong.
  Student* tempStudent = database->addStudent();
  if(tempStudent != NULL) {
    cout << "Student added with following data: \n" << tempStudent->printDataForUser() << endl;
  }
}

//From Option 9: Add Faculty. Backs up the database and adds/prints the new faculty member using database's addFaculty method.
void Simulation::addFaculty() {
  prepBackup();
  cout << "Preparing to add faculty." << endl;
  Faculty* tempFaculty = database->addFaculty();
  cout << "Faculty added with following data: \n" << tempFaculty->printDataForUser() << endl;
}

//From Option 8: Delete Student
void Simulation::deleteStudent() {
  //End early since no students present to delete.
  if(!database->studentRecordHasData()) {
    cout << "Student record is empty. No deleting possible." << endl;
    return;
  }
  int selection = 0;
  while(true) {
    //Confirm with user they wish to delete a student.
    cout << "Are you sure you wish to continue deleting a student? Type the number of your choice." << endl;
    cout << "1. Yes, I want to delete a student." << endl;
    cout << "2. No, I do not want to delete a student." << endl;
    selection = getNumResponse();
    if(selection == -1) {
      //Loop will continue until a number is given.
      cout << "You did not enter a number. Please try again." << endl;
      continue;
    }
    switch(selection) {
      case 1: {
        //User indeed wants to delete a student. Backup first.
        prepBackup();
        int tempID = 0;
        while(true) {
          //Gets student to delete from user.
          cout << "Enter the ID number of the student to delete." << endl;
          tempID = getNumResponse();
          if(tempID == -1) {
            //Loop repeats if a string was entered.
            cout << "You did not enter a number. Please try again." << endl;
          } else {
            //Attempt to delete the student.
            Student* tempStudent = database->deleteStudent(tempID);
            if(tempStudent == NULL) {
              //Unable to delete student. User is prompted to try another student.
              cout << "Student with ID number " << tempID << " does not exist. Please try again." << endl;
            } else {
              //Student found and deleted, so print the deleted student's info.
              cout << "The student with the following information has been deleted: " << endl;
              cout << tempStudent->printDataForUser() << endl;
              return;
            }
          }
        }
        break;
      }
      case 2:
        //Exits loop since user changed their mind.
        cout << "Not deleting student. Exiting to main menu." << endl;
        return;
        break;
      default:
      //Something other than a 1 or 2 was given by the user, so they are asked to try again.
        cout << "Invalid response. Please try again." << endl;
        break;
    }
  }
}

//From Option 10: Delete Faculty.
void Simulation::deleteFaculty() {
  //Exit early if no faculty are present or if only one is present (faculty is needed to teach students!)
  if(!database->facultyRecordHasData()) {
    cout << "Faculty record is empty. No deleting possible." << endl;
    return;
  }
  if(!database->facultyRecordHasMoreThanOneFaculty()) {
    cout << "Can not delete faculty member since there is only one left. Add more faculty members to perform a delete operation." << endl;
    return;
  }
  int selection = 0;
  while(true) {
    //Confirm with user they wish to delete a student.
    cout << "Are you sure you wish to continue deleting a faculty member? Type the number of your choice." << endl;
    cout << "1. Yes, I want to delete a faculty member." << endl;
    cout << "2. No, I do not want to delete a faculty member." << endl;
    selection = getNumResponse();
    if(selection == -1) {
      //Number not entered, so loop goes again.
      cout << "You did not enter a number. Please try again." << endl;
      continue;
    }
    //Switch ase based on selection.
    switch(selection) {
      case 1: {
        //Go for deletion, but first backup.
        prepBackup();
        int tempID = 0;
        while(true) {
          //Get ID of faculty member to delete.
          cout << "Enter the ID number of the faculty member to delete." << endl;
          tempID = getNumResponse();
          if(tempID == -1) {
            //User did not enter a string
            cout << "You did not enter a number. Please try again." << endl;
          } else {
            //Number entered. Attempt to delete the Faculty Member.
            Faculty* tempFaculty = database->deleteFaculty(tempID);
            if(tempFaculty == NULL) {
              //Not successful. User is told to try a different ID.
              cout << "Faculty member with ID number " << tempID << " does not exist. PLease try again." << endl;
            } else {
              //Delete was successful. Print faculty member that was deleted.
              cout << "The faculty member with the following information has been deleted: " << endl;
              cout << tempFaculty->printDataForUser() << endl;
              return;
            }
          }
        }
        break;
      }
      case 2:
        //User changed their mind and no deleting will happen.
        cout << "Not deleting faculty member. Exiting to main menu." << endl;
        return;
        break;
      default:
        //A non 1 or 2 number was given, so user is asked to try again.
        cout << "Invalid response. Please try again." << endl;
        break;
    }
  }
}

//From Option 11: Change Advisor For Student.
void Simulation::changeAdvisorForStudent() {
  //Prep the backup before starting.
  prepBackup();
  while(true) {
    //Get ID of student to change advisor of.
    cout << "Enter ID of student to change the advisor of." << endl;
    int tempID = getNumResponse();
    if(tempID == -1) {
      //Number not entered. User tries again.
      cout << "You did not enter a number. Please try again." << endl;
    } else {
      //Number entered. Rest of method takes place in Database, including error checking.
      database->changeAdvisorForStudent(tempID);
      return;
    }
  }
}

//From Option 12: Remove Advisee From Faculty
void Simulation::removeAdviseeFromFaculty() {
  //Double checks that data is present, otherwise early exit.
  if(!database->studentRecordHasData() || !database->facultyRecordHasData()) {
    cout << "You do not have any students and/or faculty present. Please add data before trying this." << endl;
    return;
  }
  //Backs up before starting.
  prepBackup();
  while(true) {
    //Gets ID number of the faculty member in question.
    cout << "Enter the ID number of the faculty member who is losing an advisee." << endl;
    int tempFacultyID = getNumResponse();
    if(tempFacultyID == -1) {
      //Number not entered. User has to try again.
      cout << "You did not enter a number. Please try again." << endl;
    } else {
      while(true) {
        //Faculty number stored. Do the same for the student ID.
        cout << "Enter the ID number of the student to remove from the list of this faculty member's advisee's" << endl;
        int tempStudentID = getNumResponse();
        if(tempStudentID == -1) {
          //Number not entered. User must try again.
          cout << "You did not enter a number. Please try again." << endl;
        } else {
          //Numbers stored for both ID's and passed to database. Rest of function continues there.
          database->removeAdviseeFromFaculty(tempFacultyID, tempStudentID);
          return;
        }
      }
    }
  }
}

//From Option 13: Rollback
void Simulation::rollback() {
  restoreBackup();
}

//Converts a string to an int, if possible.
int Simulation::getNumResponse() {
  //Gets response from user.
  string response = "";
  getline(cin, response);
  if(checkIfStringIsNumber(response)) {
    //String is number, so convert and return.
    stringstream ss(response);
    int tempNum = 0;
    ss >> tempNum;
    ss.clear();
    return tempNum;
  } else {
    //String is not a number, so return -1 (negatives do not return positive with checkIfStringIsNumber)
    return -1;
  }
}

//Creates a backup of the databases and stores it in the Rollback object.
void Simulation::prepBackup() {
  //Deep copies studentRecord and facultyRecord before storing in a BackupDatabase and pushing to Rollback.
  BackupDatabase* newBackup = new BackupDatabase(database->copyStudentRecord(), database->copyFacultyRecord());
  backups->addNewBackup(newBackup);
}

//Rolls back to previous state, if possible.
void Simulation::restoreBackup() {
  if(backups->backupsArePresent()) {
    //Backups are stored. User is alerted of this.
    cout << "RESTORING TO PREVIOUS STATE OF DATABSE." << endl;
    //Get the backup to be rolled back to.
    BackupDatabase* backup = backups->restoreBackup();
    //Swap the BST's stored in backup and database for each other.
    backup->backupStudentRecord = database->restoreStudentRecord(backup->backupStudentRecord);
    backup->backupFacultyRecord = database->restoreFacultyRecord(backup->backupFacultyRecord);
    //Delete backup and all its contents. They are no longer needed.
    delete backup;
    //Tells user how mnay possible rollbacks are left to do.
    cout << "Number of Rollback States Left: " << backups->getNumOfBackupsStored() << endl;
  } else {
    //NO backups are present, so nothing is done.
    cout << "No backups present to restore from." << endl;
  }
}
