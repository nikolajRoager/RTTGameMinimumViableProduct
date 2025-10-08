//
// Created by nikolaj on 9/30/25.
//

#include "attackPlan.h"

#include <cmath>
#include <format>
#include <iostream>
#include <SDL2/SDL_render.h>

attackPlan::attackPlan(int _launcherId, double x0, double y0, double x1, double y1, SDL_Renderer *renderer, TTF_Font *font) {
    launcherId=_launcherId;
    attackVectors.reserve(2);

    //TODO, dynamic launch time
    attackVectors.emplace_back(x0,y0,0,0,renderer,font);
    double dist = sqrt(pow(x0-x1,2)+pow(y0-y1,2));
    attackVectors.emplace_back(x1,y1,dist/projectileSpeed,dist,renderer,font);
}


void attackPlan::render(SDL_Renderer *renderer, double scale, bool isSelected) const {

    SDL_SetRenderDrawColor(renderer,255,0,0,255);

    for (int i = 0; i < attackVectors.size(); i++) {
        if (i!=0)
            SDL_RenderDrawLine(renderer, scale*attackVectors[i].x,scale*attackVectors[i].y,scale*attackVectors[i-1].x,scale*attackVectors[i-1].y);

        if (isSelected)
            attackVectors[i].timeMarker.render(scale*attackVectors[i].x,scale*attackVectors[i].y,renderer,scale);
    }
}

std::pair<double, double> attackPlan::getLocation(double time) const {
    if (time<=getLaunchTime()) {
        return std::make_pair(attackVectors[0].x,attackVectors[0].y);
    }
    else if (time>getEndTime()) {
        return std::make_pair(attackVectors.back().x,attackVectors.back().y);
    }
    else {
        for (int i = 1; i < attackVectors.size(); i++) {
            if (time<attackVectors[i].time) {
                //we are inside this line
                //We want the interpolation factor such that
                //time = fac*attackVectors[i].time+(1-fac)*attackVectors[i-1].time;
                //Or isolating the factor fac
                double fac=(time-attackVectors[i-1].time)/(attackVectors[i].time-attackVectors[i-1].time) ;
                return std::make_pair(fac*attackVectors[i].x+(1-fac)*attackVectors[i-1].x,fac*attackVectors[i].y+(1-fac)*attackVectors[i-1].y);
            }
        }
    }
    //Keeps the compiler from throwing warnings, but never actually happens
    return std::make_pair(attackVectors.back().x,attackVectors.back().y);
}

void attackPlan::addNode(double x, double y, double maxRange, SDL_Renderer* renderer, TTF_Font* font) {
    double prev_dist = attackVectors.back().distance;
    double prev_time = attackVectors.back().time;
    double x0 = attackVectors.back().x;
    double y0 = attackVectors.back().y;
    double thisDistance = sqrt(pow(x-x0,2)+pow(y-y0,2));
    double dist = thisDistance+prev_dist;
    if (dist<=maxRange)
        attackVectors.emplace_back(x,y,prev_time+thisDistance/projectileSpeed,dist,renderer,font);
}

void attackPlan::modifyLaunchTime(int amount, SDL_Renderer* renderer,  TTF_Font* font) {
    if (attackVectors.front().time+amount>=0)
        for (auto& point : attackVectors) {
                point.time+=amount;
                point.timeMarker=texwrap(std::format("{:.3f}", point.time),renderer,font,0,0,0);
        }
}
