//
// Created by nikolaj on 9/21/25.
//

#include "hexGrid.h"

#include <cmath>
#include <fstream>
#include <map>
#include <stdexcept>

hexGrid::hexGrid(const fs::path&path, SDL_Renderer* renderer):hexSelectionOutline(path/"hexoutline.png",renderer) {

    //TODO, load from a file at path
    ///Width of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    hexGridWidth=38;
    ///height of the hexagons making up the game grid in pixels (can not be regular hexagons for rounding reasons)
    hexGridHeight=24;

    //Set up hexagon drawing data
    ///Width of the hexagonal grid this game is being played on, in hexagons
    hexWidthPx=hexSelectionOutline.getWidth();
    ///Height of the hexagonal grid this game is being played on, in hexagons
    hexHeightPx=hexSelectionOutline.getHeight();

    hexRadiusPx=hexHeightPx*0.5;

    //Divisions are evil and should be kept out of the loop
    hexHalfWidthPx=hexSelectionOutline.getWidth()/2;
    hex34HeightPx=(hexSelectionOutline.getHeight()*3)/4;

    scenarioWidthPx=hexWidthPx*hexGridWidth+hexHalfWidthPx;
    scenarioHeightPx=hex34HeightPx*hexGridHeight+hexHeightPx/4;


    //Load hexagons
    //todo, replace with better scenario loading
    std::ifstream TEMP_INPUT("assets/TEMP.txt");

    if (!TEMP_INPUT.is_open())
        throw std::runtime_error("unable to open file assets/TEMPT.txt");

    for (int hexY = 0; hexY < hexGridHeight; hexY++) {
        for (int hexX = 0; hexX < hexGridWidth; hexX++) {
            int friendOrFoe;
            TEMP_INPUT>>friendOrFoe;
            double hexTopLeftX = hexX * hexWidthPx+((hexY+1)%2) * hexHalfWidthPx+hexHalfWidthPx;
            double hexTopLeftY = hexY * hex34HeightPx+hexHeightPx/2.0;
            hexTiles.emplace_back(static_cast<hexTile::hexStatus>(friendOrFoe),hexTopLeftX,hexTopLeftY);
        }
    }

    TEMP_INPUT.close();
}

void hexGrid::drawTile(SDL_Renderer *renderer, const int hexId, const double scale, tileDisplayMode displayMode, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    if (hexId >= hexTiles.size() || hexId < 0)
        return;
    const hexTile &tile=hexTiles[hexId];
    double hexTopLeftX =tile.getHexCenterX()-hexHalfWidthPx;
    double hexTopLeftY =tile.getHexCenterY()-hexHeightPx/2.0;

    hexTopLeftX *= scale;
    hexTopLeftY *= scale;

    if (displayMode==STATUS)
        switch (tile.getStatus()) {
            case hexTile::FRIEND:
                hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,0,255,0,renderer,scale);
                break;
            case hexTile::FOE:
                hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,255,0,0,renderer,scale);
                break;
            case hexTile::NEUTRAL:
                hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,125,125,125,renderer,scale);
                break;
            case hexTile::SEA:
                hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,0,125,255,renderer,scale);
                break;
        }
    else if (displayMode==COLOR) {
        hexSelectionOutline.render(hexTopLeftX,hexTopLeftY,r,g,b,a,renderer,scale);
    }
}

int hexGrid::getHexFromLocation(double x, double y, double scale) const {

    if (x>scenarioWidthPx*scale || x<0 || y>scenarioHeightPx*scale || y<0)
        return -1;
    int foundTile=-1;
    double dist=-1;

    //Get the hext nearest to the mouse coordinates and select it
    for (int hexX = 0; hexX < hexGridWidth; hexX++) {
        for (int hexY = 0; hexY < hexGridHeight; hexY++) {
            const hexTile& tile = hexTiles[hexX+hexY*hexGridWidth];
            double hexCenterX =tile.getHexCenterX();
            double hexCenterY =tile.getHexCenterY();

            hexCenterX *= scale;
            hexCenterY *= scale;

            double thisDist = std::pow(hexCenterX-x,2)+pow(hexCenterY-y,2);
            if (thisDist < dist || dist<0) {
                dist=thisDist;
                foundTile=hexX+hexY*hexGridWidth;
            }
        }
    }
    return foundTile;
}

