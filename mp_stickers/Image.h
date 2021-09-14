/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include <iostream>
#include "cs225/PNG.h"

class Image: public cs225::PNG{
    //A Subclass of PNG with more member functions for modifying the image

    public:
        //Darken an Image by decreasing luminance of every pixel by 0.1
        //This function ensures that the luminance remains in the range [0,1]
        void darken();

        //Darkens an Image by decreasing luminance of every pixel by amount
        //This function ensures that the luminance remains in the range [0,1]
        void darken(double amount);

        //Desaturates an Image by decreasing saturation of every pixel by 0.1
        //This function ensures that the saturation remains in the range [0,1]
        void desaturate();

        //Desaturates an Image by decreasing saturation of every pixel by 0.1
        //This function ensures that the saturation remains in the range [0,1]
        void desaturate(double amount);

        //turns the image grayscale
        void grayscale();

        //Illinify the image
        void illinify();

        //lighten an image by increasing the luminance of every pixel by 0.1
        //This function ensures that the saturation remains in the range [0,1]
        void lighten();

        //lighten an image by increasing the luminance of every pixel by 0.1
        //This function ensures that the saturation remains in the range [0,1]
        void lighten(double amount);

        //rotates the color wheel by degrees
        //rotating in a positive direction increases the degree of the hue
        //The function ensures that the hue remains in the range [0,360]  
        void rotateColor(double degree);

        //saturate an image by increasing the saturation of every pixel by 0.1
        //This function ensures that the saturation remains in the range [0,1]
        void saturate();

        //saturate an image by increasing the saturation of every pixel by amount
        //This function ensures that the saturation remains in the range [0,1]
        void saturate(double amount);

        //scales the image by a given factor
        void scale(double factor);

        //scales the image to fit in (w x h)
        void scale(unsigned w, unsigned h);

};