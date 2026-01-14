#include "Robot/LineSensorsManager.h"
#include "Robot/LineFollower.h"


bool LineSensorsManager::areAllSensorsAbove(int threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);
  
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
}

bool LineSensorsManager::isMiddleAbove(int threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);

  // check for forward
  if (lineSensorValues[2] > threshold)
  {
    return true;
  }
  return false;
}

bool LineSensorsManager::isLeftmostAbove(int threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);

  // check if left sensor high
  if (lineSensorValues[0] > threshold)
  {
    return true;
  }
  return false;
}

bool LineSensorsManager::isRightmostAbove(int threshold) const
{
  // read sensors
  readLineBlack(lineSensorValues);

  // check if right sensor high
  if (lineSensorValues[4] > threshold)
  {
    return true;
  }
  return false;
}

bool LineSensorsManager::areAnySensorsAbove(int threshold) const 
{
// read sensors
readLineBlack(lineSensorValues);

// if any sensor is high -> possible junction
if (lineSensorValues[0] > threshold)
  return true;
if (lineSensorValues[1] > threshold)
  return true;
if (lineSensorValues[3] > threshold)
  return true;
if (lineSensorValues[4] > threshold)
  return true;

return false;
}

const unsigned int *LineSensorsManager::getLineSensorValues()
{
  return lineSensorValues;
}

int16_t LineSensorsManager::getPosition()
{
  return readLineBlack(lineSensorValues);
}

LineSensorsManager lineSensors;