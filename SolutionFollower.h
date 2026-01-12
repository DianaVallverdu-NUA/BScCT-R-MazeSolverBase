#ifndef SOLUTION_H
#define SOLUTION_H

#include "MazeSolver.h"
#include "Robot/State.h"

class SolutionFollower : public MazeSolver
{
private:
  int count = 0;

  // Identifies type of junction and follows path accordingly
  void identifyJunction() override;

public:
  // function to be called at every main loop
  void loop() override;
};

#endif