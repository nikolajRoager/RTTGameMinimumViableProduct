//
// Created by Nikolaj Christensen on 26/09/2025.
//


#include "gui.h"

#include <format>
#include <iostream>
#include <SDL2/SDL_render.h>

gui::gui(const fs::path& guiFolder, SDL_Renderer *renderer, TTF_Font* font): backgroundTile((guiFolder/"guiTile.png"),renderer),movementPhaseMarker((guiFolder/"movementPhase.png"),renderer),attackPhaseMarker((guiFolder/"attackPhase.png"),renderer),executeMarker((guiFolder/"execute.png"),renderer),infoScreen((guiFolder/"infoScreen.png"),renderer), flipButton((guiFolder/"flipButton.png"),renderer),mapModeHexOutline("Hex outlines",renderer,font),samRangeHexOutline("SAM range",renderer,font),ssmRangeHexOutline("SSM range",renderer,font) {
    std::cout<<"Loaded gui"<<std::endl;
    infoScreenFont=font;
    infoScreenMaxExpansion=infoScreen.getHeight();

}


void gui::update( int mouseX, int mouseY, bool mouseClicked, int scenarioWidth, int scenarioHeight, double scale, uint32_t dmillis) {

    double executeButtonX = (scenarioWidth+RIGHT_BAR_PIXELS/2)*scale;
    double executeButtonY = (scenarioHeight+BOTTOM_BAR_PIXELS/2)*scale;


    pressExecuteButton = (mouseClicked && mouseX>executeButtonX-executeMarker.getWidth()*scale*0.25 && mouseY>executeButtonY-executeMarker.getHeight()*scale*0.5 && mouseX<executeButtonX+executeMarker.getWidth()*scale*0.25 && mouseY<executeButtonY+executeMarker.getHeight()*scale*0.5);
    expandInfoScreen  = mouseX>(scenarioWidth-RIGHT_BAR_PIXELS*6)*scale && mouseX<(scenarioWidth-RIGHT_BAR_PIXELS*2)*scale && mouseY>(scenarioHeight-infoScreenExpansion)*scale;

    if (expandInfoScreen) {
        if (infoScreenExpansion<infoScreenMaxExpansion) {
            infoScreenExpansion+=dmillis;
            if (infoScreenExpansion>infoScreenMaxExpansion) {
                infoScreenExpansion=infoScreenMaxExpansion;
            }
        }
    }
    else{
        if (infoScreenExpansion>0) {
            infoScreenExpansion-=dmillis;
            if (infoScreenExpansion<0) {
                infoScreenExpansion=0;
            }
        }
    }

    if (mouseX>(scenarioWidth-2*RIGHT_BAR_PIXELS+10)*scale &&
        mouseY>(scenarioHeight+10)*scale &&
        mouseX<(scenarioWidth-2*RIGHT_BAR_PIXELS+10+flipButton.getWidth()*0.5)*scale &&
        mouseY<(scenarioHeight+10+flipButton.getHeight())*scale &&
        mouseClicked)
        showHexOutline=!showHexOutline;

    if (mouseX>(scenarioWidth-2*RIGHT_BAR_PIXELS+10)*scale &&
        mouseY>(scenarioHeight+20+flipButton.getHeight())*scale &&
        mouseX<(scenarioWidth-2*RIGHT_BAR_PIXELS+10+flipButton.getWidth()*0.5)*scale &&
        mouseY<(scenarioHeight+20+2*flipButton.getHeight())*scale &&
        mouseClicked)
        showSAMRange =!showSAMRange;

    if (mouseX>(scenarioWidth-2*RIGHT_BAR_PIXELS+10)*scale &&
        mouseY>(scenarioHeight+30+2*flipButton.getHeight())*scale &&
        mouseX<(scenarioWidth-2*RIGHT_BAR_PIXELS+10+flipButton.getWidth()*0.5)*scale &&
        mouseY<(scenarioHeight+30+3*flipButton.getHeight())*scale &&
        mouseClicked)
        showSSMRange =!showSSMRange;

}

