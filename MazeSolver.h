#ifndef MAZE_H
#define MAZE_H
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

enum Decisions {
  FORWARD, 
  LEFT,
  RIGHT, 
  BACK
};

class MazeSolver {
  private:
  State state; // value of type state

  // path to be followed to solve the maze
  static const int MAX_PATH = 50;
  Decisions path[MAX_PATH] = {};
  int pathLength = 0;

  void addDecision(Decisions d);

  void displayPath();

  void followLine();

  void checkIfJunction();

  void checkIfDeadEnd();

  void identifyJunction();

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

