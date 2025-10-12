//
// Created by nikolaj on 9/20/25.
//

#ifndef PREMVPMAPGAME_UNIT_H
#define PREMVPMAPGAME_UNIT_H
#include <iostream>
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
    bool isFriend;

    int hexX;
    int hexY;

    bool readyAttack;

    uint32_t animationStart=0;


    ///X and Y location of the unit, set by the scenario based on our hexagon location
    double x,y;
    bool flip;

    int hp;

    int AIMovementTarget;

public:
    void setAIMovementTarget(int _AIMovementTarget) {AIMovementTarget=_AIMovementTarget;}
    [[nodiscard]] int getAIMovementTarget() const {return AIMovementTarget;}

    [[nodiscard]] int getHp() const {return hp;};

    void setHp(int _hp,uint32_t millis) {
        if (hp!=0 && _hp==0) {
            setAnimation(millis,unitType::DIE);
        }
        //Necromancy (happens during replays)
        else if (hp==0 && _hp!=0) {
            setAnimation(millis,unitType::READY);
        }
        hp=_hp;
    }

    [[nodiscard]] const std::string& getName() const {return myType.getName();}

    [[nodiscard]] int getMovementPoints() const { return myType.getMovementPoints(); }
    [[nodiscard]] double getSAMRange() const { return myType.getSAMRange(); }
    [[nodiscard]] double getSSMRange() const { return myType.getSSMRange(); }
    [[nodiscard]] int getSSMSalvoSize() const { return myType.getSSMSalvoSize(); }
    [[nodiscard]] bool isFriendly() const {return isFriend;}

    [[nodiscard]] uint32_t timeSinceAnimationStart(const uint32_t millis) const {return millis-animationStart;}

    unit(const unitType& type, bool _side, int _hexX, int _hexY);

    void setHexX(int _hexX) {hexX = _hexX;}
    void setHexY(int _hexY) {hexY = _hexY;}

    [[nodiscard]] double getX() const { return x; }
    [[nodiscard]] double getY() const { return y; }

    void setX (double _x) {x=_x;}
    void setY (double _y) {y=_y;}

    void setFlip(bool _flip) {flip=_flip;}

    void startMovement(uint32_t millis) {myPhase = unitType::MOVE; animationStart=millis;}
    ///Forcefully set the animation phase of this unit right now
    void setAnimation(uint32_t millis, unitType::animationPhase phase) {myPhase=phase; animationStart=millis;}
    void doReadyAttack() {readyAttack = true;};
    void unreadyAttack() {readyAttack = false;};

    [[nodiscard]] int getHexX() const { return hexX; }
    [[nodiscard]] int getHexY() const { return hexY; }

    [[nodiscard]] unitType::animationPhase getAnimationPhase() const { return myPhase; }

    void render(double scale,uint32_t millis,SDL_Renderer *renderer, const texwrap& hpMarker) const;
    void updateAnimation(uint32_t millis);



    [[nodiscard]] std::string getDescription() const;

    [[nodiscard]] int getSSMNodes() const {return myType.getSSMNodes();}
};

#endif //PREMVPMAPGAME_UNIT_H