#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>

#include "Shared.h"
#include "MazeSolver.h"
#include "SolutionFollower.h"
#include "Display/Display.h"
#include "App/Buttons.h"

using namespace Pololu3piPlus32U4;

ButtonB buttonB;

MazeSolver mazeSolver;
SolutionFollower solutionFollower;

PololuMenu<typeof(display)> menu;

void setup()
{
  // Uncomment if necessary to correct motor directions:
  // motors.flipLeftMotor(true);
  // motors.flipRightMotor(true);

  display.loadCustomCharacters();

  // Wait for button B to be pressed and released.
  display.clear();
  display.print(F("Press B"));
  display.gotoXY(0, 1);
  display.print(F("to calib"));
  while (!buttonB.getSingleDebouncedPress())
    ;

  mazeSolver.setup();

  display.showReadings();

  // Go message
  display.clear();
  display.print(F("Go!"));
}

void loop()
{
  if (!mazeSolver.finished())
  {
    mazeSolver.loop();

    // copy over path from mazeSolver to solutionFollower
    if (mazeSolver.finished())
    {

      // wait for b press
      display.gotoXY(0, 1);
      display.print(F("Finished"));
      while (!buttonB.getSingleDebouncedPress())
        ; // wait for button b to be pressed before continuing
    }

    return;
  }

  // if maze solver is finished -> follow solution
  solutionFollower.loop();
}
