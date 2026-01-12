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

char decisionToChar(DECISION d);

#endif