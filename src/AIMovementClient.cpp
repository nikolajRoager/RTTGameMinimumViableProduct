//
// Created by Nikolaj Christensen on 09/10/2025.
//

#include "AIMovementClient.h"

#include <algorithm>

void AIMovementClient::render(const hexGrid &grid, SDL_Renderer *renderer, double scale) const {
    for (int id : aiPatrolHexes) {
        grid.drawTile(renderer, id, scale,hexGrid::COLOR,255,0,0);
    }
}


void AIMovementClient::makeAIMovementPlans(const hexGrid &grid, std::vector<unit> &units, std::map<int, std::vector<int> > &movementPlans) const {

    //Count up the patrol locations which are not currently being patrolled
    //I need to use a std::vector, because I need to be able to draw a random element
    std::set<int> vacantPatrolPositions;
    for (int i : aiPatrolHexes) {
        vacantPatrolPositions.emplace(i);
    }

    std::set<int> takenPatrolPositions;


    //Loop through all hostile units, and populate the set of taken and vacant patrol positions
    for (unit& u : units) {
        //Only control hostile moveable units, i.e. no buildings
        if (!u.isFriendly() && u.getMovementPoints()>0) {
            int patrol = u.getAIMovementTarget();
            if (patrol != -1) {
                //If it is already taken, or if it is not on the menu we just became vacant
                if (takenPatrolPositions.contains(patrol) || !vacantPatrolPositions.contains(patrol)) {
                    u.setAIMovementTarget(-1);
                }
                else {
                    takenPatrolPositions.emplace(patrol);
                    vacantPatrolPositions.erase(patrol);
                }
            }
        }
    }

    std::cout<<"We have "<<vacantPatrolPositions.size()<<" patrol positions available, with "<<takenPatrolPositions.size()<<" taken"<<std::endl;

    //Convert vacant patrol positions to a vector, so we can efficiently use random access
    std::vector<int> vacantPatrolPositionsAsVector;
    vacantPatrolPositionsAsVector.reserve(vacantPatrolPositions.size());
    for (int i : vacantPatrolPositions) {
        vacantPatrolPositionsAsVector.push_back(i);
    }

    std::cout<<"Assign patrol location"<<std::endl;

    std::ranges::shuffle(vacantPatrolPositionsAsVector, generator);

    //Now loop through all units and assign a patrol location
    for (unit& u : units) {
        if (!u.isFriendly()) {
            int patrol = u.getAIMovementTarget();
            if (patrol == -1 && !vacantPatrolPositionsAsVector.empty()) {
                u.setAIMovementTarget(vacantPatrolPositionsAsVector.back());
                vacantPatrolPositionsAsVector.pop_back();
            }
        }
    }

    std::cout<<"apply movement"<<std::endl;
    //Now apply the movement
    for (int unitId = 0; unitId < units.size(); ++unitId) {
        unit& u = units[unitId];
        if (!u.isFriendly()) {
            int patrol = u.getAIMovementTarget();
            if (patrol != -1) {
                int origin = grid.getHexId(u.getHexX(),u.getHexY());


                std::set<int> obstructed;
                //We get obstructed by the current position of units, and by their destinations
                for (const unit& u : units) {
                    obstructed.insert(grid.getHexId(u.getHexX(),u.getHexY()));
                }
                for (const auto &plans: movementPlans ) {
                    if (!plans.second.empty() && plans.first!=unitId) {
                        obstructed.insert(plans.second.back());
                    }
                }


                auto fullPath =grid.findPath(origin,patrol,obstructed,units[unitId].getMovementPoints());
                /*
                auto limitedPath =std::vector<int>();
                for (int i = 0; i < fullPath.size() && i<units[unitId].getMovementPoints()+1; i++)
                    limitedPath.push_back(fullPath[i]);
                */
                if (movementPlans.contains(unitId)) {
                    movementPlans.at(unitId)=fullPath;
                }
                else
                    movementPlans.insert(std::make_pair(unitId,fullPath));

            }
        }
    }

}

