//
// Created by nikolaj on 9/16/25.
//

#include "scenario.h"

#include <fstream>
#include <iostream>
#include <ranges>

scenario::scenario(SDL_Renderer* renderer) : background("assets/background.png",renderer), hexSelectionOutline("assets/hexoutline.png",renderer), grid("assets/",renderer) {


    //Will instantly be overwritten
    mouseOverTile=0;

    //TODO: load from disk
    unitLibrary.clear();
    unitLibrary.emplace_back(true,fs::path("assets")/"units"/"SAMTruckDK",renderer);

    //TODO: load from disk, and allow spawning
    unitsFriend.clear();
    unitsFriend.emplace_back(unitLibrary[0],true,20,8);

    unitsFriend.emplace_back(unitLibrary[0],true,18,12);

    scenarioWidthPx=grid.getScenarioWidth();
    scenarioHeightPx=grid.getScenarioHeight();

    currentPhase=MOVEMENT_PLANNING_FRIEND;
}

scenario::~scenario() {

    //loaded assets, which are not pointers, automatically unload at the end
}


void scenario::render(SDL_Renderer* renderer, int screenWidth, int screenHeight, uint32_t millis) const {

    double scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx),static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx));

    background.render(0,0,renderer,scale);

    if (currentPhase==MOVEMENT_PLANNING_FRIEND) {
        //Show the tile the mouse is over
        grid.drawTile(renderer,mouseOverTile,scale);


        //Display how far we can move
        if (selectedUnit!=-1 && selectedTile!=-1) {
            const std::set<int> tilesNearSelection=grid.getNeighbours(selectedTile,4,unitsFriend,unitsFoe);
            grid.drawTiles(renderer,tilesNearSelection,scale,hexGrid::COLOR);

            const std::vector<int> line = grid.findPath(selectedTile,mouseOverTile,unitsFriend,unitsFoe);
            grid.drawPath(renderer,line,scale);
        }

        for (const auto &val: friendMovementPlans | std::views::values) {
            grid.drawPath(renderer,val,scale);
        }


        for (const unit& U: unitsFriend) {
            U.render(scale,millis,renderer);
        }
    }
    else if (currentPhase==MOVEMENT_EXECUTION) {

        for (int i = 0; i < unitsFriend.size(); i++) {
            const unit& U = unitsFriend[i];
            U.render(scale,millis,renderer);
         /*   const unit& U = unitsFriend[i];
            if (U.getAnimationPhase()!=unitType::MOVE || !friendMovementPlans.contains(i)) {
                //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
                const int hexX = U.getHexX();
                const int hexY = U.getHexY();
                const hexTile& unitTile = grid.getHexTile(hexX, hexY);

                U.render(unitTile.getHexCenterX()*scale,unitTile.getHexCenterY()*scale,scale,millis,renderer);
            }
            else {
                double hexPerMs = 1.0/1000;
                uint32_t millisSinceMovementStart = U.timeSinceAnimationStart(millis);
                double progress = millisSinceMovementStart *hexPerMs;
                //We already checked that the path exists for this thing
                const auto& path = friendMovementPlans.at(i);

                //Get the hex just before, and just after the current location (id in the path)
                int hexBefore = std::min(static_cast<int>(progress),static_cast<int>(path.size())-1);
                double fac = progress-hexBefore;

                int hexBeforeId;
                int hexAfterId;
                //Huh, I guess the path is empty, fine just use the current unit location
                if (hexBefore ==-1) {
                    hexBeforeId=grid.getHexId( U.getHexX(),U.getHexY());
                    hexAfterId=grid.getHexId( U.getHexX(),U.getHexY());
                }
                else {
                    hexBeforeId=path[hexBefore];
                    if (hexBefore+1<path.size()) {
                        hexAfterId=path[hexBefore+1];
                    }
                    else
                        hexAfterId=hexBeforeId;
                }

                const hexTile& hexBeforeTile = grid.getHexTile(hexBeforeId);
                const hexTile& hexAfterTile = grid.getHexTile(hexAfterId);

                U.render(hexBeforeTile.getHexCenterX()*scale*(1-fac)+hexAfterTile.getHexCenterX()*scale*fac,hexBeforeTile.getHexCenterY()*scale*(1-fac)+hexAfterTile.getHexCenterY()*scale*fac,scale,millis,renderer);


            }
            */
        }
    }
}

