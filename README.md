# Assignment_5

## Identifying Information:
1. AJ Keenan
1. Student ID: 2316808
1. akeenan@chapman.edu
1. CPSC 350-02
1. Assignment: Assignment 5

## Application Purpose
The purpose of this application is to be a database of students and faculty at Chapman University. The application can store Students (randomly-generated, unique ID, name, grade, major, and faculty advisor) and Faculty members (randomly-generated, unique ID, name, level in university hierarchy, department, and all the faculty member's advisees). The program can manipulate this data to add more, change the advisors around for both students and faculty, and delete old records. It also comes with a built-in rollback feature that allows for the undoing of the previous 5 variations of the database. Finally, the databases will save to a file to be modified again every time the program exits properly.

## Source Files
1. BackupDatabase.cpp
1. BackupDatabase.h
1. BST.cpp
1. Database.cpp
1. Database.h
1. Faculty.cpp
1. Faculty.h
1. FileIO.cpp
1. FileIO.h
1. LinkedList.cpp
1. LinkedListNode.cpp
1. ListADT.h
1. main.cpp
1. Makefile
1. Person.cpp
1. Person.h
1. Rollback.cpp
1. Rollback.h
1. Simulation.cpp
1. Simulation.h
1. Stack.cpp
1. Student.cpp
1. Student.h
1. TreeNode.cpp

## Known Errors:
1. You can only have up to 100,000 records in the database (students and faculty combined).
1. ID's must be randomly generated (helps with behind-the-scenes BST implementation) and can not be user-defined.
1. Exiting the program without using the Exit command (selecting option 14) will not save the data to the file.

## References
1. Class Notes (Stack/BST/LinkedList Implementation, Classes Needed)
1. ZyBooks (LinkedList functions/ListADT Implementation/BST Implementation)
1. CPlusPlus.com (std::max, rand, Pointers, std::rand, Polymorphism, std::getline(string), std::stringstream::str, std::string::compare, function isdigit, std::ofstream::open, std::is_pointer, if statement, std::is_pointer)
1. Stack Overflow (error: 'NULL' was not declared in this scope, const to Non-const Conversion in C++, Convert a String in C++ to Upper Case, Parse (split) a string in C++ using string delimiter (standard C++), C++ cast to derived class, Why am I getting string does not name a type Error?, Finding the type of an object in C++, the protected and private member variables in C++ inheritance, 'setprecision' is not a member of 'std', Getting error: ISO C++ forbids declaration of with no type, Append to a File with fstream Instead of Overwriting, Extending std::to_string to support enums and pointers, Errors when using constexpr-if: expected '(' before 'constexpr', What does "dereferencing" a pointer mean?, Determine if Type is a pointer in a template function, Error: Jump to case label, Resetting the End of file state of a ifstream object in C++)
1. StackExchange for Software Engineering (Is overriding a pure virtual function with default arguments good or bad?)
1. Tutorials Point (Input/Output Operators Overloading in C++)
1. The Best Schools (Professor Rankings: From Adjunct to Emeritus)
1. W3Schools.com (C++ Dereference, C++ Switch)
1. FluentCPP (Using toString on Custom Types in C++)
1. W3cubDocs/C++ (std::is_pointer)

## Compilation Instructions
Use the "make all" command, courtesy of the included MAKEFILE, to compile all source files. To run the program, run the assignment5.exe program from any linux terminal, such as in docker. If using previously-created databases that were stored to file, make sure those are present in the same directory as this application (studentTable.txt and facultyTable.txt).
