//
// Created by Nikolaj Christensen on 03/10/2025.
//

#ifndef PREMVPMAPGAME_PARTICLE_H
#define PREMVPMAPGAME_PARTICLE_H

struct particle {
    double x,y;
    double vx,vy;
    int ageMs;

    particle(double _x, double _y, double _vx, double _vy, int _ageMs) {
        x = _x; y = _y; vx=_vx; vy=_vy; ageMs = _ageMs;
    }
};

#endif //PREMVPMAPGAME_PARTICLE_H