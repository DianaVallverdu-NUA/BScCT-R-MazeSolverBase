#ifndef ROBOT_PATH_H
#define ROBOT_PATH_H

#include "Decision.h"
#include <Pololu3piPlus32U4.h>


/**
 * A path of decisions that the robot has taken.
 * Contains multiple useful methods to analyze & simplify path.
 */
class Path
{
private:
  // ============================ VARIABLES ============================

  /**
   * Maximum length of the path - necessary when working with Arduino.
   */
  static const uint8_t MAX_LEN = 64;

  /**
   * Array of decisions taken by the robot.
   */
  DECISION steps[MAX_LEN];

  /**
   * Current length of the path.
   * Modified when adding decisions or simplifying.
   */
  uint8_t length = 0;

  // ============================ BOOLEAN CHECKS ============================

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
   * @return true if the path has reached maximum length.
   */
  bool isFull();

  // ============================ PATH SIMPLIFICATION ============================

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
  // ============================ PATH MODIFICATION ============================
  /**
   * Add a new decision to the path & simplify if possible.
   */
  void addDecision(DECISION d);

  // ============================ GETTERS ============================

  /**
   * @return the decision at the given index in the path.
   */
  DECISION getStep(uint8_t index);

  /**
   * @return the current length of the path.
   */
  uint8_t getLength();

  // ============================ UTILS ============================

  /**
   * Display the path taken so far on the OLED screen.
   */
  void displayPath();
};
#endif