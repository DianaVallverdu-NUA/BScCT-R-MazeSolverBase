#include "Detector/Detector.h"
#include "Robot/LineFollower.h"

bool Detector::endOfMazeReached()
{
  // read sensors
  LineFollower::lineSensors.readLineBlack(LineFollower::lineSensorValues);

  // all sensors must be above 950 to be considered end of maze
  if (LineFollower::lineSensorValues[0] < 950)
    return false;
  if (LineFollower::lineSensorValues[1] < 950)
    return false;
  if (LineFollower::lineSensorValues[2] < 950)
    return false;
  if (LineFollower::lineSensorValues[3] < 950)
    return false;
  if (LineFollower::lineSensorValues[4] < 950)
    return false;

  return true;
}

bool Detector::canGoForward()
{
  // read sensors
  LineFollower::lineSensors.readLineBlack(LineFollower::lineSensorValues);

  // check for forward
  if (LineFollower::lineSensorValues[2] > 750)
  {
    return true;
  }
  return false;
}

bool Detector::canTurnLeft()
{
  // read sensors
  LineFollower::lineSensors.readLineBlack(LineFollower::lineSensorValues);

  // check for simple left
  if (LineFollower::lineSensorValues[0] > 750)
  {
    return true;
  }
  return false;
}

bool Detector::isSimpleLeft()
{
  // read sensors
  LineFollower::lineSensors.readLineBlack(LineFollower::lineSensorValues);

  // check for simple left
  if (LineFollower::lineSensorValues[0] > 750)
  {
    if (LineFollower::lineSensorValues[2] < 750 && LineFollower::lineSensorValues[4] < 750)
    {
      return true;
    }
  }
  return false;
}

bool Detector::isSimpleRight()
{
  // read sensors
  LineFollower::lineSensors.readLineBlack(LineFollower::lineSensorValues);

  // check for simple right
  if (LineFollower::lineSensorValues[4] > 750)
  {
    if (LineFollower::lineSensorValues[0] < 750 && LineFollower::lineSensorValues[2] < 750)
    {
      return true;
    }
  }
  return false;
}

bool Detector::possibleJunction()
{
  // read sensors
  LineFollower::lineSensors.readLineBlack(LineFollower::lineSensorValues);

  if (LineFollower::lineSensorValues[0] > 950)
    return true;
  if (LineFollower::lineSensorValues[1] > 950)
    return true;
  if (LineFollower::lineSensorValues[3] > 950)
    return true;
  if (LineFollower::lineSensorValues[4] > 950)
    return true;
  return false;
}

bool Detector::isSimpleTurn()
{
  return isSimpleLeft() || isSimpleRight();
}

bool Detector::reachedDeadEnd()
{
  // read sensors
  LineFollower::lineSensors.readLineBlack(LineFollower::lineSensorValues);

  if (LineFollower::lineSensorValues[2] < 500)
  {
    return true;
  }
  return false;
}