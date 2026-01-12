#ifndef SOLUTION_H
#define SOLUTION_H

#include "MazeSolver.h"
#include "Robot/State.h"

class SolutionFollower : public MazeSolver {
  private:
  int count = 0;

  // decide whethere there is a junction (including simple turns)
  void checkIfJunction() override;

  // I am in a junction -> identify the type of junction
  void identifyJunction() override;

  public:

  // function to be called at every main loop
    void loop() override;
};

#endif