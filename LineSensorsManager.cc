#include "Robot/LineSensorsManager.h"
#include "Robot/LineFollower.h"

bool LineSensorsManager::areAllSensorsAbove(uint16_t threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);

  // check all values
  if (lineSensorValues[0] < threshold)
    return false;
  if (lineSensorValues[1] < threshold)
    return false;
  if (lineSensorValues[2] < threshold)
    return false;
  if (lineSensorValues[3] < threshold)
    return false;
  if (lineSensorValues[4] < threshold)
    return false;

  return true;
}

bool LineSensorsManager::isMiddleAbove(uint16_t threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);

  // check for middle sensor
  if (lineSensorValues[2] > threshold)
    return true;

  return false;
}

bool LineSensorsManager::isLeftmostAbove(uint16_t threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);

  // check if left sensor high
  if (lineSensorValues[0] > threshold)
    return true;

  return false;
}

bool LineSensorsManager::isRightmostAbove(uint16_t threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);

  // check if right sensor high
  if (lineSensorValues[4] > threshold)
    return true;

  return false;
}

bool LineSensorsManager::areAnySideSensorsAbove(uint16_t threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);

  // if any sensor beyond middle high -> return true
  if (lineSensorValues[0] > threshold)
    return true;
  if (lineSensorValues[1] > threshold)
    return true;
  if (lineSensorValues[3] > threshold)
    return true;
  if (lineSensorValues[4] > threshold)
    return true;

  // if no sensor triggered true -> false
  return false;
}

const uint16_t *LineSensorsManager::getLineSensorValues()
{
  return lineSensorValues;
}

int16_t LineSensorsManager::getPosition()
{
  return readLineBlack(lineSensorValues);
}

// global variable used in Display, LineFollower & MazeSolver
LineSensorsManager lineSensors;