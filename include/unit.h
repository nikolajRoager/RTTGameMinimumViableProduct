//
// Created by nikolaj on 9/20/25.
//

#ifndef PREMVPMAPGAME_UNIT_H
#define PREMVPMAPGAME_UNIT_H
#include <set>

#include "unitType.h"

///An instance of a unit
class unit {
private:
    ///A reference to my archetype
    const unitType& myType;

    ///The animation phase of this unit, only visual
    unitType::animationPhase myPhase;

    ///What side is this on? true is obviously the good guys
    bool side;

    int hexX;
    int hexY;

    bool readyAttack;

    uint32_t animationStart=0;

public:

    unit(const unitType& type, bool _side, int _hexX, int _hexY):
    myType(type), myPhase(unitType::IDLE), side(_side), hexX(_hexX), hexY(_hexY), readyAttack(false)
    {
    }

    void doReadyAttack() {readyAttack = true;};
    void unreadyAttack() {readyAttack = false;};

    [[nodiscard]] int getHexX() const { return hexX; }
    [[nodiscard]] int getHexY() const { return hexY; }


    void render(double x, double y, double scale,uint32_t millis,SDL_Renderer *renderer) const;
    void updateAnimation(uint32_t millis);
};

#endif //PREMVPMAPGAME_UNIT_H