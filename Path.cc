#include "Robot/Path.h"
#include "Display/Display.h"

bool Path::memoryFull()
{
  return length >= MAX_LEN;
}

bool Path::previousWasBack()
{
  if (length < 1)
    return false;
  return steps[length - 1] == DECISION::BACK;
}

bool Path::leftBackForward()
{
  if (length < 2)
    return false;
  return steps[length - 2] == DECISION::LEFT && steps[length - 1] == DECISION::BACK && steps[length] == DECISION::FORWARD;
}

bool Path::leftBackLeft()
{
  if (length < 2)
    return false;
  return steps[length - 2] == DECISION::LEFT && steps[length - 1] == DECISION::BACK && steps[length] == DECISION::LEFT;
}

bool Path::rightBackLeft()
{
  if (length < 2)
    return false;
  return steps[length - 2] == DECISION::RIGHT && steps[length - 1] == DECISION::BACK && steps[length] == DECISION::LEFT;
}

bool Path::forwardBackForward()
{
  if (length < 2)
    return false;
  return steps[length - 2] == DECISION::FORWARD && steps[length - 1] == DECISION::BACK && steps[length] == DECISION::FORWARD;
}

bool Path::forwardBackLeft()
{
  if (length < 2)
    return false;
  return steps[length - 2] == DECISION::FORWARD && steps[length - 1] == DECISION::BACK && steps[length] == DECISION::LEFT;
}

void Path::replaceLastThree(DECISION d)
{
  steps[length - 2] = d;
  steps[length - 1] = DECISION::NONE;
  steps[length] = DECISION::NONE;
  length -= 2;
}

void Path::display()
{
  display.clear();
  display.gotoXY(0, 0);
  for (int i = 0; i < 8; i++)
  {
    display.print(decisionToChar(path.steps[i]));
  }
  display.gotoXY(0, 1);
  for (int i = 8; i < 16; i++)
  {
    display.print(decisionToChar(path.steps[i]));
  }
}

void Path::addDecision(DECISION d)
{
  if (memoryFull())
    return;

  steps[length] = d;

  simplify();

  length++;
}

void Path::simplify()
{
  if (!previousWasBack())
    return;

  if (leftBackForward() || forwardBackLeft())
  {
    replaceLastThree(DECISION::RIGHT);
    return;
  }

  if (leftBackLeft())
  {
    replaceLastThree(DECISION::FORWARD);
    return;
  }

  if (rightBackLeft() || forwardBackForward())
  {
    replaceLastThree(DECISION::BACK);
    return;
  }
};