/**
 * @file StickerSheet.cpp
 */

#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include <vector>

using namespace std;
using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    max_ = max;
    basePicture_ = picture;
    vector<Image*> scene_(max_);
    vector<vector<int>> coord_ (max_,vector<int>(2));
    stickers = 0;
    
}

StickerSheet::~StickerSheet(){}


StickerSheet::StickerSheet(const StickerSheet &other)
{
    
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other)
{
    if (this == &other){
        return *this;
    }
   
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max)
{
    scene_.resize(max);    
    coord_.resize(max);
}

int StickerSheet::addSticker(Image&sticker,unsigned x, unsigned y)
{   
    stickers += 1;
    unsigned tmp = stickers;
    if( tmp < max_){
        for (int i=0; i<stickers; i++){
            if (scene_[i] == NULL){
                scene_[i] = &sticker;
                coord_[i][0] = x;
                coord_[i][1] = y;
                return (i);
            }
        }   
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
    if (index < max_){
        coord_[index][0] = x;
        coord_[index][1] = y;
        return true;
    } return false;
}

void StickerSheet::removeSticker(unsigned index)
{
    stickers -= 1;
    if (index < max_){
        scene_.erase(scene_.begin() + index- 1);
        coord_[index -1][0] = 0;
        coord_[index -1][1] = 0;
    }
}

Image* StickerSheet::getSticker(unsigned index)
{
    if (index < max_){
        return scene_[index];
    }return NULL;
}

Image StickerSheet::render() const
{
    unsigned baseWidth = basePicture_.width();
    unsigned baseHeight = basePicture_.height();


    for (unsigned i=0; i < scene_.size(); i++){
        if (scene_[i] != nullptr ){
            unsigned height = scene_[i]->height();
            unsigned width = scene_[i]->width();
            unsigned maxHeight = max(baseHeight, height + coord_[i][1]);
            unsigned maxWidth = max(baseWidth, width + coord_[i][0]);
            baseHeight = maxHeight;
            baseWidth = maxWidth;
        }
    }

    Image newBase = basePicture_;
    newBase.resize(baseWidth, baseHeight);

    for (unsigned i=0; i<scene_.size(); i++){
        if (scene_[i] != nullptr){
            for (unsigned x = coord_[i][0]; x < (coord_[i][0]+scene_[i]->width()); x++){
                for (unsigned y = coord_[i][1]; y < (coord_[i][1]+scene_[i]->height()); y++){
                    if (scene_[i]->getPixel((x-coord_[i][0]), (y-coord_[i][1])).a != 0){
                        newBase.getPixel(x,y) = scene_[i]->getPixel((x-coord_[i][0]), (y-coord_[i][1]));
                    } 
                }
            }
        }
    }
    return newBase;
}