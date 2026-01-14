#include "Robot/SolutionFollower.h"
#include "Robot/LineSensorsManager.h"

void SolutionFollower::identifyJunction()
{

  // move forward for better sensor reading
  delay(500);
  moveForwardFor(IDENTIFY_JUNCTION_DELAY);

  // if end of maze detected return
  if (lineSensors.areAllSensorsAbove(STRONG_BLACK_THRESHOLD))
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // case simple left -> don't check decisions vector
  if (isSimpleLeft())
  {
    state = ROBOT_STATE::TURNING_LEFT;
    return;
  }

  // case simple right -> don't check decisions vector
  if (isSimpleRight())
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    return;
  }

  // if end of path array -> FINISHED
  if (pathIndex == path.getLength())
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // make correct turn
  DECISION d = path.getStep(pathIndex);
  switch (d)
  {
  case DECISION::LEFT:
    state = ROBOT_STATE::TURNING_LEFT;
    break;
  case DECISION::RIGHT:
    state = ROBOT_STATE::TURNING_RIGHT;
    break;
  case DECISION::FORWARD:
    moveForwardFor(AFTER_JUNCTION_FORWARD_DELAY);
    state = ROBOT_STATE::FOLLOWING_LINE;
    break;
  }

  // update pathIndex for next junction
  pathIndex++;
}
