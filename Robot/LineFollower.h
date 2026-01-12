#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>

using namespace Pololu3piPlus32U4;

constexpr int NUM_SENSORS = 5;

class LineFollower
{

protected:
  void followLine();

  static Motors motors;
  static int lastError;

  static const uint16_t maxSpeed = 100;
  static const int16_t minSpeed = -100;

  static const uint16_t baseSpeed = maxSpeed;

  static const uint16_t calibrationSpeed = 60;

  static const uint16_t proportional = 64; // coefficient of the P term * 256
  static const uint16_t derivative = 256;  // coefficient of the D term * 256

public:
  static LineSensors lineSensors;
  static unsigned int lineSensorValues[NUM_SENSORS];

  void calibrateSensors();

  virtual void loop();
};

#endif