//
// Created by nikolaj on 9/20/25.
//

#include "unit.h"

#include <format>


void unit::render(double scale,uint32_t millis, SDL_Renderer *renderer) const {
    myType.render(x*scale, y*scale, scale,millis-animationStart, renderer,myPhase,flip);
}

void unit::updateAnimation(uint32_t millis) {
    if (myPhase==unitType::IDLE && readyAttack) {
        myPhase=unitType::PREPARE;
        animationStart=millis;
    }

    //unprepare if ready and not called for
    if (myPhase==unitType::READY && !readyAttack) {
        myPhase=unitType::UNPREPARE;
        animationStart=millis;
    }

    //We are done preparing, we are now ready
    if (myPhase==unitType::PREPARE && myType.isAnimationFinished(millis-animationStart,myPhase)) {
        myPhase=unitType::READY;
        animationStart=millis;
    }
    //We are done unpreparing, we are now unready
    if (myPhase==unitType::UNPREPARE && myType.isAnimationFinished(millis-animationStart,myPhase)) {
        myPhase=unitType::IDLE;
        animationStart=millis;
    }
}

unit::unit(const unitType& type, bool _side, int _hexX, int _hexY):
myType(type), myPhase(unitType::IDLE), side(_side), hexX(_hexX), hexY(_hexY), readyAttack(false)
{
    //The scenario is responsible for updating our location based on our hexagon coordinates
    x=0;
    y=0;
    //pseudo Random starting flip
    flip = hexX%2==hexY%2;
}

std::string unit::getDescription() const {
    std::string out=myType.getName();
    out+=std::string("&")+(side?"Friendly\n\n":"Hostile\n\n");

    int movementPoints=getMovementPoints();
    out+="Movement points: &"+std::to_string(movementPoints)+"\n\n";


    double samRange =myType.getSAMRange();
    if (samRange>0) {
        const std::string samRangeStr = std::format("{:.3f}", samRange);
        out+="Surface to Air Missile range = &"+samRangeStr+"\n";
        out+="&Will auto-attack air targets in range\n";
    }
    double ssmRange =myType.getSSMRange();
    if (ssmRange>0) {
        const std::string ssmRangeStr = std::format("{:.3f}", ssmRange);
        out+="Surface to Surface Missile range = &"+ssmRangeStr+"\n";
        out+="&Can attack land/sea targets in range during attack phase\n";
    }
    return out;
}
