//
// Created by nikolaj on 9/20/25.
//

#include "unitType.h"

void unitType::render(double x, double y, double scale,SDL_Renderer *renderer) const {
    texture.render(x,y,renderer,nullptr,scale,true);
}
