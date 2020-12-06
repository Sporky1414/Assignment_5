/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 5
*/

#include "Simulation.h"

using namespace std;

//Main method for program. Simply runs simulation and deletes it when done.
int main (int argc, char** argv) {
  Simulation* simulation = new Simulation();
  simulation->run();
  delete simulation;
  return 0;
}
