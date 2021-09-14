/**
 * @file Image.cpp
 * 
 * @author Alan Cardiel
 */

#include <iostream>
#include <cmath>
using std::endl;

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void Image::darken(){
    for (unsigned x=0; x<this->width(); x++){
        for (unsigned y=0; y<this->height(); y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.l < 0.1){
                pixel.l = 0;
            }
            else{
                pixel.l -= 0.1;
            }
        }
    }
}

void Image::darken(double amount){
    for (unsigned x=0; x<width(); x++){
        for (unsigned y=0; y<height(); y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.l < amount){
                pixel.l = 0;
            }
            else{
                pixel.l -= amount;
            }
        }
    }   
}

void Image::desaturate(){
    for (unsigned x=0; x<width(); x++){
        for (unsigned y=0; y<height(); y++){
            HSLAPixel & pixel = getPixel(x,y);
            if (pixel.s < 0.1){
                pixel.s = 0;
            }
            else{
                pixel.s -= 0.1;
            }
        }
    }
}

void Image::desaturate(double amount){
    for (unsigned x=0; x<width(); x++){
        for (unsigned y=0; y<height(); y++){
            HSLAPixel & pixel = getPixel(x,y);
            if (pixel.s < amount){
                pixel.s = 0;
            }
            else{
                pixel.s -= amount;
            }
        }
    }
}

void Image::grayscale(){
    for (unsigned x=0; x<width(); x++){
        for (unsigned y=0; y<height(); y++){
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = 0;
        }
    }    
}

void Image::illinify(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.h > 216) {
                double a = (pixel.h) - 216;
                double b = 371 - pixel.h;
                if (abs(a) > abs(b))
                    pixel.h = 11;
                else
                    pixel.h = 216;
            }
            if (pixel.h < 216) {
                double a = 216 - pixel.h;
                double b = pixel.h - 11;
                if (abs(a) > abs(b))
                    pixel.h = 11;
                else
                    pixel.h = 216;
      }
    }
  }
}

void Image::lighten(){
    for (unsigned x=0; x<width(); x++){
        for (unsigned y=0; y<height(); y++){
            HSLAPixel & pixel = getPixel(x,y);
            if (pixel.l > 0.9){
                pixel.l = 1;
            }
            else{
                pixel.l += 0.1;
            }
        }
    }
}

void Image::lighten(double amount){
    for (unsigned x=0; x<width(); x++){
        for (unsigned y=0; y<height(); y++){
            HSLAPixel & pixel = getPixel(x,y);
            if (pixel.l > (1 - amount)){
                pixel.l = 1;
            }
            else{
                pixel.l += 0.1;
            }
        }
    }
}

void Image::saturate(){
    for (unsigned x=0; x<width(); x++){
        for (unsigned y=0; y<height(); y++){
            HSLAPixel & pixel = getPixel(x,y);
            if (pixel.s > 0.9){
                pixel.s = 1;
            }
            else{
                pixel.s += 0.1;
            }
        }
    }
}

void Image::saturate(double amount){
    for (unsigned x=0; x<width(); x++){
        for (unsigned y=0; y<height(); y++){
            HSLAPixel & pixel = getPixel(x,y);
            if (pixel.s > (1 - amount)){
                pixel.s = 1;
            }
            else{
                pixel.s += amount;
            }
        }
    }
}

void Image::rotateColor(double amount){
    for (unsigned int x=0; x<width(); x++){
        for (unsigned int y=0; y<height(); y++){
            HSLAPixel & pixel = getPixel(x,y);
            pixel.h = ((360 + pixel.h - amount) % 360);
        }
    }
}

void Image::scale(double factor){
    Image * ImageCopy = this;
    unsigned newWidth = factor * width;
    unsigned newHeight = factor * height;
    resize(newWidth, newHeight);
}

void Imgae::scale(unsigned w, unsigned h){
    unsigned widthRatio =  w / width();
    unsigned heightRatio = h / height();
}