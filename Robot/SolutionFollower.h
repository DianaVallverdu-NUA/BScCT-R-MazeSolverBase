#ifndef SOLUTION_H
#define SOLUTION_H

#include "MazeSolver.h"
#include "LineSensorsManager.h"

/**
 * Once a path is found this class loops through the stored path and follow along.
 */
class SolutionFollower : public MazeSolver
{
private:
  /**
   * Number of decisions made so far.
   */
  uint8_t pathIndex = 0;

  /**
   * 1. Move forward for better re reading
   * 2. Check if all sensors detect line -> FINISHED
   * 3. Identify simple left / right turns (only one side detected)
   * 4. Otherwise follow path stored at path variable
   */
  void identifyJunction() override;
};

#endif