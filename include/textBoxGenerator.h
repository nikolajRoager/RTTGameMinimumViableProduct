//
// Created by nikolaj on 9/27/25.
//

#ifndef PREMVPMAPGAME_TEXTBOXGENERATOR_H
#define PREMVPMAPGAME_TEXTBOXGENERATOR_H
#include <SDL2/SDL_ttf.h>

class TextBoxGenerator {
private:
    TTF_Font* font;
public:
    TextBoxGenerator(TTF_Font* _font) : font(_font) {}
};

#endif //PREMVPMAPGAME_TEXTBOXGENERATOR_H