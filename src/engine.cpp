//
// Created by nikolaj on 9/16/25.
//

#include "engine.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


engine::engine(): theScenario() {
    window = nullptr;
    renderer = nullptr;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        throw std::runtime_error( "SDL_Init Error: " + std::string( SDL_GetError() ) );
    }

    //Nearest interpolation, aka pixelation
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" );


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
}

engine::~engine() {

    if (renderer!=nullptr)
        SDL_DestroyRenderer(renderer);
    if (window!=nullptr)
        SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void engine::run() {
    bool quit = false;
    while (!quit) {
        SDL_Event event;
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
            theScenario.update();

            //Black background, shouldn't be seen but won't hurt
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear( renderer );
            theScenario.render(renderer);
            SDL_RenderPresent( renderer );
        }
    }
}

