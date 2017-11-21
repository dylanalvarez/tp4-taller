#include <iostream>
#include "../common/Sound.h"

// Move these .wav files beside executable
int main(int argc, char **argv) {
    Sound sound1("smw_1-up.wav");
    Sound sound2("smw_coin.wav");
    Sound sound3("smw_feather_get.wav");
    Sound sound4("smw_jump.wav");
    Sound sound5("smw_keyhole_exit.wav");
    Sound sound6("smw_power-up.wav");
    Sound sound7("smw_save_menu.wav");
    sound1.start();
    sound1.join();
    sound2.start();
    sound2.join();
    sound3.start();
    sound3.join();
    sound4.start();
    sound4.join();
    sound5.start();
    sound5.join();
    sound6.start();
    sound6.join();
    sound7.start();
    sound7.join();
}
