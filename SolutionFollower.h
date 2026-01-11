#ifndef SOLUTION_H
#define SOLUTION_H

#include "MazeSolver.h"

class SolutionFollower : public MazeSolver {
  private:
    void identifyJunction();
    int currentD = 0;
    int pathLength;
  
  public: 
    void setPath(Path path);
};

#endif