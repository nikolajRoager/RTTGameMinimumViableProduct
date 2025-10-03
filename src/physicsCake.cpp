#include "physicsCake.h"

#include <iostream>
#include <ranges>
//
// Created by Nikolaj Christensen on 03/10/2025.
//
void physicsCake::bake(const std::vector<unit> units, const std::map<int, std::vector<attackPlan> > &attackPlans) {
    SSMVectors.clear();
    //What owner,id attack plan does each of the SSM vectors in the list correspond to
    std::vector<std::pair<int,int>> SSMVectorsLookup;
    //Status of the different SSM
    enum missileStatus {
        UNSTARTED=0,
        FLYING=1,
        TERMINATED=2,
    };
    //Status of the simulated SSMs
    std::vector<missileStatus> SSMVectorsStatus;

    //Set up tables where we will store the locations of the SSMs
    for (const auto& unitPlans : attackPlans) {
        for (int i = 0; i < unitPlans.second.size(); ++i) {
            SSMVectors.emplace_back();
            SSMVectorsLookup.emplace_back(unitPlans.first, i);
            SSMVectorsStatus.emplace_back(UNSTARTED);
        }
    }

    //End time serves as the current time when stepping through this
    double currentTime=0.0;

    double dt = 0.1;
    bool isFinished = false;
    while (!isFinished) {
        isFinished = true;
        std::cout<<currentTime<<std::endl;

        for (int i = 0; i < SSMVectors.size(); ++i) {
            int unitId = SSMVectorsLookup[i].first;
            int planId = SSMVectorsLookup[i].second;
            if (SSMVectorsStatus[i] == UNSTARTED) {
                isFinished = false;
                //Check if it is time to launch this thing
                if (attackPlans.at(unitId)[planId].getLaunchTime()<currentTime) {
                    SSMVectorsStatus[i]=FLYING;
                }
            }
            if (SSMVectorsStatus[i] == FLYING) {
                isFinished = false;

                //Add the current location to the list of places we have been
                auto loc = attackPlans.at(unitId)[planId].getLocation(currentTime);
                SSMVectors[i].line.emplace_back(loc.first,loc.second,currentTime);

                //Finally check if we have arrived at our destination
                if (attackPlans.at(unitId)[planId].getEndTime()<currentTime) {
                    SSMVectorsStatus[i]=TERMINATED;
                }
            }
        }

        currentTime+=dt;
    }

    endTime=currentTime;
}

void physicsCake::debugRender(SDL_Renderer *renderer, double scale) const {
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    for (const auto& SSMVector : SSMVectors) {

    }
}
