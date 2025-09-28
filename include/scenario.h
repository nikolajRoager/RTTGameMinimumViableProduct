//
// Created by nikolaj on 9/16/25.
//

#ifndef PREMVPMAPGAME_SCENARIO_H
#define PREMVPMAPGAME_SCENARIO_H
#include <map>
#include <vector>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "gui.h"
#include "hexGrid.h"
#include "hexTile.h"
#include "phase.h"
#include "texwrap.h"
#include "unit.h"
#include "unitType.h"

class scenario {
private:
    texwrap background;
    texwrap hexSelectionOutline;

    std::vector<unitType> unitLibrary;

    ///Units of the player side
    std::vector<unit> unitsFriend;

    int scenarioWidthPx;
    int scenarioHeightPx;

    ///What tile is the mouse currently over
    int mouseOverTile;
    ///What tile, if any is currently selected (-1 if none)
    int selectedTile=-1;
    ///What friendly unit is currently selected (-1 if none)
    int selectedUnit=-1;

    hexGrid grid;


    ///What phase of the game are we going through
    phase currentPhase=MOVEMENT_PLANNING_FRIEND;


    ///The queued up movements for the good guys, indexed by unit id,
    std::map<int,std::vector<int> > friendMovementPlans;

    double scale;

    std::string movementPlanningDescription;
    std::string movementExecutionDescription;

    gui myGui;

public:
    explicit scenario(SDL_Renderer* renderer, TTF_Font* _font);
    ~scenario();

    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight, uint32_t millis) const;
    void update(SDL_Renderer* renderer, int screenWidth, int screenHeight, int mouseX, int mouseY, bool isLeftMouseClick, bool isRightMouseClick, bool executeClick, uint32_t millis, uint32_t dmillis);
};

#endif //PREMVPMAPGAME_SCENARIO_H