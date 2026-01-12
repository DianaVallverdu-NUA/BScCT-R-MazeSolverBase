#ifndef MAZE_H
#define MAZE_H
#include "Shared.h"
#include "Display/Display.h"
#include "App/Buttons.h"
#include "Robot/State.h"
#include "Robot/Decision.h"

struct Path
{
  static const uint8_t MAX_LEN = 64;
  DECISION steps[MAX_LEN];
  uint8_t length = 0;
};

class MazeSolver
{

private:
  void addDecision(DECISION d);

  void displayPath();

protected:
  static Path path;

  ROBOT_STATE state; // value of type state

  void followLine();

  // check whether there is a junction
  virtual void checkIfJunction();

  void checkIfDeadEnd();

  // I am in a junction -> identify the type of junction
  virtual void identifyJunction();

  void turnLeft();

  void turnRight();

  void uTurn();

public:
  // constructor
  MazeSolver();

  bool finished();

  // function to be called at every main loop
  virtual void loop();
};

#endif
