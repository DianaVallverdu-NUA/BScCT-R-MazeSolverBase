#ifndef LINE_SENSOR_MANAGER_H
#define LINE_SENSOR_MANAGER_H

#include <Pololu3piPlus32U4.h>

using namespace Pololu3piPlus32U4;

/**
 * Static class for detecting maze features such as junctions and dead ends.
 */
class LineSensorsManager : public LineSensors
{

private:
  unsigned int lineSensorValues[5];

public:
  /**
   * @returns true when all sensors are above given threshold, false otherwise
   */
  bool areAllSensorsAbove(int threshold) const;

  /**
   * @returns true if middle sensor is above given threshold, false otherwise
   */
  bool isMiddleAbove(int threshold) const;

  /**
   * @returns true if leftmost sensor is above given threshold, false otherwise.
   */
  bool isLeftmostAbove(int threshold) const;

  /**
   * @returns true if rightmost sensor is above given threshold, false otherwise.
   */
  bool isRightmostAbove(int threshold) const;

  /**
   * Detect if any of the sensors is above given threshold
   */
  bool areAnySensorsAbove(int threshold) const;

  /**
   * @returns pointer to lineSensorValues vector
   */
  const unsigned int *getLineSensorValues();

  /**
   * @returns position value based on current line sensors
   */
  int16_t getPosition();
};

extern LineSensorsManager lineSensors;

#endif