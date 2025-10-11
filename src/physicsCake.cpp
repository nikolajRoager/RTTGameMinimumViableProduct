#include "physicsCake.h"

#include <iostream>
#include <ranges>
//
// Created by Nikolaj Christensen on 03/10/2025.
//
void physicsCake::bake(const hexGrid& grid, const std::vector<unit>& units, const std::map<int, std::vector<attackPlan> > &attackPlans) {
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


    unitHealthEvents.reserve(units.size());
    for (const auto& unit : units) {
        unitHealthEvents.emplace_back();
        //Save starting health of everyone
        unitHealthEvents.back().emplace_back(unit.getHp(),0);
    }

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
                    //We will either be detonated, splashed, or crashed
                    const auto& dist = SSMVectors[i].getDestination();
                    int hexWeHitId = grid.getHexFromLocation(dist.x, dist.y,1);


                    bool hitUnit = false;

                    for (int j = 0; j < units.size(); ++j) {
                        const unit& U = units[j];
                        if (grid.getHexId(U.getHexX(),U.getHexY())==hexWeHitId) {
                            hitUnit = true;
                            SSMVectors[i].fate=bakedAttackVector::DETONATE;
                            unitHealthEvents[j].emplace_back(unitHealthEvents[j].back().health-1,currentTime);
                            break;
                        }
                    }
                    if (!hitUnit) {
                        if ( grid.getHexTile(hexWeHitId).getStatus()==hexTile::SEA) {
                            SSMVectors[i].fate=bakedAttackVector::SPLASH;
                        }
                        else {
                            SSMVectors[i].fate=bakedAttackVector::CRASH;
                        }
                    }
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
        for (int i = 1; i < SSMVector.line.size(); ++i) {
                SDL_RenderDrawLine(renderer, scale*SSMVector.line[i].x,scale*SSMVector.line[i].y,scale*SSMVector.line[i-1].x,scale*SSMVector.line[i-1].y);
            }
    }
}


void physicsCake::render(double time,const texwrap &SSMTexture, SDL_Renderer *renderer, double scale, uint32_t millis) const {

    for (const auto& SSMVector : SSMVectors) {
        if (time>SSMVector.line.front().time && time<SSMVector.line.back().time)
            for (int i = 1; i < SSMVector.line.size(); ++i) {
                if (time<SSMVector.line[i].time) {
                    //we are inside this line
                    //We want the interpolation factor such that
                    //time = fac*attackVectors[i].time+(1-fac)*attackVectors[i-1].time;
                    //Or isolating the factor fac
                    double fac=(time-SSMVector.line[i-1].time)/(SSMVector.line[i].time-SSMVector.line[i-1].time) ;
                    auto temp = std::make_pair(fac*SSMVector.line[i].x+(1-fac)*SSMVector.line[i-1].x,fac*SSMVector.line[i].y+(1-fac)*SSMVector.line[i-1].y);
                    SSMTexture.render(temp.first*scale,temp.second*scale,renderer,scale,true,false,4,(millis/(100))%4);
                    break;
                }
            }
    }
}

void physicsCake::spawnParticles(std::deque<particle> &smokeParticles, double time, double smokeSpawnRate, uint32_t dmillis) {
    for (const auto& SSMVector : SSMVectors) {
        if (time>SSMVector.line.front().time && time<SSMVector.line.back().time)
            for (int i = 1; i < SSMVector.line.size(); ++i) {
                if (time<SSMVector.line[i].time) {
                    //Check if we should spawn particles
                    double t = dmillis*0.001;
                    //Poisson distribution
                    double p = 1-std::exp(-smokeSpawnRate*t);
                    if (distribution(generator)<p) {

                        //we are inside this line
                        //We want the interpolation factor such that
                        //time = fac*attackVectors[i].time+(1-fac)*attackVectors[i-1].time;
                        //Or isolating the factor fac
                        double fac=(time-SSMVector.line[i-1].time)/(SSMVector.line[i].time-SSMVector.line[i-1].time) ;
                        auto temp = std::make_pair(fac*SSMVector.line[i].x+(1-fac)*SSMVector.line[i-1].x,fac*SSMVector.line[i].y+(1-fac)*SSMVector.line[i-1].y);
                        smokeParticles.emplace_back(temp.first,temp.second,0,0,0);

                    }
                    break;
                }
            }
    }
}

void physicsCake::updateUnits(std::vector<unit> &units, double time, uint32_t millis) const {
    for (int i = 0; i < units.size(); ++i) {
        for (int j = 0; j < unitHealthEvents[i].size(); ++j) {
            if (unitHealthEvents[i][j].time<time) {
                units[i].setHp(unitHealthEvents[i][j].health,millis);
            }
            else break;
        }
    }
}
