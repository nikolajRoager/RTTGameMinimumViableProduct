//
// Created by Nikolaj Christensen on 03/10/2025.
//

#ifndef PREMVPMAPGAME_PHYSICSCAKE_H
#define PREMVPMAPGAME_PHYSICSCAKE_H
#include <deque>
#include <map>
#include <random>
#include <vector>

#include "attackPlan.h"
#include "hexGrid.h"
#include "particle.h"
#include "unit.h"


struct bakedAttackVectorNode {
    double x, y;
    double time;

    bakedAttackVectorNode(double _x, double _y, double _time) : x(_x), y(_y),time(_time) {};
};



///A baked in attack vector for a missile
struct bakedAttackVector {
    enum attackVectorFate {
        PENDING,
        CRASH,
        SPLASH,
        DETONATE,
        INTERCEPTED,
    };

    ///What happens to us
    attackVectorFate fate=PENDING;

    ///For the playback, have we already played the effect of this finishing? (explosion or splash)
    std::vector<bakedAttackVectorNode> line;

    [[nodiscard]] const bakedAttackVectorNode& getDestination () const {return line.back();}
    bakedAttackVector()= default;
};

///A physics cake contains all the baked in physics
class physicsCake {
private:
    std::vector<bakedAttackVector> SSMVectors;
    ///We start at time 0, and end at this time
    double endTime;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;

    struct healthEvent {
        int health;
        double time;

        healthEvent(int _health, double _time) : health(_health), time(_time) {};
    };

    struct particleSoundEvent {
        enum evenType {
            SPLASH,
            CRASH,
            DETONATE,
        };
        evenType type;
        double time;

        particleSoundEvent(evenType _type, double _time) : type(_type), time(_time) {};
    };

    ///For each unit, what is our health when, in chronological order
    std::vector<std::vector<healthEvent> > unitHealthEvents;

    ///What particle and sound events happen when, in chronological order
    std::vector<particleSoundEvent> particleEvents;

public:
    explicit physicsCake(const int seed) {
        generator = std::default_random_engine(seed);
        distribution = std::uniform_real_distribution(0.0,1.0);
        endTime=0.0;
    }
    [[nodiscard]] double getEndTime () const {return endTime;}
    void bake(const hexGrid& grid, const std::vector<unit>& units,const std::map<int,std::vector<attackPlan> >& attackPlans);

    void debugRender(SDL_Renderer* renderer, double scale) const;

    void render(double time,const texwrap& SSMTexture,SDL_Renderer* renderer, double scale,uint32_t millis) const;

    void updateUnits(std::vector<unit>& units, double time, uint32_t millis) const;

    ///Spawn particles at this time, with this time interval
    void spawnParticles(std::deque<particle>& smokeParticles,double time, double smokeSpawnRate, uint32_t dmillis);

    void clear() {
        SSMVectors.clear();
        unitHealthEvents.clear();
        particleEvents.clear();
    }

};

#endif //PREMVPMAPGAME_PHYSICSCAKE_H