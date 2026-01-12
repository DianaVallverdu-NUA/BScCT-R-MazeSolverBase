#include "Robot/Decision.h"

char decisionToChar(DECISION d)
{
  switch (d)
  {
  case DECISION::FORWARD:
    return 'F';
  case DECISION::LEFT:
    return 'L';
  case DECISION::RIGHT:
    return 'R';
  case DECISION::BACK:
    return 'B';
  }
  return ' ';
}