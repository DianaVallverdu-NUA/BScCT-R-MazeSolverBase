#ifndef DETECTOR_H
#define DETECTOR_H
/**
 * Static class for detecting maze features such as junctions and dead ends.
 */
class Detector
{
public:
  /**
   * Detect end of maze - all sensors on black
   */
  static bool endOfMazeReached();

  /**
   * Detect a potential junction (including simple turns)
   */
  static bool possibleJunction();

  /*
   * Detect if the robot has reached a dead end - middle sensor on white
   */
  static bool reachedDeadEnd();

  /**
   * Detect if a forward path exists - middle sensor on black
   */
  static bool canGoForward();


  /**
   * Detect if a right path exists - right sensor on black (including simple right)
   */
  static bool canTurnRight();

  /**
   * Detect if a left path exists - left sensor on black (including simple left)
   */
  static bool canTurnLeft();

  /**
   * Detect if the junction is a simple left turn - left sensor on black, middle & right sensors on white
   */
  static bool isSimpleLeft();

  /**
   * Detect if the junction is a simple right turn - right sensor on black, middle & left sensors on white
   */
  static bool isSimpleRight();

  /**
   * Detect if the junction is a simple turn (left or right)
   */
  static bool isSimpleTurn();
};

#endif