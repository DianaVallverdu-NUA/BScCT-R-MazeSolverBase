
#include <Pololu3piPlus32U4.h>

using namespace Pololu3piPlus32U4;

#include "MazeSolver.h"
#include "Detector/Detector.h"

void MazeSolver::addDecision(DECISION d)
{

  if (path.length >= path.MAX_LEN)
    return;

  if (path.length > 1)
    if (path.steps[path.length - 1] == DECISION::BACK)
    {
      if (path.steps[path.length - 2] == DECISION::LEFT)
      {
        if (d == DECISION::FORWARD)
        {
          d = DECISION::RIGHT;
        }
        if (d == DECISION::LEFT)
        {
          d = DECISION::FORWARD;
        }
      }
      if (path.steps[path.length - 2] == DECISION::RIGHT)
      {
        if (d == DECISION::LEFT)
        {
          d = DECISION::BACK;
        }
      }

      if (path.steps[path.length - 2] == DECISION::FORWARD)
      {
        if (d == DECISION::FORWARD)
        {
          d = DECISION::BACK;
        }
        if (d == DECISION::LEFT)
        {
          d = DECISION::RIGHT;
        }
      }
      // state = FAKE_END;
      path.steps[path.length - 1] = DECISION::NONE;
      path.steps[path.length - 2] = DECISION::NONE;
      path.length -= 2;
    }

  path.steps[path.length] = d;

  path.length++;

  displayPath();
}

char decisionToChar(DECISION d)
{
  switch (d)
  {
  case DECISION::FORWARD:
    return 'F';
  case DECISION::LEFT:
    return 'L';
  case DECISION::RIGHT:
    return 'R';
  case DECISION::BACK:
    return 'B';
  }
  return ' ';
}

void MazeSolver::displayPath()
{
  display.clear();
  display.gotoXY(0, 0);
  for (int i = 0; i < 8; i++)
  {
    display.print(decisionToChar(path.steps[i]));
  }
  display.gotoXY(0, 1);
  for (int i = 8; i < 16; i++)
  {
    display.print(decisionToChar(path.steps[i]));
  }
}

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
    if (!Detector::isSimpleLeft())
      addDecision(DECISION::LEFT);
    return;
  }

  if (Detector::canGoForward())
  {
    // move forward to avoid redetecting junction
    moveForwardFor(100);

    // change state & add decision
    state = ROBOT_STATE::FOLLOWING_LINE;
    addDecision(DECISION::FORWARD);
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

void MazeSolver::loop()
{

  if (state == ROBOT_STATE::FOLLOWING_LINE)
  {
    followLine();

    if (Detector::possibleJunction())
    {
      state = ROBOT_STATE::IDENTIFYING_JUNCTION;
      motors.setSpeeds(0, 0);
    }
    else
    {
      if (Detector::reachedDeadEnd())
      {
        state = ROBOT_STATE::TURNING_BACK;
        addDecision(DECISION::BACK);
      }
    }
  }

  if (state == ROBOT_STATE::IDENTIFYING_JUNCTION)
  {
    identifyJunction();
  }

  if (state == ROBOT_STATE::TURNING_LEFT)
  {
    turnLeft();
  }

  if (state == ROBOT_STATE::TURNING_RIGHT)
  {
    turnRight();
  }
  if (state == ROBOT_STATE::TURNING_BACK)
  {
    makeUTurn();
  }
  if (state == ROBOT_STATE::FINISHED)
  {
    motors.setSpeeds(0, 0);
  }

  if (state == ROBOT_STATE::FAKE_END)
  {

    while (!buttonB.getSingleDebouncedPress())
    {
      uint16_t position = lineSensors.readLineBlack(lineSensorValues);

      display.gotoXY(0, 0);
      display.print(position);
      display.print("    ");
      display.gotoXY(0, 1);
      for (uint8_t i = 0; i < NUM_SENSORS; i++)
      {
        uint8_t barHeight = map(lineSensorValues[i], 0, 1000, 0, 8);

        if (barHeight > 8)
        {
          barHeight = 8;
        }
        const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
        display.print(barChars[barHeight]);
      }

      delay(50);
    }
  }
}

Path MazeSolver::path{};