#ifndef SOLUTION_H
#define SOLUTION_H

#include "MazeSolver.h"

class SolutionFollower {
  private:
  State state; // value of type state
  int count = 0;

  void displayPath();

  void followLine();

  // decide whethere there is a junction (including simple turns)
  void checkIfJunction();

  // I am in a junction -> identify the type of junction
  void identifyJunction();

  void turnLeft();

  void turnRight();

  public: 

    Decisions path[50];
    int totalLength;

  // function to be called at every main loop
    void loop();
};

#endif