#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image alma, illini, lettuce, itstimeToDDDDDueal, output;
  alma.readFromFile("alma.png");
  illini.readFromFile("i.png");
  lettuce.readFromFile("lettucePray.png");
  itstimeToDDDDDueal.readFromFile("veggieTales.png");

  StickerSheet mySticker(alma, 3);
  mySticker.addSticker(illini, 400, 150);
  mySticker.addSticker(lettuce, 30, 20);
  mySticker.addSticker(itstimeToDDDDDueal, 700, 500);

  output.writeToFile("myImage.png");
  return 0;
}
