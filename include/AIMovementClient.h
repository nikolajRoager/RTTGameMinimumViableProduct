//
// Created by Nikolaj Christensen on 09/10/2025.
//

#ifndef PREMVPMAPGAME_AIMOVEMENTCLIENT_H
#define PREMVPMAPGAME_AIMOVEMENTCLIENT_H
#include <map>
#include <random>
#include <vector>

#include "hexGrid.h"

class AIMovementClient {
private:

    //We use a vector because we need fast random access
    std::vector<int> aiPatrolHexes;


    std::default_random_engine& generator;

public:
    AIMovementClient(std::default_random_engine& _generator): generator(_generator) {
    }

    void addPatrolHex(int hexid) {aiPatrolHexes.push_back(hexid);}

    void render(const hexGrid& grid, SDL_Renderer *renderer,double scale) const;

    void makeAIMovementPlans(const hexGrid& grid, std::vector<unit>& units, std::map<int,std::vector<int> >& movementPlans) const;
};

#endif //PREMVPMAPGAME_AIMOVEMENTCLIENT_H