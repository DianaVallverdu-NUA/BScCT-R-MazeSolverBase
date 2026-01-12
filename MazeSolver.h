#ifndef MAZE_H
#define MAZE_H
#include "Shared.h"
#include "Display/Display.h"
#include "App/Buttons.h"

// enum creates a new type which can be used like any type
enum State {
  LINE_FOLLOWER,
  JUNCTION,
  TURN_LEFT,
  TURN_RIGHT,
  U_TURN,
  FINISHED,
  FAKE_END
};

struct Path {
    static const uint8_t MAX_LEN = 64;
    Decision steps[MAX_LEN];
    uint8_t length = 0;
};

class MazeSolver {

  private:
  void addDecision(Decision d);
  void displayPath();

  protected:
  State state; // value of type state

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

  // path to be followed to solve the maze
  static const int MAX_PATH = 50;
  Path path;
  int pathLength = 0;
  
    // constructor
    MazeSolver();

    
    const Path& getPath();

    bool finished();

    // function to be called at every main loop
    virtual void loop();

};

#endif

