#include "SoundPlayer.h"
#include "Exception.h"

void ::Sound::playWAV(const std::string &filename) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        throw Exception("Couldn't initialize SDL");
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        throw Exception("Couldn't initialize SDL Mixer");
    Mix_Chunk *wave = Mix_LoadWAV(filename.c_str());
    if (!wave)
        throw Exception("Couldn't load file: " + filename);
    if (Mix_PlayChannel(-1, wave, 0) == -1)
        throw Exception("Couldn't play wav file: " + filename);
    while (Mix_Playing(-1));
    SDL_Delay(300);
    Mix_FreeChunk(wave);
    Mix_CloseAudio();
}
