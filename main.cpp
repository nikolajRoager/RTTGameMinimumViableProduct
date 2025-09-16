#include <iostream>
#include <SDL2/SDL.h>

#include "engine.h"

//The main file just starts the engine running
int main() {
    std::cout << "Hello, World! lets play a game" << std::endl;

    try {
        engine game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cout<<"The game crashed due to an unhandled exception "<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}