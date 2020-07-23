# Time Machine - Xmas Tree
![GitHub release (latest by date)](https://img.shields.io/github/v/release/Zerfoinder/TimeMachine_XmasTree)
![GitHub All Releases](https://img.shields.io/github/downloads/Zerfoinder/TimeMachine_XmasTree/total)
![GitHub](https://img.shields.io/github/license/Zerfoinder/TimeMachine_XmasTree)
![Github Arduino Library CI](https://github.com/Zerfoinder/TimeMachine_XmasTree/workflows/Github%20Arduino%20Library%20CI/badge.svg)

XmasTree is an Arduino library used to emulate Back to the Future's Time Machine **XmasTree** in a 1.3inch I2C OLED monochrome display.

This library is used to emulate the lightings of the Back to the Future Delorean Time Machine XmasTree, to place it on a scale model car.

If you like **XmasTree**, give it a star, or fork it and contribute!

[![donate](https://img.shields.io/badge/donate-PayPal-blue.svg)](https://paypal.me/zerfoinder)

## Installation

1. Navigate to the Releases page.
1. Download the latest release.
1. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library

## How it works

XmasTree uses a a 1.3inch I2C OLED monochrome display.has 13 LED lights.
XmasTree displays a 10 x 20 5-pixel square matrix. Each matrix column displays random values, depending on the level it is at. 
There are eigth "speed levels". Each level has different random values ranges for each xmas column. Levels goes from level 1 to level 8.
When the xmas is off, it is on level 0.
When the xmas is turned on,  it is set to level 1.

**Note**: It is the responsibility of the user to generate the code that changes levels at desired time.


## Usage

```C++

#include <XmasTree.h> // Add include to XmasTree.h

using namespace bttf::timemachine; // Add using namespace

// XmasTree declaration
XmasTree tree; // create an object called: tree. (No parameters are required)

/**
 * Variable created for the purposes of this example
 * it is used to execute some task in 5 seconds loop.
 */
unsigned long _previousExecutionMillis = 0;

void setup() {

    tree.init();  // [REQUIRED] ALWAYS call init() method on setup()

}

void loop() {

    // Check Xmas state
    // If it is OFF (state == false) then turn it on.
    if (!tree.state()) {
        tree.on();  // XmasTree ON
    }

    // Enter every 5 seconds
    if (millis() >= _previousExecutionMillis + 5000) {
        _previousExecutionMillis += 5000;

        // if tree level is 8, then turn it off
        if (tree.level() == 8) {
            tree.off();    // Tree is turned OFF
        }

        // set Xmas Tree to next level
        tree.next();
    }

    // Call tree.loop() ALWAYS in the end of sketch loop().
    tree.loop();
}
```

## Components and functions
### XmasTree Class
#### Example
```C++
XmasTree tree; // create an object called: tree. (No parameters are required).
```

#### Public methods
| Method | Description |
| ---------- | ----------- |
| `XmasTree tree();` | Constructor. |
| `.init();` | Initialize XmasTree, it should run always in setup() section. |
| `.on();`   | Turns on XmasTree (It is set to Level 1). |
| `.off();`  | Turns off XmasTree. |
| `.setLevel(byte level);`    | Set XmasTree level (1-8). |
| `.next();`    | Set XmasTree to next level. |
| `.level();`    | Returns the current XmasTree level (1-8). |
| `.state();`    | Returns the current `bool` state of XmasTree. returns False when it is turned OFF and returns True when it is turned On. |
| `.loop();`    | function used to manage concurrent actions. It should be ALWAYS added in the end of sketch loop() method. |

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

[![donate](https://img.shields.io/badge/donate-PayPal-blue.svg)](https://paypal.me/zerfoinder)

## License
This library is licensed under [GPLv3](https://www.gnu.org/licenses/quick-guide-gplv3.html).
