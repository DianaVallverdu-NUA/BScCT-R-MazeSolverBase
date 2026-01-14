#include "Robot/MazeSolver.h"
#include "Robot/LineSensorsManager.h"

// ============================ ROBOT MOVEMENT ============================

void MazeSolver::turnLeft()
{
  // move forward to center robot on line.
  moveForwardFor(FORWARD_BEFORE_TURNING_DELAY);

  // turn left until
  turnLeftFor(TURN_90_DEGREES_DELAY);

  // go back to following line
  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::turnRight()
{
  // move forward to center robot on line.
  moveForwardFor(FORWARD_BEFORE_TURNING_DELAY);

  // turn right -> delay found empirically.
  turnRightFor(TURN_90_DEGREES_DELAY);

  // go back to following line
  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::makeUTurn()
{
  // turn on itself (180 degrees)
  turnLeftFor(TURN_90_DEGREES_DELAY * 2);

  // go back to following line
  state = ROBOT_STATE::FOLLOWING_LINE;
}

// ============================ UTILS ============================

void MazeSolver::identifyJunction()
{
  // move forward so robot can check better type of junction
  delay(500);
  moveForwardFor(IDENTIFY_JUNCTION_DELAY);

  // if can sense everywhere -> FINISHED
  if (lineSensors.areAllSensorsAbove(STRONG_BLACK_THRESHOLD))
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // if there's a left take it
  if (lineSensors.isLeftmostAbove(BLACK_THRESHOLD))
  {
    state = ROBOT_STATE::TURNING_LEFT;

    // It is only a decision if it is not a simple left
    if (!isSimpleLeft())
    {
      path.addDecision(DECISION::LEFT);
      path.displayPath();
    }
    return;
  }

  // if can go forward -> go forward
  if (lineSensors.isMiddleAbove(BLACK_THRESHOLD))
  {
    // move forward to avoid redetecting junction
    moveForwardFor(AFTER_JUNCTION_FORWARD_DELAY);

    // change state & add decision
    state = ROBOT_STATE::FOLLOWING_LINE;
    path.addDecision(DECISION::FORWARD);
    path.displayPath();
    return;
  }

  // if there's a right take it but don't record as decision
  // as it means no other option was available
  if (lineSensors.isRightmostAbove(BLACK_THRESHOLD))
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    return;
  }

  // any other case -> keep going there might have been a misdetection
  moveForwardFor(AFTER_JUNCTION_FORWARD_DELAY);
  state = ROBOT_STATE::FOLLOWING_LINE;
}

bool MazeSolver::isSimpleRight()
{
  // ensure you CAN turn right
  if (!lineSensors.isRightmostAbove(BLACK_THRESHOLD))
    return false;

  // ensure you CANNOT turn left or go forward
  if (lineSensors.isMiddleAbove(BLACK_THRESHOLD))
    return false;
  if (lineSensors.isLeftmostAbove(BLACK_THRESHOLD))
    return false;
  return true;
}

bool MazeSolver::isSimpleLeft()
{

  // ensure you CAN turn left
  if (!lineSensors.isLeftmostAbove(BLACK_THRESHOLD))
    return false;

  // ensure you CANNOT turn right or go forward
  if (lineSensors.isMiddleAbove(BLACK_THRESHOLD))
    return false;
  if (lineSensors.isRightmostAbove(BLACK_THRESHOLD))
    return false;
  return true;
}

void MazeSolver::detectJunctionOrDeadEnd()
{
  // if potential junction detected -> change state to identify
  if (lineSensors.areAnySideSensorsAbove(STRONG_BLACK_THRESHOLD))
  {
    state = ROBOT_STATE::IDENTIFYING_JUNCTION;
    motors.setSpeeds(0, 0);
    return;
  }

  // if dead end detected -> change state to turn back
  if (!lineSensors.isMiddleAbove(WHITE_THRESHOLD))
  {
    state = ROBOT_STATE::TURNING_BACK;
    path.addDecision(DECISION::BACK);
    path.displayPath();
    return;
  }
}

// ============================ PUBLIC FUNCTIONS ============================

bool MazeSolver::isFinished()
{
  if (state == ROBOT_STATE::FINISHED)
  {
    return true;
  }
  return false;
}

void MazeSolver::loop()
{
  // check current state and call function accordingly
  switch (state)
  {
  case ROBOT_STATE::FOLLOWING_LINE:
    followLine();
    detectJunctionOrDeadEnd(); // when following line also check for state changes
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

// ============================ STATIC VARIABLES ============================
// If static variables are not explicitly declared outside of the .h file the cannot be used
Path MazeSolver::path{};