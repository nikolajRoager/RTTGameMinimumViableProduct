//
// Created by nikolaj on 9/16/25.
//

#include "scenario.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ranges>
#include <SDL2/SDL_ttf.h>


void scenario::drawCircle(double x, double y, double radius, double scale, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer) const {
 //   circle10.render(x*scale,y*scale,r,g,b,a,renderer,scale*radius*0.2,true);
    circle10.render(x*scale,y*scale,r,g,b,a,renderer,scale*2*radius/circle10.getWidth(),true);
}

scenario::scenario(SDL_Renderer* renderer, TTF_Font* _font, std::default_random_engine& _generator) : generator(_generator), background(fs::path("assets")/"background.png",renderer), hexSelectionOutline(fs::path("assets")/"hexoutline.png",renderer),circle10(fs::path("assets")/"circle10.png",renderer), grid(fs::path("assets"),renderer), myGui(fs::path("assets")/"gui",renderer,_font), flyingSSM(fs::path("assets")/"physicsGraphics"/"SSM.png",renderer), smokeParticleTexture(fs::path("assets")/"physicsGraphics"/"smoke.png",renderer), splashParticleTexture(fs::path("assets")/"physicsGraphics"/"splash.png",renderer), crashParticleTexture(fs::path("assets")/"physicsGraphics"/"crash.png",renderer), hitTargetTexture(fs::path("assets")/"physicsGraphics"/"hitTarget.png",renderer), interceptTexture(fs::path("assets")/"physicsGraphics"/"intercept.png",renderer), myCake(_generator),aiMovementClient(_generator),hpMarker(fs::path("assets")/"hitpoint.png",renderer),noPeopleMarker(fs::path("assets")/"nopeople.png",renderer),noPowerMarker(fs::path("assets")/"nopower.png",renderer),visibleMarker(fs::path("assets")/"visible.png",renderer),shiftMarker(fs::path("assets")/"shift.png",renderer), splashSound(fs::path("assets")/"sounds"/"splash.wav"), crashOrInterceptSound(fs::path("assets")/"sounds"/"smallExplosion.wav"), hitTargetSound(fs::path("assets")/"sounds"/"hittarget.wav"), missileSound(fs::path("assets")/"sounds"/"missile.wav") {
    inGameFont = _font;
    //Will instantly be overwritten
    mouseOverTile=0;

    std::cout<<"Loading unit library"<<std::endl;
    //TODO: load from disk
    unitLibrary.clear();
    unitLibrary.emplace_back(fs::path("assets")/"units"/"SAMTruckDK",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"IverHuitfeldtFrigate",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"NeptuneLauncherDK",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"ArleighBurke",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"SlavaCruiser",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"city",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"depot",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"factory",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"powerplant",renderer);
    unitLibrary.emplace_back(fs::path("assets")/"units"/"radarTower",renderer);

    std::cout<<"Loading units"<<std::endl;
    //TODO: load from disk, and allow spawning
    units.clear();
    units.emplace_back(unitLibrary[2],true,20,9);
    units.emplace_back(unitLibrary[2],true,19,10);
    units.emplace_back(unitLibrary[0],true,21,11);
    units.emplace_back(unitLibrary[2],true,21,12);
    units.emplace_back(unitLibrary[1],true,25,20);
    units.emplace_back(unitLibrary[1],true,32,15);
    units.emplace_back(unitLibrary[1],true,30,12);


    //Location of cities, mainly for gameplay purposes, not necessarily realism
    units.emplace_back(unitLibrary[5],true,18,13);//Nuuk, really not a city
    units.emplace_back(unitLibrary[5],true,33,12);//København and Malmö
    units.emplace_back(unitLibrary[5],true,32,10);//Stockholm
    units.emplace_back(unitLibrary[5],true,33,7);//Helsinki, Tampere and Turku
    units.emplace_back(unitLibrary[5],true,31,7);//Luleå

    units.emplace_back(unitLibrary[6],true,20,11);
    units.emplace_back(unitLibrary[6],true,20,7);
    units.emplace_back(unitLibrary[6],true,30,10);
    units.emplace_back(unitLibrary[6],true,30,6);


    units.emplace_back(unitLibrary[7],true,33,13);
    units.emplace_back(unitLibrary[7],true,32,11);
    units.emplace_back(unitLibrary[7],true,31,8 );
    units.emplace_back(unitLibrary[7],true,32,6);

    units.emplace_back(unitLibrary[8],true,33,11);
    units.emplace_back(unitLibrary[8],true,32,9);
    units.emplace_back(unitLibrary[8],true,31,6 );
    units.emplace_back(unitLibrary[8],true,19,13 );

    units.emplace_back(unitLibrary[9],true,20,12);

    //Russian Warship which ought to go fuck itself
    units.emplace_back(unitLibrary[4],false,32,3);
    units.emplace_back(unitLibrary[4],false,28,23);
    //Yankee destroyer spam
    units.emplace_back(unitLibrary[3],false,8,23);
    units.emplace_back(unitLibrary[3],false,9,23);
    units.emplace_back(unitLibrary[3],false,10,23);
    units.emplace_back(unitLibrary[3],false,11,23);
    units.emplace_back(unitLibrary[3],false,12,23);
    units.emplace_back(unitLibrary[3],false,13,23);
    units.emplace_back(unitLibrary[3],false,14,23);
    units.emplace_back(unitLibrary[3],false,15,23);
    units.emplace_back(unitLibrary[3],false,16,23);
    units.emplace_back(unitLibrary[3],false,8,22);
    units.emplace_back(unitLibrary[3],false,9,22);
    units.emplace_back(unitLibrary[3],false,10,22);
    units.emplace_back(unitLibrary[3],false,11,22);
    units.emplace_back(unitLibrary[3],false,12,22);
    units.emplace_back(unitLibrary[3],false,14,22);
    aiMovementClient.addPatrolHex(99);
    aiMovementClient.addPatrolHex(179);
    aiMovementClient.addPatrolHex(554);
    aiMovementClient.addPatrolHex(521);
    aiMovementClient.addPatrolHex(332);
    aiMovementClient.addPatrolHex(563);
    aiMovementClient.addPatrolHex(95);
    aiMovementClient.addPatrolHex(207);
    aiMovementClient.addPatrolHex(359);
    aiMovementClient.addPatrolHex(472);
    aiMovementClient.addPatrolHex(665);
    aiMovementClient.addPatrolHex(587);
    aiMovementClient.addPatrolHex(404);
    aiMovementClient.addPatrolHex(215);
    aiMovementClient.addPatrolHex(393);
    aiMovementClient.addPatrolHex(775);


    std::cout<<"Verifying screen dimensions"<<std::endl;
    scenarioWidthPx=grid.getScenarioWidth();
    scenarioHeightPx=grid.getScenarioHeight();

    currentPhase=MOVEMENT_PLANNING;

    scale=1.0;


    movementPlanningDescription="Right click to select a unit, then right click to move\nPress enter or \"execute\" to execute the plan\nRight click a friendly unit for more details\n\nFriendly units are highlighted with Green";
    movementExecutionDescription="Executing movement plans&please wait";
    attackPlanningDescription="Right click to select a unit, left click to give attack order\nPress enter or \"execute\" to execute the plans";
    attackExecutionDescription="Executing attack plans\n&press space to pause/unpause or replay";

    myGui.setInfoScreenText(movementPlanningDescription,renderer);

    std::cout<<"Updating locations of all units"<<std::endl;
    //Update animation of friendly and hostile units
    for (auto & U : units) {
        //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
        const int hexX = U.getHexX();
        const int hexY = U.getHexY();

        const hexTile& unitTile = grid.getHexTile(hexX, hexY);

        U.setX(unitTile.getHexCenterX());
        U.setY(unitTile.getHexCenterY());

    }



    std::cout<< " constructor finished"<<std::endl;

}

