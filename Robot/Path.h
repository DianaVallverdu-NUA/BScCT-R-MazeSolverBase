#ifndef ROBOT_PATH_H
#define ROBOT_PATH_H

#include "Decision.h"

/**
 * A path of decisions that the robot has taken.
 */
class Path
{
private:
  // Returns true if the previous decision was a BACK.
  bool previousWasBack();

  // check patterns for simplification
  bool leftBackForward();
  bool leftBackLeft();
  bool rightBackLeft();
  bool forwardBackForward();
  bool forwardBackLeft();

  // Replace the last three decisions with a new decision.
  void replaceLastThree(DECISION d);

public:
  static const int MAX_LEN = 64;
  DECISION steps[MAX_LEN];
  int length = 0;
  
  // Returns true if the path memory is full.
  bool memoryFull();

  // Check for back patterns & simplify.
  void simplify();

  // Add a decision to the path.
  void addDecision(DECISION d);

  // Display path
  void display();
};
#endif