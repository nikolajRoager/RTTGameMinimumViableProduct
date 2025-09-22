//
// Created by nikolaj on 9/16/25.
//

#include "scenario.h"

#include <fstream>
#include <iostream>

scenario::scenario(SDL_Renderer* renderer) : background("assets/background.png",renderer), hexSelectionOutline("assets/hexoutline.png",renderer), grid("assets/",renderer) {


    //Will instantly be overwritten
    mouseOverTile=0;

    //TODO: load from disk
    unitLibrary.clear();
    unitLibrary.emplace_back(true,"assets/SAMTruck.png",renderer);

    //TODO: load from disk, and allow spawning
    unitsFriend.clear();
    unitsFriend.emplace_back(unitLibrary[0],true,20,8);

    unitsFriend.emplace_back(unitLibrary[0],true,18,12);

    scenarioWidthPx=grid.getScenarioWidth();
    scenarioHeightPx=grid.getScenarioHeight();

    currentPhase=MOVEMENT_PLANNING;
}

scenario::~scenario() {

    //loaded assets, which are not pointers, automatically unload at the end
}


void scenario::render(SDL_Renderer* renderer, int screenWidth, int screenHeight) const {

    double scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx),static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx));

    background.render(0,0,renderer,nullptr,scale);

    if (currentPhase==MOVEMENT_PLANNING) {
        //Show the tile the mouse is over
        grid.drawTile(renderer,mouseOverTile,scale);


        //Display how far we can move
        if (selectedUnit!=-1 && selectedTile!=-1) {
            const std::set<int> tilesNearSelection=grid.getNeighbours(selectedTile,4,unitsFriend,unitsFoes);
            grid.drawTiles(renderer,tilesNearSelection,scale,hexGrid::COLOR);

            const std::vector<int> line = grid.findPath(selectedTile,mouseOverTile,unitsFriend,unitsFoes);
            grid.drawPath(renderer,line,scale);
        }


        for (const unit& U: unitsFriend) {
            //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
            const int hexX = U.getHexX();
            const int hexY = U.getHexY();

            const hexTile& unitTile = grid.getHexTile(hexX, hexY);

            U.render(unitTile.getHexCenterX()*scale,unitTile.getHexCenterY()*scale,scale,renderer);
        }
    }
}

void scenario::update(int screenWidth, int screenHeight,  int mouseX, int mouseY, bool isLeftMouseClick, bool isRightMouseClick) {
    double scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx),static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx));


    mouseOverTile=grid.getHexFromLocation(mouseX,mouseY,scale);

    if (currentPhase==MOVEMENT_PLANNING) {

        //Right click to select units
        if (isRightMouseClick) {
            selectedTile=-1;
            selectedUnit=-1;
            for (int i = 0; i < unitsFriend.size(); i++) {
                if (grid.getHexId(unitsFriend[i].getHexX(),unitsFriend[i].getHexY())==mouseOverTile) {
                    selectedTile = mouseOverTile;
                    selectedUnit = i;
                }
            }
        }

        //Left click to queue movement
        if (isLeftMouseClick) {
            selectedTile=-1;
            if (selectedUnit != -1) {
                selectedTile=-1;
                selectedUnit=-1;
            }

        }
    }

}