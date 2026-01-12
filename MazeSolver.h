#ifndef MAZE_H
#define MAZE_H
#include "Shared.h"
#include "Display/Display.h"
#include "App/Buttons.h"
#include "Robot/State.h"
#include "Robot/Decision.h"
#include "Robot/Path.h"
#include "Robot/LineFollower.h"

class MazeSolver : public LineFollower
{

private:
  void addDecision(DECISION d);

  void displayPath();

protected:
  // path taken by the robot
  // stored statically so that SolutionFollower can access it
  static Path path;

  // current robot state
  ROBOT_STATE state;

  // movement functions
  void turnLeft();
  void turnRight();
  void makeUTurn();
  
  // check if robot reached a junction / deadend
  virtual bool reachedJunction();
  bool reachedDeadEnd();

  virtual void identifyJunction();


public:
  // constructor
  MazeSolver();

  bool finished();

  // function to be called at every main loop
  virtual void loop() override;
};

extern MazeSolver mazeSolver;

#endif
