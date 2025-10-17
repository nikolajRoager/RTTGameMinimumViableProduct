//
// Created by Nikolaj Christensen on 16/10/2025.
//

#ifndef PREMVPMAPGAME_SOUNDWRAP_H
#define PREMVPMAPGAME_SOUNDWRAP_H
#include <filesystem>
#include <SDL2/SDL_mixer.h>

namespace fs = std::filesystem;

class soundwrap {
private:
    Mix_Chunk* chunk;

public:
    explicit soundwrap(const fs::path& path) {
        chunk = Mix_LoadWAV(path.string().c_str());
        if (chunk == nullptr) {
            throw std::runtime_error("Unable to load sound: " + std::string(Mix_GetError()));
        }
    }

    ~soundwrap() {
        if (chunk!= nullptr)
            Mix_FreeChunk(chunk);
    }

    void play() const {
        Mix_PlayChannel(-1, chunk, 0);
    }

};

#endif //PREMVPMAPGAME_SOUNDWRAP_H