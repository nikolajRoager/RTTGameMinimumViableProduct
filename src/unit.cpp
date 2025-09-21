//
// Created by nikolaj on 9/20/25.
//

#include "unit.h"


void unit::render(double x, double y, double scale, SDL_Renderer *renderer) const {
    myType.render(x, y, scale, renderer);
}
