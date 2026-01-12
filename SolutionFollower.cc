#include "SolutionFollower.h"
#include "Shared.h"

void SolutionFollower::checkIfJunction() {
  lineSensors.readLineBlack(lineSensorValues);

  bool junction = false;

  if (lineSensorValues[0] > 950) junction = true;  // detect a line to the left
  if (lineSensorValues[1] > 950) junction = true;  // detect a line to the left
  if (lineSensorValues[3] > 950) junction = true;  // detect a line to the right
  if (lineSensorValues[4] > 950) junction = true;  // detect a line to the right
  // any other case contains one of these types

  if (junction) {
    state = JUNCTION;
    motors.setSpeeds(0, 0);
  }
}

void SolutionFollower::identifyJunction() {

  // move forward to identify other junctions
  delay(500);
  motors.setSpeeds(baseSpeed, baseSpeed);
  delay(250);
  motors.setSpeeds(0, 0);
  lineSensors.readLineBlack(lineSensorValues);

  // if can sense everywhere -> FINISHED
  if (lineSensorValues[0] > 950 && lineSensorValues[1] > 950 && lineSensorValues[2] > 950 && lineSensorValues[3] > 950 && lineSensorValues[4] > 950) {
    state = FINISHED;
    return;
  }

  // case -> a possible left is detected
  if (lineSensorValues[0] > 750) {
    if (lineSensorValues[2] < 750 && lineSensorValues[4] < 750) {
      state = TURN_LEFT;
      return;
    }
  }

  // case -> a possible right is detected
  if (lineSensorValues[4] > 750) {
    if (lineSensorValues[0] < 750 && lineSensorValues[2] < 750) {
      state = TURN_RIGHT;
      return;
    }
  }

  if(count == path.length) {
    state = FAKE_END;
    return;
  }

  // it is a junction
  Decision d = path.steps[count];

  switch (d) {
    case LEFT:
      {
        state = TURN_LEFT;
        break;
      }
    case RIGHT:
      {
        state = TURN_RIGHT;
        break;
      }
    case FORWARD:
      {
        motors.setSpeeds(baseSpeed, baseSpeed);
        delay(100);
        state = LINE_FOLLOWER;
        break;
      }
  }

  count++;
}

void SolutionFollower::loop() {

  if (state == LINE_FOLLOWER) {
    followLine();
    //check if junction there's a junction and change state otherwise
    checkIfJunction();
  }

  if (state == JUNCTION) {
    identifyJunction();
  }

  if (state == TURN_LEFT) {
    turnLeft();
  }

  if (state == TURN_RIGHT) {
    turnRight();
  }
  if (state == FINISHED) {
    motors.setSpeeds(0, 0);
  }

  if (state == FAKE_END) {


    while (!buttonB.getSingleDebouncedPress()) {
      uint16_t position = lineSensors.readLineBlack(lineSensorValues);

      display.gotoXY(0, 0);
      display.print(position);
      display.print("    ");
      display.gotoXY(0, 1);
      for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        uint8_t barHeight = map(lineSensorValues[i], 0, 1000, 0, 8);

        if (barHeight > 8) { barHeight = 8; }
        const char barChars[] = { ' ', 0, 1, 2, 3, 4, 5, 6, (char)255 };
        display.print(barChars[barHeight]);
      }

      delay(50);
    }
  }
}
