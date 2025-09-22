//
// Created by nikolaj on 9/21/25.
//

#ifndef PREMVPMAPGAME_HEXGRID_H
#define PREMVPMAPGAME_HEXGRID_H
#include <set>
#include <vector>

#include "hexTile.h"
#include "texwrap.h"
#include "unit.h"

class hexGrid {
private:
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


    int scenarioWidthPx;
    int scenarioHeightPx;

    std::vector<hexTile> hexTiles;

public:

    enum tileDisplayMode {
        STATUS,
        COLOR,
    };


    explicit hexGrid(const std::string &path, SDL_Renderer* renderer);

    [[nodiscard]] int getScenarioWidth() const { return scenarioWidthPx; }
    [[nodiscard]] int getScenarioHeight() const { return scenarioHeightPx; }

    void drawTile(SDL_Renderer *renderer, int hexId, double scale, tileDisplayMode=STATUS, Uint8 r=255, Uint8 g=125, Uint8 b=125, Uint8 a=125) const;


    void drawTiles(SDL_Renderer *renderer, const std::set<int>& tilesToDraw , double scale, tileDisplayMode display_mode=STATUS, Uint8 r=255, Uint8 g=125, Uint8 b=125, Uint8 a=125) const {
        for (int hexId: tilesToDraw) {
            drawTile(renderer,hexId,scale,display_mode,r,g,b,a);
        }
    }

    void drawPath(SDL_Renderer *renderer,const std::vector<int>& pathToDraw, double scale) const;


    [[nodiscard]] int getHexFromLocation(double x, double y, double scale) const;

    [[nodiscard]] const hexTile& getHexTile(int hexX, int hexY) const {
        return hexTiles[hexY*hexGridWidth+hexX];
    }

    [[nodiscard]] int getHexId(int hexX, int hexY) const {
        return hexY*hexGridWidth+hexX;
    }

    [[nodiscard]] const hexTile& getHexTile (int hexId) const {
        return hexTiles[hexId];
    }

    ///Get the ID's of all neighbour a maximum number of steps from a hex
    [[nodiscard]] std::set<int> getNeighbours(int hexId,int steps,const std::vector<unit>& obstructionsA,const std::vector<unit>& obstructionsB) const;

    ///Get a list of the hexes we need to travel to, to get from start to stop
    [[nodiscard]] std::vector<int> findPath(int startId, int stopId,const std::vector<unit>& obstructionsA,const std::vector<unit>& obstructionsB, bool ignoreObstructedGoal=false) const;

};

#endif //PREMVPMAPGAME_HEXGRID_H