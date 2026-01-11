#include "SolutionFollower.h"

void SolutionFollower::setPath(Path path) {
  path = path;
}

void SolutionFollower::identifyJunction() {

  delay(500);
  // move forward to identify other junctions
  motors.setSpeeds(baseSpeed, baseSpeed);
  delay(250);
  motors.setSpeeds(0, 0);
  lineSensors.readLineBlack(lineSensorValues);


  // identify simple turns
  if(lineSensorValues[2] < 750) {
    if(lineSensorValues[0] < 750) {
      state = TURN_RIGHT;
      return;
    }

    if(lineSensorValues[4] < 750) {
      state = TURN_LEFT;
      return;
    }

  // if no more decisions to follow -> finish
  if (currentD == pathLength) {
    state = FINISHED;
    return;
  }


    // case -> it's a real junction
    Decisions d = path.steps[currentD];

    switch(d) {
      case RIGHT : {
        state = TURN_RIGHT;
        break;
      }
      case FORWARD : {
        state = LINE_FOLLOWER;
        break;
      }
      case LEFT : {
        state = TURN_LEFT;
        break;
      }
    }

    currentD++;
  }
}