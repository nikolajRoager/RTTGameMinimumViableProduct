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

public:
    explicit hexTile(hexStatus _status): status(_status) {}

    [[nodiscard]] hexStatus getStatus() const { return status; }

};

#endif //PREMVPMAPGAME_HEXTILE_H