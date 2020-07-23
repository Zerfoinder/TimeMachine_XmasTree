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

#include <Arduino.h>
#include "XmasTree.h"

namespace bttf::timemachine {

    //U8G2_SH1106_128X64_NONAME_F_HW_I2C oled_display(U8G2_R0, U8X8_PIN_NONE);

    /*
     * Each Xmas column takes its random value
     *  according to its current level +-----------------------------------+
     *                                 |           L  E  V  E  L  S        |
     * These arrays have               +---+---+---+---+---+---+---+---+---+
     * random Min and Max.             | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
     *                                 +---+---+---+---+---+---+---+---+---+ */
    const byte XmasTree::randomMin[] = { 0,  0,  1,  2,  4,  5,  7, 11, 14 };
    const byte XmasTree::randomMax[] = { 0,  3,  5,  7, 10, 13, 15, 19, 22 };

    const unsigned long XmasTree::loopSpeed[] = {250, 300, 350};

    XmasTree::XmasTree()
        : oled_display { U8G2_SH1106_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE) } {
        srand(micros());
        _reset();
    }

    void XmasTree::init(void) {
        oled_display.begin();
        oled_display.setDrawColor(2);
    }

    void XmasTree::on(void) {
        _lastLoopMillis = millis();
        _state = true;
        _level = 1;
    }

    void XmasTree::off(void) {
        _reset();
    }

    void XmasTree::setLevel(byte level) {
        if (_state) {
            _level = level;
        }
    }

    void XmasTree::next(void) {
        if (_state) {
            _level++;

            if (_level == rutineLevels) {
                _level = rutineLevels - 1;
            }
        }
    }

    byte XmasTree::level(void) {
        return _level;
    }

    bool XmasTree::state(void) {
        return _state;
    }

    void XmasTree::loop(void) {

        unsigned long speedIndex = _getSpeedIndex();

        if (millis() >= _lastLoopMillis + XmasTree::loopSpeed[speedIndex]) {
            _lastLoopMillis += XmasTree::loopSpeed[speedIndex];

            _update();
        }
    }

    void XmasTree::_update(void) {
        int x = rootPointX;
        int y = rootPointY;

        oled_display.clearBuffer();
        oled_display.drawFrame(0, 0, 128, 64);

        for (int col = 0; col < xmasColumns; col++) {

            if (_columnValues[col] < maxColumnValue) {
                _columnValues[col] = (rand() % (XmasTree::randomMax[_level] - XmasTree::randomMin[_level] + 1 )) + XmasTree::randomMin[_level];
            }

            if (_columnValues[col] > maxColumnValue)
                _columnValues[col] = maxColumnValue;

            x = rootPointX;
            for (int i = 0; i < _columnValues[col]; i++) {
                oled_display.drawBox(x, y, 5, 5);
                x += 6;
            }
            y += 6;
        }

        oled_display.sendBuffer();
    }

    void XmasTree::_reset(void) {
        _state = false;
        _level = 0;

        for (int i = 0; i < xmasColumns; i++) {
            _columnValues[i] = 0;
        }
    }

    byte XmasTree::_getSpeedIndex(void) {
        if (_level < 4 )  //level 0-3: 0
            return 0;

        if (_level < 7 )  //level 3-4: 1
            return 1;
        else
            return 2;     //level 7-8: 2
    }
} // end namespace bttf::timemachine
