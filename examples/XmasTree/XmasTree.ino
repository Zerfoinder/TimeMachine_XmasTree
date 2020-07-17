/*
 * Xmas Tree sample code
 */

//-----------------------------------------
// Add include to XmasTree
#include <XmasTree.h>

//-----------------------------------------
// Add using namespace
using namespace bttf::timemachine;

//-----------------------------------------
// XmasTree declaration
// create an object called: tree. (No parameters are required)
XmasTree tree;

/**
 * Variable created for the purposes of this example
 * it is used to execute some task in 5 seconds loop.
 */
unsigned long _previousExecutionMillis = 0;

// the setup function runs once when you press reset or power the board
void setup() {

    Serial.begin(9600);
    /**
     * Call init() method 
     */
    tree.init();       // REQUIRED

}

// the loop function runs over and over again forever
void loop() {

    // Check Xmas state
    // If it is OFF (state == false) then turn it on.
    if (!tree.state()) {
        Serial.println("Encendiendo tree");
        Serial.println("");
        tree.on();  // XmasTree ON
    }

    // Enter every 5 seconds
    if (millis() >= _previousExecutionMillis + 5000) {
        Serial.print("Entra en nivel: ");
        Serial.println(tree.level());
        Serial.println("");

        // if tree level is 8, then turn it off
        if (tree.level() == 8) {
            Serial.println("Apagando tree");
            Serial.println("");
            tree.off();    // Tree is turned OFF
        }

        // set Xmas Tree to next level
        tree.next();
        Serial.print("saliendo en nivel: ");
        Serial.println(tree.level());
        Serial.println("");

        _previousExecutionMillis += 5000;
    }

    // Call tree.loop() ALWAYS in the end of sketch loop().
    tree.loop();
}
