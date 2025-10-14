#include "physicsCake.h"

#include <iostream>
#include <ranges>
//
// Created by Nikolaj Christensen on 03/10/2025.
//
void physicsCake::bake(const hexGrid& grid, const std::vector<unit>& units, const std::map<int, std::vector<attackPlan> > &attackPlans) {
    SSMVectors.clear();
    SAMVectors.clear();


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
    //Which sam (the number inside the list) is tasked against which SSM (the index)
    std::vector<int> SAMTaskedAgainstSSM;

    std::vector<SAMLauncher> SAMLaunchers;
    std::vector<SAMInAir> flyingSAMs;

    for (int i = 0; i < units.size(); i++) {
        if (units[i].getSAMRange()>0) {
            SAMLaunchers.emplace_back(i,units[i].isFriendly(),units[i].getSAMRange()/SAMSpeed,units[i].getSAMRange(),units[i].getSAMDelay());
        }
    }

    unitHealthEvents.reserve(units.size());
    for (const auto& unit : units) {
        unitHealthEvents.emplace_back();
        //Save starting health of everyone
        unitHealthEvents.back().emplace_back(unit.getHp(),0);
    }

    //Set up tables where we will store the locations of the SSMs
    for (const auto& unitPlans : attackPlans) {
        for (int i = 0; i < unitPlans.second.size(); ++i) {
            SSMVectors.emplace_back(unitPlans.second[i].getPlayerSide());
            SSMVectorsLookup.emplace_back(unitPlans.first, i);
            SSMVectorsStatus.emplace_back(UNSTARTED);
            SAMTaskedAgainstSSM.emplace_back(-1);
        }
    }

    //End time serves as the current time when stepping through this
    double currentTime=0.0;

    double dt = 0.1;
    bool isFinished = false;
    while (!isFinished) {
        isFinished = true;

        //Update all SAM launchers
        for (auto& launcher : SAMLaunchers) {
            //Only possible to launch if the unit is still alive

            //Loop through all health events in chronological order, to get the current health
            int launcherHealth=units[launcher.unitId].getHp();
            for (auto & launcherHealthEvent : unitHealthEvents[launcher.unitId]) {
                if (launcherHealthEvent.time<currentTime) {
                    launcherHealth= launcherHealthEvent.health;
                }
                else break;
            }

            if (launcherHealth>0) {
                //check that the launcher is reloaded
                if (launcher.ongoingDelay<=0) {
                    double samX = units[launcher.unitId].getX();
                    double samY = units[launcher.unitId].getY();
                    //Loop through all SSMs
                    for (int ssmId = 0; ssmId < SSMVectors.size(); ++ssmId) {
                        //Only consider flying, enemy SSMs, which DO NOT have a SAM currently tasked against them
                        if (SSMVectorsStatus[ssmId]==FLYING && SSMVectors[ssmId].playerSide!=launcher.playerSide && SAMTaskedAgainstSSM[ssmId]==-1  && SSMVectors[ssmId].line.size()>=2) {
                            //check if the SSM is in range
                            auto ssmPosition = SSMVectors[ssmId].getLastPosition();

                            //Todo, replace by stored velocity
                            double ssmVx = (ssmPosition.x - SSMVectors[ssmId].line[SSMVectors[ssmId].line.size()-2].x)/dt;
                            double ssmVy = (ssmPosition.y - SSMVectors[ssmId].line[SSMVectors[ssmId].line.size()-2].y)/dt;



                            //Intercept calculation, pretty basic stuff just google it
                            //Vector from shooter to target
                            double rx = ssmPosition.x-samX;
                            double ry = ssmPosition.y-samY;

                            //2nd degree equation to get the inverse of the time to target
                            //Has up to two solutions, but maybe 0
                            //First get the discriminant
                            double discriminant = 4*pow(rx*ssmVx+ry*ssmVy,2)-4*(rx*rx+ry*ry)*((ssmVx*ssmVx+ssmVy*ssmVy)-SAMSpeed*SAMSpeed);

                            //Negative time indicates no solution found
                            double interceptTime=-1;
                            if (discriminant>=0) {
                                double interceptTime0 = 1/((-2*(rx*ssmVx+ry*ssmVy)-sqrt(discriminant))/(2*(rx*rx+ry*ry)));
                                double interceptTime1 = 1/((-2*(rx*ssmVx+ry*ssmVy)+sqrt(discriminant))/(2*(rx*rx+ry*ry)));

                                if (interceptTime0>0 && interceptTime1>0)
                                    interceptTime=std::min(interceptTime0,interceptTime1);
                                else if (interceptTime0>0)
                                    interceptTime=interceptTime0;
                                else if (interceptTime1>0)
                                    interceptTime=interceptTime1;
                            }

                            double dist = sqrt(pow(ssmPosition.x-samX,2)+pow(ssmPosition.y-samY,2));
                            //todo calculate intercept and use that for range instead
                            if (interceptTime>0 && interceptTime<launcher.fuelTime) {
                                std::cout<<"Launcher at "<<units[launcher.unitId].getHexX()<<","<<units[launcher.unitId].getHexY()<<": engage track "<<ssmId<<" at time "<<currentTime<<std::endl;
                                //Assign SAM to track
                                {
                                    //Lock down this track, so we don't spam missiles against the same thing
                                    SAMTaskedAgainstSSM[ssmId]=flyingSAMs.size();

                                    //Todo, store inverse time
                                    double samVx = ssmVx+rx/interceptTime;
                                    double samVy = ssmVy+ry/interceptTime;

                                    flyingSAMs.emplace_back(samX,samY,samVx,samVy,launcher.fuelTime,ssmId);
                                    SAMVectors.emplace_back(launcher.playerSide);
                                }
                                //reload launcher
                                launcher.ongoingDelay=launcher.launchDelay;
                                break;
                            }
                        }

                    }
                }


                launcher.ongoingDelay=std::max(launcher.ongoingDelay-dt,0.0);
            }
        }

        //Update flying surface-to-surface missiles
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
                    const auto& dist = SSMVectors[i].getLastPosition();
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

        //Update flying SAM missiles
        for (int i = 0; i < flyingSAMs.size(); ++i) {
            auto& SAM = flyingSAMs[i];
            if (!SAM.terminated) {
                isFinished = false;
                SAM.x+=SAM.vx*dt;
                SAM.y+=SAM.vy*dt;
                SAM.fuelTimeLeft-=dt;


                SAMVectors[i].line.emplace_back(SAM.x,SAM.y,currentTime);

                if (SAM.fuelTimeLeft <= 0) {
                    SAM.terminated = true;
                    SAMVectors[i].fate=bakedAttackVector::DETONATE;
                    //Clear track
                    if (SAM.target!=-1)
                        SAMTaskedAgainstSSM[SAM.target]=-1;
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
    for (const auto& SAMVector : SAMVectors) {
        if (time>SAMVector.line.front().time && time<SAMVector.line.back().time)
            for (int i = 1; i < SAMVector.line.size(); ++i) {
                if (time<SAMVector.line[i].time) {
                    //we are inside this line
                    //We want the interpolation factor such that
                    //time = fac*attackVectors[i].time+(1-fac)*attackVectors[i-1].time;
                    //Or isolating the factor fac
                    double fac=(time-SAMVector.line[i-1].time)/(SAMVector.line[i].time-SAMVector.line[i-1].time) ;
                    auto temp = std::make_pair(fac*SAMVector.line[i].x+(1-fac)*SAMVector.line[i-1].x,fac*SAMVector.line[i].y+(1-fac)*SAMVector.line[i-1].y);
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
