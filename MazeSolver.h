#ifndef MAZE_H
#define MAZE_H
#include "Shared.h"

// enum creates a new type which can be used like any type
enum State {
  LINE_FOLLOWER,
  JUNCTION,
  TURN_LEFT,
  U_TURN,
  FINISHED,
  FAKE_END
};

struct Path {
    static const uint8_t MAX_LEN = 64;
    Decisions steps[MAX_LEN];
    uint8_t length = 0;
};

class MazeSolver {
  private:
  State state; // value of type state


  void addDecision(Decisions d);

  void displayPath();

  void followLine();

  // check whether there is a junction
  void checkIfJunction();

  void checkIfDeadEnd();

  // I am in a junction -> identify the type of junction
  void identifyJunction();

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
    void loop();

};

#endif

