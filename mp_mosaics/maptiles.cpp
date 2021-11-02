/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getColumns(), theSource.getRows());
    map<Point<3>, int> tilesMap;
    vector<Point<3>> color;

    for (size_t i=0; i<theTiles.size(); i++){
        LUVAPixel pixel = theTiles[i].getAverageColor();
        Point<3> points = convertToXYZ(pixel);
        color.push_back(points);
        tilesMap.insert(pair<Point<3>, size_t>(points,i));
    }

    KDTree<3> treeColor(color);
    for (int i=0; i< canvas->getRows(); i++){
        for (int j=0; j<canvas->getColumns(); j++){
            Point<3> regionalPoint = convertToXYZ(theSource.getRegionColor(i,j));
            Point<3> nearestPoint = treeColor.findNearestNeighbor(regionalPoint);
            size_t index = tilesMap[nearestPoint];
            canvas->setTile(i, j, &theTiles[index]);
        }        
    }
    return canvas;
}

