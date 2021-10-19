#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  travel_ = NULL;
  end = false;

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  unsigned x = current.x;
  unsigned y = current.y;
  
  Point north(x,y-1);
  Point south(x,y+1);
  Point east(x+1,y);
  Point weast(x-1,y);

  if (isValid(east)){
    travel_->add(east);
  }if (isValid(south)){
    travel_->add(south);
  }if (isValid(weast)){
    travel_->add(weast);
  }if (isValid(north)){
    travel_->add(north);
  }

  if (!travel_->empty()){
    Point next = travel_->peek();
    while (valid[next.x + next.y *png_.width()]){
      if (travel_->empty()){
        end = true;
        return *this;
      }
      next = travel_->pop();
    }
    current = next;
    valid[current.x + current.y * png_.width()] = true;
    return *this;
  }else{
    end = true;
    return *this;
  }
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (end != other.end);
}

ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal* travel) {
  png_ = png;
  current = start;
  start_ = current;
  tallerants = tolerance;
  travel_ = travel;
  end = false;

  for (unsigned i=0; i<png_.width() * png_.height();i++){
    valid.push_back(false);
  }
  if (isValid(current)){
    valid[current.x + current.y * png_.width()] = true;
  }
}

bool ImageTraversal::Iterator::visit(Point p){
  if (p.x < png_.width() && p.y < png_.height()){
    return valid[p.x + p.y*png_.width()];
  }
  return true;
}

void ImageTraversal::Iterator::markVisit(Point p){
  if (p.x < png_.width() && p.y < png_.height()){
    valid[p.x + p.y*png_.width()] = true;
  }
}

bool ImageTraversal::Iterator::isValid(Point p){
  if (p.x >= png_.width() || p.y >= png_.height()){
    return false;
  }
  if (visit(p)){return false;}

  HSLAPixel start = png_.getPixel(start_.x, start_.y);
  HSLAPixel curr = png_.getPixel(p.x, p.y);
  return (calculateDelta(start, curr) <= tallerants);
}