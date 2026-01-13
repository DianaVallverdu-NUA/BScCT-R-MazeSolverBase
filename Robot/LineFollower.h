#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <Pololu3piPlus32U4.h>

using namespace Pololu3piPlus32U4;

constexpr int NUM_SENSORS = 5;

class LineFollower
{

protected:
  /**
   * Follow line using a PD controller.
   */
  void followLine();

  /**
   * Motors object for controlling robot movement.
   */
  static Motors motors;
  /**
   * Error from last call to followLine (for derivative term).
   */
  static int lastError;

  /**
   * Max speed allowed for the motors - absolute max is 400.
   */
  static const uint16_t maxSpeed = 100;

  /**
   * Min speed allowed for the motors - absolute max is -400.
   */
  static const int16_t minSpeed = -100;

  /**
   * Base speed for the motors.
   */
  static const uint16_t baseSpeed = maxSpeed;

  /**
   * Speed used during sensor calibration.
   */
  static const uint16_t calibrationSpeed = 60;

  /**
   * Proportional coefficient out of 256.
   */
  static const uint16_t proportional = 64;

  /**
   * Derivative coefficient out of 256.
   */
  static const uint16_t derivative = 256;

  /**
   * Move forward for a specified number of milliseconds.
   */
  void moveForwardFor(uint16_t ms);

  /**
   * Turn left for a specified number of milliseconds.
   * ~730 ms for 90 degree turn at base speed.
   */
  void turnLeftFor(uint16_t ms);

  /**
   * Turn left for a specified number of milliseconds.
   * ~730 ms for 90 degree turn at base speed.
   */
  void turnRightFor(uint16_t ms);

public:
  /**
   * Line sensors object for reading line sensor values.
   * Since it changes at every read, it has been left at public & static for all classes to use.
   */
  static LineSensors lineSensors;

  /**
   * Array to hold the line sensor readings.
   * Since it changes at every read, it has been left at public & static for all classes to use.
   */
  static unsigned int lineSensorValues[NUM_SENSORS];

  /**
   * Calibrate the line sensors.
   */
  void calibrateSensors();

  /**
   * Main loop function to be called repeatedly.
   * Executes followLine by default.
   */
  virtual void loop();
};

#endif