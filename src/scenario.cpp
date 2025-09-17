//
// Created by nikolaj on 9/16/25.
//

#include "scenario.h"

scenario::scenario(SDL_Renderer* renderer) : background("assets/greenland.png",renderer), hexSelectionOutline("assets/hexoutline.png",renderer) {
    ///Width of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    hexGridWidth=5;
    ///height of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    hexGridHeight=5;

    //Hardcoded hex map of a sort-of, facing worlds scenario
    hexTiles = {
        hexTile(hexTile::FRIEND),hexTile(hexTile::SEA),hexTile(hexTile::SEA),hexTile(hexTile::SEA),hexTile(hexTile::FOE),
        hexTile(hexTile::FRIEND),hexTile(hexTile::SEA),hexTile(hexTile::SEA),hexTile(hexTile::SEA),hexTile(hexTile::FOE),
        hexTile(hexTile::FRIEND),hexTile(hexTile::SEA),hexTile(hexTile::SEA),hexTile(hexTile::SEA),hexTile(hexTile::FOE),
        hexTile(hexTile::FRIEND),hexTile(hexTile::NEUTRAL),hexTile(hexTile::NEUTRAL),hexTile(hexTile::FOE),hexTile(hexTile::FOE),
        hexTile(hexTile::NEUTRAL),hexTile(hexTile::NEUTRAL),hexTile(hexTile::NEUTRAL),hexTile(hexTile::NEUTRAL),hexTile(hexTile::FOE),
    };




    ///Width of the hexagonal grid this game is being played on, in hexagons
    hexWidthPx=hexSelectionOutline.getWidth();
    ///Height of the hexagonal grid this game is being played on, in hexagons
    hexHeightPx=hexSelectionOutline.getHeight();

    //Divisions are evil and should be kept out of the loop
    hexHalfWidthPx=hexSelectionOutline.getWidth()/2;
    hex34HeightPx=(hexSelectionOutline.getHeight()*3)/4;

}

scenario::~scenario() {

    //loaded assets, which are not pointers, automatically unload at the end
}


void scenario::render(SDL_Renderer* renderer) {

    //background.render(0,0,renderer,nullptr,1);

    //For debugging, draw hexagonal grid on top of everything

    //Yes divisions are slow, but a few each frame beats saving dozens of constant variables making the code uggly
    for (int hexX = 0; hexX < hexGridWidth; hexX++) {
        for (int hexY = 0; hexY < hexGridHeight; hexY++) {

            const hexTile& tile = hexTiles[hexX+hexY*hexGridWidth];
            int hexTopLeftX = hexX * hexWidthPx+(hexY%2) * hexHalfWidthPx;
            int hexTopLeftY = hexY * hex34HeightPx;


            switch (tile.getStatus()) {
                case hexTile::FRIEND:
            hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,0,255,0,renderer);
                    break;
                case hexTile::FOE:
            hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,255,0,0,renderer);
                    break;
                case hexTile::NEUTRAL:
            hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,125,125,125,renderer);
                    break;
                case hexTile::SEA:
            hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,0,125,255,renderer);
                    break;
            }
        }
    }

}

void scenario::update() {

}