scenario::~scenario() = default;


void scenario::render(SDL_Renderer* renderer, int mouseX, int mouseY, bool shiftKey, uint32_t millis) const {

    background.render(0,0,renderer,scale);

    if (myGui.doShowHexOutline())
        grid.drawAllTiles(renderer,scale);

    if (currentPhase==MOVEMENT_PLANNING) {
        //Show the tile the mouse is over
        grid.drawTile(renderer,mouseOverTile,scale);


        //Display how far we can move, and how far our effect range is
        if (selectedUnit!=-1 && selectedTile!=-1) {

            if (units[selectedUnit].getEffectRange()>0 && units[selectedUnit].getHp()>0) {
                //I assume units either have population, storage, or power generation, not all at once
                //Yellow for power
                if (units[selectedUnit].getProducesPower())
                    grid.drawTiles(renderer,units[selectedUnit].getEffectHexes(),scale,hexGrid::COLOR,255,255,0);
                //Orange for population
                else if (units[selectedUnit].getHasPopulation())
                    grid.drawTiles(renderer,units[selectedUnit].getEffectHexes(),scale,hexGrid::COLOR,255,125,125);
                //TODO blue for storage exchange
            }

            //TODO: DO NOT RECALCULATE THIS EVERY FRAME
            std::set<int> obstructed;
            //We get obstructed by the current position of units, and by their destinations
            for (const unit& u : units) {
                obstructed.insert(grid.getHexId(u.getHexX(),u.getHexY()));
            }
            for (const auto &[fst, snd]: movementPlans ) {
                if (!snd.empty() && fst!=selectedUnit) {
                    obstructed.insert(snd.back());
                }
            }

            const std::set<int> tilesInMovementRange=grid.getNeighbours(selectedTile,units[selectedUnit].getMovementPoints(),obstructed);
            grid.drawTiles(renderer,tilesInMovementRange,scale,hexGrid::COLOR);

            const std::vector<int> line = grid.findPath(selectedTile,mouseOverTile,obstructed,units[selectedUnit].getMovementPoints());
            grid.drawPath(renderer,line,scale);
        }

        //Draw all planned movement
        for (const auto &userPlan: movementPlans) {
            if (units[userPlan.first].isFriendly())
                grid.drawPath(renderer,userPlan.second,scale);
        }

        {
            if (myGui.doShowPowerRange()) {
                grid.drawTiles(renderer,friendlyPoweredHexes,scale,hexGrid::COLOR,255,255,0);
                //todo debug only, remove this
                grid.drawTiles(renderer,enemyPoweredHexes,scale,hexGrid::COLOR,255,255,0);
            }
            if (myGui.doShowPopulationRange()) {
                grid.drawTiles(renderer,friendlyPopulatedHexes,scale,hexGrid::COLOR,255,125,125);
                //todo debug only, remove this
                grid.drawTiles(renderer,enemyPopulatedHexes,scale,hexGrid::COLOR,255,125,125);
            }
        }

        for (int i = 0; i < units.size(); i++) {
            const unit& U = units[i];
            grid.drawTile(renderer,grid.getHexId(U.getHexX(),U.getHexY()),scale,hexGrid::COLOR,U.isFriendly()?128:255,U.isFriendly()? 255:128,128,255);
            U.render(scale,millis,renderer,hpMarker,noPowerMarker,noPeopleMarker,visibleMarker);

            if (myGui.doShowSSMRange() || i == selectedUnit) {
                //Show SSM range
                double ssmRange = U.getSSMRange();
                if (ssmRange>0)
                    drawCircle(U.getX(), U.getY(), ssmRange, scale,255,0,0,i == selectedUnit ?128:64, renderer);
            }
            if (myGui.doShowSAMRange() || i == selectedUnit) {
                //Show SAM range
                double samRange = U.getSAMRange();
                if (samRange>0)
                    drawCircle(U.getX(), U.getY(), samRange, scale,255,255,0,i == selectedUnit ?128:64, renderer);
            }
            //TODO add gui option to show radar range
            {
                drawCircle(U.getX(), U.getY(), visualDetectionRange, scale,0,255,0,i == selectedUnit ?128:64, renderer);
                double radarRange = U.getRadarRange();
                if (radarRange>0 && U.hasRadarOn() && U.getHp()>0)
                    drawCircle(U.getX(), U.getY(), radarRange, scale,0,255,0,i == selectedUnit ?128:64, renderer);
            }
        }
    }
    else if (currentPhase==MOVEMENT_EXECUTION) {

        {
            if (myGui.doShowPowerRange()) {
                grid.drawTiles(renderer,friendlyPoweredHexes,scale,hexGrid::COLOR,255,255,0);
                //todo debug
                grid.drawTiles(renderer,enemyPoweredHexes,scale,hexGrid::COLOR,255,255,0);
            }
            if (myGui.doShowPopulationRange()) {
                grid.drawTiles(renderer,friendlyPopulatedHexes,scale,hexGrid::COLOR,255,125,125);
                //todo debug
                grid.drawTiles(renderer,enemyPopulatedHexes,scale,hexGrid::COLOR,255,125,125);
            }
        }


        //Show the tile the mouse is over
        grid.drawTile(renderer,mouseOverTile,scale);

        for (const auto & U : units) {
            U.render(scale,millis,renderer,hpMarker,noPowerMarker,noPeopleMarker,visibleMarker);

            if (myGui.doShowSSMRange()) {
                //Show SSM range
                double ssmRange = U.getSSMRange();
                if (ssmRange>0)
                    drawCircle(U.getX(), U.getY(), ssmRange, scale,255,0,0,64, renderer);
            }
            if (myGui.doShowSAMRange()) {
                //Show SAM range
                double samRange = U.getSAMRange();
                if (samRange>0)
                    drawCircle(U.getX(), U.getY(), samRange, scale,255,255,0,64, renderer);
            }
        }

    }
    else if (currentPhase==ATTACK_PLANNING) {
        {
            if (myGui.doShowPowerRange()) {
                grid.drawTiles(renderer,friendlyPoweredHexes,scale,hexGrid::COLOR,255,255,0);
                //todo debug
                grid.drawTiles(renderer,enemyPoweredHexes,scale,hexGrid::COLOR,255,255,0);
            }
            if (myGui.doShowPopulationRange()) {
                grid.drawTiles(renderer,friendlyPopulatedHexes,scale,hexGrid::COLOR,255,125,125);
                //todo debug
                grid.drawTiles(renderer,enemyPopulatedHexes,scale,hexGrid::COLOR,255,125,125);
            }
        }


        grid.drawTile(renderer,mouseOverTile,scale);
        for (int i = 0; i < units.size(); i++) {
            const unit& U = units[i];
            if (i != selectedUnit || millis%500<250)
                grid.drawTile(renderer,grid.getHexId(U.getHexX(),U.getHexY()),scale,hexGrid::COLOR,U.isFriendly()?128:255,U.isFriendly()? 255:128,128,255);
            U.render(scale,millis,renderer,hpMarker,noPowerMarker,noPeopleMarker,visibleMarker);

            if (myGui.doShowSSMRange() || i == selectedUnit) {
                //Show SSM range
                double ssmRange = U.getSSMRange();
                if (ssmRange>0) {
                    drawCircle(U.getX(), U.getY(), ssmRange, scale,255,0,0,i == selectedUnit ?128:64, renderer);
                }
            }
            if (myGui.doShowSAMRange() || i == selectedUnit) {
                //Show SAM range
                double samRange = U.getSAMRange();
                if (samRange>0)
                    drawCircle(U.getX(), U.getY(), samRange, scale,255,255,0,i == selectedUnit ?128:64, renderer);
            }
        }


        for (const auto& unitAttackPlan : attackPlans) {
            for (int i = 0; i < unitAttackPlan.second.size(); i++ ) {
                const auto& attackPlan = unitAttackPlan.second[i];
                attackPlan.render(renderer,scale,i==selectedAttackPlan && unitAttackPlan.first==selectedUnit);
            }
        }


        bool hasShownGreenLine=false;
        //Show the range of the currently active attack plan, centered on said plan
        if (selectedAttackPlan!=-1 && attackPlans.contains(selectedUnit) && attackPlans.at(selectedUnit).size()>selectedAttackPlan)
        {
            const auto& selectedPlan = attackPlans.at(selectedUnit)[selectedAttackPlan];
            const auto plan_end = selectedPlan.getEndNode();

            size_t nnodes = selectedPlan.getNodes();

            double range = units[selectedUnit].getSSMRange()-selectedPlan.getLength();

            drawCircle(plan_end.first, plan_end.second, range, scale,255,0,0,128, renderer);


            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            double dist = sqrt(pow(plan_end.first-mouseX/scale,2)+pow(plan_end.second-mouseY/scale,2));
            if (dist<range && nnodes<units[selectedUnit].getSSMNodes()) {
                shiftMarker.render(mouseX,mouseY,renderer,scale,false,false,2,shiftKey?1:0);
                //Draw a little green line, showing us where a potential attack plan may go
                if (shiftKey) {
                    hasShownGreenLine=true;
                    SDL_RenderDrawLine(renderer, scale*plan_end.first,scale*plan_end.second,mouseX,mouseY);
                }
            }
        }

        //Draw a little green line, showing us where a potential attack plan may go, from the unit itself
        if (selectedUnit!=-1 && !hasShownGreenLine && (!attackPlans.contains(selectedUnit) || units[selectedUnit].getSSMSalvoSize()>attackPlans.at(selectedUnit).size())) {

            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            double dist = sqrt(pow(units[selectedUnit].getX()-mouseX/scale,2)+pow(units[selectedUnit].getY()-mouseY/scale,2));
            if (dist<units[selectedUnit].getSSMRange())
                SDL_RenderDrawLine(renderer, scale*units[selectedUnit].getX(),scale*units[selectedUnit].getY(),mouseX,mouseY);
        }
    }
    else if (currentPhase==ATTACK_EXECUTION) {
        {
            if (myGui.doShowPowerRange()) {
                grid.drawTiles(renderer,friendlyPoweredHexes,scale,hexGrid::COLOR,255,255,0);
                //todo debug
                grid.drawTiles(renderer,enemyPoweredHexes,scale,hexGrid::COLOR,255,255,0);
            }
            if (myGui.doShowPopulationRange()) {
                grid.drawTiles(renderer,friendlyPopulatedHexes,scale,hexGrid::COLOR,255,125,125);
                //todo debug
                grid.drawTiles(renderer,enemyPopulatedHexes,scale,hexGrid::COLOR,255,125,125);
            }
        }



        for (int i = 0; i < units.size(); i++) {
            const unit& U = units[i];
            U.render(scale,millis,renderer,hpMarker,noPowerMarker,noPeopleMarker,visibleMarker);

            if (myGui.doShowSSMRange() || i == selectedUnit) {
                //Show SSM range
                double ssmRange = U.getSSMRange();
                if (ssmRange>0)
                    drawCircle(U.getX(), U.getY(), ssmRange, scale,255,0,0,64, renderer);
            }
            if (myGui.doShowSAMRange() || i == selectedUnit) {
                //Show SAM range
                double samRange = U.getSAMRange();
                if (samRange>0)
                    drawCircle(U.getX(), U.getY(), samRange, scale,255,255,0,64, renderer);
            }
        }

        if (attackExecutionState==PLAYING) {
            //Loop through all attack plans and display them
            myCake.render(attackExecutionPlaybackTimer,flyingSSM,renderer,scale,millis);
        }

    }

    //Particles render regardless of the phase, and render above units
    for (const auto& particle : smokeParticles) {
        smokeParticleTexture.render(particle.x*scale,particle.y*scale,renderer,scale,true,false,4,std::min(3,(4*particle.ageMs)/smokeParticleLifetimeMs));
    }
    for (const auto& particle : splashParticles) {
        splashParticleTexture.render(particle.x*scale,particle.y*scale,renderer,scale,true,false,4,std::min(3,(4*particle.ageMs)/splashParticleLifetimeMs));
    }
    for (const auto& particle : crashParticles) {
        crashParticleTexture.render(particle.x*scale,particle.y*scale,renderer,scale,true,false,4,std::min(3,(4*particle.ageMs)/crashParticleLifetimeMs));
    }
    for (const auto& particle : hitTargetParticles) {
        hitTargetTexture.render(particle.x*scale,particle.y*scale,renderer,scale,true,false,4,std::min(3,(4*particle.ageMs)/hitTargetParticleLifetimeMs));
    }
    for (const auto& particle : interceptParticles) {
        interceptTexture.render(particle.x*scale,particle.y*scale,renderer,scale,true,false,4,std::min(3,(4*particle.ageMs)/interceptParticleLifetimeMs));
    }



    myGui.render(scenarioWidthPx,scenarioHeightPx,renderer,scale,millis,currentPhase,currentPhase==ATTACK_EXECUTION && attackExecutionState==FINISHED);

    //Render some phase dependent gui elements on top
    if (currentPhase==ATTACK_EXECUTION)
        myGui.renderAttackExecution(scenarioWidthPx,scenarioHeightPx,mouseX,mouseY,renderer,scale,attackExecutionPlaybackTimer,attackExecutionPlaybackMaxTime,pauseAttackExecutionPlayback);
    if (currentPhase==ATTACK_PLANNING)
        myGui.renderAttackPlanning(scenarioWidthPx,scenarioHeightPx,mouseX,mouseY,renderer,scale,attackPlans,selectedUnit,selectedAttackPlan);


    //for debugging only
    //aiMovementClient.render(grid,renderer,scale);
}

