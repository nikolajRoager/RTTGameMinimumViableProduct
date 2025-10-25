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
#include "soundwrap.h"
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
    bool playerSide;

    [[nodiscard]] const bakedAttackVectorNode& getLastPosition () const {return line.back();}
    explicit bakedAttackVector(bool _playerSide): playerSide(_playerSide) {}
};

///A physics cake contains all the baked in physics
class physicsCake {
private:

    double SAMSpeed=100;


    std::vector<bakedAttackVector> SSMVectors;
    std::vector<bakedAttackVector> SAMVectors;

    ///We start at time 0, and end at this time
    double endTime;

    std::default_random_engine& generator;
    std::uniform_real_distribution<double> distribution;

    ///A flying surface-to-air missile
    struct SAMInAir {
        bool terminated;
        double x,y;
        double vx,vy;
        ///What SSM is this targeting, -1 if flying with no target
        int target;
        ///Time until we run out of fuel and crash
        double fuelTimeLeft;

        ///Time until we expect to turn on our proximity fuze and likely explode
        double fuze;

        SAMInAir(double _x, double _y, double _vx, double _vy,double _fuelTimeLeft, double _fuze, int _target) : x(_x), y(_y), vx(_vx), vy(_vy), target(_target), fuelTimeLeft(_fuelTimeLeft), fuze(_fuze) {terminated=false;};
    };

    struct SAMLauncher {
        int unitId;
        bool playerSide;
        double fuelTime;
        int salvoSize;
        int loadedLaunchers;
        double launchDelay;
        double reloadDelay;
        double ongoingDelay;

        double range;

        SAMLauncher(int _unitId, bool _playerSide, double _fuelTime, double _range, double _launchDelay, int _salvoSize, double _reloadDelay) {
            unitId=_unitId;
            playerSide=_playerSide;
            fuelTime=_fuelTime;
            range=_range;
            launchDelay=_launchDelay;
            salvoSize=_salvoSize;
            reloadDelay=_reloadDelay;
            ongoingDelay=0;
            loadedLaunchers=salvoSize;
        }
    };

    struct healthEvent {
        int health;
        double time;

        healthEvent(int _health, double _time) : health(_health), time(_time) {};
    };

    //TODO, unused
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

public:
    explicit physicsCake(std::default_random_engine& _generator): generator(_generator) {
        distribution = std::uniform_real_distribution(0.0,1.0);
        endTime=0.0;
    }
    [[nodiscard]] double getEndTime () const {return endTime;}
    void bake(const hexGrid& grid, std::vector<unit>& units,const std::map<int,std::vector<attackPlan> >& attackPlans);

    void debugRender(SDL_Renderer* renderer, double scale) const;

    void render(double time,const texwrap& SSMTexture,SDL_Renderer* renderer, double scale,uint32_t millis) const;

    void updateUnits(std::vector<unit>& units, double time, uint32_t millis) const;

    ///Spawn particles at this time, with this time interval
    void spawnParticlesAndSound(std::deque<particle>& smokeParticles,std::deque<particle>& splashParticles,std::deque<particle>& crashParticles,std::deque<particle>& hitTargetParticles,std::deque<particle>& interceptParticles,const soundwrap& splashSound, const soundwrap& crashSound, const soundwrap& interceptSound, const soundwrap& hitTargetSound, const soundwrap& missileSound,double time, double smokeSpawnRate, uint32_t dmillis);

    void clear() {
        SSMVectors.clear();
        unitHealthEvents.clear();
    }

};

#endif //PREMVPMAPGAME_PHYSICSCAKE_H