//
// Created by nikolaj on 9/16/25.
//

#ifndef PREMVPMAPGAME_ENGINE_H
#define PREMVPMAPGAME_ENGINE_H
#include <SDL2/SDL.h>

#include "scenario.h"


class engine {
private:

    //The window we'll be rendering to
    SDL_Window* window;

    //The window renderer
    SDL_Renderer* renderer;

    scenario* theScenario;



    int windowWidthPx;
    int windowHeightPx;

    int mouseXPos;
    int mouseYPos;

    bool mouseDown;
    bool prevMouseDown;


    public:
    engine();
    ~engine();

    void run();
};


#endif //PREMVPMAPGAME_ENGINE_H