void scenario::updateVisibility() {
    //First set everything to undetected
    for (unit& U : units) {
        U.setVisible(U.getFiredWithoutMoving());
    }


    for (int i = 0; i < units.size(); i++) {
        unit& U = units[i];
        for (int j = i+1; j < units.size(); j++) {
            unit& V = units[j];
            //Only opposing units detect each other
            if (V.isFriendly()!=U.isFriendly()) {
                double dist = sqrt(pow(U.getX()-V.getX(),2)+pow(U.getY()-V.getY(),2));
                if (dist<=visualDetectionRange) {
                    V.setVisible(true);
                    U.setVisible(true);
                    }

                //U has an active radar
                if (U.getHp()>0 && U.hasRadarOn()) {
                    //U detects V
                    if (dist<=U.getRadarRange()) {
                        V.setVisible(true);
                    }
                    //Radars are visible at twice their range
                    if (dist<=U.getRadarRange()*2) {
                        U.setVisible(true);
                    }
                }
                if (V.getHp()>0 && V.hasRadarOn()) {
                    //V detects U
                    if (dist<=V.getRadarRange()) {
                        U.setVisible(true);
                    }
                    //Radars are visible at twice their range
                    if (dist<=V.getRadarRange()*2) {
                        V.setVisible(true);
                    }
                }
            }

        }

    }

}



