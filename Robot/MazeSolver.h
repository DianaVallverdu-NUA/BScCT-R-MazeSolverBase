#ifndef MAZE_H
#define MAZE_H
#include "../Utils/Display.h"
#include "../Utils/Buttons.h"
#include "State.h"
#include "Path.h"
#include "LineFollower.h"
#include "LineSensorManager.h"

class MazeSolver : public LineFollower
{
private:

  // delay values for turning
  static const uint16_t TURN_90_DEGREES_DELAY = 730;

  // delay values for forward
  static const uint16_t FORWARD_BEFORE_TURNING_DELAY = 250;

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

  // threshold values
  static const uint16_t BLACK_THRESHOLD = 750;
  static const uint16_t STRONG_BLACK_THRESHOLD = 950;
  static const uint16_t WHITE_THRESHOLD = 500;

  // identify junction delay
  static const uint16_t IDENTIFY_JUNCTION_DELAY = 250;
  static const uint16_t AFTER_JUNCTION_FORWARD_DELAY = 100;


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

  /**
   * @returns true if there is a left turn but no forward or right turn possible
   */
  bool isSimpleLeft();

  /**
   * @returns true if there is a right turn but no forward or left turn possible
   */
  bool isSimpleRight();

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
