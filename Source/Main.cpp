// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#include <iostream>
#include "GameSpecific/MyGame.h"

// Screen dimension constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main(int argc, char** argv) {
    MyGame game = MyGame(SCREEN_WIDTH, SCREEN_HEIGHT);
    bool success = game.Initialize();
    if (success) game.RunLoop();
    game.Shutdown();
    return 0;
}
