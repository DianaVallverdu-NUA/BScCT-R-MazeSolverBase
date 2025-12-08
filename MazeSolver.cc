
#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>

using namespace Pololu3piPlus32U4;

#include "MazeSolver.h"
#include "Shared.h"
MazeSolver::MazeSolver() {
  state = LINE_FOLLOWER;
}

void MazeSolver::followLine() {
   // get position & error
  int16_t position = lineSensors.readLineBlack(lineSensorValues);
  int16_t error = position - 2000;

  // calculate speed difference with PID formula
  int16_t speedDifference = error * (int32_t)proportional / 256 + (error - lastError) * (int32_t)derivative / 256;

  // store error
  lastError = error;

  // get new speed & constrain
  int16_t leftSpeed = (int16_t)baseSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)baseSpeed - speedDifference;
  leftSpeed = constrain(leftSpeed, minSpeed, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, minSpeed, (int16_t)maxSpeed);

  // update motor speed
  motors.setSpeeds(leftSpeed, rightSpeed);

  //check if junction there's a junction and change state otherwise
  checkIfJunction();
}

void MazeSolver::checkIfJunction() {
  lineSensors.readLineBlack(lineSensorValues);

  bool junction = false;

  if(lineSensorValues[0] > 950) junction = true; // detect a line to the left
  if(lineSensorValues[4] > 950) junction = true; // detect a line to the right
  // any other case contains one of these types

  if(junction) {
    state = JUNCTION;
  }
}

void MazeSolver::identifyJunction() {

  display.clear();
  display.print(state);

  // set motor speed to zero
  motors.setSpeeds(0, 0);

  // if there's a left take it
  if(lineSensorValues[0] > 950) {
    state = TURN_LEFT;
    return;
  }

  // move forward to identify other junctions
  motors.setSpeeds(baseSpeed, baseSpeed);
  delay(300);
  motors.setSpeeds(0, 0);

  // if can still sense -> FINISHED
  if(lineSensorValues[0] && lineSensorValues[4] > 950) {
    state = FINISHED;
    return;
  }

  // any other case -> keep going
    state = LINE_FOLLOWER;
}

void MazeSolver::turnLeft() {
  motors.setSpeeds(baseSpeed, baseSpeed);
  delay(50);
  motors.setSpeeds(-baseSpeed, baseSpeed);
  delay(50);
  state = LINE_FOLLOWER;
}

void MazeSolver::loop() {
  if (state == LINE_FOLLOWER) {
    followLine();
  }

  if (state == JUNCTION) {
    identifyJunction();
  }
  if (state == TURN_LEFT) {
    turnLeft();
  }
  if (state == U_TURN) {
    // call u turn function
  }
  if (state == FINISHED) {
    motors.setSpeeds(0, 0);
    display.clear();
    display.print(state);
    return;
  }
}
