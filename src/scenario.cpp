//
// Created by nikolaj on 9/16/25.
//

#include "scenario.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <ranges>
#include <SDL2/SDL_ttf.h>


void scenario::drawCircle(double x, double y, double radius, double scale, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer) const {
 //   circle10.render(x*scale,y*scale,r,g,b,a,renderer,scale*radius*0.2,true);
    circle10.render(x*scale,y*scale,r,g,b,a,renderer,scale*2*radius/circle10.getWidth(),true);
}

scenario::scenario(SDL_Renderer* renderer, TTF_Font* _font) : background(fs::path("assets")/"background.png",renderer), hexSelectionOutline(fs::path("assets")/"hexoutline.png",renderer),circle10(fs::path("assets")/"circle10.png",renderer), grid(fs::path("assets"),renderer), myGui(fs::path("assets")/"gui",renderer,_font), flyingSSM(fs::path("assets")/"physicsGraphics"/"SSM.png",renderer), smokeParticleTexture(fs::path("assets")/"physicsGraphics"/"smoke.png",renderer), myCake(time(NULL)),hpMarker(fs::path("assets")/"hitpoint.png",renderer){


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

    std::cout<<"Loading units"<<std::endl;
    //TODO: load from disk, and allow spawning
    units.clear();
    units.emplace_back(unitLibrary[0],true,20,8);
    units.emplace_back(unitLibrary[2],true,18,12);
    units.emplace_back(unitLibrary[4],false,20,16);
    units.emplace_back(unitLibrary[1],true,25,20);
    units.emplace_back(unitLibrary[1],true,32,15);
    units.emplace_back(unitLibrary[1],true,31,14);
    units.emplace_back(unitLibrary[3],true,10,23);
    units.emplace_back(unitLibrary[3],true,8,23);



    std::cout<<"Verifying screen dimensions"<<std::endl;
    scenarioWidthPx=grid.getScenarioWidth();
    scenarioHeightPx=grid.getScenarioHeight();

    currentPhase=MOVEMENT_PLANNING_FRIEND;

    scale=1.0;


    movementPlanningDescription="Right click to select a unit, then right click to move\nPress enter or \"execute\" to execute the plan\nRight click a friendly unit for more details\n\nFriendly units are highlighted with Green";
    movementExecutionDescription="Executing movement plans&please wait";
    attackPlanningDescription="Right click to select a unit, left click to give attack order\nPress enter or \"execute\" to execute the plans";
    attackExecutionDescription="Executing attack plans&please wait";

    myGui.setInfoScreenText(movementPlanningDescription,renderer);


    smokeParticles.emplace_back(200,200,0,0,0);

    std::cout<< " constructor finished"<<std::endl;
}

scenario::~scenario() = default;


