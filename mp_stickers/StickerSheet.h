/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
using namespace std;
#include <vector>

class StickerSheet{
    private:
        unsigned max_;
        Image basePicture_;
        vector<Image*> scene_;
        vector<vector<int>> coord_;
        int stickers;
        
    public:
        StickerSheet(const Image &picture, unsigned max);
            /**
         * Initialize this StickerSheet with a deep copy of
         * the base  picture and the ability to hold a max number
         * of sticker(images) with indices 0 through max - 1. 
         */
    
        ~StickerSheet();
        /**
         * Frees up all the space that was dynamically allocated
         * by this StickerSheer.
         */

        StickerSheet(const StickerSheet &other);
        /**
         * The copy constructor makes this StickerSheet independent  
         * copy of the source.
         */
    
        const StickerSheet& operator=(const StickerSheet &other);
        /**
         * The assignemert operator for the StickerSheet class.
         */
    
        void changeMaxStickers(unsigned max);
        /**
         * Modifies the max number of stickers that can be stored on
         * this Stickersheet without changing existing stickers' indices.
         * If the new maximum number of stickers is smaller than the 
         * current number of stickers, the stickers with indices above
         * max - 1 will be lost.
         */
    
        int addSticker(Image&sticker,unsigned x, unsigned y);
        /**
         * Adds a sticker to the StickerSheet, so that the top-left of
         * the sticker's Image is at (x, y) on StickerSheet. The sticker
         * must be added to the lowest possible layer available
         */
    
        bool translate(unsigned index, unsigned x, unsigned y);
        /**
         * Changed the x and y coordinate of the image in the specified
         * layer. If the layer is invalid or does not contain a sticker,
         * this function must return false. Otherwise, this function
         * returns true.
         */
    
        void removeSticker(unsigned index);
        /**
         * Removes the sticker at the given zero-based layer index.
         * Make sure that the other stickers don't change order.
         */
    
        Image* getSticker(unsigned index);
        /**
         * Returns a pointer to the sticker at the specified index,
         * not a copy of it. That way the user can modify the image.
         * If indexis invalid, return NULL.
         */
    
        Image render() const;
        /**
         * Renders the whole StickerSheet on one Image and returns that
         * Image. The base picture is drawn first and then each sticker
         * is drawn in order If a pixel's alpha channel in a sticker is
         * zero(0), no pixel is drawn for that sticker at that pixel. If
         * the alpha channel is non-zero, a pixel is drawn. The returned
         * Image always include the full contents of the picture and all
         * stickers. This means that the size of the result image may be
         * larger than thebase sticker if  some stickers go beyond the 
         * edge of the picture
         */
};