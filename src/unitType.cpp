//
// Created by nikolaj on 9/20/25.
//

#include "unitType.h"

#include <fstream>
#include <iostream>

void unitType::render(double x, double y, double scale,uint32_t millis,SDL_Renderer *renderer, animationPhase phase) const {

    uint32_t MSPF = getMsPerFrame();
    uint32_t frame = ((millis / MSPF));
    switch (phase) {
        case unitType::IDLE:
            //Looping idle animation
            idle.render(x,y,renderer,scale,true,idle_frames,frame%idle_frames);
            break;
        case unitType::MOVE:
            //Looping move animation
            move.render(x,y,renderer,scale,true,move_frames,frame%move_frames);
            break;
        case unitType::PREPARE:
            //Shall freeze on the last frame
            prepare.render(x,y,renderer,scale,true,prepare_frames,std::min(frame,prepare_frames-1));
            break;
        case unitType::READY:
            //Looping ready animation
            ready.render(x,y,renderer,scale,true,ready_frames,frame%ready_frames);
            break;
        case unitType::UNPREPARE:
            //Shall freeze on the last frame
            unprepare.render(x,y,renderer,scale,true,unprepare_frames,std::min(frame,unprepare_frames-1));
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
    }
}

unitType::unitType(bool landUnit, fs::path unitPath, SDL_Renderer *renderer): landUnit(landUnit), texture(unitPath/"idle.png", renderer), idle(unitPath/"idle.png",renderer), move(unitPath/"move.png",renderer), prepare(unitPath/"prepare.png",renderer),ready(unitPath/"ready.png",renderer), unprepare(unitPath/"unprepare.png",renderer) {
    std::ifstream animationStats(unitPath/"animationstats.txt");
    std::string line;

    idle_frames=1;
    move_frames=1;
    prepare_frames=1;
    ready_frames=1;
    unprepare_frames=1;
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
    }

}

