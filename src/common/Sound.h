#ifndef TOWERDEFENSE_SOUND_H
#define TOWERDEFENSE_SOUND_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/*
 * SDL and SDL Mixer need to be installed:
 *   sudo apt-get libsdl2-dev
 *   sudo apt-get libsdl2-mixer-dev
 *
 * And this flags are needed for linking:
 *   -lSDL2 -lSDL2_mixer
 */
namespace Sound {
    void playWAV(const std::string &filename);
}

#endif //TOWERDEFENSE_SOUND_H
