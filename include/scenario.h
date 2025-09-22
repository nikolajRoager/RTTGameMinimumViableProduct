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

    ///Units of the player side
    std::vector<unit> unitsFriend;
    ///Units of the other side
    std::vector<unit> unitsFoes;

    int scenarioWidthPx;
    int scenarioHeightPx;

    ///What tile is the mouse currently over
    int mouseOverTile;
    ///What tile, if any is currently selected (-1 if none)
    int selectedTile=-1;
    ///What friendly unit is currently selected (-1 if none)
    int selectedUnit=-1;

    hexGrid grid;

    enum phase {
        MOVEMENT_PLANNING,
        MOVEMENT_EXECUTION,
    };

    ///What phase of the game are we going through
    phase currentPhase=MOVEMENT_PLANNING;


    ///A plan to move a particular unit somewhere else
    struct movementPlan {
        ///What unit will do the movement
        int unitId;
        ///What tiles will we move through
        std::vector<int> tiles;
        ///Where will we end up
        int destinationTile;
    };

    ///The queued up movements for the good guys
    std::vector<movementPlan> FriendMovementPlans;
    ///Queued up movements for the bad guys
    std::vector<movementPlan> FoeMovementPlans;

public:
    explicit scenario(SDL_Renderer* renderer);
    ~scenario();

    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight) const;
    void update(int screenWidth, int screenHeight, int mouseX, int mouseY, bool isLeftMouseClick, bool isRightMouseClick);
};

#endif //PREMVPMAPGAME_SCENARIO_H