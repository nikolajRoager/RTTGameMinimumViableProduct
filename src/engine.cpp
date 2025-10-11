//
// Created by nikolaj on 9/16/25.
//

#include "engine.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


engine::engine() {
    window = nullptr;
    renderer = nullptr;
    gameFont= nullptr;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        throw std::runtime_error( "SDL_Init Error: " + std::string( SDL_GetError() ) );
    }

    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );


    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    windowWidthPx = DM.w;
    windowHeightPx = DM.h;


    window = SDL_CreateWindow( "I can write whatever I want here, and nobody can stop me! HA HA HA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidthPx, windowHeightPx, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    if( window == nullptr)
        throw std::runtime_error( "Window could not be created! SDL Error:" + std::string( SDL_GetError() ) );
    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == nullptr)
    {
        throw std::runtime_error( "Renderer could not be created! SDL Error: "+ std::string(SDL_GetError()) );
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        throw std::runtime_error( "SDL_image could not initialize! SDL Error:" + std::string( SDL_GetError() ) );
    }


    if (TTF_Init()==-1) {
        throw std::runtime_error( "SDL_TTF could not initialize! SDL Error:" + std::string( SDL_GetError() ) );
    }

    //TODO, use filepath
    gameFont=TTF_OpenFont( "assets/Montserrat-Regular.ttf", 24 );
    if (gameFont==nullptr) {
        throw std::runtime_error("Failed to load font Montserrat-Regular.ttf, error "+std::string(TTF_GetError())+"");
    }


    SDL_GetMouseState( &mouseXPos, &mouseYPos );

    generator=std::default_random_engine(time(nullptr));
    //Only load scenario AFTER SDL
    theScenario = new scenario(renderer,gameFont,generator);

    mouseXPos=0;
    mouseYPos=0;
    rightMouseDown=false;
    prevRightMouseDown=false;
    leftMouseDown=false;
    prevLeftMouseDown=false;
    executeDown=false;
    prevExecuteDown=false;
}

engine::~engine() {

    delete theScenario;
    if (renderer!=nullptr)
        SDL_DestroyRenderer(renderer);
    if (window!=nullptr)
        SDL_DestroyWindow(window);

    if (gameFont!=nullptr)
        TTF_CloseFont(gameFont);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void engine::run() {
    bool quit = false;
    rightMouseDown=false;
    prevRightMouseDown=false;
    leftMouseDown=false;
    prevLeftMouseDown=false;
    executeDown=false;
    prevExecuteDown=false;

    uint32_t pmillis=SDL_GetTicks();

    while (!quit) {
        prevRightMouseDown=rightMouseDown;
        prevLeftMouseDown=leftMouseDown;
        prevExecuteDown=executeDown;

        int scroll=0;
        SDL_Event event;
        //First handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_WINDOWEVENT) {
                switch( event.window.event ) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        windowWidthPx = event.window.data1;
                        windowHeightPx = event.window.data2;
                        break;
                    default:
                        break;
                }

            }
            if (event.type == SDL_MOUSEWHEEL) {
                scroll=event.wheel.y;
            }
            if (event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState( &mouseXPos, &mouseYPos );
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftMouseDown=true;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    rightMouseDown=true;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftMouseDown=false;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    rightMouseDown=false;
                }
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == executekey) {
                    executeDown=true;
                }
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == executekey) {
                    executeDown=false;
                }
            }
        }
        SDL_Keymod modState = SDL_GetModState();
        if (modState & KMOD_SHIFT)
            shiftDown=true;
        else
            shiftDown=false;

        //Milliseconds since program start is preferred time measurement for animations
        unsigned int millis = SDL_GetTicks();

        theScenario->update(renderer, windowWidthPx,windowHeightPx,mouseXPos,mouseYPos,(leftMouseDown && !prevLeftMouseDown),(rightMouseDown && !prevRightMouseDown),(executeDown && !prevExecuteDown),shiftDown,scroll,millis,millis-pmillis);

        //Black background, shouldn't be seen but won't hurt
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear( renderer );
        theScenario->render(renderer,mouseXPos,mouseYPos,shiftDown,millis);
        SDL_RenderPresent( renderer );
        pmillis=millis;

    }
}

