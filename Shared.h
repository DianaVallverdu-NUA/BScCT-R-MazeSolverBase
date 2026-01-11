#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Pololu3piPlus32U4.h>

using namespace Pololu3piPlus32U4;

extern LineSensors lineSensors;
extern Motors motors;

extern int16_t lastError;

constexpr int NUM_SENSORS = 5;
extern unsigned int lineSensorValues[NUM_SENSORS];

extern uint16_t maxSpeed;
extern int16_t minSpeed;

extern uint16_t baseSpeed;

extern uint16_t calibrationSpeed;

extern uint16_t proportional;  // coefficient of the P term * 256
extern uint16_t derivative;    // coefficient of the D term * 256

// decisions that can be taken on a junction
enum Decision {
  NONE,
  FORWARD,
  LEFT,
  RIGHT,
  BACK
};


#endif