void scenario::update(SDL_Renderer* renderer, int screenWidth, int screenHeight,  int mouseX, int mouseY, bool isLeftMouseClick, bool isRightMouseClick, bool executeClick, bool shiftKey, bool playbuttonClick, int scrollwheel, uint32_t millis, uint32_t dmillis) {
    scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx+gui::getRightBarPixels()),
                     static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx+gui::getBottomBarPixels()));

    mouseOverTile=grid.getHexFromLocation(mouseX,mouseY,scale);

    if (currentPhase==MOVEMENT_PLANNING) {

        if (!hasCalculatedMovementConstants) {
            //Update factories, powerplants, cities, and such

            //Update everyone's effects
            for (unit& u : units) {
            //const std::set<int> tilesInMovementRange=grid.getNeighbours(selectedTile,units[selectedUnit].getMovementPoints(),obstructed);

                std::set<int> noObstruction={};
                u.setEffectHexes(grid.getNeighbours(grid.getHexId(u.getHexX(),u.getHexY()),u.getEffectRange(),noObstruction));
            }
            friendlyPopulatedHexes.clear();
            friendlyPoweredHexes.clear();
            enemyPopulatedHexes.clear();
            enemyPoweredHexes.clear();

            for (unit& u : units) {
                const auto& effect = u.getEffectHexes();
                if (u.getProducesPower() && u.getHp()>0) {
                    if (u.isFriendly()) {
                        std::set<int> Union;
                        std::set_union(effect.begin(),effect.end(),friendlyPoweredHexes.begin(),friendlyPoweredHexes.end(),std::inserter(Union,Union.begin()));
                        friendlyPoweredHexes.swap(Union);
                    }
                    else {
                        std::set<int> Union;
                        std::set_union(effect.begin(),effect.end(),enemyPoweredHexes.begin(),enemyPoweredHexes.end(),std::inserter(Union,Union.begin()));
                        enemyPoweredHexes.swap(Union);
                    }
                }
                if (u.getHasPopulation() && u.getHp()>0) {
                    if (u.isFriendly()) {
                        std::set<int> Union;
                        std::set_union(effect.begin(),effect.end(),friendlyPopulatedHexes.begin(),friendlyPopulatedHexes.end(),std::inserter(Union,Union.begin()));
                        friendlyPopulatedHexes.swap(Union);
                    }
                    else {
                        std::set<int> Union;
                        std::set_union(effect.begin(),effect.end(),enemyPopulatedHexes.begin(),enemyPopulatedHexes.end(),std::inserter(Union,Union.begin()));
                        enemyPopulatedHexes.swap(Union);
                    }
                }
            }


            for (unit& u : units) {
                int hexID = grid.getHexId(u.getHexX(),u.getHexY());
                if (u.isFriendly()) {
                    u.setPower(friendlyPoweredHexes.contains(hexID));
                    u.setPopulation(friendlyPopulatedHexes.contains(hexID));
                }
                else {
                    u.setPower(enemyPoweredHexes.contains(hexID));
                    u.setPopulation(enemyPopulatedHexes.contains(hexID));
                }
            }

            updateVisibility();

            std::cout <<"Calculating AI movement"<< std::endl;
            aiMovementClient.makeAIMovementPlans(grid,units,movementPlans);
            std::cout <<"Calculating effect hexes"<< std::endl;




            hasCalculatedMovementConstants=true;
        }


        //Right click to select units, or give movement order
        if (isRightMouseClick) {
            //TODO, this is debug remove this
            int mouseOverHexX = 0;
            int mouseOverHexY = 0;
            grid.getHexXYs(mouseOverTile,mouseOverHexX,mouseOverHexY);
            std::cout<<mouseOverTile<<" ("<<mouseOverHexX<<","<<mouseOverHexY<<")"<<std::endl;

            //See if there is a new unit to select
            int newSelectedUnit=-1;

            for (int i = 0; i < units.size(); i++) {
                if (grid.getHexId(units[i].getHexX(),units[i].getHexY())==mouseOverTile) {
                    selectedTile = mouseOverTile;
                    newSelectedUnit = i;
                    units[i].doReadyAttack();
                }
            }
            if (newSelectedUnit != -1) {
                //Deselect selected unit
                if (selectedUnit!=-1) {
                    if (selectedUnit != newSelectedUnit) {
                        units[selectedUnit].unreadyAttack();
                        selectedUnit=newSelectedUnit;
                        myGui.setInfoScreenText(units[selectedUnit].getDescription(),renderer);
                    }
                    else if (units[selectedUnit].isFriendly()){
                        //Click the same unit to cancel movement order, if it is a friendly unit
                        units[selectedUnit].unreadyAttack();
                        if (movementPlans.contains(selectedUnit))
                            movementPlans.erase(selectedUnit);
                        selectedUnit = -1;
                        myGui.setInfoScreenText(movementPlanningDescription,renderer);
                    }
                }
                else {
                    selectedUnit=newSelectedUnit;
                    myGui.setInfoScreenText(units[selectedUnit].getDescription(),renderer);
                }
            }
            else if (selectedUnit==-1 || units[selectedUnit].isFriendly()){
                //You clicked somewhere else, while a unit was selected this is a movement command
                if (selectedUnit!=-1) {
                    units[selectedUnit].unreadyAttack();

                    //I am pretty sure this has already been set
                    if (selectedTile == -1) {
                        selectedUnit = grid.getHexId(units[selectedUnit].getHexX(),units[selectedUnit].getHexY());
                    }

                    std::set<int> obstructed;
                    //We get obstructed by the current position of units, and by their destinations
                    for (const unit& u : units) {
                        obstructed.insert(grid.getHexId(u.getHexX(),u.getHexY()));
                    }
                    for (const auto &plans: movementPlans ) {
                        if (!plans.second.empty() && plans.first!=selectedUnit) {
                            obstructed.insert(plans.second.back());
                        }
                    }


                    auto fullPath =grid.findPath(selectedTile,mouseOverTile,obstructed,units[selectedUnit].getMovementPoints());
                    if (movementPlans.contains(selectedUnit)) {
                        movementPlans.at(selectedUnit)=fullPath ;
                    }
                    else
                        movementPlans.insert(std::make_pair(selectedUnit,fullPath ));

                    selectedUnit=-1;

                    myGui.setInfoScreenText(attackPlanningDescription,renderer);
                }
            }
        }

        //Left click cancels selection
        if (isLeftMouseClick) {
            if (selectedUnit != -1) {
                units[selectedUnit].unreadyAttack();
                selectedUnit = -1;
                myGui.setInfoScreenText(movementPlanningDescription,renderer);
            }
            selectedTile=-1;
        }


        //Update animation of friendly and hostile units
        for (auto & U : units) {
            //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
            const int hexX = U.getHexX();
            const int hexY = U.getHexY();

            const hexTile& unitTile = grid.getHexTile(hexX, hexY);

            U.setX(unitTile.getHexCenterX());
            U.setY(unitTile.getHexCenterY());

        }


        if (executeClick || myGui.isExecuteButtonPressed()) {
            currentPhase=MOVEMENT_EXECUTION;
            selectedUnit=-1;
            selectedTile=-1;
            hasCalculatedMovementConstants=false;
            myGui.setInfoScreenText(movementExecutionDescription,renderer);

            for (const auto &unit: movementPlans | std::views::keys) {
                units[unit].setFiredWithoutMoving(false);
            }


            //Remove any empty plans which got added
            std::erase_if(movementPlans, [](const auto& userPlan) {
                return userPlan.second.empty();
            });
        }
    }
    else if (currentPhase == MOVEMENT_EXECUTION) {

        updateVisibility();

        //How many units have NOT finished their movements yet
        int pendingUnits=0;

        //Update animation of units, friends as well as foes
        for (int i = 0; i < units.size(); i++) {
            auto& U = units[i];
            U.unreadyAttack();
            {
                if (U.getAnimationPhase()!=unitType::MOVE || !movementPlans.contains(i)) {
                    //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
                    const int hexX = U.getHexX();
                    const int hexY = U.getHexY();
                    const hexTile& unitTile = grid.getHexTile(hexX, hexY);

                    U.setX(unitTile.getHexCenterX());
                    U.setY(unitTile.getHexCenterY());

                    if (movementPlans.contains(i)) {
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
                    const auto& path = movementPlans.at(i);

                    //Have we arrived at our destination?
                    if (progress+1>=path.size()) {

                        int hexX=0;
                        int hexY=0;
                        //We can SAFELY ASSUME the path is not empty, because we removed empty movement plans
                        grid.getHexXYs(path.back(),hexX, hexY);
                        U.setHexX(hexX);
                        U.setHexY(hexY);

                        const hexTile& unitTile = grid.getHexTile(hexX, hexY);

                        U.setX(unitTile.getHexCenterX());
                        U.setY(unitTile.getHexCenterY());

                        movementPlans.erase(i);
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

                        double xbefore=hexBeforeTile.getHexCenterX();
                        double xafter=hexAfterTile.getHexCenterX();
                        U.setX(xbefore*(1-fac)+xafter*fac);
                        U.setY(hexBeforeTile.getHexCenterY()*(1-fac)+hexAfterTile.getHexCenterY()*fac);
                        if (hexAfterId!=hexBeforeId)
                            U.setFlip(xbefore<xafter);
                    }
                }
            }
        }
        if (pendingUnits==0) {
            currentPhase=ATTACK_PLANNING;
            hasCalculatedAttackConstants=false;
            updateVisibility();
            selectedAttackPlan=-1;
            selectedUnit=-1;
            selectedTile=-1;
            myGui.setInfoScreenText(attackPlanningDescription,renderer);
            movementPlans.clear();
        }
        std::cout<<"End loop movement execution"<<std::endl;
    }
    else if (currentPhase == ATTACK_PLANNING) {

        if (!hasCalculatedAttackConstants) {
            calculateEnemyAttackPlans(renderer);
            hasCalculatedAttackConstants=true;
        }

        //Right click to select units
        if (isRightMouseClick) {
            //See if there is a new unit to select
            int newSelectedUnit=-1;

            for (int i = 0; i < units.size(); i++) {
                if (grid.getHexId(units[i].getHexX(),units[i].getHexY())==mouseOverTile) {
                    selectedTile = mouseOverTile;
                    newSelectedUnit = i;
                    units[i].doReadyAttack();
                }
            }
            if (newSelectedUnit != -1) {
                //Deselect selected unit
                if (selectedUnit!=-1) {
                    if (selectedUnit != newSelectedUnit) {
                        units[selectedUnit].unreadyAttack();
                        selectedUnit=newSelectedUnit;
                        selectedAttackPlan=-1;
                        myGui.setInfoScreenText(units[selectedUnit].getDescription(),renderer);
                    }
                }
                else {
                    selectedUnit=newSelectedUnit;
                    selectedAttackPlan=-1;
                    myGui.setInfoScreenText(units[selectedUnit].getDescription(),renderer);
                }
            }
            else {
                if (selectedUnit!=-1)
                    units[selectedUnit].unreadyAttack();
                selectedUnit=-1;
                selectedAttackPlan=-1;
                myGui.setInfoScreenText(attackPlanningDescription,renderer);
            }
        }

        //Left click to add new attack plan, or modify existing
        if (isLeftMouseClick) {
            //Obviously only possible if somebody is selected
            if (selectedUnit!=-1 && units[selectedUnit].isFriendly()) {
                //We will add a new plan, if no plan is currently selected, or the selected plan has max number of nodes
                if (!shiftKey || selectedAttackPlan==-1 || !attackPlans.contains(selectedUnit) || attackPlans[selectedUnit].size()<selectedAttackPlan || attackPlans[selectedUnit][selectedAttackPlan].getNodes()>=units[selectedUnit].getSSMNodes()) {

                    double destinationX = mouseX/scale;
                    double destinationY = mouseY/scale;

                    //Add a new attack plan from this unit
                    double sourceX = units[selectedUnit].getX();
                    double sourceY = units[selectedUnit].getY();

                    //Check if the new distance is outside range
                    const double range = sqrt(pow(destinationX-sourceX,2)+pow(destinationY-sourceY,2));
                    if (range<units[selectedUnit].getSSMRange()) {
                        if (!attackPlans.contains(selectedUnit))
                            attackPlans.emplace(selectedUnit,std::vector<attackPlan>());

                        //Check that we are not above the salvo size
                        //TODO check ammo
                        if (attackPlans[selectedUnit].size()<units[selectedUnit].getSSMSalvoSize()) {
                            attackPlans[selectedUnit].emplace_back(selectedUnit,sourceX,sourceY,destinationX,destinationY,renderer,inGameFont,units[selectedUnit].isFriendly());
                            selectedAttackPlan=attackPlans[selectedUnit].size()-1;
                        }
                    }
                }
                else {
                    double destinationX = mouseX/scale;
                    double destinationY = mouseY/scale;
                    attackPlans[selectedUnit][selectedAttackPlan].addNode(destinationX,destinationY,units[selectedUnit].getSSMRange(),renderer,inGameFont);
                }
            }
        }


        //Scroll to adjust the launch timing of the selected attack plan in 1 second intervals
        if (scrollwheel!=0) {
            if (selectedAttackPlan!=-1 && selectedUnit!=-1 && units[selectedUnit].isFriendly()&& attackPlans.contains(selectedUnit) && attackPlans[selectedUnit].size()>selectedAttackPlan) {
                attackPlans[selectedUnit][selectedAttackPlan].modifyLaunchTime(scrollwheel,renderer,inGameFont);
            }
        }

        if (selectedUnit!=-1 && units[selectedUnit].isFriendly()) {
            //Mouse over element in the gui to select it
            int newSelectedPlan = myGui.getSelectedAttackPlan(scenarioWidthPx,scenarioHeightPx,mouseX,mouseY,scale,attackPlans,selectedUnit,selectedAttackPlan);
            if (newSelectedPlan != -1) {
                selectedAttackPlan=newSelectedPlan;
                //Click to delete
                if (isLeftMouseClick || isRightMouseClick) {
                    //If we got here, we know the plan exists alright
                    attackPlans[selectedUnit].erase(attackPlans[selectedUnit].begin()+newSelectedPlan);
                    selectedAttackPlan=-1;
                }
            }
        }




        if (executeClick || myGui.isExecuteButtonPressed()) {
            currentPhase=ATTACK_EXECUTION;
            selectedUnit=-1;
            selectedTile=-1;
            selectedAttackPlan=-1;
            myGui.setInfoScreenText(attackExecutionDescription,renderer);
            attackExecutionPlaybackTimer=0.0;
            attackExecutionPlaybackMaxTime=0.0;
            attackExecutionState=UNSTARTED;
            pauseAttackExecutionPlayback=false;
        }
    }
    else if (currentPhase == ATTACK_EXECUTION) {

        if (attackExecutionState==UNSTARTED) {
            //Before we do anything, we need all units, which need to make an attack, to ready for attack
            int unreadyUnits=0;

            for (const auto &unitWithPlan: attackPlans | std::views::keys) {
                if (units[unitWithPlan].getAnimationPhase()!=unitType::READY) {
                    unreadyUnits++;
                    units[unitWithPlan].doReadyAttack();
                }
            }
            if (unreadyUnits==0) {
                attackExecutionState=PLAYING;

                myCake.bake(grid,units,attackPlans);
                attackExecutionPlaybackTimer=0.0;
                attackExecutionPlaybackMaxTime=myCake.getEndTime();
                pauseAttackExecutionPlayback=false;
            }
        }
        if (attackExecutionState==PLAYING) {

            if (playbuttonClick || (myGui.isOverPauseButton(scenarioWidthPx,scenarioHeightPx,mouseX,mouseY,scale) && (isLeftMouseClick || isRightMouseClick)))
                pauseAttackExecutionPlayback=!pauseAttackExecutionPlayback;

            if (!pauseAttackExecutionPlayback)
                attackExecutionPlaybackTimer+=dmillis*0.001;

            myCake.spawnParticlesAndSound(smokeParticles,splashParticles,crashParticles,hitTargetParticles,interceptParticles,splashSound,crashOrInterceptSound,crashOrInterceptSound,hitTargetSound,missileSound,attackExecutionPlaybackTimer,missileSmokeSpawnRate,pauseAttackExecutionPlayback?0:dmillis);
            myCake.updateUnits(units,attackExecutionPlaybackTimer,millis);

            if (attackExecutionPlaybackTimer>attackExecutionPlaybackMaxTime) {
                //wait for the player to end this state, or re-play or whatever they feel like
                attackExecutionState=FINISHED;
            }
        }

        if (attackExecutionState==FINISHED) {

            if (playbuttonClick || (myGui.isOverPauseButton(scenarioWidthPx,scenarioHeightPx,mouseX,mouseY,scale) && (isLeftMouseClick || isRightMouseClick)))
            {
                pauseAttackExecutionPlayback=false;
                attackExecutionPlaybackTimer=0.0;
                attackExecutionState=PLAYING;
            }
            if (executeClick || myGui.isExecuteButtonPressed()) {
                currentPhase=MOVEMENT_PLANNING;
                selectedUnit=-1;
                selectedTile=-1;
                selectedAttackPlan=-1;
                myGui.setInfoScreenText(movementPlanningDescription,renderer);
                attackExecutionPlaybackTimer=0.0;
                attackExecutionPlaybackMaxTime=0.0;
                attackExecutionState=UNSTARTED;
                hasCalculatedMovementConstants=false;
                attackPlans.clear();
                myCake.clear();


                //Check if health is 0 for units, and swap in a new vector of units
                //I prefer to do it this way, rather than to erase(), because each erase requires a lot of copying
                //Also, erase requires copy assignments, which doesn't work with the unit class, since the unit class contains a const reference
                std::vector<unit> newUnits;
                for (unit& u : units) {
                    if (u.getHp()>0) {
                        newUnits.push_back(u);
                    }
                }
                units.swap(newUnits);

                for (unit& u : units)
                    u.unreadyAttack();
            }
        }
    }


    //Some updates happen regardless of the phase
    for (auto& particle : smokeParticles) {
        particle.x+=particle.vx*dmillis*0.001;
        particle.y+=particle.vy*dmillis*0.001;
        particle.ageMs+=dmillis;
    }


    for (auto& particle : splashParticles) {
        particle.x+=particle.vx*dmillis*0.001;
        particle.y+=particle.vy*dmillis*0.001;
        particle.ageMs+=dmillis;
    }
    for (auto& particle : crashParticles) {
        particle.x+=particle.vx*dmillis*0.001;
        particle.y+=particle.vy*dmillis*0.001;
        particle.ageMs+=dmillis;
    }
    for (auto& particle : hitTargetParticles) {
        particle.x+=particle.vx*dmillis*0.001;
        particle.y+=particle.vy*dmillis*0.001;
        particle.ageMs+=dmillis;
    }
    for (auto& particle : interceptParticles) {
        particle.x+=particle.vx*dmillis*0.001;
        particle.y+=particle.vy*dmillis*0.001;
        particle.ageMs+=dmillis;
    }

    while (!smokeParticles.empty() && smokeParticles.front().ageMs>smokeParticleLifetimeMs) {
        smokeParticles.pop_front();
    }
    while (!splashParticles.empty() && splashParticles.front().ageMs>splashParticleLifetimeMs) {
        splashParticles.pop_front();
    }
    while (!hitTargetParticles.empty() && hitTargetParticles.front().ageMs>hitTargetParticleLifetimeMs) {
        hitTargetParticles.pop_front();
    }
    while (!interceptParticles.empty() && interceptParticles.front().ageMs>interceptParticleLifetimeMs) {
        interceptParticles.pop_front();
    }
    while (!crashParticles.empty() && crashParticles.front().ageMs> crashParticleLifetimeMs) {
         crashParticles.pop_front();
    }

    for (unit& U: units) {
        U.updateAnimation(millis);
    }

    myGui.update(mouseX,mouseY,isLeftMouseClick || isRightMouseClick,scenarioWidthPx,scenarioHeightPx,scale,dmillis);
}

