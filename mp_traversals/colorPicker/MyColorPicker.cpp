#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(115, 0.67, 0.4);
  if ((y / 100) * 100 > 3){
    pixel.h = pixel.h;
    pixel.s = pixel.s;
    pixel.l = pixel.l; 
  }
  if ((x / 100) * 100 < 1 ){
    pixel.h = 183;
    pixel.s = 0.5;
    pixel.l = 0.89;
  }
  else if ((x /100) * 100 > 5){
    pixel.h = 25;
    pixel.s = 0.95;
    pixel.l = 0.73;
  }

  return pixel;
}
