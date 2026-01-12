#ifndef ROBOT_PATH_H
#define ROBOT_PATH_H

#include "Decision.h"

/**
 * A path of decisions that the robot has taken.
 * Contains multiple useful methods to analyze & simplify path.
 */
class Path
{
private:
  /**
   * Maximum length of the path - necessary when working with Arduino.
   */
  static const int MAX_LEN = 64;

  /**
   * Array of decisions taken by the robot.
   */
  DECISION steps[MAX_LEN];

  /**
   * Current length of the path.
   * Modified when adding decisions or simplifying.
   */
  int length = 0;

  /**
   * @return true if the previous decision was BACK, false otherwise.
   */
  bool previousWasBack();

  /**
   * @return true if the last three decisions were LEFT, BACK, FORWARD.
   */
  bool leftBackForward();

  /**
   * @return true if the last three decisions were LEFT, BACK, LEFT.
   */
  bool leftBackLeft();

  /**
   * @return true if the last three decisions were RIGHT, BACK, LEFT.
   */
  bool rightBackLeft();

  /**
   * @return true if the last three decisions were FORWARD, BACK, FORWARD.
   */
  bool forwardBackForward();

  /**
   * @return true if the last three decisions were FORWARD, BACK, LEFT.
   */
  bool forwardBackLeft();

  /**
   * Replace the last three decisions with a new decision.
   * Used when simplifying.
   */
  void replaceLastThree(DECISION d);

  /**
   * Simplify the path by removing unnecessary movements when a back was made.
   * LBF => R
   * LBL => F
   * RBL => B
   * FBF => B
   */
  void simplify();

public:
  /**
   * @return true if the path has reached maximum length.
   */
  bool memoryFull();

  /**
   * Add a new decision to the path & simplify if possible.
   */
  void addDecision(DECISION d);

  /**
   * Display the path taken so far on the OLED screen.
   */
  void displayPath();

  /**
   * @return the decision at the given index in the path.
   */
  DECISION getStep(int index);

  /**
   * @return the current length of the path.
   */
  int getLength();
};
#endif