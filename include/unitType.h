//
// Created by nikolaj on 9/20/25.
//

#ifndef PREMVPMAPGAME_UNITTYPE_H
#define PREMVPMAPGAME_UNITTYPE_H
#include "texwrap.h"
#include <filesystem>

namespace fs = std::filesystem;

///A particular unit type, with its basic stats, particular instances can be created of unit types
class unitType {
public:
    enum animationPhase {
        IDLE = 0,
        MOVE = 1,
        PREPARE = 2,
        READY=3,
        UNPREPARE=4,
    };

private:
    bool landUnit;
    texwrap texture;

    texwrap idle;
    texwrap move;
    texwrap prepare;
    texwrap ready;
    texwrap unprepare;

    unsigned int idle_frames;
    unsigned int move_frames;
    unsigned int prepare_frames;
    unsigned int ready_frames;
    unsigned int unprepare_frames;

public:
    unitType(bool landUnit, const fs::path& unitPath, SDL_Renderer* renderer);

    [[nodiscard]] bool isLandUnit() const { return landUnit; }

    [[nodiscard]] unsigned int getMsPerFrame() const {return 100;}

    void render(double x, double y,double scale,uint32_t millis, SDL_Renderer* renderer,animationPhase phase, bool flip) const;

    [[nodiscard]] bool isAnimationFinished(uint32_t millis,animationPhase phase) const;
};

#endif //PREMVPMAPGAME_UNITTYPE_H