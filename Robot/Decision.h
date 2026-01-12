#ifndef ROBOT_DECISION_H
#define ROBOT_DECISION_H

/**
 * Possible decisions the robot can make at junctions.
 */
enum class DECISION
{
  NONE,
  FORWARD,
  LEFT,
  RIGHT,
  BACK
};

/**
 * Convert a DECISION enum to its corresponding character representation.
 * 'F' for FORWARD, 'L' for LEFT, 'R' for RIGHT, 'B' for BACK, and ' ' for NONE.
 */
char decisionToChar(DECISION d);

#endif