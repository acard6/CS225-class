
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */

  //PNG png;       png.readFromFile("me.png");
  PNG png;       png.readFromFile("lettucePray.png");
  //PNG png;       png.readFromFile("veggieTales.png");

  MyColorPicker myColor{};
  HSLAPixel colour(50, 1, 0.5);
  SolidColorPicker solid(colour);
  RainbowColorPicker rainbow(0.5);
  FloodFilledImage image(png);

  DFS leftEye(png, Point(400,300), 0.2);
  image.addFloodFill(leftEye, myColor);

  BFS rightEye(png, Point(121,89), 0.7);
  image.addFloodFill(rightEye, solid);

  BFS bottle(png, Point(169,420), 3.0);
  image.addFloodFill(bottle, rainbow);

  Animation animation = image.animate(1000);

  PNG lastFrame = animation.getFrame(animation.frameCount() -1);
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
