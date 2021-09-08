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
            double h,s,l,a;
            HSLAPixel();
            HSLAPixel(double A, double B, double C);
            HSLAPixel(double A, double B, double C, double D);

    };
}
