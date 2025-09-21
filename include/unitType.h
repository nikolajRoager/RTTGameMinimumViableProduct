//
// Created by nikolaj on 9/20/25.
//

#ifndef PREMVPMAPGAME_UNITTYPE_H
#define PREMVPMAPGAME_UNITTYPE_H
#include "texwrap.h"

///A particular unit type, with its basic stats, particular instances can be created of unit types
class unitType {
private:
    bool landUnit;
    texwrap texture;
public:
    unitType(bool landUnit, const std::string &texPath, SDL_Renderer* renderer): landUnit(landUnit), texture(texPath, renderer) {}

    [[nodiscard]] bool isLandUnit() const { return landUnit; }

    void render(double x, double y, double scale,SDL_Renderer* renderer) const;
};

#endif //PREMVPMAPGAME_UNITTYPE_H