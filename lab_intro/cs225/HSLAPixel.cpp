/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
    HSLAPixel::HSLAPixel(){
        h = 0;
        s = 1;
        l = 1;
        a = 1;
    }

    HSLAPixel::HSLAPixel(double A, double B, double C){
        this-> h = A;
        this -> s =B;
        this-> l =C;
        a = 1;
    }

    HSLAPixel::HSLAPixel(double A, double B, double C,double D){
        this-> h = A;
        this-> s = B;
        this-> l = C;
        this-> a = D;
    }
}
