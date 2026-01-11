/* This example uses the line sensors on the 3pi+ 32U4 to follow
a black line on a white background, using a PID-based algorithm.
It works well on courses with smooth, 6" radius curves and can
even work with tighter turns, including sharp 90 degree corners.
This example has been tested with robots using 30:1 MP motors.
Modifications might be required for it to work well on different
courses or with different motors. */

#include <Pololu3piPlus32U4.h>
#include "Shared.h"
#include "MazeSolver.h"
#include "SolutionFollower.h"
#include "Display/Display.h"
#include "App/Mode.h"
#include "App/Buttons.h"
#include "LineFollower/LineFollower.h"

using namespace Pololu3piPlus32U4;


LineSensors lineSensors;
Motors motors;

ButtonB buttonB;

int16_t lastError = 0;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

// Note that making the 3pi+ go faster on a line following course
// might involve more than just increasing this number; you will
// often have to adjust the PID constants too for it to work well.
uint16_t maxSpeed;
int16_t minSpeed;

// This is the speed the motors will run when centered on the line.
// Set to zero and set minSpeed to -maxSpeed to test the robot
// without.
uint16_t baseSpeed;

uint16_t calibrationSpeed;

// PID configuration: This example is configured for a default
// proportional constant of 1/4 and a derivative constant of 1, which
// seems to work well at low speeds for all of our 3pi+ editions.  You
// will probably want to use trial and error to tune these constants
// for your particular 3pi+ and line course, especially if you
// increase the speed.

uint16_t proportional; // coefficient of the P term * 256
uint16_t derivative; // coefficient of the D term * 256

Mode mode = Mode::SOLVING;

MazeSolver mazeSolver;
SolutionFollower solutionFollower;

LineFollower lineFollower;

void setup()
{
  // calibrate
  display.askForCalibration();
  while(!buttonB.getSingleDebouncedPress());

  lineFollower.calibrateSensors();

  display.showReadings();

  // Go message
  display.clear();
  display.print(F("Go!"));
}

void loop()
{
  if(mode == Mode::SOLVING){
    mazeSolver.loop();

    // done with solving
    if(mazeSolver.finished()) {
      solutionFollower.setPath(mazeSolver.getPath());
      mode = Mode::FOLLOWING;
    }

  }

  if(mode == Mode::FOLLOWING) {
    solutionFollower.loop();
  }
}
