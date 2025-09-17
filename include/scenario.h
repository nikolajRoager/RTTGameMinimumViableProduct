//
// Created by nikolaj on 9/16/25.
//

#ifndef PREMVPMAPGAME_SCENARIO_H
#define PREMVPMAPGAME_SCENARIO_H
#include <vector>
#include <SDL2/SDL_render.h>

#include "hexTile.h"
#include "texwrap.h"

class scenario {
private:
    texwrap background;
    texwrap hexSelectionOutline;

    ///Width of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    int hexWidthPx;
    ///height of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    int hexHeightPx;

    ///half the width of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    int hexHalfWidthPx;
    ///three quarters of the height of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    int hex34HeightPx;

    ///Width of the hexagonal grid this game is being played on, in hexagons
    int hexGridWidth;
    ///Height of the hexagonal grid this game is being played on, in hexagons
    int hexGridHeight;

    std::vector<hexTile> hexTiles;

public:
    explicit scenario(SDL_Renderer* renderer);
    ~scenario();

    void render(SDL_Renderer* renderer);
    void update();
};

#endif //PREMVPMAPGAME_SCENARIO_H