#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG* original = new cs225::PNG; //Allocated memory to the pointer

  original-> readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();

  cs225::PNG* output = new cs225::PNG(width, height);

  for (unsigned x = 0; (x < width); x++) {
      for (unsigned y = 0; (y < height); y++) {
        cs225::HSLAPixel& curr = original->getPixel(x, y);
        cs225::HSLAPixel& currOutPixel = (*output).getPixel((width - 1 - x), (height - 1 - y));
        currOutPixel = curr;
    }
  }
  output->writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3

  return png;
}
