//
// Created by Nikolaj Christensen on 03/10/2025.
//

#ifndef PREMVPMAPGAME_PHYSICSCAKE_H
#define PREMVPMAPGAME_PHYSICSCAKE_H
#include <vector>


struct bakedAttackVectorNode {
    double x, y;
    double distance;
    double time;
};

///A baked in attack vector for a missile
struct bakedAttackVector {
    std::vector<bakedAttackVector> line;
};

///A physics cake contains all the baked in physics
class physicsCake {
private:
    std::vector<bakedAttackVector> SSMVectors;
public:
    void bake();
};

#endif //PREMVPMAPGAME_PHYSICSCAKE_H