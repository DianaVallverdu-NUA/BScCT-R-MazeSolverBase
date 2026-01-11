#ifndef MAZEROBOT_H
#define MAZEROBOT_H
#include "Shared.h"

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
  protected:
  State state; // value of type state

  void displayPath();

  void followLine();

  void checkIfJunction();

  void checkIfDeadEnd();

  void turnLeft();

  void turnRight();

  void uTurn();
  
  public:

    // constructor
    MazeSolver();

    // function to be called at every main loop
    void loop();

};

#endif

