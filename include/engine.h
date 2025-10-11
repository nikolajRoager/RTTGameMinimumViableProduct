//
// Created by nikolaj on 9/16/25.
//

#ifndef PREMVPMAPGAME_ENGINE_H
#define PREMVPMAPGAME_ENGINE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "scenario.h"


class engine {
private:

    //The window we'll be rendering to
    SDL_Window* window;

    //The window renderer
    SDL_Renderer* renderer;

    TTF_Font* gameFont;

    scenario* theScenario;




    int windowWidthPx;
    int windowHeightPx;

    int mouseXPos;
    int mouseYPos;

    bool rightMouseDown;
    bool prevRightMouseDown;

    bool leftMouseDown;
    bool prevLeftMouseDown;

    bool executeDown;
    bool prevExecuteDown;

    bool shiftDown=false;
    bool prevShiftDown=false;

    std::default_random_engine generator;

    SDL_KeyCode executekey = SDLK_RETURN;


    public:
    engine();
    ~engine();

    void run();
};


#endif //PREMVPMAPGAME_ENGINE_H