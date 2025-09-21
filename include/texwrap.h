//
// Created by Nikolaj Christensen on 17/09/2025.
//

#ifndef PREMVPMAPGAME_TEXWRAP_H
#define PREMVPMAPGAME_TEXWRAP_H
#include <string>
#include <SDL2/SDL_render.h>


///Texture wrapper class
class texwrap {
private:
    //The pointer to the actual texture
    SDL_Texture* tex;

    int width;
    int height;

public:
    explicit texwrap(std::string path, SDL_Renderer* renderer);
    ~texwrap();

    void render(double x, double y, SDL_Renderer* renderer, SDL_Rect *clip = nullptr, double scale=1.0, bool center=false) const;

    void render(double x, double y, Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer, SDL_Rect *clip = nullptr, double scale=1.0, bool center=false) const;

    ///Get width of image in pixels
    [[nodiscard]] int getWidth() const {return width;}
    ///Get height of image in pixels
    [[nodiscard]] int getHeight() const {return height;}
};

#endif //PREMVPMAPGAME_TEXWRAP_H