std::set<int> hexGrid::getNeighbours(int hexId,int steps,const std::set<int>& obstructed) const {
    std::set<int> visited;

    //If the hex is out of bound, disregard it
    if (hexId<0 || hexId>=hexTiles.size())
        return visited;

    const auto startingStatus = hexTiles[hexId].getStatus();

    //The queue of the current layer we are searching for neighbours of
    std::set<int> oldQueue;

    //The queue of the next layer, which we will search shortly
    std::set<int> newQueue;

    oldQueue.insert(hexId);

    for (int depth = 0; depth < steps+1/*Add 1, because step 0 is the starting hex*/; depth++) {
        if (oldQueue.empty())
            break;

        for (int i : oldQueue) {
            //All the checks whether to check this hex is done here,
            if (i!=hexId)//Skip all checks for the initial hex (there is likely a unit there, and that is ok, I bet it was they who asked for the pathfinding to start)
                if (visited.contains(i) || startingStatus != hexTiles[i].getStatus())
                    continue;
            if (!obstructed.contains(i))
                visited.insert(i);


            //Get the x and y hex coordinates
            int hexX = i% hexGridWidth;
            //Intentionally using Integer division
            int hexY = i/ hexGridWidth;

            if (depth<steps)
            {
                //There are up to six neighbours, lets add them to the new Queue if we haven't already visited them
                //Neighbour in front
                if (hexX+1<hexGridWidth) {
                    newQueue.insert(i+1);
                }
                if (hexX>=1) {
                    newQueue.insert(i-1);
                }
                if (hexY>=1) {
                    newQueue.insert(i-hexGridWidth);
                    if (hexY%2==0) {
                        if (hexX+1<hexGridWidth) newQueue.insert(i+1-hexGridWidth);
                    }
                    else
                        if (hexX>=1) newQueue.insert(i-1-hexGridWidth);
                }
                if (hexY+1<hexGridHeight) {
                    newQueue.insert(i+hexGridWidth);
                    if (hexY%2==0) {
                        if (hexX+1<hexGridWidth) newQueue.insert(i+1+hexGridWidth);
                    }
                    else
                        if (hexX>=1) newQueue.insert(i-1+hexGridWidth);
                }
            }
        }
        //swap buffers and reset new queue
        newQueue.swap(oldQueue);
        newQueue.clear();
    }


    visited.insert(hexId);
    return visited;
}

std::vector<int> hexGrid::findPathAdvanced(int startId, int stopId, const std::set<int> &obstructed, bool ignoreObstructedGoal,int range,bool avoidObstacles) const {
    //The hexagon pathfinding algorithm is largely based on the find-neighbours algorithm
    //We are going to be searching in layers of hexes
    std::map<int,int> visitedBacktrack;

    //If the start or stop hex is out of bound, disregard it
    if (startId<0 || startId>=hexTiles.size())
        return {};
    if (stopId<0 || stopId>=hexTiles.size() || obstructed.count(stopId))//Obstructions are not blocks for our movement, just places we can't stand
        return {};

    const auto startingStatus = hexTiles[startId].getStatus();

    //The queue of the current layer we are searching for neighbours of, and where we came from
    std::map<int,int> oldQueue;

    //The queue of the next layer, which we will search shortly, and where we came from
    std::map<int,int> newQueue;

    //We will be searching backwards, to make back-tracking give us the correct path
    oldQueue.emplace(stopId,stopId);

    int layer=0;

    while (!oldQueue.empty()) {

        for (auto i_from : oldQueue) {
            int i = i_from.first;
            int from = i_from.second;

            //All the checks whether to check this hex is done here,
            if (i!=startId)//Skip all checks for the initial hex (there is likely a unit there, and that is ok)
            {

                if (i!=stopId) {
                    if (visitedBacktrack.contains(i) || startingStatus != hexTiles[i].getStatus() || (avoidObstacles && obstructed.count(i)) /*Uncomment this to make units impassable*/)
                        continue;
                }
                else
                    if (visitedBacktrack.contains(i) || startingStatus != hexTiles[i].getStatus())
                        continue;
            }
            else {
                //Oh, we found the target, start backtracking
                std::vector<int> out = {startId};
                for (int j = from; j!=stopId; j=visitedBacktrack[j])
                    out.push_back(j);
                out.push_back(stopId);

                if (range==-1)
                    return out;

                auto limitedPath =std::vector<int>();
                for (int i = 0; i < out.size() && i<range+1; i++)
                    limitedPath.push_back(out[i]);

                if (limitedPath.empty() || obstructed.count(limitedPath.back()))
                    return {};

                return limitedPath;
            }
            visitedBacktrack.emplace(i,from);


            //Get the x and y hex coordinates
            int hexX = i% hexGridWidth;
            //Intentionally using Integer division
            int hexY = i/ hexGridWidth;

            {
                //There are up to six neighbours, lets add them to the new Queue if we haven't already visited them
                //Neighbour in front
                if (hexX+1<hexGridWidth) {
                    newQueue.emplace(i+1,i);
                }
                if (hexX>=1) {
                    newQueue.emplace(i-1,i);
                }
                if (hexY>=1) {
                    newQueue.emplace(i-hexGridWidth,i);
                    if (hexY%2==0) {
                        if (hexX+1<hexGridWidth) newQueue.emplace(i+1-hexGridWidth,i);
                    }
                    else
                        if (hexX>=1) newQueue.emplace(i-1-hexGridWidth,i);
                }
                if (hexY+1<hexGridHeight) {
                    newQueue.emplace(i+hexGridWidth,i);
                    if (hexY%2==0) {
                        if (hexX+1<hexGridWidth) newQueue.emplace(i+1+hexGridWidth,i);
                    }
                    else
                        if (hexX>=1) newQueue.emplace(i-1+hexGridWidth,i);
                }
            }


        }
        //swap buffers and reset new queue
        newQueue.swap(oldQueue);
        newQueue.clear();
        layer++;
    }

    //If we got here, we FAILED to find a valid path
    return {};
}


void hexGrid::drawPath(SDL_Renderer *renderer, const std::vector<int> &pathToDraw, double scale) const {
    for (int i =0; i+1 < pathToDraw.size(); i++) {
        double x0 = hexTiles[pathToDraw[i]].getHexCenterX()*scale;
        double y0 = hexTiles[pathToDraw[i]].getHexCenterY()*scale;

        double x1 = hexTiles[pathToDraw[i+1]].getHexCenterX()*scale;
        double y1 = hexTiles[pathToDraw[i+1]].getHexCenterY()*scale;
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawLine(renderer, x0,y0,x1,y1);
    }
}
