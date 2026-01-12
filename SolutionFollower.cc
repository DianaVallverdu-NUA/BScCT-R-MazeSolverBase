#include "SolutionFollower.h"
#include "Shared.h"
#include "Detector/Detector.h"

/**
 * 1. Move forward and re read sensor values
 * 2. Check if all sensors detect line -> FINISHED
 * 3. Identify simple left / right turns (only one side detected)
 * 4. Otherwise follow path stored at path variable
 */
void SolutionFollower::identifyJunction()
{

  // move forward & rescan
  delay(500);
  moveForwardFor(250);
  lineSensors.readLineBlack(lineSensorValues);

  // if end of maze detected return
  if (Detector::endOfMazeReached())
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // case -> simple left -> don't follow decisions vector
  if (Detector::isSimpleLeft())
  {
    state = ROBOT_STATE::TURNING_LEFT;
    return;
  }

  // case -> simple right -> don't follow decisions vector
  if (Detector::isSimpleRight())
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    return;
  }

  // if end of path array -> FINISHED
  if (count == path.length)
  {
    state = ROBOT_STATE::FINISHED;
    return;
  }

  // make correct turn
  DECISION d = path.steps[count];
  switch (d)
  {
  case DECISION::LEFT:
  {
    state = ROBOT_STATE::TURNING_LEFT;
    break;
  }
  case DECISION::RIGHT:
  {
    state = ROBOT_STATE::TURNING_RIGHT;
    break;
  }
  case DECISION::FORWARD:
  {
    moveForwardFor(100);
    state = ROBOT_STATE::FOLLOWING_LINE;
    break;
  }
  }

  // update count for next junction
  count++;
}

void SolutionFollower::loop()
{

  if (state == ROBOT_STATE::FOLLOWING_LINE)
  {
    followLine();
    // check if junction there's a junction and change state otherwise
    if (Detector::possibleJunction())
    {
      state = ROBOT_STATE::IDENTIFYING_JUNCTION;
      motors.setSpeeds(0, 0);
    }
  }

  if (state == ROBOT_STATE::IDENTIFYING_JUNCTION)
  {
    identifyJunction();
  }

  if (state == ROBOT_STATE::TURNING_LEFT)
  {
    turnLeft();
  }

  if (state == ROBOT_STATE::TURNING_RIGHT)
  {
    turnRight();
  }
  if (state == ROBOT_STATE::FINISHED)
  {
    motors.setSpeeds(0, 0);
  }

  if (state == ROBOT_STATE::FAKE_END)
  {

    while (!buttonB.getSingleDebouncedPress())
    {
      uint16_t position = lineSensors.readLineBlack(lineSensorValues);

      display.gotoXY(0, 0);
      display.print(position);
      display.print("    ");
      display.gotoXY(0, 1);
      for (uint8_t i = 0; i < NUM_SENSORS; i++)
      {
        uint8_t barHeight = map(lineSensorValues[i], 0, 1000, 0, 8);

        if (barHeight > 8)
        {
          barHeight = 8;
        }
        const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
        display.print(barChars[barHeight]);
      }

      delay(50);
    }
  }
}
