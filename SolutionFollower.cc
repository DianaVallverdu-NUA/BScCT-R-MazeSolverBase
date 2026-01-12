#include "SolutionFollower.h"
#include "Shared.h"
#include "Detector/Detector.h"

/**
 * 1. Move forward and re read sensor values
 * 2. Check if all sensors detect line -> FINISHED
 * 3. Identify simple left / right turns (only one side detected)
 * 4. Otherwise follow path stored at path variable
 */
void SolutionFollower::identifyJunction()
{

  // move forward & rescan
  delay(500);
  moveForwardFor(250);
  lineSensors.readLineBlack(lineSensorValues);

  // if end of maze detected return
  if (Detector::endOfMazeReached())
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // case -> simple left -> don't follow decisions vector
  if (Detector::isSimpleLeft())
  {
    state = ROBOT_STATE::TURNING_LEFT;
    return;
  }

  // case -> simple right -> don't follow decisions vector
  if (Detector::isSimpleRight())
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    return;
  }

  // if end of path array -> FINISHED
  if (count == path.length)
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // make correct turn
  DECISION d = path.steps[count];
  switch (d)
  {
  case DECISION::LEFT:
  {
    state = ROBOT_STATE::TURNING_LEFT;
    break;
  }
  case DECISION::RIGHT:
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    break;
  }
  case DECISION::FORWARD:
  {
    moveForwardFor(100);
    state = ROBOT_STATE::FOLLOWING_LINE;
    break;
  }
  }

  // update count for next junction
  count++;
}
