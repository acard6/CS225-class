/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying
 */
HSLAPixel* myFavoriteColor() {
    HSLAPixel p(250, 0.8, 0.5);
    return &p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG; //Allocated memory to the pointer
    std::cout << "Reached line " << __LINE__ << std::endl; //print statement for debugging
    original-> readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
    std::cout << "Reached line " << __LINE__ << std::endl; //print statement for debugging
    // Create out.png
    PNG* output = new PNG;
    setupOutput(width, height);

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor();

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    std::cout << "Reached line " << __LINE__ << std::endl; //print statement for debugging
    for (unsigned y = 1; 0 < y < height; y++) {
        for (unsigned x = 1; 0 < x < width; x++) {
            // Calculate the pixel difference
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            HSLAPixel& curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);
            std::cout << "y is " << y <<" and x is "<< x <<std::endl;
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel& currOutPixel = (output)->getPixel(x, y);
            std::cout << "Reached line " << __LINE__ << std::endl; //print statement for debugging
            if (diff > 20) {
                currOutPixel = *myPixel;
            }
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}
