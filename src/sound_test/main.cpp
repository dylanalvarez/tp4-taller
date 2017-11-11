#include "../common/SoundPlayer.h"

// Move these .wav files beside executable
int main(int argc, char **argv) {
    Sound::playWAV("smw_save_menu.wav");
    Sound::playWAV("smw_feather_get.wav");
    Sound::playWAV("smw_coin.wav");
    Sound::playWAV("smw_1-up.wav");
    Sound::playWAV("smw_jump.wav");
    Sound::playWAV("smw_keyhole_exit.wav");
    Sound::playWAV("smw_power-up.wav");
}
