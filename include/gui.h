//
// Created by Nikolaj Christensen on 26/09/2025.
//

#ifndef PREMVPMAPGAME_GUI_H
#define PREMVPMAPGAME_GUI_H
#include <filesystem>
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

    bool pressExecuteButton = false;
    bool expandInfoScreen = false;

    double infoScreenExpansion=0;
    double infoScreenMaxExpansion;

public:
    gui(const fs::path& guiFolder, SDL_Renderer* renderer);

    static int getRightBarPixels() {return RIGHT_BAR_PIXELS;}
    static int getBottomBarPixels() {return BOTTOM_BAR_PIXELS;}

    void update( int mouseX, int mouseY, bool mouseClicked, int scenarioWidth, int scenarioHeight, double scale);
    void render(int scenarioWidth, int scenarioHeight, SDL_Renderer* renderer, double scale, uint32_t millis, phase thePhase) const;

    bool isExecuteButtonPressed() const {return pressExecuteButton;}
};

#endif //PREMVPMAPGAME_GUI_H