//
// Created by nikolaj on 9/16/25.
//

#ifndef PREMVPMAPGAME_SCENARIO_H
#define PREMVPMAPGAME_SCENARIO_H
#include <SDL2/SDL_render.h>

class scenario {
private:

public:
    scenario();
    ~scenario();

    void render(SDL_Renderer* renderer);
    void update();
};

#endif //PREMVPMAPGAME_SCENARIO_H