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


    ///X and Y location of the unit, set by the scenario based on our hexagon location
    double x,y;
    bool flip;
public:
    [[nodiscard]] uint32_t timeSinceAnimationStart(const uint32_t millis) const {return millis-animationStart;}

    unit(const unitType& type, bool _side, int _hexX, int _hexY);

    void setX (double _x) {x=_x;}
    void setY (double _y) {y=_y;}

    void setFlip(bool _flip) {flip=_flip;}

    void startMovement(uint32_t millis) {myPhase = unitType::MOVE; animationStart=millis;}
    void doReadyAttack() {readyAttack = true;};
    void unreadyAttack() {readyAttack = false;};

    [[nodiscard]] int getHexX() const { return hexX; }
    [[nodiscard]] int getHexY() const { return hexY; }

    [[nodiscard]] unitType::animationPhase getAnimationPhase() const { return myPhase; }

    void render(double scale,uint32_t millis,SDL_Renderer *renderer) const;
    void updateAnimation(uint32_t millis);
};

#endif //PREMVPMAPGAME_UNIT_H