void scenario::calculateEnemyAttackPlans(SDL_Renderer* renderer) {
    for (int unitId = 0; unitId < units.size(); ++unitId) {
        unit& U = units[unitId];
        if (!U.isFriendly() && U.getHp()>0 && U.getSSMSalvoSize()>0) {
            //Ids of all potential targets, which are inside range and spotted
            std::vector<int> potentialTargets;

            for (int id = 0; id < units.size(); ++id) {
                //Only friendly units may be targeted
                if (units[id].isFriendly() && units[id].getHp()>0 && units[id].getVisible()) {
                    double x1 = units[id].getX();
                    double y1 = units[id].getY();
                    double x0 = U.getX();
                    double y0 = U.getY();
                    double dist = sqrt(pow(x0-x1,2)+pow(y0-y1,2));

                    if (dist<U.getSSMRange()) {
                        potentialTargets.emplace_back(id);
                    }
                }
            }

            //TODO, check ammo
            if (!potentialTargets.empty()) {
                if (!attackPlans.contains(unitId))
                    attackPlans.emplace(unitId,std::vector<attackPlan>());
                //Loop through all rockets in our salvo
                //TODO, check ammo
                for (int i = 0; i < U.getSSMSalvoSize(); ++i) {
                    std::uniform_int_distribution<> dist(0,potentialTargets.size()-1);
                    int targetID = potentialTargets[dist(generator)];

                    double sourceX = U.getX();
                    double sourceY = U.getY();
                    double destinationX = units[targetID].getX();
                    double destinationY = units[targetID].getY();

                    attackPlans[unitId].emplace_back(unitId,sourceX,sourceY,destinationX,destinationY,renderer,inGameFont,false);
                    attackPlans[unitId].back().modifyLaunchTime(i,renderer,inGameFont);
                }
            }
        }
    }
}
