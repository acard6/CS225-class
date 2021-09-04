/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel{
        public:
            double h; // the hue value of the pixel from [0,360]
            double s; // the saturation of the pixel from [0,1]
            double l; // the luminance of the pixel from [0,1]
            double a; // the alpha channel or transparancy of the pixel from [0,1]
    }
}
