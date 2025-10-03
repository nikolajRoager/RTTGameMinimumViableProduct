//
// Created by Nikolaj Christensen on 03/10/2025.
//

#ifndef PREMVPMAPGAME_PHYSICSCAKE_H
#define PREMVPMAPGAME_PHYSICSCAKE_H
#include <map>
#include <vector>

#include "attackPlan.h"
#include "unit.h"


struct bakedAttackVectorNode {
    double x, y;
    double time;

    bakedAttackVectorNode(double _x, double _y, double _time) : x(_x), y(_y),time(_time) {};
};


///A baked in attack vector for a missile
struct bakedAttackVector {
    std::vector<bakedAttackVectorNode> line;
    bakedAttackVector(){}
};

///A physics cake contains all the baked in physics
class physicsCake {
private:
    std::vector<bakedAttackVector> SSMVectors;
    ///We start at time 0, and end at this time
    double endTime;
public:
    physicsCake() {
        endTime=0.0;
    }
    [[nodiscard]] double getEndTime () const {return endTime;}
    void bake(const std::vector<unit> units,const std::map<int,std::vector<attackPlan> >& attackPlans);

    void debugRender(SDL_Renderer* renderer, double scale) const;
};

#endif //PREMVPMAPGAME_PHYSICSCAKE_H