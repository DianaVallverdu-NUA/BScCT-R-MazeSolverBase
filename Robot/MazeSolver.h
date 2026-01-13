#ifndef MAZE_H
#define MAZE_H
#include "../Utils/Display.h"
#include "../Utils/Buttons.h"
#include "State.h"
#include "Path.h"
#include "LineFollower.h"

class MazeSolver : public LineFollower
{
private:
  /**
   * Turns 90 degrees left.
   */
  void turnLeft();

  /**
   * Turns 90 degrees right.
   */
  void turnRight();

  /**
   * Turns 180 degrees.
   */
  void makeUTurn();

  /**
   * Checks for potential junction & dead end.
   */
  void checkForStateChange();

protected:
  /**
   * Path taken by the robot through the maze.
   * stored statically so that SolutionFollower can access it.
   */
  static Path path;

  /**
   * Current state of the robot in the maze solving process.
   */
  ROBOT_STATE state = ROBOT_STATE::FOLLOWING_LINE;
  ;

  /**
   * Identifies the junction type and makes a decision based on the "left-hand on wall" rule.
   * Update path if a decision was needed (does not store simple turns).
   */
  virtual void identifyJunction();

public:
  /**
   * @returns true if the maze has been solved, false otherwise.
   */
  bool finished();

  /**
   * Main loop function to be called repeatedly.
   * Executes different behaviors based on the current state.
   */
  void loop() override;
};

extern MazeSolver mazeSolver;

#endif
