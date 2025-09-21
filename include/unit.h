//
// Created by nikolaj on 9/20/25.
//

#ifndef PREMVPMAPGAME_UNIT_H
#define PREMVPMAPGAME_UNIT_H
#include "unitType.h"

///An instance of a unit
class unit {
private:
    ///A reference to my archetype
    const unitType& myType;

    ///What side is this on? true is obviously the good guys
    bool side;

    int hexX;
    int hexY;

public:

    unit(const unitType& type, bool _side, int _hexX, int _hexY):
    myType(type), side(_side), hexX(_hexX), hexY(_hexY)
    {
    }

    [[nodiscard]] int getHexX() const { return hexX; }
    [[nodiscard]] int getHexY() const { return hexY; }


    void render(double x, double y, double scale,SDL_Renderer *renderer) const;
};

#endif //PREMVPMAPGAME_UNIT_H