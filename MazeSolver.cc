
#include <Pololu3piPlus32U4.h>

using namespace Pololu3piPlus32U4;

#include "MazeSolver.h"
#include "Detector/Detector.h"

MazeSolver::MazeSolver()
{
  state = ROBOT_STATE::FOLLOWING_LINE;
}

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

  delay(500);
  moveForwardFor(250);
  lineSensors.readLineBlack(lineSensorValues);

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
    if (!Detector::isSimpleLeft()){
      path.addDecision(DECISION::LEFT);
      path.displayPath();
    }
    return;
  }

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

  // if there's a right but don't record as it will only be simple
  if (Detector::isSimpleRight())
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    return;
  }

  // any other case -> keep going there might have been a misdetection
  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::turnLeft()
{
  moveForwardFor(250);

  turnLeftFor(730);

  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::turnRight()
{
  moveForwardFor(250);

  turnRightFor(730);

  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::makeUTurn()
{
  motors.setSpeeds(-baseSpeed, baseSpeed);
  delay(1450);
  motors.setSpeeds(0, 0);
  state = ROBOT_STATE::FOLLOWING_LINE;
}

void MazeSolver::checkForStateChange()
{
  // if potential junction detected -> change state
  if (Detector::possibleJunction())
  {
    state = ROBOT_STATE::IDENTIFYING_JUNCTION;
    motors.setSpeeds(0, 0);
    return;
  }

  // if dead end detected -> change state
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

  switch (state)
  {
  case ROBOT_STATE::FOLLOWING_LINE:
    followLine();
    checkForStateChange();
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
    motors.setSpeeds(0, 0);
    break;
  case ROBOT_STATE::FAKE_END:
    display.printBar(8);
    break;
  }
}

Path MazeSolver::path{};