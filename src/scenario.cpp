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
    unitLibrary.emplace_back(fs::path("assets")/"units"/"SAMTruckDK",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"IverHuitfeldtFrigate",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"NeptuneLauncherDK",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"ArleighBurke",renderer);

    //TODO: load from disk, and allow spawning
    unitsFriend.clear();
    unitsFriend.emplace_back(unitLibrary[0],true,20,8);
    unitsFriend.emplace_back(unitLibrary[2],true,18,12);
    unitsFriend.emplace_back(unitLibrary[1],true,25,20);
    unitsFriend.emplace_back(unitLibrary[1],true,32,15);
    unitsFriend.emplace_back(unitLibrary[1],true,31,14);
    unitsFriend.emplace_back(unitLibrary[3],true,10,23);
    unitsFriend.emplace_back(unitLibrary[3],true,8,23);



    scenarioWidthPx=grid.getScenarioWidth();
    scenarioHeightPx=grid.getScenarioHeight();

    currentPhase=MOVEMENT_PLANNING_FRIEND;

    scale=1.0;
}

scenario::~scenario() = default;


void scenario::render(SDL_Renderer* renderer, int screenWidth, int screenHeight, uint32_t millis) const {

    background.render(0,0,renderer,scale);

    if (currentPhase==MOVEMENT_PLANNING_FRIEND) {
        //Show the tile the mouse is over
        grid.drawTile(renderer,mouseOverTile,scale);


        //Display how far we can move
        if (selectedUnit!=-1 && selectedTile!=-1) {

            std::set<int> obstructed;
            //We get obstructed by the current position of units, and by their destinations
            for (const unit& u : unitsFriend) {
                obstructed.insert(grid.getHexId(u.getHexX(),u.getHexY()));
            }
            for (const auto &plans: friendMovementPlans ) {
                if (!plans.second.empty() && plans.first!=selectedUnit) {
                    obstructed.insert(plans.second.back());
                }
            }

            const std::set<int> tilesNearSelection=grid.getNeighbours(selectedTile,unitsFriend[selectedUnit].getMovementPoints(),obstructed);
            grid.drawTiles(renderer,tilesNearSelection,scale,hexGrid::COLOR);

            const std::vector<int> line = grid.findPath(selectedTile,mouseOverTile,obstructed);
            grid.drawPath(renderer,line,scale);
        }

        for (const auto &val: friendMovementPlans | std::views::values) {
            grid.drawPath(renderer,val,scale);
        }


        for (const unit& U: unitsFriend) {
            grid.drawTile(renderer,grid.getHexId(U.getHexX(),U.getHexY()),scale,hexGrid::COLOR,128,255,128,255);
            U.render(scale,millis,renderer);
        }
    }
    else if (currentPhase==MOVEMENT_EXECUTION) {

        for (const auto & U : unitsFriend) {
            U.render(scale,millis,renderer);
        }
    }
}

void scenario::update(int screenWidth, int screenHeight,  int mouseX, int mouseY, bool isLeftMouseClick, bool isRightMouseClick, bool executeClick,uint32_t millis) {
    scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx+guiRightBarPixels),
                     static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx+guiBottomBarPixels));


    mouseOverTile=grid.getHexFromLocation(mouseX,mouseY,scale);

    if (currentPhase==MOVEMENT_PLANNING_FRIEND) {

        //Right click to select units, or give movement order
        if (isRightMouseClick) {

            //See if there is a new unit to select
            int newSelectedUnit=-1;

            for (int i = 0; i < unitsFriend.size(); i++) {
                if (grid.getHexId(unitsFriend[i].getHexX(),unitsFriend[i].getHexY())==mouseOverTile) {
                    selectedTile = mouseOverTile;
                    newSelectedUnit = i;
                    unitsFriend[i].doReadyAttack();
                }
            }
            if (newSelectedUnit != -1) {
                //Deselect selected unit
                if (selectedUnit!=-1) {
                    if (selectedUnit != newSelectedUnit) {
                        unitsFriend[selectedUnit].unreadyAttack();
                        selectedUnit=newSelectedUnit;
                    }
                    else {
                        //Click the same unit to cancel movement order
                        unitsFriend[selectedUnit].unreadyAttack();
                        if (friendMovementPlans.contains(selectedUnit))
                            friendMovementPlans.erase(selectedUnit);
                        selectedUnit = -1;
                    }
                }
                else
                    selectedUnit=newSelectedUnit;
            }
            else {
                //You clicked somewhere else, while a unit was selected this is a movement command
                if (selectedUnit!=-1) {
                    unitsFriend[selectedUnit].unreadyAttack();

                    //I am pretty sure this has already been set
                    if (selectedTile == -1) {
                        selectedUnit = grid.getHexId(unitsFriend[selectedUnit].getHexX(),unitsFriend[selectedUnit].getHexY());
                    }

                    std::set<int> obstructed;
                    //We get obstructed by the current position of units, and by their destinations
                    for (const unit& u : unitsFriend) {
                        obstructed.insert(grid.getHexId(u.getHexX(),u.getHexY()));
                    }
                    for (const auto &plans: friendMovementPlans ) {
                        if (!plans.second.empty() && plans.first!=selectedUnit) {
                            obstructed.insert(plans.second.back());
                        }
                    }


                    auto fullPath =grid.findPath(selectedTile,mouseOverTile,obstructed);
                    auto limitedPath =std::vector<int>();
                    for (int i = 0; i < fullPath.size() && i<unitsFriend[selectedUnit].getMovementPoints()+1; i++)
                        limitedPath.push_back(fullPath[i]);

                    if (friendMovementPlans.contains(selectedUnit)) {
                        friendMovementPlans.at(selectedUnit)=limitedPath;
                    }
                    else
                        friendMovementPlans.insert(std::make_pair(selectedUnit,limitedPath));

                    selectedUnit=-1;
                }
            }
        }

        //Left click cancels selection
        if (isLeftMouseClick) {
            if (selectedUnit != -1) {
                unitsFriend[selectedUnit].unreadyAttack();
                selectedUnit = -1;
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
            selectedUnit=-1;
            selectedTile=-1;
        }
    }
    else if (currentPhase == MOVEMENT_EXECUTION) {

        //How many units have NOT finished their movements yet
        int pendingUnits=0;

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

                    if (friendMovementPlans.contains(i)) {
                        ++pendingUnits;
                        U.startMovement(millis);
                    }
                }
                else {
                    ++pendingUnits;
                    double hexPerMs = 2.0/1000;
                    uint32_t millisSinceMovementStart = U.timeSinceAnimationStart(millis);
                    double progress = millisSinceMovementStart *hexPerMs;
                    //We already checked that the path exists for this thing
                    const auto& path = friendMovementPlans.at(i);

                    //Have we arrived at our destination?
                    if (progress+1>=path.size()) {


                        int hexX=0;
                        int hexY=0;
                        grid.getHexXYs(path.back(),hexX, hexY);
                        U.setHexX(hexX);
                        U.setHexY(hexY);

                        const hexTile& unitTile = grid.getHexTile(hexX, hexY);

                        U.setX(unitTile.getHexCenterX()*scale);
                        U.setY(unitTile.getHexCenterY()*scale);

                        friendMovementPlans.erase(i);
                        U.setAnimation(millis,unitType::IDLE);
                    }
                    else {

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
        }


        if (pendingUnits==0) {
            currentPhase=MOVEMENT_PLANNING_FRIEND;
            friendMovementPlans.clear();
        }

    }

    for (unit& U: unitsFriend) {
        U.updateAnimation(millis);
    }
}