void gui::render(int scenarioWidth, int scenarioHeight, SDL_Renderer *renderer, double scale,uint32_t millis, phase thePhase) const {

    for (int x = scenarioWidth+RIGHT_BAR_PIXELS;x>-RIGHT_BAR_PIXELS;x-=RIGHT_BAR_PIXELS-1) {
        backgroundTile.render(x*scale,scenarioHeight*scale,renderer,scale);
        backgroundTile.render(x*scale,(scenarioHeight+BOTTOM_BAR_PIXELS-1)*scale,renderer,scale);
    }
    for (int y = scenarioHeight;y>-BOTTOM_BAR_PIXELS;y-=BOTTOM_BAR_PIXELS-1) {
        backgroundTile.render(scenarioWidth*scale,y*scale,renderer,scale);
        backgroundTile.render((scenarioWidth+RIGHT_BAR_PIXELS-1)*scale,y*scale,renderer,scale);
    }

    //Flip button for hexagon tiles
    flipButton.render((scenarioWidth-2*RIGHT_BAR_PIXELS+10)*scale,(scenarioHeight+10)*scale,renderer,scale,false,false,2,showHexOutline?1:0);
    mapModeHexOutline.render((scenarioWidth-2*RIGHT_BAR_PIXELS+flipButton.getWidth()*0.5+10)*scale,(scenarioHeight+10)*scale,renderer,scale);
    //button for SAM range
    flipButton.render((scenarioWidth-2*RIGHT_BAR_PIXELS+10)*scale,(scenarioHeight+20+flipButton.getHeight())*scale,renderer,scale,false,false,2,showSAMRange?1:0);
    samRangeHexOutline.render((scenarioWidth-2*RIGHT_BAR_PIXELS+flipButton.getWidth()*0.5+10)*scale,(scenarioHeight+20+flipButton.getHeight())*scale,renderer,scale);
    //button for SSM range
    flipButton.render((scenarioWidth-2*RIGHT_BAR_PIXELS+10)*scale,(scenarioHeight+30+flipButton.getHeight()*2)*scale,renderer,scale,false,false,2,showSSMRange?1:0);
    ssmRangeHexOutline.render((scenarioWidth-2*RIGHT_BAR_PIXELS+flipButton.getWidth()*0.5+10)*scale,(scenarioHeight+30+2*flipButton.getHeight())*scale,renderer,scale);


    //The flashing buttons are drawn atop each other, on the 2nd tile from the right
    movementPhaseMarker.render((scenarioWidth-RIGHT_BAR_PIXELS)*scale,scenarioHeight*scale,renderer,scale,false,false,3,
        (thePhase == MOVEMENT_PLANNING_FRIEND ) ?  (millis%1000<500 ? 1 : 0) : (
        (thePhase == MOVEMENT_EXECUTION) ?  (millis%1000<500 ? 2 : 1) : 0
            )
        );
    attackPhaseMarker.render((scenarioWidth-RIGHT_BAR_PIXELS)*scale,(scenarioHeight+movementPhaseMarker.getHeight())*scale,renderer,scale,false,false,3,
        thePhase == ATTACK_PLANNING ?  (millis%1000<500 ? 1 : 0) :  (thePhase == ATTACK_EXECUTION ?  (millis%1000<500 ? 2 : 1) : 0)
        );

    //The execute button is in the bottom right tile
    executeMarker.render((scenarioWidth+RIGHT_BAR_PIXELS/2)*scale,(scenarioHeight+BOTTOM_BAR_PIXELS/2)*scale,renderer,scale,true,false,2,thePhase==MOVEMENT_EXECUTION? 1 : 0);

    //The info screen is four tiles wide and just to the left of the phase markers

    infoScreen.render((scenarioWidth-RIGHT_BAR_PIXELS*6)*scale,(scenarioHeight-infoScreenExpansion)*scale,renderer,scale);

    double infoScreenLineX0 = (scenarioWidth-RIGHT_BAR_PIXELS*6+24)*scale;
    double infoScreenLineY0 = (scenarioHeight-infoScreenExpansion+24)*scale;
    //Render the text on the info-screen
    for (const auto& line : infoScreenLines) {
        line.first.render(infoScreenLineX0+line.second.first*scale,infoScreenLineY0+line.second.second*scale,renderer,scale);
    }
}

void gui::renderAttackExecution(int scenarioWidth, int scenarioHeight, SDL_Renderer *renderer, double scale, double playbackTime, double maxPlaybackTime) const {

    //Yes, creating a temporary texture class with a string every frame is bad practice
    //But this thing ACTUALLY changes every single frame so we NEED a new texture every frame
    texwrap currentTimeCounter (std::format("{:.3f}", playbackTime),renderer,infoScreenFont);

    currentTimeCounter.render((scenarioWidth+RIGHT_BAR_PIXELS/2)*scale,(BOTTOM_BAR_PIXELS/2)*scale,renderer,scale);
}


void gui::setInfoScreenText(std::string text, SDL_Renderer* renderer) {
    infoScreenLines.clear();

    //Split the text by lines
    std::stringstream textStream(text);
    std::string line;
    double y=0;
    while (std::getline(textStream, line)) {

        //Also split the text by & character
        std::stringstream lineStream(line);
        std::string lineSegment;
        std::getline(lineStream, lineSegment,'&');
        infoScreenLines.emplace_back(texwrap(lineSegment,renderer,infoScreenFont),std::make_pair(0,y));

        if (std::getline(lineStream, lineSegment,'&')) {
            infoScreenLines.emplace_back(texwrap(lineSegment,renderer,infoScreenFont),std::make_pair(0,y));
            infoScreenLines.back().second.first=infoScreen.getWidth()-48-infoScreenLines.back().first.getWidth();
        }

        y+=infoScreenLines.back().first.getHeight();
    }

}
