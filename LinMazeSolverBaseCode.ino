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


ButtonB buttonB;

Mode mode = Mode::SOLVING;

MazeSolver mazeSolver;
SolutionFollower solutionFollower;


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