void scenario::render(SDL_Renderer* renderer, int screenWidth, int screenHeight, uint32_t millis) const {

    //TODO, this is for debugging an unidentified crash bug, remove when the bug is found
 //   std::cout<<"render"<<std::endl;
    background.render(0,0,renderer,scale);

    if (myGui.doShowHexOutline())
        grid.drawAllTiles(renderer,scale);

    if (currentPhase==MOVEMENT_PLANNING_FRIEND) {
        //Show the tile the mouse is over
        grid.drawTile(renderer,mouseOverTile,scale);


        //Display how far we can move
        if (selectedUnit!=-1 && selectedTile!=-1) {

            //TODO: DO NOT RECALCULATE THIS EVERY FRAME
            std::set<int> obstructed;
            //We get obstructed by the current position of units, and by their destinations
            for (const unit& u : units) {
                obstructed.insert(grid.getHexId(u.getHexX(),u.getHexY()));
            }
            for (const auto &[fst, snd]: friendMovementPlans ) {
                if (!snd.empty() && fst!=selectedUnit) {
                    obstructed.insert(snd.back());
                }
            }

            const std::set<int> tilesNearSelection=grid.getNeighbours(selectedTile,units[selectedUnit].getMovementPoints(),obstructed);
            grid.drawTiles(renderer,tilesNearSelection,scale,hexGrid::COLOR);

            const std::vector<int> line = grid.findPath(selectedTile,mouseOverTile,obstructed);
            grid.drawPath(renderer,line,scale);
        }

        //Draw all planned movement
        for (const auto &val: friendMovementPlans | std::views::values) {
            grid.drawPath(renderer,val,scale);
        }


        for (int i = 0; i < units.size(); i++) {
            const unit& U = units[i];
            grid.drawTile(renderer,grid.getHexId(U.getHexX(),U.getHexY()),scale,hexGrid::COLOR,U.isFriendly()?128:255,U.isFriendly()? 255:128,128,255);
            U.render(scale,millis,renderer,hpMarker);

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
        }
    }
    else if (currentPhase==MOVEMENT_EXECUTION) {
        //Show the tile the mouse is over
        grid.drawTile(renderer,mouseOverTile,scale);

        for (const auto & U : units) {
            U.render(scale,millis,renderer,hpMarker);

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
        grid.drawTile(renderer,mouseOverTile,scale);
        for (int i = 0; i < units.size(); i++) {
            const unit& U = units[i];
            if (i != selectedUnit || millis%500<250)
                grid.drawTile(renderer,grid.getHexId(U.getHexX(),U.getHexY()),scale,hexGrid::COLOR,U.isFriendly()?128:255,U.isFriendly()? 255:128,128,255);
            U.render(scale,millis,renderer,hpMarker);

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


        for (const auto& unitAttackPlan : attackPlans | std::views::values) {
            for (const auto& attackPlan : unitAttackPlan) {
                //attackPlan.attackVectors[0];
                attackPlan.render(renderer,scale);
            }
        }


        //Show the range of the currently active attack plan, centered on said plan
        if (selectedAttackPlan!=-1 && attackPlans.contains(selectedUnit) && attackPlans.at(selectedUnit).size()>selectedAttackPlan)
        {
            const auto& selectedPlan = attackPlans.at(selectedUnit)[selectedAttackPlan];
            const auto plan_end = selectedPlan.getEndNode();

            double range = units[selectedUnit].getSSMRange()-selectedPlan.getLength();

            drawCircle(plan_end.first, plan_end.second, range, scale,255,0,0,128, renderer);
        }
    }
    else if (currentPhase==ATTACK_EXECUTION) {
        for (int i = 0; i < units.size(); i++) {
            const unit& U = units[i];
            U.render(scale,millis,renderer,hpMarker);

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



    myGui.render(scenarioWidthPx,scenarioHeightPx,renderer,scale,millis,currentPhase);

    if (currentPhase==ATTACK_EXECUTION)
        myGui.renderAttackExecution(scenarioWidthPx,scenarioHeightPx,renderer,scale,attackExecutionPlaybackTimer,attackExecutionPlaybackMaxTime);
}

void scenario::update(SDL_Renderer* renderer, int screenWidth, int screenHeight,  int mouseX, int mouseY, bool isLeftMouseClick, bool isRightMouseClick, bool executeClick, bool shiftKey, uint32_t millis, uint32_t dmillis) {
    scale = std::min(static_cast<double>(screenWidth) / static_cast<double>(scenarioWidthPx+gui::getRightBarPixels()),
                     static_cast<double>(screenHeight) / static_cast<double>(scenarioHeightPx+gui::getBottomBarPixels()));

    //TODO, this is for debugging an unidentified crash bug, remove when the bug is found
  //  std::cout<<"update"<<std::endl;

    mouseOverTile=grid.getHexFromLocation(mouseX,mouseY,scale);

    if (currentPhase==MOVEMENT_PLANNING_FRIEND) {

        //Right click to select units, or give movement order
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
                        myGui.setInfoScreenText(units[selectedUnit].getDescription(),renderer);
                    }
                    else {
                        //Click the same unit to cancel movement order
                        units[selectedUnit].unreadyAttack();
                        if (friendMovementPlans.contains(selectedUnit))
                            friendMovementPlans.erase(selectedUnit);
                        selectedUnit = -1;
                        myGui.setInfoScreenText(movementPlanningDescription,renderer);
                    }
                }
                else {
                    selectedUnit=newSelectedUnit;
                    myGui.setInfoScreenText(units[selectedUnit].getDescription(),renderer);
                }
            }
            else {
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
                    for (const auto &plans: friendMovementPlans ) {
                        if (!plans.second.empty() && plans.first!=selectedUnit) {
                            obstructed.insert(plans.second.back());
                        }
                    }


                    auto fullPath =grid.findPath(selectedTile,mouseOverTile,obstructed);
                    auto limitedPath =std::vector<int>();
                    for (int i = 0; i < fullPath.size() && i<units[selectedUnit].getMovementPoints()+1; i++)
                        limitedPath.push_back(fullPath[i]);

                    if (friendMovementPlans.contains(selectedUnit)) {
                        friendMovementPlans.at(selectedUnit)=limitedPath;
                    }
                    else
                        friendMovementPlans.insert(std::make_pair(selectedUnit,limitedPath));

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


        //Update animation of friendly and todo hostile units
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
            myGui.setInfoScreenText(movementExecutionDescription,renderer);
        }
    }
    else if (currentPhase == MOVEMENT_EXECUTION) {

        //How many units have NOT finished their movements yet
        int pendingUnits=0;

        //Update animation of units, friends as well as todo foes
        for (int i = 0; i < units.size(); i++) {
            auto& U = units[i];
            U.unreadyAttack();
            {
                if (U.getAnimationPhase()!=unitType::MOVE || !friendMovementPlans.contains(i)) {
                    //It is the scenario which is responsible for the grid, so we are responsible for getting the coordinates
                    const int hexX = U.getHexX();
                    const int hexY = U.getHexY();
                    const hexTile& unitTile = grid.getHexTile(hexX, hexY);

                    U.setX(unitTile.getHexCenterX());
                    U.setY(unitTile.getHexCenterY());

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

                        U.setX(unitTile.getHexCenterX());
                        U.setY(unitTile.getHexCenterY());

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
            selectedAttackPlan=-1;
            selectedUnit=-1;
            selectedTile=-1;
            myGui.setInfoScreenText(attackPlanningDescription,renderer);
            friendMovementPlans.clear();
        }
    }
    else if (currentPhase == ATTACK_PLANNING) {
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
            if (selectedUnit!=-1) {
                //We will add a new plan, if no plan is currently selected, or the selected plan has max number of nodes
                if (!shiftKey || selectedAttackPlan==-1 || !attackPlans.contains(selectedUnit) || attackPlans[selectedUnit].size()<selectedAttackPlan || attackPlans[selectedUnit][selectedAttackPlan].getNodes()>=units[selectedUnit].getSSMNodes()) {

                    double destinationX = mouseX/scale;
                    double destinationY = mouseY/scale;

                    //Add a new attack plan from this unit
                    double sourceX = units[selectedUnit].getX();
                    double sourceY = units[selectedUnit].getY();

                    //Check if the new distance is outside range
                    const double range = sqrt(pow(destinationX-sourceX,2)+pow(destinationY-sourceY,2));
                    if (range<units[selectedUnit].getSSMRange()*grid.getHexRadius()) {
                        if (!attackPlans.contains(selectedUnit))
                            attackPlans.emplace(selectedUnit,std::vector<attackPlan>());

                        //Check that we are not above the salvo size
                        if (attackPlans[selectedUnit].size()<units[selectedUnit].getSSMSalvoSize()) {
                            attackPlans[selectedUnit].emplace_back(selectedUnit,sourceX,sourceY,destinationX,destinationY,renderer,inGameFont);
                            selectedAttackPlan=attackPlans[selectedUnit].size()-1;
                        }
                    }
                }
                else {
                    double destinationX = mouseX/scale;
                    double destinationY = mouseY/scale;
                    attackPlans[selectedUnit][selectedAttackPlan].addNode(destinationX,destinationY,renderer,inGameFont);
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

            }
        }
        if (attackExecutionState==PLAYING) {
            attackExecutionPlaybackTimer+=dmillis*0.001;

            myCake.spawnParticles(smokeParticles,attackExecutionPlaybackTimer,missileSmokeSpawnRate,dmillis);
            myCake.updateUnits(units,attackExecutionPlaybackTimer,millis);

            if (attackExecutionPlaybackTimer>attackExecutionPlaybackMaxTime) {
                //wait for the player to end this state, or re-play or whatever they feel like
                attackExecutionState=FINISHED;
            }
        }
    }


    //Some updates happen regardless of the phase
    for (auto& particle : smokeParticles) {
        particle.x+=particle.vx*dmillis*0.001;
        particle.y+=particle.vy*dmillis*0.001;
        particle.ageMs+=dmillis;
    }

    while (!smokeParticles.empty() && smokeParticles.front().ageMs>smokeParticleLifetimeMs) {
        smokeParticles.pop_front();
    }

    for (unit& U: units) {
        U.updateAnimation(millis);
    }

    myGui.update(mouseX,mouseY,isLeftMouseClick || isRightMouseClick,scenarioWidthPx,scenarioHeightPx,scale,dmillis);
}