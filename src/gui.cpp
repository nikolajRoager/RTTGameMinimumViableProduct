//
// Created by Nikolaj Christensen on 26/09/2025.
//


#include "gui.h"

#include <iostream>
#include <SDL2/SDL_render.h>

gui::gui(const fs::path& guiFolder, SDL_Renderer *renderer): backgroundTile((guiFolder/"guiTile.png").string(),renderer),movementPhaseMarker((guiFolder/"movementPhase.png").string(),renderer),attackPhaseMarker((guiFolder/"attackPhase.png").string(),renderer),executeMarker((guiFolder/"execute.png").string(),renderer),infoScreen((guiFolder/"infoScreen.png").string(),renderer) {
    std::cout<<"Loaded gui"<<std::endl;
    infoScreenMaxExpansion=infoScreen.getHeight();
}


void gui::update( int mouseX, int mouseY, bool mouseClicked, int scenarioWidth, int scenarioHeight, double scale) {

    double executeButtonX = (scenarioWidth+RIGHT_BAR_PIXELS/2)*scale;
    double executeButtonY = (scenarioHeight+BOTTOM_BAR_PIXELS/2)*scale;


    pressExecuteButton = (mouseClicked && mouseX>executeButtonX-executeMarker.getWidth()*scale*0.25 && mouseY>executeButtonY-executeMarker.getHeight()*scale*0.5 && mouseX<executeButtonX+executeMarker.getWidth()*scale*0.25 && mouseY<executeButtonY+executeMarker.getHeight()*scale*0.5);

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

    //The flashing buttons are drawn atop each other, on the 2nd tile from the right
    movementPhaseMarker.render((scenarioWidth-RIGHT_BAR_PIXELS)*scale,scenarioHeight*scale,renderer,scale,false,false,3,
        (thePhase == MOVEMENT_PLANNING_FRIEND ) ?  (millis%1000<500 ? 1 : 0) : (
        (thePhase == MOVEMENT_EXECUTION) ?  (millis%1000<500 ? 2 : 1) : 0
            )
        );
    attackPhaseMarker.render((scenarioWidth-RIGHT_BAR_PIXELS)*scale,(scenarioHeight+movementPhaseMarker.getHeight())*scale,renderer,scale,false,false,3,0);

    //The execute button is in the bottom right tile
    executeMarker.render((scenarioWidth+RIGHT_BAR_PIXELS/2)*scale,(scenarioHeight+BOTTOM_BAR_PIXELS/2)*scale,renderer,scale,true,false,2,thePhase==MOVEMENT_EXECUTION? 1 : 0);

    //The info screen is four tiles wide and just to the left of the phase markers

    infoScreen.render((scenarioWidth-RIGHT_BAR_PIXELS*5)*scale,(scenarioHeight-infoScreenExpansion)*scale,renderer,scale);

}
