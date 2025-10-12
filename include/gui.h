//
// Created by Nikolaj Christensen on 26/09/2025.
//

#ifndef PREMVPMAPGAME_GUI_H
#define PREMVPMAPGAME_GUI_H
#include <filesystem>
#include <map>
#include <vector>
#include <SDL2/SDL_render.h>

#include "attackPlan.h"
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

    texwrap flipButton;

    texwrap mapModeHexOutline;
    texwrap mapModeSamRange;
    texwrap mapModeSsmRange;

    texwrap sidebarLaunch;
    texwrap sidebarNode;
    texwrap sidebarTarget;
    texwrap sidebarTrash;

    texwrap playBar;
    texwrap playButton;
    texwrap pauseButton;
    texwrap replayButton;

    texwrap sidebarSelection;

    TTF_Font *infoScreenFont;

    std::vector<std::pair<texwrap,std::pair<int,int> > > infoScreenLines;


    bool pressExecuteButton = false;
    bool expandInfoScreen = false;

    double infoScreenExpansion=0;
    double infoScreenMaxExpansion;

    bool showHexOutline=false;
    bool showSAMRange = false;
    bool showSSMRange = false;

public:
    [[nodiscard]] bool doShowSAMRange () const {return showSAMRange;}
    [[nodiscard]] bool doShowSSMRange () const {return showSSMRange;}
    [[nodiscard]] bool doShowHexOutline () const {return showHexOutline;}


    gui(const fs::path& guiFolder, SDL_Renderer* renderer, TTF_Font* font);

    static int getRightBarPixels() {return RIGHT_BAR_PIXELS;}
    static int getBottomBarPixels() {return BOTTOM_BAR_PIXELS;}

    void update(int mouseX, int mouseY, bool mouseClicked, int scenarioWidth, int scenarioHeight, double scale, uint32_t dmillis);
    void render(int scenarioWidth, int scenarioHeight, SDL_Renderer* renderer, double scale, uint32_t millis, phase thePhase, bool overrideShowExecute) const;

    ///Render the GUI specifically for the playback of the attack animation
    void renderAttackExecution(int scenarioWidth, int scenarioHeight, int mouseX, int mouseY, SDL_Renderer* renderer, double scale, double playbackTime, double maxPlaybackTime, bool isPaused) const;

    ///Render the GUI specifically for the planning of the attacks (the sidebar
    void renderAttackPlanning(int scenarioWidth, int scenarioHeight, int mouseX, int mouseY, SDL_Renderer* renderer, double scale, const std::map<int,std::vector<attackPlan> >& attackPlans, int selectedUnit, int selectedPlan) const;

    [[nodiscard]] int getSelectedAttackPlan(int scenarioWidth, int scenarioHeight, int mouseX, int mouseY, double scale, const std::map<int,std::vector<attackPlan> >& attackPlans, int selectedUnit, int selectedPlan) const;

    [[nodiscard]] bool isExecuteButtonPressed() const {return pressExecuteButton;}

    ///Set screen on the infoscreen, use newline character to force line-breaks
    void setInfoScreenText(std::string text, SDL_Renderer* renderer);
};

#endif //PREMVPMAPGAME_GUI_H