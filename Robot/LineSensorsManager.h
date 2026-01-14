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
  // ============================ LINE SENSOR VALUES ============================
  uint16_t lineSensorValues[5];

public:
  // ============================ GETTERS ============================

  /**
   * @returns pointer to lineSensorValues vector
   */
  const uint16_t *getLineSensorValues();

  /**
   * @returns position value based on current line sensors
   */
  int16_t getPosition();

  // ============================ BOOLEAN CHECKS ============================

  /**
   * @returns true when all sensors are above given threshold, false otherwise
   */
  bool areAllSensorsAbove(uint16_t threshold) const;

  /**
   * @returns true if middle sensor is above given threshold, false otherwise
   */
  bool isMiddleAbove(uint16_t threshold) const;

  /**
   * @returns true if leftmost sensor is above given threshold, false otherwise.
   */
  bool isLeftmostAbove(uint16_t threshold) const;

  /**
   * @returns true if rightmost sensor is above given threshold, false otherwise.
   */
  bool isRightmostAbove(uint16_t threshold) const;

  /**
   * Detect if any of the sensors is above given threshold
   */
  bool areAnySideSensorsAbove(uint16_t threshold) const;
};

// global variable used in Display, LineFollower & MazeSolver
extern LineSensorsManager lineSensors;

#endif