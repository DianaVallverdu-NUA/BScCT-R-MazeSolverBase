#ifndef STATE_H
#define STATE_H

/**
 * Possible states the robot can be in as it navigates the maze.
 * These states are used both by MazeSolver and SolutionFollower.
 */
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