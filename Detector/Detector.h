#ifndef DETECTOR_H
#define DETECTOR_H

#include <Pololu3piPlus32U4.h>
using namespace Pololu3piPlus32U4;

class Detector
{
public:
  // detect end of maze
  static bool endOfMazeReached();

  // potential junction ahead
  static bool possibleJunction();

  // reached dead end
  static bool reachedDeadEnd();

  // detect if forward path exists
  static bool canGoForward();

  // detect if a left exists -> regardless if it is simple or not
  static bool canTurnLeft();

  // detect simple left / right / overall turn
  static bool isSimpleLeft();
  static bool isSimpleRight();
  static bool isSimpleTurn();
};

#endif