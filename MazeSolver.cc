#include "Robot/MazeSolver.h"
#include "Robot/Detector.h"

bool MazeSolver::finished()
{
  if (state == ROBOT_STATE::FINISHED)
  {
    return true;
  }
  return false;
}

void MazeSolver::identifyJunction()
{
  // move forward so robot can check better type of junction
  delay(500);
  moveForwardFor(250);

  // if can sense everywhere -> FINISHED
  if (Detector::endOfMazeReached())
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // if there's a left take it
  if (Detector::canTurnLeft())
  {
    state = ROBOT_STATE::TURNING_LEFT;

    // only add as decision if it's not a simple left
    if (!Detector::isSimpleLeft())
    {
      path.addDecision(DECISION::LEFT);
      path.displayPath();
    }
    return;
  }

  // if can go forward -> go forward
  if (Detector::canGoForward())
  {
    // move forward to avoid redetecting junction
    moveForwardFor(100);

    // change state & add decision
    state = ROBOT_STATE::FOLLOWING_LINE;
    path.addDecision(DECISION::FORWARD);
    path.displayPath();
    return;
  }

  // if there's a right take it but don't record as decision
  // as it means no other option was available
  if (Detector::isSimpleRight())
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    return;
  }

  // any other case -> keep going there might have been a misdetection
  moveForwardFor(50);
  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::turnLeft()
{
  // move forward to center robot on line.
  moveForwardFor(250);

  // turn left -> delay found empirically.
  turnLeftFor(730);

  // go back to following line
  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::turnRight()
{
  // move forward to center robot on line.
  moveForwardFor(250);

  // turn right -> delay found empirically.
  turnRightFor(730);

  // go back to following line
  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::makeUTurn()
{
  // turn on itself for 1450 ms -> delay found empirically.
  turnLeftFor(1450);

  // go back to following line
  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::checkForStateChange()
{
  // if potential junction detected -> change state to identify
  if (Detector::possibleJunction())
  {
    state = ROBOT_STATE::IDENTIFYING_JUNCTION;
    motors.setSpeeds(0, 0);
    return;
  }

  // if dead end detected -> change state to turn back
  if (Detector::reachedDeadEnd())
  {
    state = ROBOT_STATE::TURNING_BACK;
    path.addDecision(DECISION::BACK);
    path.displayPath();
    return;
  }
}

void MazeSolver::loop()
{
  // check current state and call function accordingly
  switch (state)
  {
  case ROBOT_STATE::FOLLOWING_LINE:
    followLine();
    checkForStateChange(); // when following line also check for state changes
    break;
  case ROBOT_STATE::IDENTIFYING_JUNCTION:
    identifyJunction();
    break;
  case ROBOT_STATE::TURNING_LEFT:
    turnLeft();
    break;
  case ROBOT_STATE::TURNING_RIGHT:
    turnRight();
    break;
  case ROBOT_STATE::TURNING_BACK:
    makeUTurn();
    break;
  case ROBOT_STATE::FINISHED:
    motors.setSpeeds(0, 0); // done -> stop moving
    break;
  case ROBOT_STATE::FAKE_END:
    // fake end is used here for debugging purposes.
    // if pololu is behaving unexpectedly, it can be used to stop the robot & display calibration.
    motors.setSpeeds(0, 0);
    display.printBar(8);
    break;
  }
}

Path MazeSolver::path{};