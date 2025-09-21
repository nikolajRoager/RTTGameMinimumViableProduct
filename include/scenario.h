//
// Created by nikolaj on 9/16/25.
//

#ifndef PREMVPMAPGAME_SCENARIO_H
#define PREMVPMAPGAME_SCENARIO_H
#include <map>
#include <vector>
#include <SDL2/SDL_render.h>

#include "hexGrid.h"
#include "hexTile.h"
#include "texwrap.h"
#include "unit.h"
#include "unitType.h"

class scenario {
private:
    texwrap background;
    texwrap hexSelectionOutline;

    std::vector<unitType> unitLibrary;

    ///Units of the player side (side=true)
    std::vector<unit> unitsA;
    ///Units of the other side (side=false)
    std::vector<unit> unitsB;

    int scenarioWidthPx;
    int scenarioHeightPx;

    ///What tile is the mouse currently over
    int mouseOverTile;
    ///What tile, if any is currently selected (-1 if none)
    int selectedTile=-1;

    hexGrid grid;

public:
    explicit scenario(SDL_Renderer* renderer);
    ~scenario();

    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight) const;
    void update(int screenWidth, int screenHeight, int mouseX, int mouseY, bool isRightMouseClick);
};

#endif //PREMVPMAPGAME_SCENARIO_H