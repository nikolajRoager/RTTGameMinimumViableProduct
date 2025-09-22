//
// Created by nikolaj on 9/20/25.
//

#include "unit.h"


void unit::render(double x, double y, double scale,uint32_t millis, SDL_Renderer *renderer) const {
    myType.render(x, y, scale,millis-animationStart, renderer,myPhase);
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