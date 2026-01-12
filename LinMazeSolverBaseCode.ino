#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>

#include "Robot/MazeSolver.h"
#include "Robot/SolutionFollower.h"
#include "Utils/Display.h"
#include "Utils/Buttons.h"

using namespace Pololu3piPlus32U4;

ButtonB buttonB;

MazeSolver mazeSolver;
SolutionFollower solutionFollower;

PololuMenu<typeof(display)> menu;

void setup()
{
  // ask for calibration & wait for button press
  display.askForCalibration();
  while (!buttonB.getSingleDebouncedPress())
    ;

  // calibrate sensors -> done statically for all inherited classes
  mazeSolver.calibrateSensors();

  // show sensor readings until button B is pressed
  display.showReadings();

  // Go message
  display.clear();
  display.print(F("Go!"));
}

void loop()
{
  // if maze solver not finished -> keep solving maze
  if (!mazeSolver.finished())
  {
    mazeSolver.loop();

    // if maze solver finished in THIS LOOP -> wait for be press
    if (mazeSolver.finished())
    {

      // display finished message on line two
      display.gotoXY(0, 1);
      display.print(F("Finished"));

      // wait for b press
      while (!buttonB.getSingleDebouncedPress())
        ; 
    }

    return;
  }

  // if maze solver is finished -> follow solution
  solutionFollower.loop();
}
