//
// Created by Nikolaj Christensen on 26/09/2025.
//

#ifndef PREMVPMAPGAME_GUI_H
#define PREMVPMAPGAME_GUI_H
#include <filesystem>
#include <vector>
#include <SDL2/SDL_render.h>

#include "phase.h"
#include "texwrap.h"

namespace fs = std::filesystem;

#define RIGHT_BAR_PIXELS 200
#define BOTTOM_BAR_PIXELS 150

class gui {
private:
    texwrap backgroundTile;
    texwrap movementPhaseMarker;
    texwrap attackPhaseMarker;

    texwrap executeMarker;

    texwrap infoScreen;

    TTF_Font *infoScreenFont;

    std::vector<std::pair<texwrap,std::pair<int,int> > > infoScreenLines;


    bool pressExecuteButton = false;
    bool expandInfoScreen = false;

    double infoScreenExpansion=0;
    double infoScreenMaxExpansion;

public:
    gui(const fs::path& guiFolder, SDL_Renderer* renderer, TTF_Font* font);

    static int getRightBarPixels() {return RIGHT_BAR_PIXELS;}
    static int getBottomBarPixels() {return BOTTOM_BAR_PIXELS;}

    void update( int mouseX, int mouseY, bool mouseClicked, int scenarioWidth, int scenarioHeight, double scale, uint32_t dmillis);
    void render(int scenarioWidth, int scenarioHeight, SDL_Renderer* renderer, double scale, uint32_t millis, phase thePhase) const;


    [[nodiscard]] bool isExecuteButtonPressed() const {return pressExecuteButton;}

    ///Set screen on the infoscreen, use newline character to force line-breaks, write hline to get a horizontal line
    void setInfoScreenText(std::string text, SDL_Renderer* renderer);
};

#endif //PREMVPMAPGAME_GUI_H