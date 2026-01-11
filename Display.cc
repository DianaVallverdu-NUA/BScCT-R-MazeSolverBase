#include "Display/Display.h"
#include "App/Buttons.h"


DisplayManager::DisplayManager()
{
  // Change next line to this if you are using the older 3pi+
  // with a black and green LCD display:
  // LCD display;
  loadCustomCharacters();
}

// Sets up special characters in the LCD so that we can display
// bar graphs.
void DisplayManager::loadCustomCharacters()
{
  static const char levels[] PROGMEM = {
      0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
  };
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
  if (height > 8) { height = 8; }
  const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
  print(barChars[height]);
}

// Displays the estimated line position and a bar graph of sensor
// readings on the LCD. Returns after the user presses B.
void DisplayManager::showReadings()
{
  clear();

  while(!buttonB.getSingleDebouncedPress())
  {
    uint16_t position = lineSensors.readLineBlack(lineSensorValues);

    gotoXY(0, 0);
    print(position);
    print("    ");
    gotoXY(0, 1);
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
      uint8_t barHeight = map(lineSensorValues[i], 0, 1000, 0, 8);
      printBar(barHeight);
    }

    delay(50);
  }
}

DisplayManager display;