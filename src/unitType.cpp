//
// Created by nikolaj on 9/20/25.
//

#include "unitType.h"

#include <fstream>
#include <iostream>

void unitType::render(double x, double y, double scale,uint32_t millis,SDL_Renderer *renderer, animationPhase phase,bool flip) const {

    const uint32_t MSPF = getMsPerFrame();
    const uint32_t frame = ((millis / MSPF));
    switch (phase) {
        case unitType::IDLE:
            //Looping idle animation
            idle.render(x,y,renderer,scale,true,flip,idle_frames,frame%idle_frames);
            break;
        case unitType::MOVE:
            //Looping move animation
            move.render(x,y,renderer,scale,true,flip,move_frames,frame%move_frames);
            break;
        case unitType::PREPARE:
            //Shall freeze on the last frame
            prepare.render(x,y,renderer,scale,true,flip,prepare_frames,std::min(frame,prepare_frames-1));
            break;
        case unitType::READY:
            //Looping ready animation
            ready.render(x,y,renderer,scale,true,flip,ready_frames,frame%ready_frames);
            break;
        case unitType::UNPREPARE:
            //Shall freeze on the last frame
            unprepare.render(x,y,renderer,scale,true,flip,unprepare_frames,std::min(frame,unprepare_frames-1));
            break;
        case unitType::DIE:
            //Shall freeze on the last frame
            die.render(x,y,renderer,scale,true,flip,die_frames,std::min(frame,die_frames-1));
            break;
    }

}

bool unitType::isAnimationFinished(uint32_t millis, animationPhase phase) const {
    uint32_t MSPF = getMsPerFrame();
    uint32_t frame = ((millis / MSPF));
    switch (phase) {
        default:
        case unitType::IDLE:
            return frame>=idle_frames;
        case unitType::MOVE:
            return frame>=move_frames;
        case unitType::PREPARE:
            return frame>=prepare_frames;
        case unitType::READY:
            return frame>=ready_frames;
        case unitType::UNPREPARE:
            return frame>=unprepare_frames;
        case unitType::DIE:
            return frame>=die_frames;
    }
}

unitType::unitType(const fs::path& unitPath, SDL_Renderer *renderer): texture((unitPath/"idle.png"), renderer), idle((unitPath/"idle.png"),renderer), move((unitPath/"move.png"),renderer), prepare((unitPath/"prepare.png"),renderer),ready((unitPath/"ready.png"),renderer), unprepare((unitPath/"unprepare.png"),renderer), die((unitPath/"die.png"),renderer) {
    std::ifstream animationStats(unitPath/"unitStats.txt");
    std::string line;

    idle_frames=1;
    move_frames=1;
    prepare_frames=1;
    ready_frames=1;
    unprepare_frames=1;
    die_frames=1;
    landUnit=true;
    movementPoints=3;

    SAMRange=0;
    SSMRange=0;

    while (std::getline(animationStats, line)) {
        std::stringstream ss(line);
        std::string tag;
        ss >> tag;
        if (tag=="idle") {
            ss>>idle_frames;
        }
        if (tag=="move") {
            ss >>move_frames;
        }
        if (tag=="prepare") {
            ss >> prepare_frames;
        }
        if (tag=="ready") {
            ss >> ready_frames;
        }
        if (tag=="unprepare") {
            ss >> unprepare_frames;
        }
        if (tag=="die") {
            ss >> die_frames;
        }
        if (tag=="movementPoints") {
            ss >> movementPoints;
        }
        if (tag=="landUnit") {
            std::string str;
            ss >> str;
            if (str=="true")
                landUnit = true;
            else
                landUnit = false;
        }
        if (tag=="name") {
            //A little circus with strings to get the name (which is the rest of the line)
            name="";
            ss >> name;
            std::string str;
            while (ss >> str)
                name += " "+str;
            std::cout << name << std::endl;
        }
        if (tag=="SAMRange") {
            ss >> SAMRange;
        }
        if (tag=="SSMRange") {
            ss >> SSMRange;
        }
        if (tag=="SSMSalvoSize") {
            ss >> SSMSalvoSize;
        }
        if (tag=="SSMNodes") {
            ss >> SSMNodes;
        }
        if (tag=="maxHp") {
            ss >> maxHp;
        }
        if (tag=="SAMDelay") {
            ss >> SAMDelay;
        }
        if (tag=="SAMReloadDelay") {
            ss >> SAMReloadDelay;
        }
        if (tag=="SAMSalvoSize") {
            ss >> SAMSalvoSize;
        }
        if (tag=="populationRange") {
            ss >> populationRange;
        }
        if (tag=="powerRange") {
            ss >> powerRange;
        }
    }

}

