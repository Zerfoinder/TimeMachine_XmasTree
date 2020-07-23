/**
 * ----------------------------------------------------------------
 * Copyright (C) 2020  Luis Acosta <zerfoinder@gmail.com>
 *
 * XmasTree library, This library for Arduino is used to emulate
 * Back to the Future's Time Machine XmasTree in a 1.3inch I2C OLED Display.
 *
 * www.github.com/Zerfoinder/TimeMachine_XmasTree (github as default source provider)
 *
 * This file is part of XmasTree library.
 *
 * XmasTree is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XmasTree is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------
 */

/**
 *  name:         XmasTree
 *  version:      0.1.1
 *  Author:       Luis Acosta <zerfoinder@gmail.com>
 *  Date:         2020-07-22
 *  Description:  XmasTree is an Arduino Library for emulate Back to the
 *  Future Delorean XmasTree in 1.3in I2C OLED Display.
 */

#ifndef TIMEMACHINE_XMAS_TREE_H
#define TIMEMACHINE_XMAS_TREE_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

namespace bttf::timemachine {

    /**
     * @brief      This class describes a Xmas Tree.
     *
     *             The XmasTree is drawn in a 128 x 64 pixels I2C OLED Display.
     *             Each light in XmasTree is represented by one 5x5 pixels
     *             square.
     *
     *             It consists of 10 columns. Each one with 20 squares.
     */
    class XmasTree {

        /************ CONSTANTS ***************/

        /**
         * Oled display object
         */
        U8G2_SH1106_128X64_NONAME_F_HW_I2C oled_display;

        /**
         * Flux Capacitor rutine levels to reach.
         *
         * Levels are from 0 to 8.
        */
        static const byte rutineLevels = 9;

        /**
         * Total columns draw in Xmas tree
         */
        static const byte xmasColumns = 10;

        /**
         * Max value in a column in Xmas tree
         */
        static const byte maxColumnValue = 20;

        /*
         * Each Xmas column takes its random value 
         * according to its current level.
         * These arrays have random Min and Max.
         */
        static const byte randomMin[];
        static const byte randomMax[];

        /**
         * array with different loop speed
         */
        static const unsigned long loopSpeed[];

        /**
         * X & Y coordinates to start drawing the Tree.
         */
        static const byte rootPointX = 4;
        static const byte rootPointY = 2;

      public:

        /**
         * @brief      Constructs a new instance.
         */
        XmasTree();

        /**
         * @brief      Initializes the object.
         * @warning    It should ALWAYS run in setup() section.
         */
        void init(void);

        /**
         * @brief      Turns on Xmas Tree.
         *             Once it is ON, Xmas Tree goes to level One.
         */
        void on(void);

        /**
         * @brief      Turns off Xmas Tree.
         */
        void off(void);

        /**
         * @brief      Set Xmas Tree level.
         *
         * @param[in]  level  Level to set. (0-8).
         */
        void setLevel(byte level);

        /**
         * @brief      Set Xmas Tree to next level.
         */
        void next(void);

        /**
         * @brief      Returns the current Xmas Tree level.
         *
         * @return     The current Xmas Tree level.
         */
        byte level(void);

        /**
         * @brief      Get the current state of Xmas Tree.
         *
         * @return     True: if it is ON, False if it is OFF
         */
        bool state(void);

        /**
         * @brief      function used to manage concurrent actions
         *
         * @warning    it should be ALWAYS added in the end of sketch loop() method.
         */
        void loop(void);

      protected:

      private:
        /************ METHODS ***************/

        /**
         * @brief      Updates XmasTree state.
         */
        void _update(void);

        /**
         * @brief      Resets XmasTree to initial state.
         */
        void _reset(void);

        /**
         * @brief      Gets the speed index.
         *
         * @return     The speed index.
         */
        byte _getSpeedIndex(void);

        /************ VARIABLES ***************/

        /**
         * Column values
         *
         * 10 Columns
         */
        int _columnValues[xmasColumns];

        /**
         * Xmas Tree level
         */
        byte _level;

        /**
         * Xmas Tree state
         */
        bool _state;

        /**
         * local variable used to save last loop millis()
         */
        unsigned long _lastLoopMillis;
    }; // end class XmasTree

} // end namespace bttf::timemachine

#endif // TIMEMACHINE_XMAS_TREE_H
