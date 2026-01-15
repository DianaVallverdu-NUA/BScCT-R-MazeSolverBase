# Lin Maze Solver Base Code

An Arduino-based robot project that autonomously solves a line-following maze with no cycles and then efficiently navigates the optimal path.

## Project Overview

This project implements a maze-solving robot for the Pololu 3π+ 32U4 platform. The robot:
1. **Explores the maze** using the `MazeSolver` class to find the exit
  - While exploring, it **optimizes the path** by eliminating dead ends and unnecessary turns
3. **Re-traces the solution** using the `SolutionFollower` class for the fastest route

### Key Features
- **Line following**: Uses infrared sensors to follow black lines on a white surface
- **Junction / Dead-end detection**: Identifies intersections and dead ends
- **Path optimization**: Automatically simplifies the path by removing backtracking
- **Memory efficient**: Uses `uint8_t` and `uint16_t` types to minimize memory footprint
- **Calibration system**: Interactive sensor calibration before maze solving - ported from Pololu examples
- **LCD display feedback**: Real-time status and sensor readings via LCD screen - ported from Pololu examples

## Building

This project is designed for the Arduino IDE. Ensure you have:
1. Arduino IDE installed
2. Pololu 3π+ 32U4 board support installed
3. Required libraries: `Pololu3piPlus32U4`
More information to install dependencies can be found in ... LINK

## Project Structure

```
LinMazeSolverBaseCode/
├── LinMazeSolverBaseCode.ino        # Main Arduino sketch
├── Robot/                           # Core robot functionality
│   ├── State.h                      # Robot state enumeration
│   ├── LineFollower.h               # Base class: primitive line-following
│   ├── MazeSolver.h                 # Maze exploration & path optimization
│   ├── SolutionFollower.h           # Efficient path execution
│   ├── Path.h                       # Path data structure & optimization
│   ├── LineSensorsManager.h         # Sensor management
│   ├── Decision.h                   # Decision enumeration (LEFT, RIGHT, FORWARD, BACK)
└── Utils/                           # Utility classes
│   ├── Display.h                    # LCD display control
│   ├── Buttons.h                    # Button input handling
└── (all .cc files)                  # Implementation files need (in root folder for Arduino IDE compatibility)
```

## Class Hierarchy

```
LineFollower (base)
├── MazeSolver
└── SolutionFollower (inherits from MazeSolver)
```

### LineFollower
- **Purpose**: Base class providing primitive line-following movement
- **Key Methods**: `followLine()`, motor control primitives
- **Capabilities**: Sensor calibration, basic movement

### MazeSolver
- **Purpose**: Explores the maze and finds the optimal path
- **Inherits from**: LineFollower
- **Key Properties**:
  - `Path path`- list of optimized decisions to get to where robot currently is. If state is Finished this is the maze solution.
    - static variable to be accessed by `SolutionFollower`
- **Key Methods**:
  - `turnLeft()`, `turnRight()`, `makeUTurn()` - turns left & right are 90º, may need to recalibrate delays for specific robots
  - `detectJunctionOrDeadEnd()` - used to update state when either a Junction or dead end is found
  - `identifyJunction()` - Once robot knows it's in a junction, it identifies the type of junction and adds any decisions to the path
  - `loop()` - main maze-solving loop
  - `isFinished()` - determines when exit is reached

### SolutionFollower
- **Purpose**: Executes the optimized path found by MazeSolver
- **Inherits from**: MazeSolver
- **Key Methods**:
  - `loop()` - follows pre-calculated optimal path
  - `identifyJunction()` - Overrides `MazeFollower` function. Once robot knows it's in a junction, it identifies the type of junction and acts following path
  - Accesses `Path` stored by MazeSolver

### Path
- **Purpose**: Stores and optimizes the sequence of decisions
- **Data Structure**: Array of `DECISION` enums (max 64 steps)
- **Key Methods**:
  - `addDecision(DECISION d)` - adds a path and calls `simplify`
  - `simplify()`- used to removes dead ends (backtracking sequences)

## Robot States

The robot operates in the following states (defined in `State.h`):

| State | Purpose |
|-------|---------|
| `FOLLOWING_LINE` | Navigating along a line segment |
| `IDENTIFYING_JUNCTION` | Analyzing intersection options |
| `TURNING_LEFT` | Executing left turn |
| `TURNING_RIGHT` | Executing right turn |
| `TURNING_BACK` | Executing 180° U-turn |
| `FINISHED` | Found the maze exit |
| `FAKE_END` | Used for Debugging purposes. Can be called to calibrate turn delays. |

## Operation Flow

### Initialization (Setup)
1. Display calibration prompt
2. Wait for button press to begin
3. Calibrate line sensors
4. Display sensor readings for verification
5. Wait for button press to start solving

### Maze Solving (Main Loop - Phase 1)
1. Robot follows line using IR sensors
2. Detects junctions and evaluates options
3. Makes decisions (LEFT, RIGHT, FORWARD, BACK)
4. Records each decision in Path
5. Continues until exit is found

### Path Optimization
As decisions are added to the Path:
- Dead ends are optimized following transformations:
...

### Solution Following (Main Loop - Phase 2)
Robot follows the optimized path

## Key Constants

### Timing (MazeSolver)
- `TURN_90_DEGREES_DELAY = 730ms` - Time to rotate 90 degrees
- `FORWARD_BEFORE_TURNING_DELAY = 250ms` - Distance before junction turns
....

### Storage (Path)
- `MAX_LEN = 64` - Maximum path length (memory constraint)

## Memory Optimization

The code uses unsigned integer types to minimize memory usage:
- `uint8_t` - For counters, indices, and small values (1 byte)
- `uint16_t` - For timing delays and longer sequences (2 bytes)

## LCD Display Output

A custom `DisplayManager` class inherits from the Pololu `Display` class to show readings and custom messages.

## Button Controls

Only the Button B in the Pololu is implemented, used to start Robot & change from MazeSolver to SolutionFollower. 

## TO DOs

Planned TO DOs for this project are:

1. **Improve interaction & display** - add a Menu & more clarity in display messages
2. **Speed optimization** - Adjust motor speeds and turn delays for maximum speeds
3. **Alternative pathfinding algorithms** - Explore other algorithms to solve mazes, including algorithms that can deal with maze cycles


## Troubleshooting

### Wrong Timing
If you observer robot is turniing too much, or turns infinitely - especially on a dead end - it means that the delay for turning is off. You can use the `FAKE_END` state to make the robot stop halfway through.

For example, to recalibrate a left turn:

1. Modify `turnLeft()` implementation to:

MazeSolver.cc
```cpp
void MazeSolver::turnLeft()
{
  // move forward to center robot on line.
  moveForwardFor(FORWARD_BEFORE_TURNING_DELAY);

  // turn left until
  turnLeftFor(TURN_90_DEGREES_DELAY);

  // use fake end here to debug
  state = ROBOT_STATE::FAKE_END;
}
```

2. Make the robot run on a circuit with a left turn and observe whether the robot turned too much (needs lowering delay) or not enough (needs raising delay)

3. Play with delay value `TURN_90_DEGREES_DELAY` to recalibrate

**Note:** The delay value `TURN_90_DEGREES_DELAY` is also used for a right turn and a uTurn (doubled). If this isn't working for you, you could separate those into different variables. 

---

**Last Updated**: January 14, 2026  
**Status**: Active development
