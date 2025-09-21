//
// Created by Nikolaj Christensen on 17/09/2025.
//

#ifndef PREMVPMAPGAME_HEXTILE_H
#define PREMVPMAPGAME_HEXTILE_H

class hexTile {
public:
    //The current itteration of the game can only handle two combatent sides
    enum hexStatus {
        SEA=0,
        FRIEND=1,
        FOE=2,
        NEUTRAL=3,
    };
private:
    hexStatus status;

    double hexCenterX;
    double hexCenterY;

public:
    hexTile(hexStatus _status, double _hexCenterX, double _hexCenterY): status(_status),hexCenterX(_hexCenterX),hexCenterY(_hexCenterY) {}

    [[nodiscard]] hexStatus getStatus() const { return status; }

    [[nodiscard]] double getHexCenterX() const { return hexCenterX; }
    [[nodiscard]] double getHexCenterY() const { return hexCenterY; }
};

#endif //PREMVPMAPGAME_HEXTILE_H