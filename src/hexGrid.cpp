//
// Created by nikolaj on 9/21/25.
//

#include "hexGrid.h"

#include <fstream>
#include <stdexcept>

hexGrid::hexGrid(const std::string &path, SDL_Renderer* renderer):hexSelectionOutline("assets/hexoutline.png",renderer) {

    //TODO, load from a file at path
    ///Width of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    hexGridWidth=38;
    ///height of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    hexGridHeight=24;

    //Set up hexagon drawing data
    ///Width of the hexagonal grid this game is being played on, in hexagons
    hexWidthPx=hexSelectionOutline.getWidth();
    ///Height of the hexagonal grid this game is being played on, in hexagons
    hexHeightPx=hexSelectionOutline.getHeight();

    //Divisions are evil and should be kept out of the loop
    hexHalfWidthPx=hexSelectionOutline.getWidth()/2;
    hex34HeightPx=(hexSelectionOutline.getHeight()*3)/4;

    scenarioWidthPx=hexWidthPx*hexGridWidth+hexHalfWidthPx;
    scenarioHeightPx=hex34HeightPx*hexGridHeight+hexHeightPx/4;


    //Load hexagons
    //todo, replace with better scenario loading
    std::ifstream TEMP_INPUT("assets/TEMP.txt");

    if (!TEMP_INPUT.is_open())
        throw std::runtime_error("unable to open file assets/TEMPT.txt");

    for (int hexY = 0; hexY < hexGridHeight; hexY++) {
        for (int hexX = 0; hexX < hexGridWidth; hexX++) {
            int friendOrFoe;
            TEMP_INPUT>>friendOrFoe;
            double hexTopLeftX = hexX * hexWidthPx+((hexY+1)%2) * hexHalfWidthPx+hexHalfWidthPx;
            double hexTopLeftY = hexY * hex34HeightPx+hexHeightPx/2.0;
            hexTiles.emplace_back(static_cast<hexTile::hexStatus>(friendOrFoe),hexTopLeftX,hexTopLeftY);
        }
    }

    TEMP_INPUT.close();
}

void hexGrid::drawTile(SDL_Renderer *renderer, const int hexId, const double scale, tileDisplayMode displayMode, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    if (hexId >= hexTiles.size() || hexId < 0)
        return;
    const hexTile &tile=hexTiles[hexId];
    double hexTopLeftX =tile.getHexCenterX()-hexHalfWidthPx;
    double hexTopLeftY =tile.getHexCenterY()-hexHeightPx/2.0;

    hexTopLeftX *= scale;
    hexTopLeftY *= scale;

    if (displayMode==STATUS)
        switch (tile.getStatus()) {
            case hexTile::FRIEND:
                hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,0,255,0,renderer,nullptr,scale);
                break;
            case hexTile::FOE:
                hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,255,0,0,renderer,nullptr,scale);
                break;
            case hexTile::NEUTRAL:
                hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,125,125,125,renderer,nullptr,scale);
                break;
            case hexTile::SEA:
                hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,0,125,255,renderer,nullptr,scale);
                break;
        }
    else if (displayMode==COLOR) {
        hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,r,g,b,renderer,nullptr,scale);
    }
}

int hexGrid::getHexFromLocation(double x, double y, double scale) const {

    int foundTile=-1;
    double dist=-1;

    //Get the hext nearest to the mouse coordinates and select it
    for (int hexX = 0; hexX < hexGridWidth; hexX++) {
        for (int hexY = 0; hexY < hexGridHeight; hexY++) {

            const hexTile& tile = hexTiles[hexX+hexY*hexGridWidth];
            double hexCenterX =tile.getHexCenterX();// hexX * hexWidthPx+(hexY%2) * hexHalfWidthPx;
            double hexCenterY =tile.getHexCenterY();// hexY * hex34HeightPx;

            hexCenterX *= scale;
            hexCenterY *= scale;

            double thisDist = pow(hexCenterX-x,2)+pow(hexCenterY-y,2);
            if (thisDist < dist || dist<0) {
                dist=thisDist;
                foundTile=hexX+hexY*hexGridWidth;
            }
        }
    }
    return foundTile;
}

std::set<int> hexGrid::getNeighbours(int hexId,int steps) const {
    std::set<int> visited;
    //Get the x and y hex coordinates
    int hexX = hexId % hexGridWidth;
    //Intentionally using Integer division
    int hexY = hexId / hexGridWidth;

    int depth;
    //The queue of the current layer we are searching for neighbours of
    std::set<int> oldQueue;

    //The queue of the next layer, which we will search shortly
    std::set<int> newQueue;

    oldQueue.insert(hexId);


    //swap buffers and reset old queue
    visited.insert(hexId);
    return visited;
    }

