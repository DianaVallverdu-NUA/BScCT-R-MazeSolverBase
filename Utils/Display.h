#ifndef DISPLAY_H
#define DISPLAY_H


#include <Pololu3piPlus32U4.h>
using namespace Pololu3piPlus32U4;

/**
 * Manages the OLED display on the 3pi+ robot.
 */
class DisplayManager : public OLED
{
public:
  /**
   * Constructor - loads custom characters.
   */
  DisplayManager();

  /**
   * Loads custom characters for bar graph display.
   */
  void loadCustomCharacters();

  /**
   * Prints a vertical bar of the given height (0-8).
   */
  void printBar(uint8_t height);

  /**
   * Shows sensor readings as a bar graph until button B is pressed.
   */
  void showReadings();

  /**
   * Asks the user to calibrate the sensors.
   */
  void askForCalibration();
};

extern DisplayManager display;

#endif