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
    std::string name;

    bool landUnit;
    ///Number of moves possible per turn
    int movementPoints;

    texwrap texture;

    texwrap idle;
    texwrap move;
    texwrap prepare;
    texwrap ready;
    texwrap unprepare;

    //Use unsigned int to avoid casting issues since millis is unsigned
    unsigned int idle_frames;
    unsigned int move_frames;
    unsigned int prepare_frames;
    unsigned int ready_frames;
    unsigned int unprepare_frames;

    ///Range of surface-to-air missiles aboard this thing
    ///0 if has no SAM,
    ///SAM will automatically engage all air threats in range
    double SAMRange;

    ///Range of surface-to-surface missiles aboard this thing
    ///0 if has no SSM
    double SSMRange;

public:

    [[nodiscard]] double getSAMRange() const {return SAMRange;};
    [[nodiscard]] double getSSMRange() const {return SSMRange;};

    [[nodiscard]] int getMovementPoints() const { return movementPoints; }

    unitType(const fs::path& unitPath, SDL_Renderer* renderer);

    [[nodiscard]] bool isLandUnit() const { return landUnit; }

    [[nodiscard]] unsigned int getMsPerFrame() const {return 100;}

    void render(double x, double y,double scale,uint32_t millis, SDL_Renderer* renderer,animationPhase phase, bool flip) const;

    [[nodiscard]] bool isAnimationFinished(uint32_t millis,animationPhase phase) const;

    [[nodiscard]] const std::string& getName() const { return name; }
};

#endif //PREMVPMAPGAME_UNITTYPE_H