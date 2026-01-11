#ifndef LineFollower_H
#define LineFollower_H

#include <Pololu3piPlus32U4.h>
using namespace Pololu3piPlus32U4;

#include "../Display/Display.h"

class LineFollower
{
public:
  void calibrateSensors();

protected:
  int maxSpeed = 100;
  int minSpeed = -100;
  int baseSpeed = maxSpeed;
  int calibrationSpeed = 60;
  int proportional = 64; // P coefficient = 1/4
  int derivative = 256;  // D coefficient = 1
};

#endif