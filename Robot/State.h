#ifndef STATE_H
#define STATE_H

// enum creates a new type which can be used like any type
enum class ROBOT_STATE
{
  FOLLOWING_LINE,
  IDENTIFYING_JUNCTION,
  TURNING_LEFT,
  TURNING_RIGHT,
  TURNING_BACK,
  FINISHED,
  FAKE_END
};

#endif