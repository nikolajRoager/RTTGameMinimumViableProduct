//
// Created by nikolaj on 9/16/25.
//

#ifndef PREMVPMAPGAME_SCENARIO_H
#define PREMVPMAPGAME_SCENARIO_H
#include <deque>
#include <map>
#include <vector>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "AIMovementClient.h"
#include "attackPlan.h"
#include "gui.h"
#include "hexGrid.h"
#include "particle.h"
#include "phase.h"
#include "physicsCake.h"
#include "soundwrap.h"
#include "texwrap.h"
#include "unit.h"
#include "unitType.h"

class scenario {
private:
    texwrap background;
    texwrap hexSelectionOutline;
    ///A white circle with a radius of 10 hex sizes
    texwrap circle10;

    texwrap hpMarker;
    texwrap shiftMarker;
    texwrap noPeopleMarker;
    texwrap noPowerMarker;

    soundwrap splashSound;
    soundwrap crashOrInterceptSound;
    soundwrap hitTargetSound;
    soundwrap missileSound;

    std::vector<unitType> unitLibrary;

    ///Units of the player side
    std::vector<unit> units;

    int scenarioWidthPx;
    int scenarioHeightPx;

    ///What tile is the mouse currently over
    int mouseOverTile;
    ///What tile, if any is currently selected (-1 if none)
    int selectedTile=-1;
    ///What friendly unit is currently selected (-1 if none)
    int selectedUnit=-1;

    int selectedAttackPlan =-1;

    hexGrid grid;

    ///What phase of the game are we going through
    phase currentPhase=MOVEMENT_PLANNING;


    ///The queued up movements for the good guys, indexed by unit id,
    std::map<int,std::vector<int> > movementPlans;

    ///The queued up attack plans for each unit, again index by unit id
    std::map<int,std::vector<attackPlan> > attackPlans;

    ///Union of the effect hexes of all friendly power generating units
    std::set<int> friendlyPoweredHexes;
    ///Union of the effect hexes of all friendly population units
    std::set<int> friendlyPopulatedHexes;


    ///Union of the effect hexes of all friendly power generating units
    std::set<int> enemyPoweredHexes;
    ///Union of the effect hexes of all friendly population units
    std::set<int> enemyPopulatedHexes;


    //TODO, add hostile

    double scale;

    std::string movementPlanningDescription;
    std::string movementExecutionDescription;
    std::string attackPlanningDescription;
    std::string attackExecutionDescription;

    gui myGui;

    TTF_Font* inGameFont;

    ///Timer for the physics playback of the attack execution phase
    double attackExecutionPlaybackTimer=0.0;
    ///How long physics playback have we backed in
    double attackExecutionPlaybackMaxTime = 0.0;
    ///How far are we
    enum attackExecutionPlaybackPlayingState {
        UNSTARTED,
        PLAYING,
        FINISHED
    };
    bool pauseAttackExecutionPlayback = false;

    attackExecutionPlaybackPlayingState attackExecutionState=UNSTARTED;

    ///A surface-to-surface missile in flight
    texwrap flyingSSM;

    texwrap smokeParticleTexture;
    texwrap splashParticleTexture;
    texwrap crashParticleTexture;
    texwrap hitTargetTexture;
    texwrap interceptTexture;

    //Each particle type has its own queue
    //Since all particles have the same lifetime, and are inserted at the back of a list, they need to be removed from the front
    //A double ended queue (deque) is perfect for this
    std::deque<particle> smokeParticles;
    std::deque<particle> splashParticles;
    std::deque<particle> crashParticles;
    std::deque<particle> hitTargetParticles;
    std::deque<particle> interceptParticles;
    //TODO: crash particle, detonate particle, splash particle intercept particle


    int smokeParticleLifetimeMs=1000;
    int splashParticleLifetimeMs=200;
    int crashParticleLifetimeMs=200;
    int hitTargetParticleLifetimeMs=200;
    int interceptParticleLifetimeMs=200;

    ///average number of smoke particles spawned per second by missiles
    double missileSmokeSpawnRate = 20;

    physicsCake myCake;

    bool hasCalculatedMovementConstants=false;

    AIMovementClient aiMovementClient;

    void drawCircle(double x, double y, double radius, double scale, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer) const;
public:
    explicit scenario(SDL_Renderer* renderer, TTF_Font* _font, std::default_random_engine& _generator);
    ~scenario();

    void render(SDL_Renderer* renderer, int mouseX, int mouseY, bool shiftKey, uint32_t millis) const;
    void update(SDL_Renderer* renderer, int screenWidth, int screenHeight, int mouseX, int mouseY, bool isLeftMouseClick, bool isRightMouseClick, bool executeClick, bool shiftKey, bool playbuttonClick, int scrollwheel, uint32_t millis, uint32_t dmillis);
};

#endif //PREMVPMAPGAME_SCENARIO_H