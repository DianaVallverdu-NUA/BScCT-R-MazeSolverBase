#ifndef ROBOT_PATH_H
#define ROBOT_PATH_H

#include "Decision.h"

/**
 * A path of decisions that the robot has taken.
 */
struct Path
{
  static const uint8_t MAX_LEN = 64;
  DECISION steps[MAX_LEN];
  uint8_t length = 0;
};

#endif