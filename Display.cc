#include "Utils/Display.h"
#include "Utils/Buttons.h"
#include "Robot/LineFollower.h"
#include "Robot/MazeSolver.h"

DisplayManager::DisplayManager()
{
  loadCustomCharacters();
}

void DisplayManager::askForCalibration()
{
  clear();
  print(F("Press B"));
  gotoXY(0, 1);
  print(F("to calib"));
}

void DisplayManager::loadCustomCharacters()
{
  static const char levels[] PROGMEM = {
      0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63};
  loadCustomCharacter(levels + 0, 0); // 1 bar
  loadCustomCharacter(levels + 1, 1); // 2 bars
  loadCustomCharacter(levels + 2, 2); // 3 bars
  loadCustomCharacter(levels + 3, 3); // 4 bars
  loadCustomCharacter(levels + 4, 4); // 5 bars
  loadCustomCharacter(levels + 5, 5); // 6 bars
  loadCustomCharacter(levels + 6, 6); // 7 bars
}

void DisplayManager::printBar(uint8_t height)
{
  if (height > 8)
  {
    height = 8;
  }
  const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
  print(barChars[height]);
}

void DisplayManager::showReadings()
{
  clear();

  while (!buttonB.getSingleDebouncedPress())
  {
    uint16_t position = mazeSolver.lineSensors.readLineBlack(mazeSolver.lineSensorValues);

    gotoXY(0, 0);
    print(position);
    print("    ");
    gotoXY(0, 1);
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
      uint8_t barHeight = map(mazeSolver.lineSensorValues[i], 0, 1000, 0, 8);
      printBar(barHeight);
    }

    delay(50);
  }
}

DisplayManager display;