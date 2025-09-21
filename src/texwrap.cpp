//
// Created by Nikolaj Christensen on 17/09/2025.
//

#include "texwrap.h"

#include <stdexcept>
#include <SDL2/SDL_image.h>

texwrap::~texwrap() {
    if (tex!=nullptr)
        SDL_DestroyTexture(tex);
}

texwrap::texwrap(std::string path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        throw std::runtime_error("Unable to load image: " + std::string(SDL_GetError()));
    }

    tex= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (tex == nullptr) {
        throw std::runtime_error("Unable to create texture: " + std::string(SDL_GetError()));
    }

    width = surface->w;
    height = surface->h;
}
void texwrap::render(double x, double y, SDL_Renderer *renderer, SDL_Rect *clip, double scale,bool center) const {
    render(x,y,255,255,255,renderer,clip,scale,center);
}

void texwrap::render(double x, double y, Uint8 r, Uint8 g, Uint8 b, SDL_Renderer *renderer, SDL_Rect *clip, double scale, bool center) const {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { static_cast<int>(x), static_cast<int>(y), width, height};

    //Set clip rendering dimensions
    if( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    renderQuad.w *= scale;
    renderQuad.h *= scale;

    if (center) {
        renderQuad.x -= renderQuad.w/2;
        renderQuad.y -= renderQuad.h/2;
    }

    //Render to screen
    SDL_SetTextureColorMod(tex, r,g,b);
    SDL_RenderCopy( renderer, tex, clip, &renderQuad );
}


