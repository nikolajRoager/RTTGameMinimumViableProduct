//
// Created by nikolaj on 9/20/25.
//

#include "unit.h"

#include <format>


void unit::render(double scale,uint32_t millis, SDL_Renderer *renderer, const texwrap& hpMarker) const {
    myType.render(x*scale, y*scale, scale,millis-animationStart, renderer,myPhase,flip);
    for (int i = 0; i < myType.getMaxHp(); ++i) {
        hpMarker.render((x+25/*TODO, temp gamejam syndrome*/)*scale,(y)*scale-i*hpMarker.getHeight(),renderer,scale,false,false,2,i<hp?0:1);
    }
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
myType(type), myPhase(unitType::IDLE), isFriend(_side), hexX(_hexX), hexY(_hexY), readyAttack(false)
{
    //The scenario is responsible for updating our location based on our hexagon coordinates
    x=0;
    y=0;
    //pseudo Random starting flip
    flip = hexX%2==hexY%2;

    hp = myType.getMaxHp();
}

std::string unit::getDescription() const {
    std::string out=myType.getName();
    out+=std::string("&")+(isFriend?"Friendly\n":"Hostile\n");

    int movementPoints=getMovementPoints();
    out+="Movement points: &"+std::to_string(movementPoints)+"\n";

    out+="Hit Points: &"+std::to_string(hp)+"/"+std::to_string(myType.getMaxHp())+"\n";

    double samRange =myType.getSAMRange();
    if (samRange>0) {
        const std::string samRangeStr = std::format("{:.3f}", samRange);
        out+="Surface to Air Missile range: &"+samRangeStr+"\n";
        out+="&Will auto-attack air targets in range\n";
    }
    double ssmRange =myType.getSSMRange();
    if (ssmRange>0) {
        const std::string ssmRangeStr = std::format("{:.3f}", ssmRange);
        out+="Surface to Surface Missile range: &"+ssmRangeStr+" hex\n";
        out+="&Can attack land/sea targets in range during attack phase\n";

        int ssmSalvo=myType.getSSMSalvoSize();
        out+="Surface to Surface Missile max salvo size: &"+std::to_string(ssmSalvo)+"\n";
        int ssmNodes=myType.getSSMNodes()-2;
        out+="Surface to Surface Missile intermediate nodes: &"+std::to_string(ssmNodes)+"\n";
        if (ssmNodes>0) {
            out+="&Missiles can maneuver in flight!\n";
        }

    }


    return out;
}
