#ifndef DISPLAY_H
#define DISPLAY_H

#include "../Shared.h"

#include <Pololu3piPlus32U4.h>
using namespace Pololu3piPlus32U4;

class DisplayManager : public OLED {
  public:
    DisplayManager();

    void loadCustomCharacters();

    void printBar(uint8_t height);

    void showReadings();
};

extern DisplayManager display;

#endif