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
    unitsA.clear();
    unitsA.emplace_back(unitLibrary[0],true,20,8);

    scenarioWidthPx=grid.getScenarioWidth();
    scenarioHeightPx=grid.getScenarioHeight();
}

scenario::~scenario() {

    //loaded assets, which are not pointers, automatically unload at the end
}


void scenario::render(SDL_Renderer* renderer, int screenWidth, int screenHeight) const {

    double scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx),static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx));

    background.render(0,0,renderer,nullptr,scale);


    //Show the tile the mouse is over
    grid.drawTile(renderer,mouseOverTile,scale);

    std::set<int> tilesNearSelection=grid.getNeighbours(selectedTile);

    grid.drawTiles(renderer,tilesNearSelection,scale,hexGrid::COLOR);

    for (const unit& U: unitsA) {
        //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
        int hexX = U.getHexX();
        int hexY = U.getHexY();

        const hexTile& unitTile = grid.getHexTile(hexX, hexY);

        U.render(unitTile.getHexCenterX()*scale,unitTile.getHexCenterY()*scale,scale,renderer);
    }
}

void scenario::update(int screenWidth, int screenHeight,  int mouseX, int mouseY, bool isRightMouseClick) {
    double scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx),static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx));

    mouseOverTile=grid.getHexFromLocation(mouseX,mouseY,scale);

    if (isRightMouseClick) {
        selectedTile = mouseOverTile;
    }
}