void scenario::update(int screenWidth, int screenHeight,  int mouseX, int mouseY, bool isLeftMouseClick, bool isRightMouseClick, bool executeClick,uint32_t millis) {
    const double scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx),static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx));


    mouseOverTile=grid.getHexFromLocation(mouseX,mouseY,scale);

    if (currentPhase==MOVEMENT_PLANNING_FRIEND) {

        //Right click to select units
        if (isRightMouseClick) {
            selectedTile=-1;
            //Deselect selected unit
            if (selectedUnit!=-1)
                unitsFriend[selectedUnit].unreadyAttack();
            selectedUnit=-1;

            for (int i = 0; i < unitsFriend.size(); i++) {
                if (grid.getHexId(unitsFriend[i].getHexX(),unitsFriend[i].getHexY())==mouseOverTile) {
                    selectedTile = mouseOverTile;
                    selectedUnit = i;
                    unitsFriend[i].doReadyAttack();
                }
            }
        }

        //Left click to queue movement
        if (isLeftMouseClick) {
            if (selectedUnit != -1) {
                unitsFriend[selectedUnit].unreadyAttack();

                //I am pretty sure this has already been set
                if (selectedTile == -1) {
                    selectedUnit = grid.getHexId(unitsFriend[selectedUnit].getHexX(),unitsFriend[selectedUnit].getHexY());
                }

                if (friendMovementPlans.contains(selectedUnit))
                    friendMovementPlans.at(selectedUnit)=grid.findPath(selectedTile,mouseOverTile,unitsFriend,unitsFoe);
                else
                    friendMovementPlans.insert(std::make_pair(selectedUnit,grid.findPath(selectedTile,mouseOverTile,unitsFriend,unitsFoe) ));

                selectedUnit=-1;
            }
            selectedTile=-1;

        }


        //Update animation of friendly and todo hostile units
        for (auto & U : unitsFriend) {
            //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
            const int hexX = U.getHexX();
            const int hexY = U.getHexY();

            const hexTile& unitTile = grid.getHexTile(hexX, hexY);

            U.setX(unitTile.getHexCenterX()*scale);
            U.setY(unitTile.getHexCenterY()*scale);

        }


        if (executeClick) {
            currentPhase=MOVEMENT_EXECUTION;
        }
    }
    else if (currentPhase == MOVEMENT_EXECUTION) {
        //Update animation of units, friends as well as todo foes
        for (int i = 0; i < unitsFriend.size(); i++) {
            auto& U = unitsFriend[i];
            U.unreadyAttack();


            {
                if (U.getAnimationPhase()!=unitType::MOVE || !friendMovementPlans.contains(i)) {
                    //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
                    const int hexX = U.getHexX();
                    const int hexY = U.getHexY();
                    const hexTile& unitTile = grid.getHexTile(hexX, hexY);

                    U.setX(unitTile.getHexCenterX()*scale);
                    U.setY(unitTile.getHexCenterY()*scale);

                    if (friendMovementPlans.contains(i))
                        U.startMovement(millis);
                }
                else {
                    double hexPerMs = 1.0/1000;
                    uint32_t millisSinceMovementStart = U.timeSinceAnimationStart(millis);
                    double progress = millisSinceMovementStart *hexPerMs;
                    //We already checked that the path exists for this thing
                    const auto& path = friendMovementPlans.at(i);

                    //Get the hex just before, and just after the current location (id in the path)
                    int hexBefore = std::min(static_cast<int>(progress),static_cast<int>(path.size())-1);
                    double fac = progress-hexBefore;

                    int hexBeforeId;
                    int hexAfterId;
                    //Huh, I guess the path is empty, fine just use the current unit location
                    if (hexBefore ==-1) {
                        hexBeforeId=grid.getHexId( U.getHexX(),U.getHexY());
                        hexAfterId=grid.getHexId( U.getHexX(),U.getHexY());
                    }
                    else {
                        hexBeforeId=path[hexBefore];
                        if (hexBefore+1<path.size()) {
                            hexAfterId=path[hexBefore+1];
                        }
                        else
                            hexAfterId=hexBeforeId;
                    }

                    const hexTile& hexBeforeTile = grid.getHexTile(hexBeforeId);
                    const hexTile& hexAfterTile = grid.getHexTile(hexAfterId);

                    double xbefore=hexBeforeTile.getHexCenterX()*scale;
                    double xafter=hexAfterTile.getHexCenterX()*scale;
                    U.setX(xbefore*(1-fac)+xafter*fac);
                    U.setY(hexBeforeTile.getHexCenterY()*scale*(1-fac)+hexAfterTile.getHexCenterY()*scale*fac);
                    if (hexAfterId!=hexBeforeId)
                        U.setFlip(xbefore<xafter);
                }
            }
        }
        for (auto& unit : unitsFoe) unit.unreadyAttack();


    }

    for (unit& U: unitsFriend) {
        U.updateAnimation(millis);
    }
    for (unit& U: unitsFoe) {
        U.updateAnimation(millis);
    }
}