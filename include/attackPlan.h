//
// Created by nikolaj on 9/30/25.
//

#ifndef PREMVPMAPGAME_ATTACKPLAN_H
#define PREMVPMAPGAME_ATTACKPLAN_H
#include <format>
#include <vector>
#include <SDL2/SDL_render.h>

#include "texwrap.h"

///An attack plan involving a Surface to Surface Missile
class attackPlan {
private:
    ///ID, in the list of entities, of whoever launches this SSM attack
    int launcherId;
    double projectileSpeed=50;

    struct attackVectorPoint {
        double x;
        double y;
        double time;
        double distance;
        texwrap timeMarker;
        attackVectorPoint(double _x, double _y, double _time,double _distance,SDL_Renderer* renderer, TTF_Font* font): x(_x),y(_y),time(_time),distance(_distance),timeMarker(std::format("{:.3f}", _time),renderer,font,0,0,0)  {
        }
    };
    std::vector<attackVectorPoint> attackVectors;

public:

    attackPlan(int _launcherId,double x0,double y0, double x1,double y1, SDL_Renderer* renderer,  TTF_Font* font);

    void render(SDL_Renderer *renderer, double scale, bool isSelected=false) const;
    [[nodiscard]] double getLaunchTime() const {return attackVectors.front().time;}
    [[nodiscard]] double getEndTime() const {return attackVectors.back().time;}
    [[nodiscard]] std::pair<double,double> getEndNode() const {return {attackVectors.back().x,attackVectors.back().y};}

    [[nodiscard]] bool isActive(double time) const {
        return time>getLaunchTime()&& time<getEndTime();
    }
    [[nodiscard]] std::pair<double,double> getLocation(double time) const;

    [[nodiscard]] size_t getNodes () const {return attackVectors.size();}

    [[nodiscard]] double getLength () const {return attackVectors.back().distance;}

    [[nodiscard]] double getProjectileSpeed () const {return projectileSpeed;}

    void addNode(double x, double y,double maxRange,SDL_Renderer* renderer, TTF_Font* font);

    [[nodiscard]] const texwrap& getTimeMarker(int id) const {
        return attackVectors[id].timeMarker;
    }

    ///Modify the launch time an amount of seconds
    void modifyLaunchTime(int amount, SDL_Renderer* renderer,  TTF_Font* font);
};

#endif //PREMVPMAPGAME_ATTACKPLAN_H