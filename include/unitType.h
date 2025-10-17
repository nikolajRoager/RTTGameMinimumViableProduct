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
        DIE=5,
    };

private:
    std::string name;

    bool landUnit=false;
    ///Number of moves possible per turn
    ///Buildings have 0 movement points
    int movementPoints=0;

    texwrap texture;

    texwrap idle;
    texwrap move;
    texwrap prepare;
    texwrap ready;
    texwrap unprepare;
    texwrap die;

    //Use unsigned int to avoid casting issues since millis is unsigned
    unsigned int idle_frames=1;
    unsigned int move_frames=1;
    unsigned int prepare_frames=1;
    unsigned int ready_frames=1;
    unsigned int unprepare_frames=1;
    unsigned int die_frames=1;

    ///Range of surface-to-air missiles aboard this thing
    ///is 0 if it has no SAM,
    ///SAM will automatically engage all air threats in range
    double SAMRange=0;

    double SAMDelay=0.5;
    int SAMSalvoSize=4;
    double SAMReloadDelay=4;

    ///Range of surface-to-surface missiles aboard this thing
    ///is 0 if it has no SSM
    double SSMRange=0;

    ///How many SSMs we can fire in one turn
    int SSMSalvoSize=4;

    ///How many attack vector nodes can surface to surface missiles fired from this thing have
    ///should be at least 2 (has no effect below 2)
    int SSMNodes=3;

    int maxHp=2;

public:
    [[nodiscard]] int getSAMSalvoSize() const {return SAMSalvoSize;}
    [[nodiscard]] double getSAMReloadDelay() const {return SAMReloadDelay;}
    [[nodiscard]] double getSAMRange() const {return SAMRange;};
    [[nodiscard]] double getSAMDelay() const {return SAMDelay;};


    [[nodiscard]] double getSSMRange() const {return SSMRange;};

    [[nodiscard]] int getSSMSalvoSize() const {return SSMSalvoSize;};

    [[nodiscard]] int getSSMNodes() const {return SSMNodes;};
    [[nodiscard]] int getMaxHp() const {return maxHp;};


    [[nodiscard]] int getMovementPoints() const { return movementPoints; }

    unitType(const fs::path& unitPath, SDL_Renderer* renderer);

    [[nodiscard]] bool isLandUnit() const { return landUnit; }

    [[nodiscard]] unsigned int getMsPerFrame() const {return 100;}

    void render(double x, double y,double scale,uint32_t millis, SDL_Renderer* renderer,animationPhase phase, bool flip) const;

    [[nodiscard]] bool isAnimationFinished(uint32_t millis,animationPhase phase) const;

    [[nodiscard]] const std::string& getName() const { return name; }

};

#endif //PREMVPMAPGAME_UNITTYPE_H