#include "Robot/SolutionFollower.h"
#include "Robot/Detector.h"

void SolutionFollower::identifyJunction()
{

  // move forward for better sensor reading
  delay(500);
  moveForwardFor(250);

  // if end of maze detected return
  if (Detector::endOfMazeReached())
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // case simple left -> don't follow decisions vector
  if (Detector::isSimpleLeft())
  {
    state = ROBOT_STATE::TURNING_LEFT;
    return;
  }

  // case simple right -> don't follow decisions vector
  if (Detector::isSimpleRight())
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    return;
  }

  // if end of path array -> FINISHED
  if (count == path.getLength())
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // make correct turn
  DECISION d = path.getStep(count);
  switch (d)
  {
  case DECISION::LEFT:
    state = ROBOT_STATE::TURNING_LEFT;
    break;
  case DECISION::RIGHT:
    state = ROBOT_STATE::TURNING_RIGHT;
    break;
  case DECISION::FORWARD:
    moveForwardFor(100);
    state = ROBOT_STATE::FOLLOWING_LINE;
    break;
  }

  // update count for next junction
  count++;
}
