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


    SDL_GetMouseState( &mouseXPos, &mouseYPos );

    //Only load scenario AFTER SDL
    theScenario = new scenario(renderer);

    mouseXPos=0;
    mouseYPos=0;
    rightMouseDown=false;
    prevRightMouseDown=false;
    leftMouseDown=false;
    prevLeftMouseDown=false;
}

engine::~engine() {

    delete theScenario;
    if (renderer!=nullptr)
        SDL_DestroyRenderer(renderer);
    if (window!=nullptr)
        SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void engine::run() {
    bool quit = false;
    rightMouseDown=false;
    prevRightMouseDown=false;
    leftMouseDown=false;
    prevLeftMouseDown=false;

    while (!quit) {
        prevRightMouseDown=rightMouseDown;
        prevLeftMouseDown=leftMouseDown;
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
        }
        //Milli seconds since program start is preferred time measurement for animations
        unsigned int millis = SDL_GetTicks();

        theScenario->update(windowWidthPx,windowHeightPx,mouseXPos,mouseYPos,(leftMouseDown && !prevLeftMouseDown),(rightMouseDown && !prevRightMouseDown),millis);

        //Black background, shouldn't be seen but won't hurt
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear( renderer );
        theScenario->render(renderer,windowWidthPx,windowHeightPx,millis);
        SDL_RenderPresent( renderer );
    }
}

