//
// Created by andre on 14/12/2023.
//

#include "GameOver.h"
#include "../../GameSpecific/MyGame.h"

GameOverScreen::GameOverScreen(class MyGame *game):
        Menu(game, "") {

    mGame->GetPlayer()->Disable();
}

void GameOverScreen::OnProcessInput(const Uint8 *state) {
    if(state[SDL_SCANCODE_RETURN])
        mGame->Quit();
}