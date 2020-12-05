#include "Simulation.h"

using namespace std;

int main (int argc, char** argv) {
  Simulation* simulation = new Simulation();
  simulation->run();
  delete simulation;
  return 0;
}
